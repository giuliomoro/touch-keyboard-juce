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
 
  MainApplicationController.h: contains the overall glue that holds
  together the various parts of the TouchKeys code. It works together
  with the user interface to let the user configure the hardware and
  manage the mappings, but it is kept separate from any particular user
  interface configuration.
*/

#ifndef __TouchKeys__MainApplicationController__
#define __TouchKeys__MainApplicationController__

#include <iostream>
#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "TouchKeys/MidiInputController.h"
#include "TouchKeys/MidiKeyboardSegment.h"
#include "TouchKeys/MidiOutputController.h"
#include "TouchKeys/TouchkeyDevice.h"
#include "TouchKeys/Osc.h"
#include "Mappings/Vibrato/TouchkeyVibratoMappingFactory.h"
#include "Mappings/PitchBend/TouchkeyPitchBendMappingFactory.h"
#include "Mappings/Control/TouchkeyControlMappingFactory.h"
#include "Mappings/ReleaseAngle/TouchkeyReleaseAngleMappingFactory.h"
#include "Mappings/OnsetAngle/TouchkeyOnsetAngleMappingFactory.h"
#include "Mappings/MultiFingerTrigger/TouchkeyMultiFingerTriggerMappingFactory.h"
#include "Mappings/KeyDivision/TouchkeyKeyDivisionMappingFactory.h"
#include "Mappings/MappingFactorySplitter.h"
#include "TouchKeys/LogPlayback.h"

const char kDefaultOscTransmitHost[] = "127.0.0.1";
const char kDefaultOscTransmitPort[] = "8000";
const int kDefaultOscReceivePort = 8001;

class InterfaceSelectorComponent;

class MainApplicationController : public OscHandler {
public:
    // *** Constructor ***
    MainApplicationController();
    
    // *** Destructor ***
    ~MainApplicationController();
    
    // *** TouchKeys device methods ***
    
    // Return the path prefix of the TouchKeys device
    std::string touchkeyDevicePrefix();
    
    // Return a list of paths to all available touchkey devices
    std::vector<std::string> availableTouchkeyDevices();

    // Run the main startup sequence: open device, check its presence,
    // start data collection, all in one method. Returns true if successful.
    // Will set the error message string if not
    bool touchkeyDeviceStartupSequence(const char * path);
    void touchkeyDeviceClearErrorMessage() {
        touchkeyErrorMessage_ = "";
        touchkeyErrorOccurred_ = false;
    }
    
    // Select a particular touchkey device
    bool openTouchkeyDevice(const char * path) {
        return touchkeyController_.openDevice(path);
    }
    void closeTouchkeyDevice() {
        touchkeyController_.closeDevice();
    }
    
    // Check for device present
    bool touchkeyDeviceCheckForPresence(int waitMilliseconds = 250, int tries = 10);
    
    // Start/stop the TouchKeys data collection
    bool startTouchkeyDevice() {
        return touchkeyController_.startAutoGathering();
    }
    void stopTouchkeyDevice() {
        touchkeyController_.stopAutoGathering();
    }
    
    // Status queries on TouchKeys
    // Returns true if device has been opened
    bool touchkeyDeviceIsOpen() {
        return touchkeyController_.isOpen();
    }
    // Return true if device is collecting data
    bool touchkeyDeviceIsRunning() {
        return touchkeyController_.isAutoGathering();
    }
    // Returns true if an error has occurred
    bool touchkeyDeviceErrorOccurred() {
        return touchkeyErrorOccurred_;
    }
    // Return the error message if one occurred
    std::string touchkeyDeviceErrorMessage() {
        return touchkeyErrorMessage_;
    }
    // How many octaves on the current device
    int touchkeyDeviceNumberOfOctaves() {
        return touchkeyController_.numberOfOctaves();
    }
    // Return the lowest MIDI note
    int touchkeyDeviceLowestMidiNote() {
        return touchkeyController_.lowestMidiNote();
    }
    // Set the lowest MIDI note for the TouchKeys
    void touchkeyDeviceSetLowestMidiNote(int note) {
        keyboardDisplay_.clearAllTouches();
        touchkeyController_.setLowestMidiNote(note);
    }
    // Attempt to autodetect the correct TouchKey octave from MIDI data
    void touchkeyDeviceAutodetectLowestMidiNote();
    void touchkeyDeviceStopAutodetecting();
    bool touchkeyDeviceIsAutodetecting();
    
