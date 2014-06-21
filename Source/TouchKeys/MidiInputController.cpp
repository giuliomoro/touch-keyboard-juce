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
 
  MidiInputController.cpp: handles incoming MIDI data and manages input
  ports. Detailed processing is broken down by keyboard segment; see
  MidiKeyboardSegment.h/cpp for more.
*/


#include "MidiInputController.h"
#include "MidiOutputController.h"
#include "../Mappings/MappingFactory.h"

#undef DEBUG_MIDI_INPUT_CONTROLLER
#undef MIDI_INPUT_CONTROLLER_DEBUG_RAW

// Constructor

MidiInputController::MidiInputController(PianoKeyboard& keyboard) 
: keyboard_(keyboard), midiOutputController_(0), primaryActivePort_(-1),
  segmentUniqueIdentifier_(0)
{    
    logFileCreated = false;
    loggingActive = false;

}

void MidiInputController::setMidiOutputController(MidiOutputController* ct) {
    midiOutputController_ = ct;
    
    // Propagate the change to the keyboard segments
    ScopedLock sl(segmentsMutex_);
    for(int i = 0; i < segments_.size(); i++) {
        segments_[i]->setMidiOutputController(ct);
    }
}

// ------------------------------------------------------
// create a new MIDI log file, ready to have data written to it
void MidiInputController::createLogFile(string midiLog_filename, string path)
{
    // indicate that we have created a log file (so we can close it later)
    logFileCreated = true;
    
    if (path.compare("") != 0)
    {
        path = path + "/";
    }
    
    midiLog_filename = path + midiLog_filename;
    
    char *fileName = (char*)midiLog_filename.c_str();
    
    // create output file
    midiLog.open (fileName, ios::out | ios::binary);
    midiLog.seekp(0);
}

// ------------------------------------------------------
// close the existing log file
void MidiInputController::closeLogFile()
{
    if (logFileCreated)
    {
        midiLog.close();
        logFileCreated = false;
    }
}

// ------------------------------------------------------
// start logging midi data
void MidiInputController::startLogging()
{
    loggingActive = true;
}

// ------------------------------------------------------
// stop logging midi data
void MidiInputController::stopLogging()
{
    loggingActive = false;
}

// Iterate through the available MIDI devices.  Return a vector containing
// indices and names for each device.  The index will later be passed back
// to indicate which device to open.

vector<pair<int, string> > MidiInputController::availableMidiDevices() {
	vector<pair<int, string> > deviceList;
    
	try {
        StringArray deviceStrings = MidiInput::getDevices();
		
		for(int i = 0; i < deviceStrings.size(); i++) {
			pair<int, string> p(i, string(deviceStrings[i].toUTF8()));
			deviceList.push_back(p);
		}
	}
	catch(...) {
		deviceList.clear();
	}
	
	return deviceList;
}

// Enable a new MIDI port according to its index (returned from availableMidiDevices())
// Returns true on success.

bool MidiInputController::enablePort(int portNumber, bool isPrimary) {
	if(portNumber < 0)
		return false;
    // If this is already the primary port, nothing to do
    if(isPrimary && primaryActivePort_ == portNumber)
        return true;
    
    // If this port is active already but we are not making it primary,
    // then fail: can't override primary with aux
    if(!isPrimary)
        if(activePorts_.count(portNumber) > 0)
            return false;
	
    // If there is already a (different) primary active port, disable it
    if(isPrimary && primaryActivePort_ >= 0 && activePorts_.count(primaryActivePort_) > 0)
        disablePort(primaryActivePort_);
    
    // Enable the port if it hasn't been already
    if(activePorts_.count(portNumber) == 0) {
        MidiInput *device = MidiInput::openDevice(portNumber, this);
            
        if(device == 0) {
#ifdef DEBUG_MIDI_INPUT_CONTROLLER
            cout << "Failed to enable MIDI input port " << portNumber << ")\n";
#endif
            return false;
        }
        
        
#ifdef DEBUG_MIDI_INPUT_CONTROLLER
        cout << "Enabling MIDI input port " << portNumber << " (" << device->getName() << ")\n";
#endif
        device->start();

        // Save the device in the set of ports
        activePorts_[portNumber] = device;
    }
    else {
#ifdef DEBUG_MIDI_INPUT_CONTROLLER
        cout << "MIDI input port " << portNumber << " already enabled\n";
#endif
    }
    
    if(isPrimary)
        primaryActivePort_ = portNumber;
    
	return true;
}

// Enable all current MIDI ports

