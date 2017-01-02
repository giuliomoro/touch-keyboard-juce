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
 
  MidiKeyboardSegment.cpp: handles incoming MIDI data and certain input-output
  mappings for one segment of a keyboard. The keyboard may be divided up into
  any number of segments with different behaviors. An important role of this
  class is to manage the output channel allocation when using one MIDI channel
  per note (for example, to handle polyphonic pitch bend).
*/

#include "MidiKeyboardSegment.h"
#include "MidiOutputController.h"
#include "../Mappings/MappingFactory.h"
#include "../Mappings/Vibrato/TouchkeyVibratoMappingFactory.h"
#include "../Mappings/PitchBend/TouchkeyPitchBendMappingFactory.h"
#include "../Mappings/Control/TouchkeyControlMappingFactory.h"
#include "../Mappings/ReleaseAngle/TouchkeyReleaseAngleMappingFactory.h"
#include "../Mappings/OnsetAngle/TouchkeyOnsetAngleMappingFactory.h"
#include "../Mappings/MultiFingerTrigger/TouchkeyMultiFingerTriggerMappingFactory.h"
#include "../Mappings/KeyDivision/TouchkeyKeyDivisionMappingFactory.h"
#include "OscMidiConverter.h"
#include <algorithm>
#include <string>
#include <sstream>

#undef DEBUG_MIDI_KEYBOARD_SEGMENT

const int MidiKeyboardSegment::kMidiControllerDamperPedal = 64;
const int MidiKeyboardSegment::kMidiControllerSostenutoPedal = 66;
const int MidiKeyboardSegment::kPedalActiveValue = 64;

// Factores to use
const int kNumMappingFactoryTypes = 7;
const char* kMappingFactoryNames[kNumMappingFactoryTypes] = {"Control", "Vibrato", "Pitch Bend", "Split Key", "Multi-Finger Trigger", "Onset Angle", "Release Angle"};


// Constructor
MidiKeyboardSegment::MidiKeyboardSegment(PianoKeyboard& keyboard)
: keyboard_(keyboard), outputPortNumber_(0), mappingFactorySplitter_(keyboard),
  mappingFactoryUniqueIdentifier_(0),
  mode_(ModeOff), channelMask_(0),
  noteMin_(0), noteMax_(127), outputChannelLowest_(0), outputTransposition_(0),
  damperPedalEnabled_(true), touchkeyStandaloneMode_(false),
  usesKeyboardChannelPressure_(false), usesKeyboardPitchWheel_(false),
  usesKeyboardModWheel_(false), usesKeyboardPedals_(true),
  usesKeyboardMidiControllers_(false),
  pitchWheelRange_(2.0), useVoiceStealing_(false)
{
	// Register for OSC messages from the internal keyboard source
	setOscController(&keyboard_);
    keyboard_.setMappingFactory(this, &mappingFactorySplitter_);
    
    setAllControllerActionsTo(kControlActionBlock);
    resetControllerValues();
    
    for(int i = 0; i < 128; i++)
        noteOnsetTimestamps_[i] = 0;
}

// Destructor
MidiKeyboardSegment::~MidiKeyboardSegment() {
    removeAllMappingFactories();
    keyboard_.removeMappingFactory(this);
}

bool MidiKeyboardSegment::respondsToMessage(const MidiMessage& message) {
    int channel = message.getChannel();

    // If the message is not something universal, check if it matches our channel
    if(channel > 0) {
        if(!(channelMask_ && (1 << (channel - 1))))
            return false;
    }
    
    // If the message has a note number, see if it's in range
    if(message.isNoteOn() || message.isNoteOff() || message.isAftertouch()) {
        int noteNumber = message.getNoteNumber();
        if(noteNumber < noteMin_ || noteNumber > noteMax_)
            return false;
    }
    
    return true;
}

bool MidiKeyboardSegment::respondsToNote(int noteNumber) {
    if(noteNumber < noteMin_ || noteNumber > noteMax_)
        return false;
    return true;
}

// Listen on a given MIDI channel
void MidiKeyboardSegment::enableChannel(int channelNumber) {
    if(channelNumber >= 0 && channelNumber < 16)
        channelMask_ |= (1 << channelNumber);
}

// Listen on all MIDI channels
void MidiKeyboardSegment::enableAllChannels() {
    channelMask_ = 0xFFFF;
}

// Disable listening to a specific MIDI channel
void MidiKeyboardSegment::disableChannel(int channelNumber) {
    if(channelNumber >= 0 && channelNumber < 16)
        channelMask_ &= ~(1 << channelNumber);
}

// Disable all MIDI channels
void MidiKeyboardSegment::disableAllChanels() {
    channelMask_ = 0;
}

// Set the range of notes we listen to. Sets the range to between
// minNote and maxNote, inclusive.
void MidiKeyboardSegment::setNoteRange(int minNote, int maxNote) {
    // Sanity check
    if(minNote > maxNote)
        return;
    if(minNote < 0)
        noteMin_ = 0;
    else if(minNote > 127)
        noteMin_ = 127;
    else
        noteMin_ = minNote;

    if(maxNote < 0)
        noteMax_ = 0;
    else if(maxNote > 127)
        noteMax_ = 127;
    else
        noteMax_ = maxNote;
    
}

// Set the MIDI pitch wheel range
void MidiKeyboardSegment::setMidiPitchWheelRange(float semitones, bool send) {
    if(semitones < 0)
        pitchWheelRange_ = 0;
    else if(semitones > 48.0)
        pitchWheelRange_ = 48.0;
    else
        pitchWheelRange_ = semitones;
    
    if(send)
        sendMidiPitchWheelRange();
}

// Send the MIDI pitch wheel range RPN
// If in polyphonic mode, send to all channels; otherwise send only
// to the channel in question.
void MidiKeyboardSegment::sendMidiPitchWheelRange() {
    // MPE-TODO
    if(mode_ == ModePolyphonic) {
        for(int i = outputChannelLowest_; i < outputChannelLowest_ + retransmitMaxPolyphony_; i++)
            sendMidiPitchWheelRangeHelper(i);
    }
    else
        sendMidiPitchWheelRangeHelper(outputChannelLowest_);
}


// Enable TouchKeys standalone mode (no MIDI input, touch triggers note)
void MidiKeyboardSegment::enableTouchkeyStandaloneMode() {
    if(touchkeyStandaloneMode_)
        return;
    
    addOscListener("/touchkeys/on");
    addOscListener("/touchkeys/off");
    touchkeyStandaloneMode_ = true;
}

// Disable TouchKeys standalone mode (no MIDI input, touch triggers note)
void MidiKeyboardSegment::disableTouchkeyStandaloneMode() {
    if(!touchkeyStandaloneMode_)
        return;

    removeOscListener("/touchkeys/on");
    removeOscListener("/touchkeys/off");
    touchkeyStandaloneMode_ = false;
}

// Disable any currently active notes
void MidiKeyboardSegment::allNotesOff() {
	// TODO: implement me
}

// Reset controller values to defaults
void MidiKeyboardSegment::resetControllerValues() {
    // Most controls default to 0
    for(int i = 0; i < kControlMax; i++)
        controllerValues_[i] = 0;
    // ...except pitch wheel, which defaults to center
    controllerValues_[kControlPitchWheel] = 8192;
}

// Set the operating mode of the controller.  The mode determines the behavior in
// response to incoming MIDI data.

void MidiKeyboardSegment::setMode(int mode) {
    if(mode == ModePassThrough)
        setModePassThrough();
    else if(mode == ModeMonophonic)
        setModeMonophonic();
    else if(mode == ModePolyphonic)
        setModePolyphonic();
    else if(mode == ModeMPE)
        setModeMPE();
    else
        setModeOff();
}

void MidiKeyboardSegment::setModeOff() {
	allNotesOff();
	removeOscListener("/midi/noteon");
    setAllControllerActionsTo(kControlActionBlock);
	mode_ = ModeOff;
}

