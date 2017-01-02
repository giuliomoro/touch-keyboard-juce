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
 
  MidiKeyboardSegment.h: handles incoming MIDI data and certain input-output
  mappings for one segment of a keyboard. The keyboard may be divided up into
  any number of segments with different behaviors. An important role of this
  class is to manage the output channel allocation when using one MIDI channel
  per note (for example, to handle polyphonic pitch bend).
*/


#ifndef __TouchKeys__MidiKeyboardSegment__
#define __TouchKeys__MidiKeyboardSegment__

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "../JuceLibraryCode/JuceHeader.h"
#include "PianoKeyboard.h"
#include "../Mappings/MappingFactorySplitter.h"

class OscMidiConverter;

// This class handles the processing of MIDI input data for a particular
// segment of the keyboard. It defines the processing mode and stores certain
// state information about active notes for this particular part of the keyboard.
// The MidiInputController class will use one or more of these segments to define
// keyboard behavior. In the case of a split keyboard arrangement, MIDI channel
// or note number might determine which segment takes ownership of a particular note.

class MidiKeyboardSegment : public OscHandler {
private:
    static const int kMidiControllerDamperPedal;
    static const int kMidiControllerSostenutoPedal;
    static const int kPedalActiveValue;
    
public:
	// Operating modes for MIDI input on this segment
	enum {
		ModeOff = 0,
		ModePassThrough,
		ModeMonophonic,
		ModePolyphonic,
        ModeMPE
	};
	
    // The MIDI Pitch Wheel is not handled by control change like the others,
    // but it is something we will want to map to.  Use a special control number
    // to designate mapping OSC to the Pitch Wheel.  Use 14 bit values when mapping
    // to this control. Similarly, we might want to map to channel aftertouch value.
    // The mechanics here are identical to 7-bit controllers.
    enum {
        kControlDisabled = -1,
        kControlPitchWheel = 128,
        kControlChannelAftertouch,
        kControlPolyphonicAftertouch,
        kControlMax
    };
    
    enum {
        kControlActionPassthrough = 0,
        kControlActionBroadcast,
        kControlActionSendToLatest,
        kControlActionBlock
    };
    
public:
	// Constructor
	MidiKeyboardSegment(PianoKeyboard& keyboard);
    
    // Destructor
    ~MidiKeyboardSegment();
 
    // Set/query the output controller
	MidiOutputController* midiOutputController() { return midiOutputController_; }
	void setMidiOutputController(MidiOutputController* ct) { midiOutputController_ = ct; }
	
    // Check whether this MIDI message is for this segment
    bool respondsToMessage(const MidiMessage& message);
    bool respondsToNote(int noteNumber);
    
    // Set which channels we listen to
	void enableChannel(int channelNumber);
	void enableAllChannels();
	void disableChannel(int channelNumber);
	void disableAllChanels();
    void setChannelMask(int channelMask) { channelMask_ = channelMask; }
    
    // Set which notes we listen to
    void setNoteRange(int minNote, int maxNote);
    std::pair<int, int> noteRange() { return std::pair<int,int>(noteMin_, noteMax_); }
    
    // Set whether or not we use aftertouch, pitchwheel or other controls
    // directly from the keyboard
    bool usesKeyboardChannnelPressure() { return usesKeyboardChannelPressure_; }
    void setUsesKeyboardChannelPressure(bool use) {
        usesKeyboardChannelPressure_ = use;
        // Reset to default if not using
        if(!use)
            controllerValues_[kControlChannelAftertouch] = 0;
    }
    
    bool usesKeyboardPitchWheel() { return usesKeyboardPitchWheel_; }
    void setUsesKeyboardPitchWheel(bool use) {
        usesKeyboardPitchWheel_ = use;
        // Reset to default if not using
        if(!use)
            controllerValues_[kControlPitchWheel] = 8192;
    }

    bool usesKeyboardModWheel() { return usesKeyboardModWheel_; }
    void setUsesKeyboardModWheel(bool use) {
        usesKeyboardModWheel_ = use;
        // Reset to default if not using
        if(!use) {
            controllerValues_[1] = 0;
        }
    }
    
    bool usesKeyboardPedals() { return usesKeyboardPedals_; }
    void setUsesKeyboardPedals(bool use) {
        usesKeyboardPedals_ = use;
        // Reset to default if not using
        if(!use) {
            // MIDI CCs 64 to 69 are for pedals
            for(int i = 64; i <= 69; i++)
                controllerValues_[i] = 0;
        }
    }
    
