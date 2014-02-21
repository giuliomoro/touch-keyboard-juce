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

  TouchkeyPitchBendMappingFactory.cpp: factory for the pitch-bend mapping,
  which handles changing pitch based on relative finger motion.
*/

#include "TouchkeyPitchBendMappingFactory.h"
#include "TouchkeyPitchBendMappingShortEditor.h"

// Default constructor, containing a reference to the PianoKeyboard class.

TouchkeyPitchBendMappingFactory::TouchkeyPitchBendMappingFactory(PianoKeyboard &keyboard, MidiKeyboardSegment& segment) :
TouchkeyBaseMappingFactory<TouchkeyPitchBendMapping>(keyboard, segment),
bendRangeSemitones_(TouchkeyPitchBendMapping::kDefaultBendRangeSemitones),
bendThresholdSemitones_(TouchkeyPitchBendMapping::kDefaultBendThresholdSemitones),
bendThresholdKeyLength_(TouchkeyPitchBendMapping::kDefaultBendThresholdKeyLength),
bendMode_(TouchkeyPitchBendMapping::kDefaultPitchBendMode),
fixedModeMinEnableDistance_(TouchkeyPitchBendMapping::kDefaultFixedModeEnableDistance),
fixedModeBufferDistance_(TouchkeyPitchBendMapping::kDefaultFixedModeBufferDistance),
bendIgnoresTwoFingers_(TouchkeyPitchBendMapping::kDefaultIgnoresTwoFingers),
bendIgnoresThreeFingers_(TouchkeyPitchBendMapping::kDefaultIgnoresThreeFingers)
{
    // Set up the MIDI converter to use pitch wheel
    // setName("/touchkeys/pitchbend");
    setBendParameters();
}

// ***** Destructor *****

TouchkeyPitchBendMappingFactory::~TouchkeyPitchBendMappingFactory() {
    
}

// ***** Accessors / Modifiers *****

void TouchkeyPitchBendMappingFactory::setName(const string& name) {
    TouchkeyBaseMappingFactory<TouchkeyPitchBendMapping>::setName(name);
    setBendParameters();
}


// ***** Bend Methods *****

void TouchkeyPitchBendMappingFactory::setBendRange(float rangeSemitones, bool updateCurrent) {
    /*if(updateCurrent) {
     // Send new range to all active mappings
     // TODO: mutex protect
     std::map<int, mapping_pair>::iterator it = mappings_.begin();
     while(it != mappings_.end()) {
     // Tell this mapping to update its range
     TouchkeyPitchBendMapping *mapping = it->second.second;
     mapping->setRange(rangeSemitones);
     it++;
     }
     }*/
    
    bendRangeSemitones_ = rangeSemitones;
}

void TouchkeyPitchBendMappingFactory::setBendThresholdSemitones(float thresholdSemitones) {
    bendThresholdSemitones_ = thresholdSemitones;    
}

void TouchkeyPitchBendMappingFactory::setBendThresholdKeyLength(float thresholdKeyLength) {
    bendThresholdKeyLength_ = thresholdKeyLength;    
}

void TouchkeyPitchBendMappingFactory::setBendThresholds(float thresholdSemitones, float thresholdKeyLength, bool updateCurrent) {
    /*if(updateCurrent) {
     // Send new range to all active mappings
     // TODO: mutex protect
     std::map<int, mapping_pair>::iterator it = mappings_.begin();
     while(it != mappings_.end()) {
     // Tell this mapping to update its range
     TouchkeyPitchBendMapping *mapping = it->second.second;
     mapping->setThresholds(thresholdSemitones, thresholdKeyLength);
     it++;
     }
     }*/
    
    bendThresholdSemitones_ = thresholdSemitones;
    bendThresholdKeyLength_ = thresholdKeyLength;
}

// Set the mode to bend a fixed amount up and down the key, regardless of where
// the touch starts. minimumDistanceToEnable sets a floor below which the bend isn't
// possible (for starting very close to an edge) and bufferAtEnd sets the amount
// of key length beyond which no further bend takes place.
void TouchkeyPitchBendMappingFactory::setBendFixedEndpoints(float minimumDistanceToEnable, float bufferAtEnd) {
    bendMode_ = TouchkeyPitchBendMapping::kPitchBendModeFixedEndpoints;
    fixedModeMinEnableDistance_ = minimumDistanceToEnable;
    fixedModeBufferDistance_ = bufferAtEnd;
}

// Set the mode to bend an amount proportional to distance, which means
// that the total range of bend will depend on where the finger started.
void TouchkeyPitchBendMappingFactory::setBendVariableEndpoints() {
    bendMode_ = TouchkeyPitchBendMapping::kPitchBendModeVariableEndpoints;
}

void TouchkeyPitchBendMappingFactory::setBendIgnoresMultipleFingers(bool ignoresTwo, bool ignoresThree) {
    // TODO: update current
    bendIgnoresTwoFingers_ = ignoresTwo;
    bendIgnoresThreeFingers_ = ignoresThree;
}

// ***** GUI Support *****
MappingEditorComponent* TouchkeyPitchBendMappingFactory::createBasicEditor() {
    return new TouchkeyPitchBendMappingShortEditor(*this);
}

// ***** Private Methods *****

// Set the initial parameters for a new mapping
void TouchkeyPitchBendMappingFactory::initializeMappingParameters(int noteNumber, TouchkeyPitchBendMapping *mapping) {
    mapping->setRange(bendRangeSemitones_);
    mapping->setThresholds(bendThresholdSemitones_, bendThresholdKeyLength_);
    if(bendMode_ == TouchkeyPitchBendMapping::kPitchBendModeFixedEndpoints) {
        mapping->setFixedEndpoints(fixedModeMinEnableDistance_, fixedModeBufferDistance_);
    }
    else
        mapping->setVariableEndpoints();
    mapping->setIgnoresMultipleFingers(bendIgnoresTwoFingers_, bendIgnoresThreeFingers_);
}

void TouchkeyPitchBendMappingFactory::setBendParameters() {
    // Range of 0 indicates special case of using global pitch wheel range
    setMidiParameters(MidiKeyboardSegment::kControlPitchWheel, 0.0, 0.0, 0.0);
    
    if(midiConverter_ != 0) {
        midiConverter_->listenToIncomingControl(MidiKeyboardSegment::kControlPitchWheel);
    }
}