void MidiKeyboardSegment::setModePassThrough() {
	allNotesOff();
	removeOscListener("/midi/noteon");
    setAllControllerActionsTo(kControlActionPassthrough);
	mode_ = ModePassThrough;
}

void MidiKeyboardSegment::setModeMonophonic() {
	allNotesOff();
	removeOscListener("/midi/noteon");
    setAllControllerActionsTo(kControlActionPassthrough);
	mode_ = ModeMonophonic;
}

void MidiKeyboardSegment::setModePolyphonic() {
	// First turn off any notes in the current mode
	allNotesOff();
    setAllControllerActionsTo(kControlActionBroadcast);
	
	// Register a callback for touchkey data.  When we get a note-on message,
	// we request this callback occur once touch data is available.  In this mode,
	// we know the eventual channel before any touch data ever occurs: thus, we
	// only listen to the MIDI onset itself, which happens after all the touch
	// data is sent out.
	addOscListener("/midi/noteon");
    
	mode_ = ModePolyphonic;
	
    if(retransmitMaxPolyphony_ < 1)
        retransmitMaxPolyphony_ = 1;
    modePolyphonicSetupHelper();
}

void MidiKeyboardSegment::setModeMPE() {
    // First turn off any notes in the current mode
    allNotesOff();
    
    // MPE-TODO some things need to be set to master-zone retransmit
    // also reset pitch wheel value to 0 since it's sent separately
    setAllControllerActionsTo(kControlActionBroadcast);
    
    // Register a callback for touchkey data.  When we get a note-on message,
    // we request this callback occur once touch data is available.  In this mode,
    // we know the eventual channel before any touch data ever occurs: thus, we
    // only listen to the MIDI onset itself, which happens after all the touch
    // data is sent out.
    addOscListener("/midi/noteon");
    
    mode_ = ModeMPE;
    
    // MPE-TODO
    // Set RPN 6 to enable MPE with the appropriate zone
    
}

// Set the maximum polyphony, affecting polyphonic mode only
void MidiKeyboardSegment::setPolyphony(int polyphony) {
    // First turn off any notes if this affects current polyphonic mode
    // (other modes unaffected so we can make these changes in background)
    if(mode_ == ModePolyphonic)
        allNotesOff();
    
    if(polyphony < 1)
        retransmitMaxPolyphony_ = 1;
    else if(polyphony > 16)
        retransmitMaxPolyphony_ = 16;
    else
        retransmitMaxPolyphony_ = polyphony;
    
    // MPE-TODO
    // Send RPN 6 to change the zone configuration
    // -- maybe in modePolyphonicSetupHelper()
    
    if(mode_ == ModePolyphonic)
        modePolyphonicSetupHelper();
}

// Set whether the damper pedal is enabled or not
void MidiKeyboardSegment::setDamperPedalEnabled(bool enable) {
    if(damperPedalEnabled_ && !enable) {
        // Pedal was enabled before, now it isn't. Clear out any notes
        // currently in the pedal so they can be retaken.
        damperPedalWentOff();
    }
    
    damperPedalEnabled_ = enable;
}

// Set the lowest output channel
void MidiKeyboardSegment::setOutputChannelLowest(int ch) {
    // FIXME this is probably broken for polyphonic mode!
    // MPE-TODO: send new RPN 6 for disabling old zone and creating new one
    outputChannelLowest_ = ch;
}

// Handle an incoming MIDI message
void MidiKeyboardSegment::midiHandlerMethod(MidiInput* source, const MidiMessage& message) {
    // Log the timestamps of note onsets and releases, regardless of the mode
    // of processing
    if(message.isNoteOn()) {
        if(message.getNoteNumber() >= 0 && message.getNoteNumber() < 128)
            noteOnsetTimestamps_[message.getNoteNumber()] = keyboard_.schedulerCurrentTimestamp();
    }
    else if(message.isNoteOff()) {
        // Remove the onset timestamp unless we have the specific condition:
        // (damper pedal enabled) && (pedal is down) && (polyphonic mode)
        // In this condition, onsets will be removed when note goes off
        if(message.getNoteNumber() >= 0 && message.getNoteNumber() < 128) {
            if(!damperPedalEnabled_ || controllerValues_[kMidiControllerDamperPedal] < kPedalActiveValue ||
               (mode_ != ModePolyphonic && mode_ != ModeMPE)) {
                noteOnsetTimestamps_[message.getNoteNumber()] = 0;
            }
        }
    }
    else if(message.isAllNotesOff() || message.isAllSoundOff()) {
        for(int i = 0; i < 128; i++)
            noteOnsetTimestamps_[i] = 0;
    }
    
    // Log the values of incoming control changes in case mappings need to use them later
    if(message.isController() && !(message.isAllNotesOff() || message.isAllSoundOff())) {
        // Handle damper pedal specially: it may affect note allocation
        if(message.getControllerNumber() == kMidiControllerDamperPedal) {
            if(message.getControllerValue() < kPedalActiveValue &&
               controllerValues_[kMidiControllerDamperPedal] >= kPedalActiveValue) {
                damperPedalWentOff();
            }
        }
        
        if(message.getControllerNumber() >= 0 && message.getControllerNumber() < 128) {
            if(message.getControllerNumber() == 1 && usesKeyboardModWheel_) {
                controllerValues_[message.getControllerNumber()] = message.getControllerValue();
                handleControlChangeRetransit(message.getControllerNumber(), message);
            }
            else if(message.getControllerNumber() >= 64 && message.getControllerNumber() <= 69
                     && usesKeyboardPedals_) {
                // MPE-TODO send this on master zone
                controllerValues_[message.getControllerNumber()] = message.getControllerValue();
                handleControlChangeRetransit(message.getControllerNumber(), message);
            }
            else if(usesKeyboardMidiControllers_) {
                controllerValues_[message.getControllerNumber()] = message.getControllerValue();
                handleControlChangeRetransit(message.getControllerNumber(), message);
            }
        }
    }
    else if(message.isChannelPressure()) {
        if(usesKeyboardChannelPressure_) {
            controllerValues_[kControlChannelAftertouch] = message.getChannelPressureValue();
            handleControlChangeRetransit(kControlChannelAftertouch, message);
        }
    }
    else if(message.isPitchWheel()) {
        if(usesKeyboardPitchWheel_) {
            if(mode_ == ModeMPE) {
                // MPE-TODO send this on master zone instead of putting it into the calculations
            }
            else {
                controllerValues_[kControlPitchWheel] = message.getPitchWheelValue();
                handleControlChangeRetransit(kControlPitchWheel, message);
            }
        }
    }
    else {
        // Process the message differently depending on the current mode
        switch(mode_) {
            case ModePassThrough:
                modePassThroughHandler(source, message);
                break;
            case ModeMonophonic:
                modeMonophonicHandler(source, message);
                break;
            case ModePolyphonic:
                modePolyphonicHandler(source, message);
                break;
            case ModeMPE:
                modeMPEHandler(source, message);
                break;
            case ModeOff:
            default:
                // Ignore message
                break;
        }
    }
}

// OscHandler method which parses incoming OSC messages we've registered for.  In this case,
// we use OSC callbacks to find out about touch data for notes we want to trigger.

bool MidiKeyboardSegment::oscHandlerMethod(const char *path, const char *types, int numValues, lo_arg **values, void *data) {
    if(touchkeyStandaloneMode_) {
        if(!strcmp(path, "/touchkeys/on") && numValues > 0) {
            int noteNumber = values[0]->i;
            if(!respondsToNote(noteNumber))
                return true;
            if(noteNumber >= 0 && noteNumber < 128) {
                // Generate MIDI note on for this message
                MidiMessage msg(MidiMessage::noteOn(1, noteNumber, (uint8)64));
                midiHandlerMethod(0, msg);
            }
            return true;
        }
        else if(!strcmp(path, "/touchkeys/off") && numValues > 0) {
            int noteNumber = values[0]->i;
            if(!respondsToNote(noteNumber))
                return true;
            if(noteNumber >= 0 && noteNumber < 128) {
                // Generate MIDI note off for this message
                MidiMessage msg(MidiMessage::noteOff(1, noteNumber));
                midiHandlerMethod(0, msg);
            }
            return true;
        }
    }
    
	if(mode_ == ModePolyphonic || mode_ == ModeMPE) {
		modePolyphonicMPENoteOnCallback(path, types, numValues, values);
	}
	
	return true;
}

