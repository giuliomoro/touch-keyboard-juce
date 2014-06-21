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
 
  MidiOutputController.h: handles outgoing MIDI messages and manages output
  ports; uses Juce MIDI library functions.
*/

#ifndef MIDI_OUTPUT_CONTROLLER_H
#define MIDI_OUTPUT_CONTROLLER_H

#include <map>
#include "MidiInputController.h"

const juce::String kMidiVirtualOutputName = "TouchKeys";

using namespace std;

class MidiOutputController {
private:
    struct MidiOutputControllerRecord {
        int portNumber;
        MidiOutput *output;
    };
    
public:
    enum {
        kMidiVirtualOutputPortNumber = -2,
        kMidiOutputNotOpen = -1
    };
	
	// Constructor
	MidiOutputController();
	
	// Query available devices
	vector<pair<int, string> > availableMidiDevices();
	
	// Methods to connect/disconnect from a target port
    bool enablePort(int identifier, int deviceNumber);
#ifndef JUCE_WINDOWS
    bool enableVirtualPort(int identifier, const char *name);
#endif
	void disablePort(int identifier);
	void disableAllPorts();
    
    int enabledPort(int identifier);
    std::vector<std::pair<int, int> > enabledPorts();
	
    // Get the name of a particular port index
    String deviceName(int portNumber);
    
    // Find the index of a device with a given name; return -1 if not found
    int indexOfDeviceNamed(String const& name);
    
	// Send MIDI messages
	void sendNoteOn(int port, unsigned char channel, unsigned char note, unsigned char velocity);
    void sendNoteOff(int port, unsigned char channel, unsigned char note, unsigned char velocity = 64);
	void sendControlChange(int port, unsigned char channel, unsigned char control, unsigned char value);
	void sendProgramChange(int port, unsigned char channel, unsigned char value);
	void sendAftertouchChannel(int port, unsigned char channel, unsigned char value);
	void sendAftertouchPoly(int port, unsigned char channel, unsigned char note, unsigned char value);
	void sendPitchWheel(int port, unsigned char channel, unsigned int value);
	void sendReset(int port);
	
	// Generic pre-formed messages
	void sendMessage(int port, const MidiMessage& message);
	
	// Destructor
	~MidiOutputController() { disableAllPorts(); }
	
private:
    std::map<int, MidiOutputControllerRecord> activePorts_;              // Destinations for MIDI data
};

#endif /* MIDI_OUTPUT_CONTROLLER_H */