    bool usesKeyboardMIDIControllers() { return usesKeyboardMidiControllers_; }
    void setUsesKeyboardMIDIControllers(bool use) {
        usesKeyboardMidiControllers_ = use;
        // Reset to default if not using
        if(!use) {
            for(int i = 2; i < 128; i++)
                controllerValues_[i] = 0;
        }
    }
    
    // Get or set the MIDI pitch wheel range in semitones, and optionally send an RPN
    // message announcing its new value.
    float midiPitchWheelRange() { return pitchWheelRange_; }
    void setMidiPitchWheelRange(float semitones, bool send = false);
    void sendMidiPitchWheelRange();
    
    // TouchKeys standalone mode generates MIDI note onsets from touch data
    // without needing a MIDI keyboard
    void enableTouchkeyStandaloneMode();
    void disableTouchkeyStandaloneMode();
    bool touchkeyStandaloneModeEnabled() { return touchkeyStandaloneMode_; }
    
    // All Notes Off: can be sent by MIDI or controlled programmatically
	void allNotesOff();
    
    // Query the value of a controller
    int controllerValue(int index) {
        if(index < 0 || index >= kControlMax)
            return 0;
        return controllerValues_[index];
    }
    
    // Reset MIDI controller values to defaults
    void resetControllerValues();
	
	// Change or query the operating mode of the controller
	int mode() { return mode_; }
    void setMode(int mode);
	void setModeOff();
	void setModePassThrough();
    void setModeMonophonic();
	void setModePolyphonic();
    void setModeMPE();
    
    // Get/set polyphony and voice stealing for polyphonic mode
    int polyphony() { return retransmitMaxPolyphony_; }
    void setPolyphony(int polyphony);
    bool voiceStealingEnabled() { return useVoiceStealing_; }
    void setVoiceStealingEnabled(bool enable) { useVoiceStealing_ = enable; }
    
    // Get/set the number of the output port that messages on this segment should go to
    int outputPort() { return outputPortNumber_; }
    void setOutputPort(int port) { outputPortNumber_ = port; }
    
    // Set the minimum MIDI channel that should be used for output (0-15)
    int outputChannelLowest() { return outputChannelLowest_; }
    void setOutputChannelLowest(int ch);
    
    // Get set the output transposition in semitones, relative to input MIDI notes
    int outputTransposition() { return outputTransposition_; }
    void setOutputTransposition(int trans) { outputTransposition_ = trans; }
    
    // Whether the damper pedal is enabled in note channel allocation
    bool damperPedalEnabled() { return damperPedalEnabled_; }
    void setDamperPedalEnabled(bool enable);
    
    // MIDI handler routine
    void midiHandlerMethod(MidiInput* source, const MidiMessage& message);
    
    // OSC method: used to get touch callback data from the keyboard
	bool oscHandlerMethod(const char *path, const char *types, int numValues, lo_arg **values, void *data);
    
    // OSC control method: called separately via the MidiInputController to manipulate
    // control parameters of this object
    OscMessage* oscControlMethod(const char *path, const char *types, int numValues, lo_arg **values, void *data);
    
    // **** Mapping-related methods *****
    
    // OSC-MIDI converters: request and release methods. The acquire method
    // will create a converter if it does not already exist, or return an existing
    // one if it does. The release method will release the object when the
    // acquirer no longer needs it.    
    OscMidiConverter* acquireOscMidiConverter(int controlId);
    void releaseOscMidiConverter(int controlId);
    
    // *** Mapping methods ***
    // Return the number of mapping factory types available
    static int numberOfMappingFactories();
    
    // Return the name of a given mapping factory type
    static String mappingFactoryNameForIndex(int index);
    
    // Whether a given mapping is experimental
    static bool mappingIsExperimental(int index);
    
    // Create a new mapping factory of the given type, attached to
    // the supplied segment
    MappingFactory* createMappingFactoryForIndex(int index);
    
    // Create a new mapping factory for this segment. A pointer should be passed in
    // of a newly-allocated object. It will be released upon removal.
    void addMappingFactory(MappingFactory* factory, bool autoGenerateName = false);
    
    // Remove a mapping factory, releasing the associated object.
    void removeMappingFactory(MappingFactory* factory);
    
    // Remove all mapping factories, releasing each one
    void removeAllMappingFactories();
    
    // Return a list of current mapping factories.
    vector<MappingFactory*> const& mappingFactories();

