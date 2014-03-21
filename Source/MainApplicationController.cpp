/*
  TouchKeys: multi-touch musical keyboard control software
  Copyright (c) 2013 Andrew McPherson

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
  =====================================================================
 
  MainApplicationController.cpp: contains the overall glue that holds
  together the various parts of the TouchKeys code. It works together
  with the user interface to let the user configure the hardware and 
  manage the mappings, but it is kept separate from any particular user 
  interface configuration.
*/

#include "MainApplicationController.h"
#ifndef TOUCHKEYS_NO_GUI
#include "Display/KeyboardTesterDisplay.h"
#endif
#include <cstdlib>
#include <sstream>

// Strings for pitch classes (two forms for sharps), for static methods
const char* kNoteNames[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
const char* kNoteNamesAlternate[12] = {"C", "Db", "D ", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};

MainApplicationController::MainApplicationController()
: midiInputController_(keyboardController_),
  oscReceiver_(0, "/touchkeys"),
  touchkeyController_(keyboardController_),
  touchkeyEmulator_(keyboardController_, oscReceiver_),
#ifdef TOUCHKEY_ENTROPY_GENERATOR_ENABLE
  touchkeyEntropyGenerator_(keyboardController_),
  entropyGeneratorSelected_(false),
#endif
  touchkeyErrorOccurred_(false),
  touchkeyErrorMessage_(""),
  touchkeyAutodetecting_(false),
  touchkeyStandaloneModeEnabled_(false),
  deviceUpdateCounter_(0),
  oscReceiveEnabled_(false),
  oscReceivePort_(kDefaultOscReceivePort),
  experimentalMappingsEnabled_(false),
#ifndef TOUCHKEYS_NO_GUI
  keyboardDisplayWindow_(0),
  keyboardTesterDisplay_(0),
  keyboardTesterWindow_(0),
#endif
  segmentCounter_(0),
  loggingActive_(false)
{
    // Set our OSC controller
    setOscController(&keyboardController_);
    oscTransmitter_.setEnabled(false);
    //oscTransmitter_.setDebugMessages(true);
    
    // Initialize the links between objects
    keyboardController_.setOscTransmitter(&oscTransmitter_);
    keyboardController_.setMidiOutputController(&midiOutputController_);
    keyboardController_.setGUI(&keyboardDisplay_);
	midiInputController_.setMidiOutputController(&midiOutputController_);
    
    // Set up an initial OSC transmit host/port
    oscTransmitter_.addAddress(kDefaultOscTransmitHost, kDefaultOscTransmitPort);

    // Set up default logging directory
    loggingDirectory_ = (File::getSpecialLocation(File::userHomeDirectory).getFullPathName() + "/Desktop").toUTF8();
    
    // Defaults for display, until we get other information
    keyboardDisplay_.setKeyboardRange(36, 72);
    
    // Add one keyboard segment at the beginning
    midiSegmentAdd();
}

MainApplicationController::~MainApplicationController() {
#ifdef ENABLE_TOUCHKEYS_SENSOR_TEST
    if(touchkeySensorTestIsRunning())
        touchkeySensorTestStop();
#endif
}

bool MainApplicationController::touchkeyDeviceStartupSequence(const char * path) {
#ifdef TOUCHKEY_ENTROPY_GENERATOR_ENABLE
    if(!strcmp(path, "/dev/Entropy Generator") || !strcmp(path, "\\\\.\\Entropy Generator")) {
        entropyGeneratorSelected_ = true;
        touchkeyEntropyGenerator_.start();
    }
    else {
        entropyGeneratorSelected_ = false;
#endif
        
    // Step 1: attempt to open device
    if(!openTouchkeyDevice(path)) {
        touchkeyErrorMessage_ = "Failed to open";
        touchkeyErrorOccurred_ = true;
        return false;
    }
    
    // Step 2: see if a real TouchKeys device is present at the other end
    if(!touchkeyDeviceCheckForPresence()) {
        touchkeyErrorMessage_ = "Device not recognized";
        touchkeyErrorOccurred_ = true;
        return false;
    }
    
    // Step 3: update the display
    keyboardDisplay_.setKeyboardRange(touchkeyController_.lowestKeyPresentMidiNote(), touchkeyController_.highestMidiNote());
#ifndef TOUCHKEYS_NO_GUI
    if(keyboardDisplayWindow_ != 0) {
        keyboardDisplayWindow_->getConstrainer()->setFixedAspectRatio(keyboardDisplay_.keyboardAspectRatio());
        keyboardDisplayWindow_->setBoundsConstrained(keyboardDisplayWindow_->getBounds());
    }
#endif
    
    // Step 4: start data collection from the device
    if(!startTouchkeyDevice()) {
        touchkeyErrorMessage_ = "Failed to start";
        touchkeyErrorOccurred_ = true;
    }

#ifdef TOUCHKEY_ENTROPY_GENERATOR_ENABLE
    }
#endif
    
    // Success!
    touchkeyErrorMessage_ = "";
    touchkeyErrorOccurred_ = false;
    return true;
}

std::string MainApplicationController::touchkeyDevicePrefix() {
#ifdef _MSC_VER
	return "\\\\.\\";
#else
    if(SystemStats::getOperatingSystemType() == SystemStats::Linux) {
        return "/dev/serial/by-id/";
    }
    else {
        return "/dev/";
    }
#endif
}

// Return a list of available TouchKey devices
std::vector<std::string> MainApplicationController::availableTouchkeyDevices() {
    std::vector<std::string> devices;

#ifdef _MSC_VER
    for(int i = 1; i <= 128; i++) {
		String comPortName("COM");
		comPortName += i;

        DWORD dwSize = 0;
        LPCOMMCONFIG lpCC = (LPCOMMCONFIG) new BYTE[1];
        BOOL ret = GetDefaultCommConfig(comPortName.toUTF8(), lpCC, &dwSize);
        delete [] lpCC;
        
		if(ret) 
			devices.push_back(comPortName.toStdString());
		else {
			if(GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
				//Logger::writeToLog(String::formatted("Found " + comPortName));
				lpCC = (LPCOMMCONFIG) new BYTE[dwSize];
				ret = GetDefaultCommConfig(comPortName.toUTF8(), lpCC, &dwSize);
				if(ret)
					devices.push_back(comPortName.toStdString());
				else {
					int error = GetLastError();
					//Logger::writeToLog(String("2Didn't find " + comPortName + "; error " + String(error)));
				}
				delete [] lpCC;
			}
			else {
				int error = GetLastError();
				//Logger::writeToLog(String("Didn't find " + comPortName + "; error " + String(error)));
			}
		}
    }
#else
    if(SystemStats::getOperatingSystemType() == SystemStats::Linux) {
        DirectoryIterator devDirectory(File("/dev/serial/by-id"),false,"*");
        
        while(devDirectory.next()) {
            devices.push_back(string(devDirectory.getFile().getFileName().toUTF8()));
        }
    }
    else {
        DirectoryIterator devDirectory(File("/dev"),false,"cu.usbmodem*");
        
        while(devDirectory.next()) {
            devices.push_back(string(devDirectory.getFile().getFileName().toUTF8()));
        }
    }
#endif
    
#ifdef TOUCHKEY_ENTROPY_GENERATOR_ENABLE
    devices.push_back("Entropy Generator");
#endif
    
    return devices;
}

// Close the currently open TouchKeys device
void MainApplicationController::closeTouchkeyDevice() {
#ifdef TOUCHKEY_ENTROPY_GENERATOR_ENABLE
    if(entropyGeneratorSelected_)
        touchkeyEntropyGenerator_.stop();
    else
        touchkeyController_.closeDevice();
#else
    touchkeyController_.closeDevice();
#endif
}

// Check whether a TouchKey device is present. Returns true if device found.
bool MainApplicationController::touchkeyDeviceCheckForPresence(int waitMilliseconds, int tries) {
    
    int count = 0;
    while(1) {
        if(touchkeyController_.checkIfDevicePresent(waitMilliseconds))
            break;
        if(++count >= tries) {
            return false;
        }
    }
    
    return true;
}

// Return true if device is collecting data
bool MainApplicationController::touchkeyDeviceIsRunning() {
#ifdef TOUCHKEY_ENTROPY_GENERATOR_ENABLE
    if(entropyGeneratorSelected_)
        return touchkeyEntropyGenerator_.isRunning();
    else
        return touchkeyController_.isAutoGathering();
#else
    return touchkeyController_.isAutoGathering();
#endif
}

// Start an autodetection routine to match touch data to MIDI
void MainApplicationController::touchkeyDeviceAutodetectLowestMidiNote() {
    if(touchkeyAutodetecting_)
        return;
    
    touchkeyAutodetecting_ = true;
    addOscListener("/midi/noteon");
}

// Abort an autodetection routine
void MainApplicationController::touchkeyDeviceStopAutodetecting() {
    if(!touchkeyAutodetecting_)
        return;
    
    removeOscListener("/midi/noteon");
    touchkeyAutodetecting_ = false;
}

bool MainApplicationController::touchkeyDeviceIsAutodetecting() {
    return touchkeyAutodetecting_;
}

// Start logging TouchKeys/MIDI data to a file. Filename is autogenerated
// based on current time.
void MainApplicationController::startLogging() {
    if(loggingActive_)
        stopLogging();
    
    std::stringstream out;
    out << time(NULL);
    std::string fileId = out.str();
    

    string midiLogFileName = "midiLog_" + fileId + ".bin";
    string keyTouchLogFileName = "keyTouchLog_" + fileId + ".bin";
    string analogLogFileName = "keyAngleLog_" + fileId + ".bin";
    
    // Create log files with these names
    midiInputController_.createLogFile(midiLogFileName, loggingDirectory_);
    touchkeyController_.createLogFiles(keyTouchLogFileName, analogLogFileName, loggingDirectory_);
    
    // Enable logging from each controller
    midiInputController_.startLogging();
    touchkeyController_.startLogging();
    
    loggingActive_ = true;
}

// Stop a currently running log.
void MainApplicationController::stopLogging() {
    if(!loggingActive_)
        return;
    
    // stop logging data
    midiInputController_.stopLogging();
    touchkeyController_.stopLogging();
    
    // close the log files
    midiInputController_.closeLogFile();
    touchkeyController_.closeLogFile();
    
    loggingActive_ = false;
}

void MainApplicationController::setLoggingDirectory(const char *directory) {
    loggingDirectory_ = directory;
}

// Add a new MIDI keyboard segment. This method also handles numbering of the segments
MidiKeyboardSegment* MainApplicationController::midiSegmentAdd() {
    // For now, the segment counter increments with each new segment. Eventually, we could
    // consider renumbering every time a segment is removed so that we always have an index
    // 0-N which corresponds to the indexes within MidiInputController (and also the layout
    // of the tabs).
    MidiKeyboardSegment *newSegment = midiInputController_.addSegment(segmentCounter_++, 12, 127);
    
    // Set up defaults
    newSegment->setModePassThrough();
    newSegment->setPolyphony(8);
    newSegment->setVoiceStealingEnabled(false);
    newSegment->enableAllChannels();
    newSegment->setOutputTransposition(0);
    newSegment->setUsesKeyboardPitchWheel(true);
    
    // Enable standalone mode on the new segment if generally enabled
    if(touchkeyStandaloneModeEnabled_)
        newSegment->enableTouchkeyStandaloneMode();
    
    return newSegment;
}

// Remove a MIDI keyboard segment.
void MainApplicationController::midiSegmentRemove(MidiKeyboardSegment *segment) {
    if(segment == 0)
        return;
    // Check if this segment uses a virtual output port. Right now, we have a unique
    // output per segment. If it does, then disable the virtual output port.
    int identifier = segment->outputPort();
    if(midiOutputController_.enabledPort(identifier) == MidiOutputController::kMidiVirtualOutputPortNumber)
        midiOutputController_.disablePort(identifier);
    midiInputController_.removeSegment(segment);
}


// Enable TouchKeys standalone mode
void MainApplicationController::midiTouchkeysStandaloneModeEnable() {
    touchkeyStandaloneModeEnabled_ = true;
    // Go through all segments and enable standalone mode
    for(int i = 0; i < midiInputController_.numSegments(); i++) {
        midiInputController_.segment(i)->enableTouchkeyStandaloneMode();
    }
}

void MainApplicationController::midiTouchkeysStandaloneModeDisable() {
    touchkeyStandaloneModeEnabled_ = false;
    // Go through all segments and disable standalone mode
    for(int i = 0; i < midiInputController_.numSegments(); i++) {
        midiInputController_.segment(i)->disableTouchkeyStandaloneMode();
    }
}

// OSC handler method
bool MainApplicationController::oscHandlerMethod(const char *path, const char *types, int numValues, lo_arg **values, void *data) {
	if(!strcmp(path, "/midi/noteon") && touchkeyAutodetecting_ && numValues > 0) {
        // std::cout << "/midi/noteon\n";
        // Found a MIDI note. Look for a unique touch on this pitch class to
        // determine which octave the keyboard is set to
        if(types[0] != 'i')
            return false;   // Ill-formed message
        int midiNote = values[0]->i;
        if(midiNote < 0 || midiNote > 127)
            return false;
        
        // Go through each octave and see if a touch is present
        int midiTestNote = midiNote % 12;
        int count = 0;
        int lastFoundTouchNote = 0;
        while(midiTestNote <= 127) {
            if(keyboardController_.key(midiTestNote) != 0) {
                if(keyboardController_.key(midiTestNote)->touchIsActive()) {
                    count++;
                    lastFoundTouchNote = midiTestNote;
                }
            }
            midiTestNote += 12;
        }
        
        // We return success if exactly one note had a touch on this pitch class
        if(count == 1) {
            int noteDifference = lastFoundTouchNote - midiNote;
            int currentMinNote = touchkeyController_.lowestMidiNote();

            // std::cout << "Found difference of " << noteDifference << std::endl;

            currentMinNote -= noteDifference;
            if(currentMinNote >= 0 && currentMinNote <= 127)
                touchkeyController_.setLowestMidiNote(currentMinNote);
            
            touchkeyDeviceStopAutodetecting();
        }
        return false; // Others may still want to handle this message
    }
    
    return false;
}

// Factores to use
const int kNumMappingFactoryTypes = 7;
const char* kMappingFactoryNames[kNumMappingFactoryTypes] = {"Control", "Vibrato", "Pitch Bend", "Split Key", "Multi-Finger Trigger", "Onset Angle", "Release Angle"};

// Return the number of mapping factory types available
int MainApplicationController::numberOfMappingFactories() {
    return kNumMappingFactoryTypes;
}

// Return the name of the given mapping factory type
String MainApplicationController::mappingFactoryNameForIndex(int index) {
    if(index < 0 || index >= kNumMappingFactoryTypes)
        return String();
    return kMappingFactoryNames[index];
}

// Return a new object of the given mapping factory type
MappingFactory* MainApplicationController::createMappingFactoryForIndex(int index, MidiKeyboardSegment& segment) {
    switch(index) {
        case 0:
            return new TouchkeyControlMappingFactory(keyboardController_, segment);
        case 1:
            return new TouchkeyVibratoMappingFactory(keyboardController_, segment);
        case 2:
            return new TouchkeyPitchBendMappingFactory(keyboardController_, segment);
        case 3:
            return new TouchkeyKeyDivisionMappingFactory(keyboardController_, segment);
        case 4:
            return new TouchkeyMultiFingerTriggerMappingFactory(keyboardController_, segment);
        case 5:
            return new TouchkeyOnsetAngleMappingFactory(keyboardController_, segment);
        case 6:
            return new TouchkeyReleaseAngleMappingFactory(keyboardController_, segment);
        default:
            return 0;
    }
}

// Return whethera  given mapping is experimental or not
bool MainApplicationController::mappingIsExperimental(int index) {
    if(index > 2)
        return true;
    return false;
}

// Save the current settings to an XML file
// Returns true on success
bool MainApplicationController::savePresetToFile(const char *filename) {
    File outputFile(filename);
    
    return savePresetHelper(outputFile);
}

// Load settings from a saved XML file
// Returns true on success
bool MainApplicationController::loadPresetFromFile(const char *filename) {
    File inputFile(filename);

    return loadPresetHelper(inputFile);
}

#ifndef TOUCHKEYS_NO_GUI
// Present the user with a Save dialog and then save the preset
bool MainApplicationController::savePresetWithDialog() {
    FileChooser myChooser ("Save preset...",
                           File::nonexistent, // File::getSpecialLocation (File::userHomeDirectory),
                           "*.tkpreset");
    if(myChooser.browseForFileToSave(true)) {
        File outputFile(myChooser.getResult());
        return savePresetHelper(outputFile);
    }
    // User clicked cancel...
    return true;
}


// Present the user with a Load dialog and then save the preset
bool MainApplicationController::loadPresetWithDialog() {
    FileChooser myChooser ("Select a preset...",
                           File::nonexistent, // File::getSpecialLocation (File::userHomeDirectory),
                           "*.tkpreset");
    if(myChooser.browseForFileToOpen()) {
        return loadPresetHelper(myChooser.getResult());
    }
    // User clicked cancel...
    return true;
}
#endif

bool MainApplicationController::loadPresetHelper(File const& inputFile) {
    if(!inputFile.existsAsFile())
        return false;
    
    // Load the XML element from the file and check that it is valid
    XmlDocument document(inputFile);
    ScopedPointer<XmlElement> mainElement = document.getDocumentElement();
    
    if(mainElement == 0)
        return false;
    if(mainElement->getTagName() != "TouchKeysPreset")
        return false;
    XmlElement *segmentsElement = mainElement->getChildByName("KeyboardSegments");
    if(segmentsElement == 0)
        return false;
        
    // Load the preset from this element
    bool result = midiInputController_.loadSegmentPreset(segmentsElement);
    
    // Loading a preset won't set standalone mode; so re-enable it when finished
    // if needed
    if(touchkeyStandaloneModeEnabled_) {
        midiTouchkeysStandaloneModeEnable();
    }
    
    return result;
}

bool MainApplicationController::savePresetHelper(File& outputFile) {
    XmlElement mainElement("TouchKeysPreset");
    mainElement.setAttribute("format", "0.1");
    
    XmlElement* segmentsElement = midiInputController_.getSegmentPreset();
    mainElement.addChildElement(segmentsElement);
    
    return mainElement.writeToFile(outputFile, "");
}

// Clear the current preset and restore default settings
void MainApplicationController::clearPreset() {
    midiInputController_.removeAllSegments();
    //midiOutputController_.disableAllPorts();
    segmentCounter_ = 0;
    
    // Re-add a new segment, starting at 0
    midiSegmentAdd();
}

#ifdef ENABLE_TOUCHKEYS_SENSOR_TEST
// Start testing the TouchKeys sensors. Returns true on success.
bool MainApplicationController::touchkeySensorTestStart(const char *path, int firstKey) {
#ifndef TOUCHKEYS_NO_GUI
    if(path == 0 || firstKey < touchkeyController_.lowestMidiNote())
        return false;
    if(keyboardTesterDisplay_ != 0)
        return true;
    
    // First, close the existing device which stops the data autogathering
    closeTouchkeyDevice();
    
    // Now reopen the TouchKeys device
    if(!touchkeyController_.openDevice(path)) {
        touchkeyErrorMessage_ = "Failed to open";
        touchkeyErrorOccurred_ = true;
        return false;
    }
    
    // Next, see if a real TouchKeys device is present at the other end
    if(!touchkeyDeviceCheckForPresence()) {
        touchkeyErrorMessage_ = "Device not recognized";
        touchkeyErrorOccurred_ = true;
        return false;
    }
    
    // Now, create the KeyboardTesterDisplay object which will handle processing
    // raw data and displaying the results. Also a new window to hold it.
    keyboardTesterDisplay_ = new KeyboardTesterDisplay(*this, keyboardController_);
    keyboardTesterDisplay_->setKeyboardRange(touchkeyController_.lowestKeyPresentMidiNote(), touchkeyController_.highestMidiNote());
    keyboardTesterWindow_ = new GraphicsDisplayWindow("TouchKeys Sensor Test", *keyboardTesterDisplay_);
    
    // Start raw data gathering from the indicated key (converted to octave/key notation)
    int keyOffset = firstKey - touchkeyController_.lowestMidiNote();
    if(keyOffset < 0) // Shouldn't happen...
        keyOffset = 0;
    
    if(!touchkeyController_.startRawDataCollection(keyOffset / 12, keyOffset % 12, 3, 2)) { // FIXME: check these values
        touchkeyErrorMessage_ = "Failed to start";
        touchkeyErrorOccurred_ = true;
        return false;
    }
    
    touchkeyErrorMessage_ = "";
    touchkeyErrorOccurred_ = false;
    return true;
#endif
}

// Stop testing the TouchKeys sensors
void MainApplicationController::touchkeySensorTestStop() {
#ifndef TOUCHKEYS_NO_GUI
    if(keyboardTesterDisplay_ == 0)
        return;
    
    // Stop raw data gathering first and close device
    touchkeyController_.stopAutoGathering();
    touchkeyController_.closeDevice();
    
    // Delete the testing objects
    delete keyboardTesterWindow_;
    delete keyboardTesterDisplay_;
    
    keyboardTesterWindow_ = 0;
    keyboardTesterDisplay_ = 0;
    
    touchkeyErrorMessage_ = "";
    touchkeyErrorOccurred_ = false;
#endif
}

// Is the sensor test running?
bool MainApplicationController::touchkeySensorTestIsRunning() {
#ifdef TOUCHKEYS_NO_GUI   
    return false;
#else
    return (keyboardTesterDisplay_ != 0);
#endif
}

// Set the current key that is begin tested
void MainApplicationController::touchkeySensorTestSetKey(int key) {
#ifndef TOUCHKEYS_NO_GUI
    if(keyboardTesterDisplay_ == 0 || key < touchkeyController_.lowestMidiNote())
        return;

    int keyOffset = key - touchkeyController_.lowestMidiNote();
    if(keyOffset < 0) // Shouldn't happen...
        keyOffset = 0;
    
    touchkeyController_.rawDataChangeKeyAndMode(keyOffset / 12, keyOffset % 12, 3, 2);
#endif
}

// Reset the testing state to all sensors off
void MainApplicationController::touchkeySensorTestResetState() {
#ifndef TOUCHKEYS_NO_GUI
    if(keyboardTesterDisplay_ == 0)
        return;
    for(int key = 0; key < 128; key++)
        keyboardTesterDisplay_->resetSensorState(key);
#endif
}

#endif // ENABLE_TOUCHKEYS_SENSOR_TEST

// Return the name of a MIDI note given its number
std::string MainApplicationController::midiNoteName(int noteNumber) {
    if(noteNumber < 0 || noteNumber > 127)
        return "";
    char name[6];
#ifdef _MSC_VER
	_snprintf_s(name, 6, _TRUNCATE, "%s%d", kNoteNames[noteNumber % 12], (noteNumber / 12) - 1);
#else
    snprintf(name, 6, "%s%d", kNoteNames[noteNumber % 12], (noteNumber / 12) - 1);
#endif

    return name;
}

// Get the number of a MIDI note given its name
int MainApplicationController::midiNoteNumberForName(std::string const& name) {
    // Any valid note name will have at least two characters
    if(name.length() < 2)
        return -1;
    
    // Find the pitch class first, then the octave
    int pitchClass = -1;
    int startIndex = 1;
    if(!name.compare(0, 2, "C#") ||
       !name.compare(0, 2, "c#") ||
       !name.compare(0, 2, "Db") ||
       !name.compare(0, 2, "db")) {
        pitchClass = 1;
        startIndex = 2;
    }
    else if(!name.compare(0, 2, "D#") ||
            !name.compare(0, 2, "d#") ||
            !name.compare(0, 2, "Eb") ||
            !name.compare(0, 2, "eb")) {
        pitchClass = 3;
        startIndex = 2;
    }
    else if(!name.compare(0, 2, "F#") ||
            !name.compare(0, 2, "f#") ||
            !name.compare(0, 2, "Gb") ||
            !name.compare(0, 2, "gb")){
        pitchClass = 6;
        startIndex = 2;
    }
    else if(!name.compare(0, 2, "G#") ||
            !name.compare(0, 2, "g#") ||
            !name.compare(0, 2, "Ab") ||
            !name.compare(0, 2, "ab")){
        pitchClass = 8;
        startIndex = 2;
    }
    else if(!name.compare(0, 2, "A#") ||
            !name.compare(0, 2, "a#") ||
            !name.compare(0, 2, "Bb") ||
            !name.compare(0, 2, "bb")){
        pitchClass = 10;
        startIndex = 2;
    }
    else if(!name.compare(0, 1, "C") ||
            !name.compare(0, 1, "c"))
        pitchClass = 0;
    else if(!name.compare(0, 1, "D") ||
            !name.compare(0, 1, "d"))
        pitchClass = 2;
    else if(!name.compare(0, 1, "E") ||
            !name.compare(0, 1, "e"))
        pitchClass = 4;
    else if(!name.compare(0, 1, "F") ||
            !name.compare(0, 1, "f"))
        pitchClass = 5;
    else if(!name.compare(0, 1, "G") ||
            !name.compare(0, 1, "g"))
        pitchClass = 7;
    else if(!name.compare(0, 1, "A") ||
            !name.compare(0, 1, "a"))
        pitchClass = 9;
    else if(!name.compare(0, 1, "B") ||
            !name.compare(0, 1, "b"))
        pitchClass = 11;
    
    if(pitchClass < 0) // No valid note found
        return -1;
    
    int octave = atoi(name.substr(startIndex).c_str());
    int noteNumber = (octave + 1) * 12 + pitchClass;
    
    if(noteNumber < 0 || noteNumber > 127)
        return -1;
    return noteNumber;
}