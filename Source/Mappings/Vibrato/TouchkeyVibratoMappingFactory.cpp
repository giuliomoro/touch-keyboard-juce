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

  TouchkeyVibratoMappingFactory.cpp: factory for the vibrato mapping class,
  which creates vibrato through side-to-side motion of the finger on the
  key surface.
*/

#include "TouchkeyVibratoMappingFactory.h"
#include "TouchkeyVibratoMappingShortEditor.h"

// Class constants
const float TouchkeyVibratoMappingFactory::kDefaultPitchWheelRangeSemitones = 12.0;
const int TouchkeyVibratoMappingFactory::kDefaultVibratoControl = MidiKeyboardSegment::kControlPitchWheel;

// Default constructor, containing a reference to the PianoKeyboard class.

TouchkeyVibratoMappingFactory::TouchkeyVibratoMappingFactory(PianoKeyboard &keyboard, MidiKeyboardSegment& segment) :
TouchkeyBaseMappingFactory<TouchkeyVibratoMapping>(keyboard, segment), pitchWheelRangeSemitones_(kDefaultPitchWheelRangeSemitones),
vibratoControl_(kDefaultVibratoControl),
vibratoRange_(TouchkeyVibratoMapping::kDefaultVibratoRangeSemitones),
vibratoPrescaler_(TouchkeyVibratoMapping::kDefaultVibratoPrescaler),
vibratoTimeout_(TouchkeyVibratoMapping::kDefaultVibratoTimeout),
vibratoOnsetThresholdX_(TouchkeyVibratoMapping::kDefaultVibratoThresholdX),
vibratoOnsetThresholdY_(TouchkeyVibratoMapping::kDefaultVibratoThresholdY),
vibratoOnsetRatioX_(TouchkeyVibratoMapping::kDefaultVibratoRatioX),
vibratoOnsetRatioY_(TouchkeyVibratoMapping::kDefaultVibratoRatioY)
{    
    // Set up the MIDI converter to use pitch wheel
    configurePitchWheelVibrato();
}

// ***** Destructor *****

TouchkeyVibratoMappingFactory::~TouchkeyVibratoMappingFactory() {

}

// ***** Accessors / Modifiers *****

void TouchkeyVibratoMappingFactory::setMIDIPitchWheelRange(float maxBendSemitones) {
    if(maxBendSemitones <= 0)
        return;
    pitchWheelRangeSemitones_ = maxBendSemitones;
    
    if(vibratoControl_ != MidiKeyboardSegment::kControlPitchWheel)
        return;
    configurePitchWheelVibrato();
}

void TouchkeyVibratoMappingFactory::setName(const string& name) {
    TouchkeyBaseMappingFactory<TouchkeyVibratoMapping>::setName(name);
    setVibratoControl(vibratoControl_);
}

// ***** Vibrato Methods *****

void TouchkeyVibratoMappingFactory::setVibratoControl(int vibratoControl) {
    if(vibratoControl < 0 || vibratoControl >= MidiKeyboardSegment::kControlMax)
        return;
    
    // Update the variable which affects future mappings
    vibratoControl_ = vibratoControl;
    
    if(vibratoControl_ == MidiKeyboardSegment::kControlPitchWheel)
        configurePitchWheelVibrato();
    else
        configureControlChangeVibrato();
}

void TouchkeyVibratoMappingFactory::setVibratoRange(float range, bool updateCurrent) {
    /*if(updateCurrent) {
        // Send new range to all active mappings
        // TODO: mutex protect
        std::map<int, mapping_pair>::iterator it = mappings_.begin();
        while(it != mappings_.end()) {
            // Tell this mapping to update its range
            TouchkeyVibratoMapping *mapping = it->second.first;
            mapping->setRange(rangeSemitones);
            it++;
        }
    }*/
    
    // Update the variable which affects future mappings
    vibratoRange_ = range;
    if(vibratoRange_ < 0.01)
        vibratoRange_ = 0.01;
    if(vibratoRange_ > 127.0)
        vibratoRange_ = 127.0;
}