    // Return the specific index of this mapping factory
    int indexOfMappingFactory(MappingFactory *factory);
    
    // Return a unique identifier of the mapping state, so we know when something has changed
    int mappingFactoryUniqueIdentifier() { return mappingFactoryUniqueIdentifier_; }
    
    // **** Preset methods ****
    
    // Get an XML element describing current settings (for saving presets)
    XmlElement* getPreset();
    
    // Load settings from an XML element
    bool loadPreset(XmlElement const* preset);

private:
	// Mode-specific MIDI input handlers
	void modePassThroughHandler(MidiInput* source, const MidiMessage& message);
	void modeMonophonicHandler(MidiInput* source, const MidiMessage& message);
    
	void modePolyphonicHandler(MidiInput* source, const MidiMessage& message);
	void modePolyphonicNoteOn(unsigned char note, unsigned char velocity);
	void modePolyphonicNoteOff(unsigned char note, bool forceOff = false);
	void modePolyphonicMPENoteOnCallback(const char *path, const char *types, int numValues, lo_arg **values);
    
    void modeMPEHandler(MidiInput* source, const MidiMessage& message);
    void modeMPENoteOn(unsigned char note, unsigned char velocity);

    // Helper functions for polyphonic mode
    void modePolyphonicSetupHelper();
    int oldestNote();
    int oldestNoteInPedal();
    int newestNote();
    
    // Methods for managing controllers
    void handleControlChangeRetransit(int controllerNumber, const MidiMessage& message);
    void setAllControllerActionsTo(int action);
    
    // Handle action of the damper pedal: when released, clear out any notes held there
    void damperPedalWentOff();
    
    // Send pitch wheel range to a specific channel
    void sendMidiPitchWheelRangeHelper(int channel);
    
    // ***** Member Variables *****
    
    PianoKeyboard& keyboard_;						// Reference to main keyboard data
	MidiOutputController *midiOutputController_;	// Destination for MIDI output
    int outputPortNumber_;                          // Which port to use on the output controller
    vector<MappingFactory*> mappingFactories_;      // Collection of mappings for this segment
    MappingFactorySplitter mappingFactorySplitter_; // ...and a splitter class to facilitate communication
    int mappingFactoryUniqueIdentifier_;            // Unique ID indicating mapping factory changes

	int mode_;                                      // Current operating mode of the segment
    unsigned int channelMask_;                      // Which channels we listen to (1 bit per channel)
    int noteMin_, noteMax_;                         // Ranges of the notes we respond to
    int outputChannelLowest_;                       // Lowest (or only) MIDI channel we send to
    int outputTransposition_;                       // Transposition of notes at output
    bool damperPedalEnabled_;                       // Whether to handle damper pedal events in allocating channels
    bool touchkeyStandaloneMode_;                   // Whether we emulate MIDI data from TouchKeys
    bool usesKeyboardChannelPressure_;              // Whether this segment passes aftertouch from the keyboard
    bool usesKeyboardPitchWheel_;                   // Whether this segment passes pitchwheel from the keyboard
    bool usesKeyboardModWheel_;                     // Whether this segment passes CC 1 (mod wheel) from keyboard
    bool usesKeyboardPedals_;                       // Whether this segment passes CCs 64-69 (pedals) from the keyboard
    bool usesKeyboardMidiControllers_;              // Whether this segment passes other controllers
    float pitchWheelRange_;                         // Range of MIDI pitch wheel (in semitones)
    
    int controllerValues_[kControlMax];             // Values of MIDI controllers from input device
    int controllerActions_[kControlMax];            // What to do with MIDI CCs when they come in
    
    // Mapping between input notes and output channels.  Depending on the mode of operation,
	// each note may be rebroadcast on its own MIDI channel.  Need to keep track of what goes where.
	// key is MIDI note #, value is output channel (0-15)
	map<int, int> retransmitChannelForNote_;
	set<int> retransmitChannelsAvailable_;
    set<int> retransmitNotesHeldInPedal_;
	int retransmitMaxPolyphony_;
    bool useVoiceStealing_;
    timestamp_type noteOnsetTimestamps_[128];       // When each currently active note began, for stealing
    
    // OSC-MIDI conversion objects for use with data mapping. These are stored in each
    // keyboard segment and specific mapping factories can request one when needed.
    map<int, OscMidiConverter*> oscMidiConverters_;
    map<int, int> oscMidiConverterReferenceCounts_;
};

#endif /* defined(__TouchKeys__MidiKeyboardSegment__) */