// Control method via OSC. This comes in via MainApplicationController to MidiInputController
// and is used specifically for querying and modifying the status of the zone and its mappings,
// as opposed to the more frequent OSC messages to oscHandlerMethod() which provide touch and
// MIDI data. Return true if message was successfully handled.
OscMessage* MidiKeyboardSegment::oscControlMethod(const char *path, const char *types, int numValues, lo_arg **values, void *data) {
    // First check if this message is destined for a mapping within the segment
    // e.g. /mapping/my_mapping_name/message_for_mapping
    if(!strncmp(path, "/mapping/", 9) && strlen(path) > 9) {
        std::string subpath(&path[9]);
        
        int separatorLoc = subpath.find_first_of('/');
        if(separatorLoc == std::string::npos || separatorLoc == subpath.length() - 1) {
            // Malformed input (no slash or it's the last character): ignore
            return 0;
        }
        
        // Find the name of the mapping in the nextsegment
        std::string mappingName = subpath.substr(0, separatorLoc);
        
        // Look for a matching factory. TODO: this should probably be mutex-protected
        vector<MappingFactory*>::iterator it;
        for(it = mappingFactories_.begin(); it != mappingFactories_.end(); ++it) {
            if((*it)->getShortName() == mappingName) {
                std::string mappingAction = subpath.substr(separatorLoc);
                
                if(mappingAction == "/delete") {
                    removeMappingFactory(*it);
                    return OscTransmitter::createSuccessMessage();
                }
                else {
                    // Pass message to mapping factory here
                    OscMessage *response = (*it)->oscControlMethod(mappingAction.c_str(), types, numValues, values, data);
                    
                    // Prepend the mapping name to the response except in case of simple status response
                    if(response == 0)
                        return 0;
                    else if(!strcmp(response->path(), "/result"))
                        return response;
                    response->prependPath(mappingName.c_str());
                    response->prependPath("/mapping/");
                    return response;
                }
            }
        }
    }
    else if(!strcmp(path, "/list-mappings")) {
        // Return a list of mapping names and types
        // TODO: this should be mutex-protected
        
        OscMessage *response = OscTransmitter::createMessage("/list-mappings/result", "i", mappingFactories_.size(), LO_ARGS_END);
        
        vector<MappingFactory*>::iterator it;
        for(it = mappingFactories_.begin(); it != mappingFactories_.end(); ++it) {
            lo_message_add_string(response->message(), (*it)->getShortName().c_str());
        }
        
        return response;
    }
    else if(!strcmp(path, "/add-mapping")) {
        // Add a new mapping of a given type
        if(numValues >= 1) {
            if(types[0] == 'i') {
                int type = values[0]->i;
                
                if(type < 0 || type >= kNumMappingFactoryTypes)
                    return OscTransmitter::createFailureMessage();
 
                // Create mapping factory of the requested type
                MappingFactory *newFactory = createMappingFactoryForIndex(type);
                if(newFactory == 0)
                    return OscTransmitter::createFailureMessage();
 
                // Add the mapping factory to this segment, autogenerating the
                // name unless it is specified
                if(numValues >= 2) {
                    if(types[1] == 's') {
                        // Set the name as it was passed in
                        newFactory->setName(&values[1]->s);
                        addMappingFactory(newFactory, false);
                    }
                    else
                        addMappingFactory(newFactory, true);
                }
                else
                    addMappingFactory(newFactory, true);
                
                return OscTransmitter::createSuccessMessage();
            }
        }
    }
    else if(!strcmp(path, "/set-range")) {
        // Set the MIDI note range
        if(numValues >= 2) {
            if(types[0] == 'i' && types[1] == 'i') {
                int rangeLow = values[0]->i;
                int rangeHigh = values[1]->i;
                
                if(rangeLow < 0 || rangeLow > 127 || rangeHigh < 0 || rangeHigh > 127)
                    return OscTransmitter::createFailureMessage();
                if(rangeLow > rangeHigh) {
                    // Swap values so lowest one is always first
                    int temp = rangeLow;
                    rangeLow = rangeHigh;
                    rangeHigh = temp;
                }
                
                setNoteRange(rangeLow, rangeHigh);
                return OscTransmitter::createSuccessMessage();
            }
        }
    }
    else if(!strcmp(path, "/set-transpose")) {
        // Set the transposition of the output
        if(numValues >= 1) {
            if(types[0] == 'i') {
                int transpose = values[0]->i;
                
                if(transpose < -48 || transpose > 48)
                    return OscTransmitter::createFailureMessage();

                setOutputTransposition(transpose);
                return OscTransmitter::createSuccessMessage();
            }
        }
    }
    else if(!strcmp(path, "/set-transpose-octave-up")) {
        // Set the transposition of the output
        int transpose = outputTransposition() + 12;
        if(transpose > 48)
            transpose = 48;
        setOutputTransposition(transpose);

        return OscTransmitter::createSuccessMessage();
    }
    else if(!strcmp(path, "/set-transpose-octave-down")) {
        // Set the transposition of the output
        int transpose = outputTransposition() - 12;
        if(transpose < -48)
            transpose = -48;
        setOutputTransposition(transpose);
        
        return OscTransmitter::createSuccessMessage();
    }
    else if(!strcmp(path, "/set-controller-pass")) {
        // Set which controllers to pass through
        // Arguments: (channel pressure), (pitch wheel), (mod wheel), (pedals), (other CCs)
        
        if(numValues >= 5) {
            if(types[0] == 'i' && types[1] == 'i' && types[2] == 'i' && types[3] == 'i' && types[4] == 'i') {
                setUsesKeyboardChannelPressure(values[0]->i != 0);
                setUsesKeyboardPitchWheel(values[1]->i != 0);
                setUsesKeyboardModWheel(values[2]->i != 0);
                setUsesKeyboardPedals(values[3]->i != 0);
                setUsesKeyboardMIDIControllers(values[4]->i != 0);
                
                return OscTransmitter::createSuccessMessage();
            }
        }
    }
    else if(!strcmp(path, "/set-pitchwheel-range")) {
        // Set the MIDI pitchwheel range in semitones
        if(numValues >= 1) {
            if(types[0] == 'i') {
                int range = values[0]->i;
                
                setMidiPitchWheelRange(range);
                return OscTransmitter::createSuccessMessage();
            }
            else if(types[0] == 'f') {
                float range = values[0]->f;
                
                setMidiPitchWheelRange(range);
                return OscTransmitter::createSuccessMessage();
            }
        }
    }
    else if(!strcmp(path, "/send-pitchwheel-range")) {
        // Send an RPN value with the current pitchwheel range
        sendMidiPitchWheelRange();
        return OscTransmitter::createSuccessMessage();
    }
    else if(!strcmp(path, "/set-midi-mode")) {
        // Set the MIDI mode (mono, poly etc.)
        if(numValues >= 1) {
            if(types[0] == 's') {
                char *mode = &values[0]->s;
                
                if(!strcmp(mode, "off"))
                    setModeOff();
                else if(!strncmp(mode, "pass", 4))
                    setModePassThrough();
                else if(!strncmp(mode, "mono", 4))
                    setModeMonophonic();
                else if(!strncmp(mode, "poly", 4))
                    setModePolyphonic();
                else if(!strncmp(mode, "mpe", 3))
                    setModeMPE();
                else
                    return OscTransmitter::createFailureMessage();

                return OscTransmitter::createSuccessMessage();
            }
        }
    }
    else if(!strcmp(path, "/set-midi-channels")) {
        // Set the MIDI channels
        if(numValues >= 2) {
            if(types[0] == 'i' && types[1] == 'i') {
                int channelLow = values[0]->i;
                int channelHigh = values[1]->i;
                
                if(channelLow < 1 || channelLow > 16 || channelHigh < 1 || channelHigh > 16)
                    return OscTransmitter::createFailureMessage();
                if(channelLow > channelHigh) {
                    // Swap values so lowest one is always first
                    int temp = channelLow;
                    channelLow = channelHigh;
                    channelHigh = temp;
                }
                
                setOutputChannelLowest(channelLow - 1); // 1-16 --> 0-15 indexing
                int polyphony = channelHigh - channelLow + 1;
                if(polyphony < 1)
                    polyphony = 1;
                setPolyphony(polyphony);
                
                return OscTransmitter::createSuccessMessage();
            }
        }
    }
    else if(!strcmp(path, "/set-midi-stealing")) {
        // Set whether MIDI voice stealing is enabled
        if(numValues >= 1) {
            if(types[0] == 'i') {
                setVoiceStealingEnabled(values[0]->i != 0);
                return OscTransmitter::createSuccessMessage();
            }
        }
    }

    // No match
    return 0;
}