bool MidiInputController::enableAllPorts(int primaryPortNumber) {
	bool enabledPort = false;
	vector<pair<int, string> > ports = availableMidiDevices();
	vector<pair<int, string> >::iterator it = ports.begin();
	
#ifdef DEBUG_MIDI_INPUT_CONTROLLER
    cout << "Enabling all MIDI input ports\n";
#endif
    
	while(it != ports.end()) {
		// Don't enable MIDI input from our own virtual output
		if(it->second != string(kMidiVirtualOutputName.toUTF8()))
			enabledPort |= enablePort((it++)->first, it->first == primaryPortNumber);
		else
			it++;
	}
	
	return enabledPort;
}

// Remove a specific MIDI input source and free associated memory

void MidiInputController::disablePort(int portNumber) {
	if(activePorts_.count(portNumber) <= 0)
		return;
	
	MidiInput *device = activePorts_[portNumber];

    if(device == 0)
        return;
    
#ifdef DEBUG_MIDI_INPUT_CONTROLLER
	cout << "Disabling MIDI input port " << portNumber << " (" << device->getName() << ")\n";
#endif
    
    device->stop();
    delete device;
    
	activePorts_.erase(portNumber);
    if(primaryActivePort_ == portNumber)
        primaryActivePort_ = -1;
}

// Remove the primary MIDI input source

void MidiInputController::disablePrimaryPort() {
    if(primaryActivePort_ < 0)
        return;
    disablePort(primaryActivePort_);
}

// Remove all MIDI input sources and free associated memory

void MidiInputController::disableAllPorts(bool auxiliaryOnly) {
	map<int, MidiInput*>::iterator it;
	MidiInput* primaryPort = 0;
	
#ifdef DEBUG_MIDI_INPUT_CONTROLLER
    cout << "Disabling all MIDI input ports\n";
#endif
    
	it = activePorts_.begin();
	
	while(it != activePorts_.end()) {
        if(it->second == 0) {
            it++;
            continue;
        }
        
        // Save primary port?
        if(it->first == primaryActivePort_ && auxiliaryOnly)
            primaryPort = it->second;
        else {
            it->second->stop();                     // disable port
            delete it->second;						// free MidiInputCallback
        }
		it++;
	}
	
    // Clear all ports including primary
    activePorts_.clear();
    
    // But did we save the priamry port?
    if(auxiliaryOnly && primaryPort != 0) {
        // Re-insert primary only
        activePorts_[primaryActivePort_] = primaryPort;
    }
    else
        primaryActivePort_ = -1;
}

// Return the primary active port corresponding to the TK keyboard

int MidiInputController::primaryActivePort() {
    return primaryActivePort_;
}

// Return a list of active ports other than the primary

vector<int> MidiInputController::auxiliaryActivePorts() {
    vector<int> ports;
    
	map<int, MidiInput*>::iterator it;
    
    for(it = activePorts_.begin(); it != activePorts_.end(); ++it) {
        if(it->first == primaryActivePort_)
            continue;
        ports.push_back(it->first);
    }
    
    return ports;
}

// Get the name of a particular MIDI input port
String MidiInputController::deviceName(int portNumber) {
    StringArray const& deviceStrings = MidiInput::getDevices();
    if(portNumber < 0 || portNumber >= deviceStrings.size())
        return "";
    return deviceStrings[portNumber];
}

// Find the index of a device with a given name; return -1 if not found
int MidiInputController::indexOfDeviceNamed(String const& name) {
    StringArray const& deviceStrings = MidiInput::getDevices();
    
    for(int i = 0; i < deviceStrings.size(); i++) {
        if(name == deviceStrings[i])
            return i;
    }
    
    return -1;
}

// Add a new keyboard segment. Returns a pointer to the newly created segment
MidiKeyboardSegment* MidiInputController::addSegment(int outputPortNumber,
                                                          int noteMin, int noteMax,
                                                          int channelMask) {
    ScopedLock sl(segmentsMutex_);
    
    // Create a new segment and populate its values
    MidiKeyboardSegment *segment = new MidiKeyboardSegment(keyboard_);
    
    segment->setMidiOutputController(midiOutputController_);
    segment->setOutputPort(outputPortNumber);
    segment->setNoteRange(noteMin, noteMax);
    segment->setChannelMask(channelMask);
    
    // Add the segment to the vector and return the pointer
    segments_.push_back(segment);
    segmentUniqueIdentifier_++;
    return segment;
}

// Remove a segment by index or by object
void MidiInputController::removeSegment(int index) {
    ScopedLock sl(segmentsMutex_);
    
    if(index < 0 || index >= segments_.size())
        return;
    
    MidiKeyboardSegment* segment = segments_[index];
    delete segment;
    segments_.erase(segments_.begin() + index);
    segmentUniqueIdentifier_++;
}