void TouchkeyVibratoMappingFactory::setVibratoPrescaler(float prescaler, bool updateCurrent) {
    /*if(updateCurrent) {
        // Send new range to all active mappings
        // TODO: mutex protect
        std::map<int, mapping_pair>::iterator it = mappings_.begin();
        while(it != mappings_.end()) {
            // Tell this mapping to update its range
            TouchkeyVibratoMapping *mapping = it->second.first;
            mapping->setPrescaler(prescaler);
            it++;
        }
    }*/
    
    // Update the variable which affects future mappings
    vibratoPrescaler_ = prescaler;
}

void TouchkeyVibratoMappingFactory::setVibratoThreshold(float threshold, bool updateCurrent) {
    vibratoOnsetThresholdX_ = threshold;
    if(vibratoOnsetThresholdX_ < 0)
        vibratoOnsetThresholdX_ = 0;
    if(vibratoOnsetThresholdX_ > 1.0)
        vibratoOnsetThresholdX_ = 1.0;
}

void TouchkeyVibratoMappingFactory::setVibratoThresholds(float thresholdX, float thresholdY, float ratioX, float ratioY, bool updateCurrent) {
    /*if(updateCurrent) {
        // Send new range to all active mappings
        // TODO: mutex protect
        std::map<int, mapping_pair>::iterator it = mappings_.begin();
        while(it != mappings_.end()) {
            // Tell this mapping to update its range
            TouchkeyVibratoMapping *mapping = it->second.first;
            mapping->setThresholds(thresholdX, thresholdY, ratioX, ratioY);
            it++;
        }
    }*/
    
    // Update the variables which affect future mappings
    vibratoOnsetThresholdX_ = thresholdX;
    vibratoOnsetThresholdY_ = thresholdY;
    vibratoOnsetRatioX_ = ratioX;
    vibratoOnsetRatioY_ = ratioY;
}

void TouchkeyVibratoMappingFactory::setVibratoTimeout(timestamp_diff_type timeout, bool updateCurrent) {
    /*if(updateCurrent) {
        // Send new range to all active mappings
        // TODO: mutex protect
        std::map<int, mapping_pair>::iterator it = mappings_.begin();
        while(it != mappings_.end()) {
            // Tell this mapping to update its range
            TouchkeyVibratoMapping *mapping = it->second.first;
            mapping->setTimeout(timeout);
            it++;
        }
    }*/
    
    // Update the variable which affects future mappings
    vibratoTimeout_ = timeout;
}

// ***** GUI Support *****
MappingEditorComponent* TouchkeyVibratoMappingFactory::createBasicEditor() {
    return new TouchkeyVibratoMappingShortEditor(*this);
}

// ***** Private Methods *****

// Set the initial parameters for a new mapping
void TouchkeyVibratoMappingFactory::initializeMappingParameters(int noteNumber, TouchkeyVibratoMapping *mapping) {
    mapping->setRange(vibratoRange_);
    mapping->setPrescaler(vibratoPrescaler_);
    mapping->setThresholds(vibratoOnsetThresholdX_, vibratoOnsetThresholdY_, vibratoOnsetRatioX_, vibratoOnsetRatioY_);
    mapping->setTimeout(vibratoTimeout_);
}

// Configure the OSC-MIDI converter to handle pitchwheel vibrato
void TouchkeyVibratoMappingFactory::configurePitchWheelVibrato() {
    setMidiParameters(MidiKeyboardSegment::kControlPitchWheel, -pitchWheelRangeSemitones_, pitchWheelRangeSemitones_, 0.0);
    
    if(midiConverter_ != 0) {
        midiConverter_->setMidiPitchWheelRange(pitchWheelRangeSemitones_);
        midiConverter_->listenToIncomingControl(MidiKeyboardSegment::kControlPitchWheel);
    }
}

// Configure the OSC-MIDI converter to handle vibrato based on a CC
void TouchkeyVibratoMappingFactory::configureControlChangeVibrato() {
    setMidiParameters(vibratoControl_, 0.0, 127.0, 0.0, 0, 0, 127, 0, false, OscMidiConverter::kOutOfRangeExtrapolate);
    
    if(midiConverter_ != 0) {
        midiConverter_->listenToIncomingControl(vibratoControl_);
    }
}