// Acquire an OSC-MIDI converter. If a converter for this control already exists,
// return it. If not, create it. This method keeps track of how many objects have
// acquired the converter. When all acquirers have released ihe converter, it is
// destroyed.
OscMidiConverter* MidiKeyboardSegment::acquireOscMidiConverter(int controlId) {
    OscMidiConverter *converter;

    if(oscMidiConverters_.count(controlId) == 0) {
        converter = new OscMidiConverter(keyboard_, *this, controlId);
        converter->setMidiOutputController(midiOutputController_);
        
        oscMidiConverters_[controlId] = converter;
        oscMidiConverterReferenceCounts_[controlId] = 1;
    }
    else {
        if(oscMidiConverterReferenceCounts_.count(controlId) == 0) {
            cerr << "BUG: found a converter with missing reference counter\n";
        }
        else if(oscMidiConverterReferenceCounts_[controlId] <= 0) {
            cerr << "BUG: found a converter with no references\n";
            oscMidiConverterReferenceCounts_[controlId] = 1;
        }
        else
            oscMidiConverterReferenceCounts_[controlId]++;
        converter = oscMidiConverters_[controlId];
    }
    
    return converter;
}

// Release a previously acquired OSC-MIDI converter. This call must be paired with
// acquireOscMidiConverter.
void MidiKeyboardSegment::releaseOscMidiConverter(int controlId) {
    if(oscMidiConverters_.count(controlId) == 0 ||
       oscMidiConverterReferenceCounts_.count(controlId) == 0) {
        cerr << "BUG: releasing a missing OSC-MIDI converter\n";
        return;
    }
    
    oscMidiConverterReferenceCounts_[controlId]--;
    if(oscMidiConverterReferenceCounts_[controlId] == 0) {
        // This was the last release of this converter. Delete it.
        OscMidiConverter *converter = oscMidiConverters_[controlId];
        delete converter;
        oscMidiConverters_.erase(controlId);
        oscMidiConverterReferenceCounts_.erase(controlId);
    }
}

// Helper predicate function for filtering strings
inline bool char_is_not_alphanumeric(int c) {
#ifdef _MSC_VER
	return !isalnum(c);
#else
    return !std::isalnum(c);
#endif
}

// Return the number of mapping factory types available
int MidiKeyboardSegment::numberOfMappingFactories() {
    return kNumMappingFactoryTypes;
}

// Return the name of the given mapping factory type
String MidiKeyboardSegment::mappingFactoryNameForIndex(int index) {
    if(index < 0 || index >= kNumMappingFactoryTypes)
        return String();
    return kMappingFactoryNames[index];
}

// Return a new object of the given mapping factory type
MappingFactory* MidiKeyboardSegment::createMappingFactoryForIndex(int index) {
    switch(index) {
        case 0:
            return new TouchkeyControlMappingFactory(keyboard_, *this);
        case 1:
            return new TouchkeyVibratoMappingFactory(keyboard_, *this);
        case 2:
            return new TouchkeyPitchBendMappingFactory(keyboard_, *this);
        case 3:
            return new TouchkeyKeyDivisionMappingFactory(keyboard_, *this);
        case 4:
            return new TouchkeyMultiFingerTriggerMappingFactory(keyboard_, *this);
        case 5:
            return new TouchkeyOnsetAngleMappingFactory(keyboard_, *this);
        case 6:
            return new TouchkeyReleaseAngleMappingFactory(keyboard_, *this);
        default:
            return 0;
    }
}

// Return whethera  given mapping is experimental or not
bool MidiKeyboardSegment::mappingIsExperimental(int index) {
    if(index == 5)
        return true;
    return false;
}

// Create a new mapping factory for this segment. A pointer should be passed in
// of a newly-allocated object. It will be released upon removal.
void MidiKeyboardSegment::addMappingFactory(MappingFactory* factory, bool autoGenerateName) {
    // Check for duplicates-- can't add the same factory twice
    vector<MappingFactory*>::iterator it;
    for(it = mappingFactories_.begin(); it != mappingFactories_.end(); ++it) {
        if(*it == factory)
            return;
    }
    
    // If the name should autogenerate, find a unique name for this factory
    if(autoGenerateName) {
        std::string baseName = factory->factoryTypeName();
        
        // Remove spaces, newlines, other invalid characters, leaving only alphanumerics
        baseName.erase(std::remove_if(baseName.begin(), baseName.end(), char_is_not_alphanumeric),
                       baseName.end());
        std::transform(baseName.begin(), baseName.end(), baseName.begin(), ::tolower);

        // Now look for an OSC path with this name. If found, add a number to the end, incrementing
        // it until a unique name is found
        std::string name = baseName;
        bool isUnique = false;
        int appendDigit = 2;
        
        while(!isUnique) {
            isUnique = true;
            
            for(int i = 0; i < mappingFactories_.size(); i++) {
                std::string compareName = mappingFactories_[i]->getName();
                int lastSeparator = compareName.find_last_of('/');
                if((lastSeparator != std::string::npos) && (lastSeparator < compareName.size() - 1))
                    compareName = compareName.substr(lastSeparator + 1);
                
                if(name == compareName) {
                    isUnique = false;
                    
                    // Try a new name with a new digit at the end...
                    std::stringstream ss;
                    ss << baseName << appendDigit;
                    name = ss.str();
                    appendDigit++;
                    
                    break;
                }
            }
        }
        
        factory->setName(name);
    }
    
    // Add factory to internal vector, and add it to splitter class
    mappingFactories_.push_back(factory);
    mappingFactorySplitter_.addFactory(factory);
    mappingFactoryUniqueIdentifier_++;
}

// Remove a mapping factory, releasing the associated object.
void MidiKeyboardSegment::removeMappingFactory(MappingFactory* factory) {
    vector<MappingFactory*>::iterator it;
    
    for(it = mappingFactories_.begin(); it != mappingFactories_.end(); ++it) {
        if(*it == factory) {
            mappingFactorySplitter_.removeFactory(factory);
            delete factory;
            mappingFactories_.erase(it);
            break;
        }
    }
    
    mappingFactoryUniqueIdentifier_++;
}

// Remove all mapping factories, releasing each one
void MidiKeyboardSegment::removeAllMappingFactories() {
    vector<MappingFactory*>::iterator it;
    
    mappingFactorySplitter_.removeAllFactories();
    for(it = mappingFactories_.begin(); it != mappingFactories_.end(); ++it) {
        delete *it;
    }
    
    mappingFactories_.clear();
    mappingFactoryUniqueIdentifier_++;
}

