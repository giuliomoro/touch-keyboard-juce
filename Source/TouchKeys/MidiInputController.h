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
	// Constructor
	MidiInputController(PianoKeyboard& keyboard);
	
	// Query available devices
	vector<pair<int, string> > availableMidiDevices();
	
	// Add/Remove MIDI input ports;
	// Enable methods return true on success (at least one port enabled) 
	bool enablePort(int portNumber, bool isPrimary);
	bool enableAllPorts(int primaryPortNumber);
	void disablePort(int portNumber);
    void disablePrimaryPort();
	void disableAllPorts(bool auxiliaryOnly);
    int primaryActivePort();
	vector<int> auxiliaryActivePorts();
    
    // Get the name of a particular port index
    String deviceName(int portNumber);
    int indexOfDeviceNamed(String const& name);

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
    bool removeSegment(int index);
    bool removeSegment(MidiKeyboardSegment* segment);
    void removeAllSegments();
    
    // Preset save/load for keyboard segments
    XmlElement* getSegmentPreset();
    bool loadSegmentPreset(XmlElement const* preset);
    
    // OSC handling for keyboard segments
    OscMessage* oscControlMessageForSegment(int segment, const char *path, const char *types, int numValues, lo_arg **values, void *data);
    
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
	// ***** Member Variables *****
	
	PianoKeyboard& keyboard_;						// Reference to main keyboard data
    MidiOutputController *midiOutputController_;	// Destination for MIDI output
    
	map<int, MidiInput*> activePorts_;              // Sources of MIDI data
    int primaryActivePort_;                         // Which source is primary
    
    vector<MidiKeyboardSegment*> segments_;         // Segments of the keyboard
    CriticalSection segmentsMutex_;                 // Mutex protecting the segments list
    int segmentUniqueIdentifier_;                   // Identifier of when segment structure has changed
    
    // for logging
    ofstream midiLog;
};

#endif /* MIDI_INPUT_CONTROLLER_H */