    // *** MIDI device methods ***
    
    // Return a list of IDs and paths to all available MIDI devices
    std::vector<std::pair<int, std::string> > availableMIDIInputDevices() {
        return midiInputController_.availableMidiDevices();
    }
    
    std::vector<std::pair<int, std::string> > availableMIDIOutputDevices() {
        return midiOutputController_.availableMidiDevices();
    }
    
    // Return the number of keyboard segments
    int midiSegmentsCount() {
        return midiInputController_.numSegments();
    }
    // Return the pointer to a specific segment
    MidiKeyboardSegment* midiSegment(int index) {
        return midiInputController_.segment(index);
    }
    // Return a unique signature of segment configuration which
    // tells any listeners whether an update has happened
    int midiSegmentUniqueIdentifier() {
        return midiInputController_.segmentUniqueIdentifier();
    }
    // Add a new segment, returning the result. Segments are
    // stored 
    MidiKeyboardSegment* midiSegmentAdd();
    // Remove a segment
    void midiSegmentRemove(MidiKeyboardSegment *segment) {
        midiInputController_.removeSegment(segment);
    }

    // Select MIDI input/output devices
    void enableMIDIInputPort(int portNumber) {
        midiInputController_.enablePort(portNumber);
    }
    void enableAllMIDIInputPorts() {
        midiInputController_.enableAllPorts();
    }
    void disableMIDIInputPort(int portNumber) {
        midiInputController_.disablePort(portNumber);
    }
    void disableAllMIDIInputPorts() {
        midiInputController_.disableAllPorts();
    }
    void enableMIDIOutputPort(int identifier, int deviceNumber) {
        midiOutputController_.enablePort(identifier, deviceNumber);
    }
    void enableMIDIOutputVirtualPort(int identifier, const char *name) {
        midiOutputController_.enableVirtualPort(identifier, name);
    }
    void disableMIDIOutputPort(int identifier) {
        midiOutputController_.disablePort(identifier);
    }
    void disableAllMIDIOutputPorts() {
        midiOutputController_.disableAllPorts();
    }
    
    // Get selected MIDI input/output devices by ID
    std::vector<int> selectedMIDIInputPorts() {
        return midiInputController_.activePorts();
    }
    int selectedMIDIOutputPort(int identifier) {
        return midiOutputController_.enabledPort(identifier);
    }
    
    void midiTouchkeysStandaloneModeEnable();
    void midiTouchkeysStandaloneModeDisable();
    bool midiTouchkeysStandaloneModeIsEnabled() { return touchkeyStandaloneModeEnabled_; }
    
    // *** OSC device methods ***
    
    bool oscTransmitEnabled() {
        return oscTransmitter_.enabled();
    }
    void oscTransmitSetEnabled(bool enable) {
        oscTransmitter_.setEnabled(enable);
    }
    bool oscTransmitRawDataEnabled() {
        return touchkeyController_.transmitRawDataEnabled();
    }
    void oscTransmitSetRawDataEnabled(bool enable) {
        touchkeyController_.setTransmitRawData(enable);
    }
    std::vector<lo_address> oscTransmitAddresses() {
        return oscTransmitter_.addresses();
    }
    int oscTransmitAddAddress(const char * host, const char * port, int proto = LO_UDP) {
        return oscTransmitter_.addAddress(host, port, proto);
    }
	void oscTransmitRemoveAddress(int index) {
        return oscTransmitter_.removeAddress(index);
    }
	void oscTransmitClearAddresses() {
        return oscTransmitter_.clearAddresses();
    }
    