// Return a list of current mapping factories.
vector<MappingFactory*> const& MidiKeyboardSegment::mappingFactories(){
    return mappingFactories_;
}

// Return the specific index of a mapping factory for this segment
int MidiKeyboardSegment::indexOfMappingFactory(MappingFactory *factory) {
    vector<MappingFactory*>::iterator it;
    int i = 0;
    
    for(it = mappingFactories_.begin(); it != mappingFactories_.end(); ++it) {
        if(*it == factory)
            return i;
        i++;
    }
    
    return -1;
}

// Get an XML element describing current settings (for saving presets)
// This element will need to be released (or added to another XML element
// that is released) by the caller
XmlElement* MidiKeyboardSegment::getPreset() {
    XmlElement* segmentElement = new XmlElement("Segment");

    // Add segment settings
    PropertySet properties;
    properties.setValue("outputPort", outputPortNumber_);
    properties.setValue("mode", mode_);
    properties.setValue("channelMask", (int)channelMask_);
    properties.setValue("noteMin", noteMin_);
    properties.setValue("noteMax", noteMax_);
    properties.setValue("outputChannelLowest", outputChannelLowest_);
    properties.setValue("outputTransposition", outputTransposition_);
    properties.setValue("damperPedalEnabled", damperPedalEnabled_);
    // Don't set standalone mode; that's an input parameter
    properties.setValue("usesKeyboardChannelPressure", usesKeyboardChannelPressure_);
    properties.setValue("usesKeyboardPitchWheel", usesKeyboardPitchWheel_);
    properties.setValue("usesKeyboardModWheel", usesKeyboardModWheel_);
    properties.setValue("usesKeyboardPedals", usesKeyboardPedals_);
    properties.setValue("usesKeyboardMidiControllers", usesKeyboardMidiControllers_);
    properties.setValue("pitchWheelRange", pitchWheelRange_);
    properties.setValue("retransmitMaxPolyphony", retransmitMaxPolyphony_);
    properties.setValue("useVoiceStealing", useVoiceStealing_);

    segmentElement->addChildElement(properties.createXml("Properties"));
    
    // Go through mapping factories and add their settings
    vector<MappingFactory*>::iterator it;
    for(it = mappingFactories_.begin(); it != mappingFactories_.end(); ++it) {
        XmlElement* factoryElement = (*it)->getPreset();
        segmentElement->addChildElement(factoryElement);
    }
    
    return segmentElement;
}

// Load settings from an XML element
bool MidiKeyboardSegment::loadPreset(XmlElement const* preset) {
    removeAllMappingFactories();
    
    XmlElement *propertiesElement = preset->getChildByName("Properties");
    if(propertiesElement == 0)
        return false;
    
    // Load segment settings
    PropertySet properties;
    properties.restoreFromXml(*propertiesElement);
    
    if(!properties.containsKey("outputPort"))
        return false;
    outputPortNumber_ = properties.getIntValue("outputPort");
    if(!properties.containsKey("mode"))
        return false;
    int mode = properties.getIntValue("mode");
    // Setting the mode affects a few other variables so use the
    // functions rather than setting mode_ directly
    if(mode == ModePassThrough)
        setModePassThrough();
    else if(mode == ModeMonophonic)
        setModeMonophonic();
    else if(mode == ModePolyphonic)
        setModePolyphonic();
    else if(mode == ModeMPE)
        setModeMPE();
    else // Off or unknown
        setModeOff();
    if(!properties.containsKey("channelMask"))
        return false;
    channelMask_ = properties.getIntValue("channelMask");
    if(!properties.containsKey("noteMin"))
        return false;
    noteMin_ = properties.getIntValue("noteMin");
    if(!properties.containsKey("noteMax"))
        return false;
    noteMax_ = properties.getIntValue("noteMax");
    if(!properties.containsKey("outputChannelLowest"))
        return false;
    outputChannelLowest_ = properties.getIntValue("outputChannelLowest");
    if(!properties.containsKey("outputTransposition"))
        return false;
    outputTransposition_ = properties.getIntValue("outputTransposition");
    if(!properties.containsKey("damperPedalEnabled"))
        return false;
    damperPedalEnabled_ = properties.getBoolValue("damperPedalEnabled");
    if(!properties.containsKey("usesKeyboardChannelPressure"))
        return false;
    usesKeyboardChannelPressure_ = properties.getBoolValue("usesKeyboardChannelPressure");
    if(!properties.containsKey("usesKeyboardPitchWheel"))
        return false;
    usesKeyboardPitchWheel_ = properties.getBoolValue("usesKeyboardPitchWheel");
    if(!properties.containsKey("usesKeyboardModWheel"))
        return false;
    usesKeyboardModWheel_ = properties.getBoolValue("usesKeyboardModWheel");
    if(properties.containsKey("usesKeyboardPedals"))
        usesKeyboardPedals_ = properties.getBoolValue("usesKeyboardPedals");
    else
        usesKeyboardPedals_ = false;    // For backwards compatibility with older versions
    if(!properties.containsKey("usesKeyboardMidiControllers"))
        return false;
    usesKeyboardMidiControllers_ = properties.getBoolValue("usesKeyboardMidiControllers");
    if(!properties.containsKey("pitchWheelRange"))
        return false;
    pitchWheelRange_ = properties.getDoubleValue("pitchWheelRange");
    if(!properties.containsKey("retransmitMaxPolyphony"))
        return false;
    setPolyphony(properties.getIntValue("retransmitMaxPolyphony"));
    if(!properties.containsKey("useVoiceStealing"))
        return false;
    useVoiceStealing_ = properties.getBoolValue("useVoiceStealing");
    
    // Load each mapping factory
    XmlElement *element = preset->getChildByName("MappingFactory");
    
    while(element != 0) {
        if(!element->hasAttribute("type"))
            return false;
        
        // Create a new factory whose type depends on the XML tag
        MappingFactory *factory;
        String const& factoryType = element->getStringAttribute("type");
        
        if(factoryType == "Control")
            factory = new TouchkeyControlMappingFactory(keyboard_, *this);
        else if(factoryType == "Vibrato")
            factory = new TouchkeyVibratoMappingFactory(keyboard_, *this);
        else if(factoryType == "PitchBend")
            factory = new TouchkeyPitchBendMappingFactory(keyboard_, *this);
        else if(factoryType == "KeyDivision")
            factory = new TouchkeyKeyDivisionMappingFactory(keyboard_, *this);
        else if(factoryType == "MultiFingerTrigger")
            factory = new TouchkeyMultiFingerTriggerMappingFactory(keyboard_, *this);
        else if(factoryType == "OnsetAngle")
            factory = new TouchkeyOnsetAngleMappingFactory(keyboard_, *this);
        else if(factoryType == "ReleaseAngle")
            factory = new TouchkeyReleaseAngleMappingFactory(keyboard_, *this);
        else {
            // Type unknown or unsupported; ignore and continue
            element = element->getNextElementWithTagName("MappingFactory");
            continue;
        }
        
        // Tell factory to load its settings from this element
        if(!factory->loadPreset(element)) {
            delete factory;
            return false;
        }
        
        // Add factory; don't autogenerate name as it will be saved
        addMappingFactory(factory, false);
        
        element = element->getNextElementWithTagName("MappingFactory");
    }
    
    return true;
}

// Mode-specific MIDI handlers.  These methods handle incoming MIDI data according to the rules
// defined by a particular mode of operation.