void MidiInputController::removeSegment(MidiKeyboardSegment* segment) {
    ScopedLock sl(segmentsMutex_);
    
    for(int i = 0; i < segments_.size(); i++) {
        if(segments_[i] == segment) {
            delete segment;
            segments_.erase(segments_.begin() + i);
            break;
        }
    }
    segmentUniqueIdentifier_++;
}

void MidiInputController::removeAllSegments() {
    ScopedLock sl(segmentsMutex_);

    for(int i = 0; i < segments_.size(); i++)
        delete segments_[i];
    segments_.clear();
    segmentUniqueIdentifier_++;
}

// Disable any currently active notes

void MidiInputController::allNotesOff() {
    ScopedLock sl(segmentsMutex_);
    
    for(int i = 0; i < segments_.size(); i++)
        segments_[i]->allNotesOff();
}

// Return the current preset as an XmlElement, suitable for
// saving to file. This element will need to be deleted when finished

XmlElement* MidiInputController::getSegmentPreset() {
    ScopedLock sl(segmentsMutex_);
    XmlElement* controllerElement = new XmlElement("KeyboardSegments");
    
    // Add settings for each zone to the element
    for(int i = 0; i < segments_.size(); i++) {
        XmlElement* segmentElement = segments_[i]->getPreset();
        controllerElement->addChildElement(segmentElement);
    }
    
    // Return the element
    return controllerElement;
}

// Load keyboard segments from a preset; returns true on success

bool MidiInputController::loadSegmentPreset(XmlElement const* preset) {
    ScopedLock sl(segmentsMutex_);

    for(int i = 0; i < segments_.size(); i++)
        delete segments_[i];
    segments_.clear();
    
    XmlElement *element = preset->getChildByName("Segment");
    while(element != 0) {
        // Create a new segment and populate its values
        MidiKeyboardSegment *segment = new MidiKeyboardSegment(keyboard_);
        segment->setMidiOutputController(midiOutputController_);
        
        // Load settings for this particular segment
        if(!segment->loadPreset(element)) {
            delete segment;
            for(int i = 0; i < segments_.size(); i++)
                delete segments_[i];
            segments_.clear();
            return false;
        }
    
        segments_.push_back(segment);
        element = element->getNextElementWithTagName("Segment");
    }
    
    segmentUniqueIdentifier_++;
    return true;
}

// This gets called every time MIDI data becomes available on any input controller. source tells
// us where the message came from, and may be 0 if being called internally.

void MidiInputController::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
//void MidiInputController::rtMidiCallback(double deltaTime, vector<unsigned char> *message, int inputNumber)
{
	// Juce will give us one MIDI command per callback, which makes processing easier for us.

    // Ignore sysex messages for now
    if(message.isSysEx())
        return;
    
    // Pull out the raw bytes
    int dataSize = message.getRawDataSize();
    if(dataSize <= 0)
        return;
    const unsigned char *messageData = message.getRawData();
	
    // if logging is active
    if (loggingActive)
    {
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
        //////////////////// BEGIN LOGGING /////////////////////
        
        int midi_channel = (int)(messageData[0]);
        int midi_number = dataSize > 1 ? (int)(messageData[1]) : 0;
        int midi_velocity = dataSize > 2 ? (int)(messageData[2]) : 0;
        timestamp_type timestamp = keyboard_.schedulerCurrentTimestamp();
        
        midiLog.write ((char*)&timestamp, sizeof (timestamp_type));
        midiLog.write ((char*)&midi_channel, sizeof (int));
        midiLog.write ((char*)&midi_number, sizeof (int));
        midiLog.write ((char*)&midi_velocity, sizeof (int));
        
        ///////////////////// END LOGGING //////////////////////
        ////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////
    }
        
#ifdef MIDI_INPUT_CONTROLLER_DEBUG_RAW
    if(source == 0)
        cout << "MIDI Input [internal]: ";
    else
        cout << "MIDI Input [" << source->getName() << "]: ";
	for(int debugPrint = 0; debugPrint < dataSize; debugPrint++)
		printf("%x ", messageData[debugPrint]);
	cout << endl;
#endif /* MIDI_INPUT_CONTROLLER_DEBUG_RAW */
    
    ScopedLock ksl(keyboard_.performanceDataMutex_);
    ScopedLock sl(segmentsMutex_);
    for(int i = 0; i < segments_.size(); i++) {
        if(segments_[i]->respondsToMessage(message))
            segments_[i]->midiHandlerMethod(source, message);
    }
}

// Destructor.  Free any existing callbacks
MidiInputController::~MidiInputController() {
    if(logFileCreated) {
        midiLog.close();
    }
	disableAllPorts(false);
    removeAllSegments();
}
