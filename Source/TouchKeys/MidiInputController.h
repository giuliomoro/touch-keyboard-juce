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
 
  MidiInputController.h: handles incoming MIDI data and manages input
  ports. Detailed processing is broken down by keyboard segment; see
  MidiKeyboardSegment.h/cpp for more.
*/


#ifndef MIDI_INPUT_CONTROLLER_H
#define MIDI_INPUT_CONTROLLER_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "../JuceLibraryCode/JuceHeader.h"
#include "PianoKeyboard.h"
#include "Osc.h"
#include "MidiKeyboardSegment.h"

using namespace std;

class MidiOutputController;

// MIDI standard messages

enum {
	kMidiMessageNoteOff = 0x80,
	kMidiMessageNoteOn = 0x90,
	kMidiMessageAftertouchPoly = 0xA0,
	kMidiMessageControlChange = 0xB0,
	kMidiMessageProgramChange = 0xC0,
	kMidiMessageAftertouchChannel = 0xD0,
	kMidiMessagePitchWheel = 0xE0,
	kMidiMessageSysex = 0xF0,
	kMidiMessageSysexEnd = 0xF7,
	kMidiMessageActiveSense = 0xFE,
	kMidiMessageReset = 0xFF
};

enum {
	kMidiControlAllSoundOff = 120,
	kMidiControlAllControllersOff = 121,
	kMidiControlLocalControl = 122,
	kMidiControlAllNotesOff = 123
};

class MidiInputController : public MidiInputCallback {
public:
    /*
	// Operating modes for MIDI input
	enum {
		ModeOff = 0,
		ModePassThrough,
		ModeMonophonic,
		ModePolyphonic,
		ModeChannelSelect,
		ModeConstantControllers
	};
	
	// Switch types for Channel Select mode
	enum {
		ChannelSelectSwitchTypeUnknown = 0,
		ChannelSelectSwitchTypeLocation,
		ChannelSelectSwitchTypeSize,
		ChannelSelectSwitchTypeNumTouches,
		ChannelSelectSwitchTypeAngle
	};
     */
	
public:
	// Constructor
	MidiInputController(PianoKeyboard& keyboard);

	
	// Query available devices
	vector<pair<int, string> > availableMidiDevices();
	
	// Add/Remove MIDI input ports;
	// Enable methods return true on success (at least one port enabled) 
	bool enablePort(int portNumber);
	bool enableAllPorts();
	void disablePort(int portNumber);
	void disableAllPorts();
	vector<int> activePorts();

    //void touchkeyStandaloneTouchBegan(int noteNumber,  Node<KeyTouchFrame>* touchBuffer);
    //void touchkeyStandaloneTouchEnded(int noteNumber);
    
    /*
	// Set which channels we listen to
	bool enableChannel(int channelNumber);
	bool enableAllChannels();
	void disableChannel(int channelNumber);
	void disableAllChanels();
	*/
    
	// Set/query the output controller
	MidiOutputController* midiOutputController() { return midiOutputController_; }
	void setMidiOutputController(MidiOutputController* ct);
	
	// All Notes Off: can be sent by MIDI or controlled programmatically
	void allNotesOff();
    
    // Return the number of keyboard segments, and a specific segment
    int numSegments() {
        ScopedLock sl(segmentsMutex_);
        return segments_.size();
    }
    MidiKeyboardSegment* segment(int num) {
        ScopedLock sl(segmentsMutex_);
        if(num < 0 || num >= segments_.size())
            return 0;
        return segments_[num];
    }
    // Return a unique signature which tells us when the MIDI segments have changed,
    // allowing any listeners to re-query all the segments.
    int segmentUniqueIdentifier() {
        return segmentUniqueIdentifier_;
    }

    // Add a new keyboard segment. Returns a pointer to the newly created segment
    MidiKeyboardSegment* addSegment(int outputPortNumber, int noteMin = 0, int noteMax = 127, int channelMask = 0xFFFF);
    
    // Remove a segment by index or by object
    void removeSegment(int index);
    void removeSegment(MidiKeyboardSegment* segment);
    void removeAllSegments();
    