// Pass-Through: Retransmit any input data to the output unmodified.
void MidiKeyboardSegment::modePassThroughHandler(MidiInput* source, const MidiMessage& message) {
    // Check if there is a note on or off, and update the keyboard class accordingly
    if(message.isNoteOn()) {
        int note = message.getNoteNumber();
        if(keyboard_.key(note) != 0)
            keyboard_.key(note)->midiNoteOn(this, message.getVelocity(), message.getChannel() - 1,
                                            keyboard_.schedulerCurrentTimestamp());
        
        // Retransmit, possibly with transposition
        if(midiOutputController_ != 0) {
            MidiMessage newMessage = MidiMessage::noteOn(message.getChannel(), message.getNoteNumber() + outputTransposition_, message.getVelocity());
            midiOutputController_->sendMessage(outputPortNumber_, newMessage);
        }
    }
    else if(message.isNoteOff()) {
        int note = message.getNoteNumber();
        if(keyboard_.key(note) != 0)
            keyboard_.key(note)->midiNoteOff(this, keyboard_.schedulerCurrentTimestamp());
        
        // Retransmit, possibly with transposition
        if(midiOutputController_ != 0) {
            MidiMessage newMessage = MidiMessage::noteOff(message.getChannel(), message.getNoteNumber() + outputTransposition_);
            midiOutputController_->sendMessage(outputPortNumber_, newMessage);
        }
    }
    else if(message.isAftertouch()) { // Polyphonic aftertouch: adjust to transposition
        if(midiOutputController_ != 0) {
            MidiMessage newMessage = MidiMessage::aftertouchChange(message.getChannel(), message.getNoteNumber() + outputTransposition_, message.getAfterTouchValue());
            midiOutputController_->sendMessage(outputPortNumber_, newMessage);
        }
    }
    else if(midiOutputController_ != 0) // Anything else goes through unchanged
        midiOutputController_->sendMessage(outputPortNumber_, message);
}

// Monophonic: all MIDI messages pass through to the output, which is assumed to be a monosynth.
// However the most recent key which determines the currently sounding note will have its mapping
// active; all others are suspended.
void MidiKeyboardSegment::modeMonophonicHandler(MidiInput* source, const MidiMessage& message) {
    if(message.isNoteOn()) {
        // First suspend any other mappings. This might include the current note if the touch
        // data has caused a mapping to be created.
        if(keyboard_.mappingFactory(this) != 0) {
            keyboard_.mappingFactory(this)->suspendAllMappings();
        }
        
        // And turn on note on MIDI controller
        if(midiOutputController_ != 0) {
            MidiMessage newMessage = MidiMessage::noteOn(message.getChannel(), message.getNoteNumber() + outputTransposition_, message.getVelocity());
            midiOutputController_->sendMessage(outputPortNumber_, newMessage);
        }
        
        // Now start the next one
        int note = message.getNoteNumber();
        if(keyboard_.key(note) != 0)
            keyboard_.key(note)->midiNoteOn(this, message.getVelocity(),
                                            message.getChannel() - 1, keyboard_.schedulerCurrentTimestamp());
        
        // Now resume the current note's mapping
        if(keyboard_.mappingFactory(this) != 0) {
            keyboard_.mappingFactory(this)->resumeMapping(note, true);
        }
    }
    else if(message.isNoteOff()) {
        // First stop this note
        int note = message.getNoteNumber();
        if(keyboard_.key(note) != 0)
            keyboard_.key(note)->midiNoteOff(this, keyboard_.schedulerCurrentTimestamp());
        
        // Then reactivate the most recent note's mappings
        if(keyboard_.mappingFactory(this) != 0) {
            int newest = newestNote();
            if(newest >= 0)
                keyboard_.mappingFactory(this)->resumeMapping(newest, true);
        }
        
        // And turn off note on MIDI controller
        if(midiOutputController_ != 0) {
            MidiMessage newMessage = MidiMessage::noteOff(message.getChannel(), message.getNoteNumber() + outputTransposition_, message.getVelocity());
            midiOutputController_->sendMessage(outputPortNumber_, newMessage);
        }
    }
}

// Polyphonic: Each incoming note gets its own unique MIDI channel so its controllers
// can be manipulated separately (e.g. by touchkey data).  Keep track of available channels
// and currently active notes.
void MidiKeyboardSegment::modePolyphonicHandler(MidiInput* source, const MidiMessage& message) {
	
    if(message.getRawDataSize() <= 0)
        return;
    const unsigned char *rawData = message.getRawData();
    
	if(rawData[0] == kMidiMessageReset) {
		// Reset state and pass along to all relevant channels
		
		retransmitChannelForNote_.clear();	// Clear current note information
		retransmitChannelsAvailable_.clear();
        retransmitNotesHeldInPedal_.clear();
		for(int i = 0; i < retransmitMaxPolyphony_; i++) {
			retransmitChannelsAvailable_.insert(i);
		}
		if(midiOutputController_ != 0)
			midiOutputController_->sendReset(outputPortNumber_);
	}
    else if(message.isNoteOn()) {
        if(retransmitChannelForNote_.count(message.getNoteNumber()) > 0
           && retransmitNotesHeldInPedal_.count(message.getNoteNumber()) == 0) {
            // Case (2)-- retrigger an existing note
            if(midiOutputController_ != 0) {
                midiOutputController_->sendNoteOn(outputPortNumber_, retransmitChannelForNote_[message.getNoteNumber()],
                                                  message.getNoteNumber() + outputTransposition_, message.getVelocity());
            }
        }
        else {
            // New note
            modePolyphonicNoteOn(message.getNoteNumber(), message.getVelocity());
        }
    }
    else if(message.isNoteOff()) {
        modePolyphonicNoteOff(message.getNoteNumber());
    }
    else if(message.isAllNotesOff() || message.isAllSoundOff()) {
        retransmitChannelForNote_.clear();	// Clear current note information
        retransmitChannelsAvailable_.clear();
        retransmitNotesHeldInPedal_.clear();
        for(int i = 0; i < retransmitMaxPolyphony_; i++)
            retransmitChannelsAvailable_.insert(i);
    }
    else if(message.isAftertouch()) { // polyphonic aftertouch
        if(retransmitChannelForNote_.count(message.getNoteNumber()) > 0) {
            int retransmitChannel = retransmitChannelForNote_[message.getNoteNumber()];
            if(midiOutputController_ != 0) {
                midiOutputController_->sendAftertouchPoly(outputPortNumber_, retransmitChannel,
                                                          message.getNoteNumber() + outputTransposition_, message.getAfterTouchValue());
            }
        }
    }
}