    // OSC Input (receiver) methods
    // Enable or disable on the OSC receive, and report is status
    bool oscReceiveEnabled() {
        return oscReceiveEnabled_;
    }
    // Enable method returns true on success (false only if it was
    // unable to set the port)
    bool oscReceiveSetEnabled(bool enable) {
        if(enable && !oscReceiveEnabled_) {
            oscReceiveEnabled_ = true;
            return oscReceiver_.setPort(oscReceivePort_);
        }
        else if(!enable && oscReceiveEnabled_) {
            oscReceiveEnabled_ = false;
            return oscReceiver_.setPort(0);
        }
        return true;
    }
    
    // Whether the OSC server is running (false means couldn't open port)
    bool oscReceiveRunning() {
        return oscReceiver_.running();
    }
    // Get the current OSC receive port
    int oscReceivePort() {
        return oscReceivePort_;
    }
    // Set the current OSC receive port (returns true on success)
    bool oscReceiveSetPort(int port) {
        oscReceivePort_ = port;
        return oscReceiver_.setPort(port);
    }
    
    
    // *** Display methods ***
    
    KeyboardDisplay& keyboardDisplay() { return keyboardDisplay_; }
#ifndef TOUCHKEYS_NO_GUI
    void setKeyboardDisplayWindow(DocumentWindow *window) { keyboardDisplayWindow_ = window; }
    void showKeyboardDisplayWindow() {
        if(keyboardDisplayWindow_ != 0) {
            keyboardDisplayWindow_->setVisible(true);
            keyboardDisplayWindow_->toFront(true);
        }
    }
#endif
    
    // *** Logging methods ***
    // Logging methods which record TouchKeys and MIDI data to files for
    // later analysis/playback
    
    void startLogging();
    void stopLogging();
    bool isLogging() { return loggingActive_; }
    void setLoggingDirectory(const char *directory);
    
    // *** OSC handler method (different from OSC device selection) ***
    
	bool oscHandlerMethod(const char *path, const char *types, int numValues, lo_arg **values, void *data);
    
    
    // *** Mapping methods ***
    // Return the number of mapping factory types available
    int numberOfMappingFactories();
    
    // Return the name of a given mapping factory type
    String mappingFactoryNameForIndex(int index);
    
    // Create a new mapping factory of the given type, attached to
    // the supplied segment
    MappingFactory* createMappingFactoryForIndex(int index, MidiKeyboardSegment& segment);
 
    // Whether experimental (not totally finished/tested) mappings are available
    bool experimentalMappingsEnabled() { return experimentalMappingsEnabled_; }
    void setExperimentalMappingsEnabled(bool enable) { experimentalMappingsEnabled_ = enable; }
    
    // Whether a given mapping is experimental
    bool mappingIsExperimental(int index);
    
    // *** Static utility methods ***
    static std::string midiNoteName(int noteNumber);
    static int midiNoteNumberForName(std::string const& name);
    
private:
    // TouchKeys objects
    PianoKeyboard keyboardController_;
    MidiInputController midiInputController_;
    MidiOutputController midiOutputController_;
    TouchkeyDevice touchkeyController_;
    OscTransmitter oscTransmitter_;
    OscReceiver oscReceiver_;
    
    bool touchkeyErrorOccurred_;
    std::string touchkeyErrorMessage_;
    bool touchkeyAutodetecting_;
    bool touchkeyStandaloneModeEnabled_;
    
    // OSC information
    bool oscReceiveEnabled_;
    int oscReceivePort_;
    
    // Mapping objects
    bool experimentalMappingsEnabled_;
    
    // Display objects
    KeyboardDisplay keyboardDisplay_;
#ifndef TOUCHKEYS_NO_GUI
    DocumentWindow *keyboardDisplayWindow_;
#endif
    
    // Segment info
    int segmentCounter_;
    
    // Logging info
    bool loggingActive_;
    std::string loggingDirectory_;
};

#endif /* defined(__TouchKeys__MainApplicationController__) */