    /*
	// Change or query the operating mode of the controller
	int mode() { return mode_; }
	void setModeOff();
	void setModePassThrough();
    void setModeMonophonic();
	void setModePolyphonic();
	void setModeChannelSelect(int switchType, int numDivisions, int defaultChannel);

    int polyphony() { return retransmitMaxPolyphony_; }
    void setPolyphony(int polyphony);
    bool voiceStealingEnabled() { return useVoiceStealing_; }
    void setVoiceStealingEnabled(bool enable) { useVoiceStealing_ = enable; }
    */
    
    // Juce MIDI callbacks
    void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message);
    void handlePartialSysexMessage(MidiInput* source,
                                   const uint8* messageData,
                                   int numBytesSoFar,
                                   double timestamp) {}
	
	// OSC method: used to get touch callback data from the keyboard
	// bool oscHandlerMethod(const char *path, const char *types, int numValues, lo_arg **values, void *data);
    
    // for logging
    void createLogFile(string midiLog_filename, string path);
    void closeLogFile();
    void startLogging();
    void stopLogging();
    
    bool logFileCreated;
    bool loggingActive;

	// Destructor
	~MidiInputController();
	
private:
	// Filtering by channel: return whether this message concerns one of the active channels
	// we're listening to.
	// bool messageIsForActiveChannel(const MidiMessage& message);
	
    /*
	// Mode-specific MIDI input handlers
	void modePassThroughHandler(MidiInput* source, const MidiMessage& message);	
	void modeMonophonicHandler(MidiInput* source, const MidiMessage& message);

	void modePolyphonicHandler(MidiInput* source, const MidiMessage& message);
	void modePolyphonicNoteOn(unsigned char note, unsigned char velocity);
	void modePolyphonicNoteOff(unsigned char note);
	void modePolyphonicNoteOnCallback(const char *path, const char *types, int numValues, lo_arg **values);
	
	void modeChannelSelectHandler(MidiInput* source, const MidiMessage& message);
	void modeChannelSelectNoteOn(unsigned char note, unsigned char velocity);
	void modeChannelSelectNoteOff(unsigned char note);
	void modeChannelSelectNoteOnCallback(const char *path, const char *types, int numValues, lo_arg **values);
	
	void modeConstantControllersHandler(MidiInput* source, const MidiMessage& message);
	
    // Helper functions for polyphonic mode
    void modePolyphonicSetupHelper();
    int oldestNote();
    int newestNote();
     */
    
	// ***** Member Variables *****
	
	PianoKeyboard& keyboard_;						// Reference to main keyboard data
    MidiOutputController *midiOutputController_;	// Destination for MIDI output
    
	map<int, MidiInput*> activePorts_;              // Sources of MIDI data
    
    vector<MidiKeyboardSegment*> segments_;         // Segments of the keyboard
    CriticalSection segmentsMutex_;                 // Mutex protecting the segments list
    int segmentUniqueIdentifier_;                   // Identifier of when segment structure has changed
    

    /*

	
	// Current operating mode of the controller
	int mode_;
	
	// Mapping between input notes and output channels.  Depending on the mode of operation,
	// each note may be rebroadcast on its own MIDI channel.  Need to keep track of what goes where.
	// key is MIDI note #, value is output channel (0-15)
	map<int, int> retransmitChannelForNote_;
	set<int> retransmitChannelsAvailable_;
	int retransmitMaxPolyphony_;
    bool useVoiceStealing_;
    map<int, timestamp_type> noteOnsetTimestamps_; // When each currently active note began, for stealing
	
	// Parameters for Channel Select mode of operation
	int channelSelectSwitchType_;
	int channelSelectNumberOfDivisions_;
	int channelSelectDefaultChannel_;
	int channelSelectLastOnsetChannel_;
    */
    
    // for logging
    ofstream midiLog;
    
    // for generating timestamps
    // Scheduler eventScheduler_;
};

#endif /* MIDI_INPUT_CONTROLLER_H */