// Handle note on message in polyphonic mode.  Allocate a new channel
// for this note and rebroadcast it.
void MidiKeyboardSegment::modePolyphonicNoteOn(unsigned char note, unsigned char velocity) {
    int newChannel = -1;
    
#ifdef DEBUG_MIDI_KEYBOARD_SEGMENT
    cout << "Channels available: ";
    for(set<int>::iterator it = retransmitChannelsAvailable_.begin();
        it != retransmitChannelsAvailable_.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "Channels allocated: ";
    for(map<int, int>::iterator it = retransmitChannelForNote_.begin();
        it != retransmitChannelForNote_.end(); ++it) {
        cout << it->second << "(" << it->first << ") ";
    }
    cout << endl;
#endif
    
    if(retransmitNotesHeldInPedal_.count(note) > 0) {
        // For notes that are still sounding in the pedal, reuse the same MIDI channel
        // they had before.
        if(retransmitChannelForNote_.count(note) > 0)
            newChannel = retransmitChannelForNote_[note];
        else {
#ifdef DEBUG_MIDI_KEYBOARD_SEGMENT
            cout << "BUG: note " << note << " held in pedal but has no channel\n";
#endif
            retransmitNotesHeldInPedal_.erase(note);
            return;
        }
        
        // No longer held in pedal: it will be an active note again with the same channel
        retransmitNotesHeldInPedal_.erase(note);
    }
    else {
        // Otherwise, allocate a new channel to this note
        if(retransmitChannelsAvailable_.size() == 0) {
            if(damperPedalEnabled_) {
                // First priority is always to take a note that is being sustained
                // in the pedal but not actively held. This is true whether or not
                // voice stealing is enabled.
                int oldNote = oldestNoteInPedal();
                int oldChannel = -1;
                if(retransmitChannelForNote_.count(oldNote) > 0)
                    oldChannel = retransmitChannelForNote_[oldNote];
                if(oldNote >= 0) {
#ifdef DEBUG_MIDI_KEYBOARD_SEGMENT
                    cout << "Stealing note " << oldNote << " from pedal for note " << (int)note << endl;
#endif
                    modePolyphonicNoteOff(oldNote, true);
                }
            }
            
            // Now try again...
            if(retransmitChannelsAvailable_.size() == 0) {
                if(useVoiceStealing_) {
                    // Find the voice with the oldest timestamp and turn it off
                    int oldNote = oldestNote();
                    int oldChannel = -1;
                    if(retransmitChannelForNote_.count(oldNote) > 0)
                        oldChannel = retransmitChannelForNote_[oldNote];
                    if(oldNote < 0) {
                        // Shouldn't happen...
#ifdef DEBUG_MIDI_KEYBOARD_SEGMENT
                        cout << "No notes present, but no MIDI output channel available for note " << (int)note << endl;
#endif
                        return;
                    }
#ifdef DEBUG_MIDI_KEYBOARD_SEGMENT
                    cout << "Stealing note " << oldNote << " for note " << (int)note << endl;
#endif
                    modePolyphonicNoteOff(oldNote, true);
                }
                else {
                    // No channels available.  Print a warning and finish
#ifdef DEBUG_MIDI_KEYBOARD_SEGMENT
                    cout << "No MIDI output channel available for note " << (int)note << endl;
#endif
                    return;
                }
            }
        }
        
        // Request the first available channel
        newChannel = *retransmitChannelsAvailable_.begin();
        retransmitChannelsAvailable_.erase(newChannel);
        retransmitChannelForNote_[note] = newChannel;
	}
    
	if(keyboard_.key(note) != 0) {
		keyboard_.key(note)->midiNoteOn(this, velocity, newChannel, keyboard_.schedulerCurrentTimestamp());
	}
	
	// The above function will cause a callback to be generated, which in turn will generate
	// the Note On message.
}

// Handle note off message in polyphonic mode.  Release any channel
// associated with this note.
void MidiKeyboardSegment::modePolyphonicNoteOff(unsigned char note, bool forceOff) {    
	// If no channel associated with this note, ignore it
	if(retransmitChannelForNote_.count(note) == 0) {
        if(note >= 0 && note < 128)
            noteOnsetTimestamps_[note] = 0;
		return;
    }
    
	if(keyboard_.key(note) != 0) {
		keyboard_.key(note)->midiNoteOff(this, keyboard_.schedulerCurrentTimestamp());
	}

    int oldNoteChannel = retransmitChannelForNote_[note];
    
    if(midiOutputController_ != 0) {
        if(forceOff) {
            // To silence a note, we need to clear any pedals that might be holding it
            if(controllerValues_[kMidiControllerDamperPedal] >= kPedalActiveValue) {
                midiOutputController_->sendControlChange(outputPortNumber_, oldNoteChannel,
                                                         kMidiControllerDamperPedal, 0);
            }
            if(controllerValues_[kMidiControllerSostenutoPedal] >= kPedalActiveValue) {
                midiOutputController_->sendControlChange(outputPortNumber_, oldNoteChannel,
                                                         kMidiControllerSostenutoPedal, 0);
            }
            
            // Send All Notes Off and All Sound Off
            midiOutputController_->sendControlChange(outputPortNumber_, oldNoteChannel, kMidiControlAllNotesOff, 0);
            midiOutputController_->sendControlChange(outputPortNumber_, oldNoteChannel, kMidiControlAllSoundOff, 0);
        }
        else {
            // Send a Note Off message to the appropriate channel
            midiOutputController_->sendNoteOff(outputPortNumber_, oldNoteChannel, note + outputTransposition_);
        }
    }
    
    // If the pedal is enabled and currently active, don't re-enable this channel
    // just yet. Instead, let the note continue ringing until we have to steal it later.
    if(damperPedalEnabled_ && controllerValues_[kMidiControllerDamperPedal] >= kPedalActiveValue && !forceOff) {
        retransmitNotesHeldInPedal_.insert(note);
    }
    else {
        // Otherwise release the channel mapping associated with this note
        if(retransmitNotesHeldInPedal_.count(note) > 0)
            retransmitNotesHeldInPedal_.erase(note);
        retransmitChannelsAvailable_.insert(retransmitChannelForNote_[note]);
        retransmitChannelForNote_.erase(note);
        if(note >= 0 && note < 128)
            noteOnsetTimestamps_[note] = 0;
    }
    
    if(forceOff) {
        // Now re-enable any pedals that we might have temporarily lifted on this channel
        if(controllerValues_[kMidiControllerDamperPedal] >= kPedalActiveValue) {
            midiOutputController_->sendControlChange(outputPortNumber_, oldNoteChannel,
                                                     kMidiControllerDamperPedal,
                                                     controllerValues_[kMidiControllerDamperPedal]);
        }
        if(controllerValues_[kMidiControllerSostenutoPedal] >= kPedalActiveValue) {
            midiOutputController_->sendControlChange(outputPortNumber_, oldNoteChannel,
                                                     kMidiControllerSostenutoPedal,
                                                     controllerValues_[kMidiControllerSostenutoPedal]);
        }
    }
}

// Callback function after we request a note on.  PianoKey class will respond
// with touch data (if available within a specified timeout), or with a frame
// indicating an absence of touch data.  Once we receive this, we can send the
// MIDI note on message.

void MidiKeyboardSegment::modePolyphonicMPENoteOnCallback(const char *path, const char *types, int numValues, lo_arg **values) {
	if(numValues < 3)	// Sanity check: first 3 values hold MIDI information
		return;
	if(types[0] != 'i' || types[1] != 'i' || types[2] != 'i')
		return;
	
	int midiNote = values[0]->i;
	int midiChannel = values[1]->i;
	int midiVelocity = values[2]->i;
	
	if(midiNote < 0 || midiNote > 127)
		return;
    // If there are multiple segments of the keyboard active, there may be OSC
    // messages generated from keys that didn't come from us. Don't grab them by mistake.
    // FIXME: the real fix here is to include a source ID with the OSC message
    if(!respondsToNote(midiNote))
        return;
	
	// Send the Note On message to the correct channel
	if(midiOutputController_ != 0) {
		midiOutputController_->sendNoteOn(outputPortNumber_, midiChannel, midiNote + outputTransposition_, midiVelocity);
	}
}

// MPE (Multidimensional Polyphonic Expression): Each incoming note gets its own unique MIDI channel.
// Like polyphonic mode but implementing the details of the MPE specification which differ subtly
// from a straightforward polyphonic allocation
void MidiKeyboardSegment::modeMPEHandler(MidiInput* source, const MidiMessage& message) {
    // MPE-TODO
}

// Handle note on message in MPE mode.  Allocate a new channel
// for this note and rebroadcast it.
void MidiKeyboardSegment::modeMPENoteOn(unsigned char note, unsigned char velocity) {
    // MPE-TODO
    // allocate notes to channels like polyphonic mode, with certain changes:
    // -- round-robin as default rather than first available
    // -- different stealing behaviour:
    // ---- when no channels are available, add to an existing one with the fewest sounding notes
    // ---- old note doesn't need to be turned off, but it could(?) have its mappings disabled
}

// Private helper method to handle changes in polyphony
void MidiKeyboardSegment::modePolyphonicSetupHelper() {
    // Limit polyphony to 16 (number of MIDI channels) or fewer if starting above channel 1
    if(retransmitMaxPolyphony_ + outputChannelLowest_ > 16)
		retransmitMaxPolyphony_ = 16 - outputChannelLowest_;
    retransmitChannelsAvailable_.clear();
	for(int i = outputChannelLowest_; i < outputChannelLowest_ + retransmitMaxPolyphony_; i++)
		retransmitChannelsAvailable_.insert(i);
	retransmitChannelForNote_.clear();
    retransmitNotesHeldInPedal_.clear();
}

// Find the oldest onset of the currently playing notes. Used for voice stealing.
// Returns -1 if no notes are playing.
int MidiKeyboardSegment::oldestNote() {
    int oldestNoteNumber = -1;
    timestamp_type oldestTimestamp = missing_value<timestamp_type>::missing();
    
    for(int i = 0; i < 128; i++) {
        if(missing_value<timestamp_type>::isMissing(oldestTimestamp) && noteOnsetTimestamps_[i] != 0) {
            oldestNoteNumber = i;
            oldestTimestamp = noteOnsetTimestamps_[i];
        }
        else if(noteOnsetTimestamps_[i] < oldestTimestamp && noteOnsetTimestamps_[i] != 0) {
            oldestNoteNumber = i;
            oldestTimestamp = noteOnsetTimestamps_[i];
        }
    }
    
    return oldestNoteNumber;
}

// Finds the oldest onset of the notes currently finished but sustaining in the pedal.
// Used for voice stealing. Returns -1 if no notes are held in the pedal.
int MidiKeyboardSegment::oldestNoteInPedal() {
    if(!damperPedalEnabled_ || retransmitNotesHeldInPedal_.empty())
        return -1;
    
    set<int>::iterator it;
    int oldestNoteNumber = -1;
    timestamp_type oldestTimestamp = missing_value<timestamp_type>::missing();
    
#ifdef DEBUG_MIDI_KEYBOARD_SEGMENT
    cout << "notes in pedal: ";
#endif
    
    for(it = retransmitNotesHeldInPedal_.begin(); it != retransmitNotesHeldInPedal_.end(); ++it) {
        int note = *it;
        timestamp_type timestamp;
        if(noteOnsetTimestamps_[note] != 0)
            timestamp = noteOnsetTimestamps_[note];
        else
            timestamp = 0; // Why is there a note held in pedal with no onset? Steal it!
#ifdef DEBUG_MIDI_KEYBOARD_SEGMENT
        cout << note << " (" << timestamp << ") ";
#endif
        
        if(missing_value<timestamp_type>::isMissing(oldestTimestamp)) {
            oldestNoteNumber = note;
            oldestTimestamp = timestamp;
        }
        else if(timestamp < oldestTimestamp) {
            oldestNoteNumber = note;
            oldestTimestamp = timestamp;
        }
    }
#ifdef DEBUG_MIDI_KEYBOARD_SEGMENT
    cout << endl;
#endif
    
    return oldestNoteNumber;
}

// Find the newest onset of the currently playing notes. Used for monophonic mode.
// Returns -1 if no notes are playing.
int MidiKeyboardSegment::newestNote() {
    int newestNoteNumber = -1;
    timestamp_type newestTimestamp = missing_value<timestamp_type>::missing();
    
    for(int i = 0; i < 128; i++) {
        if(missing_value<timestamp_type>::isMissing(newestTimestamp) && noteOnsetTimestamps_[i] != 0) {
            newestNoteNumber = i;
            newestTimestamp = noteOnsetTimestamps_[i];
        }
        else if(noteOnsetTimestamps_[i] > newestTimestamp && noteOnsetTimestamps_[i] != 0) {
            newestNoteNumber = i;
            newestTimestamp = noteOnsetTimestamps_[i];
        }
    }
    
    return newestNoteNumber;
}

// Given a controller number (including special "controllers" channel-pressure and pitch-wheel),
// retransit or not to outgoing MIDI channels depending on the current behaviour defined in
// controllerActions_.
void MidiKeyboardSegment::handleControlChangeRetransit(int controllerNumber, const MidiMessage& message) {
    // MPE-TODO need a new mode for sending on master zone, e.g. for pitch wheel
    if(midiOutputController_ == 0)
        return;
    if(controllerActions_[controllerNumber] == kControlActionPassthrough) {
        // Tell OSC-MIDI converter to resend if present, otherwise pass through
        if(oscMidiConverters_.count(controllerNumber) != 0) {
            oscMidiConverters_[controllerNumber]->resend(message.getChannel() - 1);
        }
        else {
            // Send this control change through unchanged
            midiOutputController_->sendMessage(outputPortNumber_, message);
        }
    }
    else if(controllerActions_[controllerNumber] == kControlActionBroadcast) {
        // Send this control change to all active channels
        MidiMessage newMessage(message); // Modifiable copy of the original message
        
        if(oscMidiConverters_.count(controllerNumber) != 0) {
            for(int i = 0; i < retransmitMaxPolyphony_; i++)
                oscMidiConverters_[controllerNumber]->resend(i);
        }
        else {
            for(int i = 0; i < retransmitMaxPolyphony_; i++) {
                newMessage.setChannel(i + 1); // Juce uses 1-16, we use 0-15
                midiOutputController_->sendMessage(outputPortNumber_, newMessage);
            }
        }
    }
    else if(controllerActions_[controllerNumber] == kControlActionSendToLatest) {
        // Send this control change to the channel of the most recent note
        int noteNumber = newestNote();
        if(noteNumber < 0)
            return;
        if(keyboard_.key(noteNumber) != 0) {
            int channel = keyboard_.key(noteNumber)->midiChannel();
            
            if(oscMidiConverters_.count(controllerNumber) != 0)
                oscMidiConverters_[controllerNumber]->resend(channel);
            else {
                MidiMessage newMessage(message); // Modifiable copy of the original message
                newMessage.setChannel(channel + 1);  // Juce uses 1-16, we use 0-15
                midiOutputController_->sendMessage(outputPortNumber_, newMessage);
            }
        }
    }
    else {} // Block or unknown action
}

// Set all controllers to behave a particular way when messages received
void MidiKeyboardSegment::setAllControllerActionsTo(int action) {
    for(int i = 0; i < kControlMax; i++)
        controllerActions_[i] = action;
}

// Pedal went off. If we're saving notes in the pedal, release them
void MidiKeyboardSegment::damperPedalWentOff() {
    if(!damperPedalEnabled_)
        return;
    // Go through a list of any notes currently in the damper pedal and release them
    set<int>::iterator it;
    for(it = retransmitNotesHeldInPedal_.begin(); it != retransmitNotesHeldInPedal_.end(); ++it) {
        int note = *it;
#ifdef DEBUG_MIDI_KEYBOARD_SEGMENT
        cout << "releasing note " << note << " on channel " << retransmitChannelForNote_[note] << endl;
#endif
        retransmitChannelsAvailable_.insert(retransmitChannelForNote_[note]);
        retransmitChannelForNote_.erase(note);
        noteOnsetTimestamps_[note] = 0;
    }
    retransmitNotesHeldInPedal_.clear();
}

// Handle the actual sending of the pitch wheel range RPN to a specific channel
void MidiKeyboardSegment::sendMidiPitchWheelRangeHelper(int channel) {
    if(midiOutputController_ == 0)
        return;
    
    // Find number of semitones and cents
    int majorRange = (int)floorf(pitchWheelRange_);
    int minorRange = (int)(100.0 * (pitchWheelRange_ - floorf(pitchWheelRange_)));
    
    // Set RPN controller = 0
    midiOutputController_->sendControlChange(outputPortNumber_, channel, 101, 0);
    midiOutputController_->sendControlChange(outputPortNumber_, channel, 100, 0);
    // Set data value MSB/LSB for bend range in semitones
    midiOutputController_->sendControlChange(outputPortNumber_, channel, 6, majorRange);
    midiOutputController_->sendControlChange(outputPortNumber_, channel, 38, minorRange);
    // Set RPN controller back to 16383
    midiOutputController_->sendControlChange(outputPortNumber_, channel, 101, 127);
    midiOutputController_->sendControlChange(outputPortNumber_, channel, 100, 127);
}
