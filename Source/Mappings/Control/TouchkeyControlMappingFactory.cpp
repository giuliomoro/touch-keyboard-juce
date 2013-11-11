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

  TouchkeyControlMappingFactory.cpp: factory for the TouchKeys control
  mapping, which converts an arbitrary touch parameter into a MIDI or
  OSC control message.
*/

#include "TouchkeyControlMappingFactory.h"
#include "TouchkeyControlMappingShortEditor.h"

const int TouchkeyControlMappingFactory::kDefaultController = 1;
const float TouchkeyControlMappingFactory::kDefaultOutputRangeMin = 0.0;
const float TouchkeyControlMappingFactory::kDefaultOutputRangeMax = 127.0;
const float TouchkeyControlMappingFactory::kDefaultOutputDefault = 0.0;

TouchkeyControlMappingFactory::TouchkeyControlMappingFactory(PianoKeyboard &keyboard, MidiKeyboardSegment& segment) :
TouchkeyBaseMappingFactory<TouchkeyControlMapping>(keyboard, segment),
inputParameter_(TouchkeyControlMapping::kInputParameterYPosition),
inputType_(TouchkeyControlMapping::kTypeAbsolute),
outputRangeMin_(kDefaultOutputRangeMin), outputRangeMax_(kDefaultOutputRangeMax),
outputDefault_(kDefaultOutputDefault), threshold_(0.0),
ignoresTwoFingers_(TouchkeyControlMapping::kDefaultIgnoresTwoFingers),
ignoresThreeFingers_(TouchkeyControlMapping::kDefaultIgnoresThreeFingers),
direction_(TouchkeyControlMapping::kDefaultDirection)
{
    setController(kDefaultController);
}

// ***** Destructor *****

TouchkeyControlMappingFactory::~TouchkeyControlMappingFactory() {

}

// ***** Accessors / Modifiers *****

void TouchkeyControlMappingFactory::setInputParameter(int inputParameter) {
    inputParameter_ = inputParameter;
}

void TouchkeyControlMappingFactory::setInputType(int inputType) {
    inputType_ = inputType;
}

void TouchkeyControlMappingFactory::setController(int controller) {
    // Before changing the controller, check if we were going to or from the pitch wheel.
    // If so, we should scale the value to or from a 14-bit value
    if(midiControllerNumber_ == MidiKeyboardSegment::kControlPitchWheel &&
       controller != MidiKeyboardSegment::kControlPitchWheel) {
        outputRangeMax_ = outputRangeMax_ / 128.0;
        if(outputRangeMax_ > 127.0)
            outputRangeMax_ = 127.0;
        outputRangeMin_ = outputRangeMin_ / 128.0;
        if(outputRangeMin_ > 127.0)
            outputRangeMin_ = 127.0;
        outputDefault_ = outputDefault_ / 128.0;
        if(outputDefault_ > 127.0)
            outputDefault_ = 127.0;
    }
    else if(midiControllerNumber_ != MidiKeyboardSegment::kControlPitchWheel &&
            controller == MidiKeyboardSegment::kControlPitchWheel) {
        if(outputRangeMax_ == 127.0)
            outputRangeMax_ = 16383.0;
        else
            outputRangeMax_ = outputRangeMax_ * 128.0;
        if(outputRangeMin_ == 127.0)
            outputRangeMin_ = 16383.0;
        else
            outputRangeMin_ = outputRangeMin_ * 128.0;
        if(outputDefault_ == 127.0)
            outputDefault_ = 16383.0;
        else
            outputDefault_ = outputDefault_ * 128.0;
    }

    setMidiParameters(controller, inputRangeMin_, inputRangeMax_, inputRangeCenter_,
                      outputDefault_, outputRangeMin_, outputRangeMax_);
    
    // Listen to incoming controls from the keyboard too, if this is enabled
    // in MidiKeyboardSegment
    if(midiConverter_ != 0) {
        midiConverter_->listenToIncomingControl(midiControllerNumber_);
    }
}

/*void TouchkeyControlMappingFactory::setRange(float inputMin, float inputMax, float inputCenter, float outputMin, float outputMax, float outputDefault) {
    // All possible input parameters are in the range [-1, 1],
    // and actually in the range [0, 1] if absolute values are used
    // (though we don't check this here)
    if(inputMin < -1.0)
        inputRangeMin_ = -1.0;
    else if(inputMin > 1.0)
        inputRangeMin_ = 1.0;
    else
        inputRangeMin_ = inputMin;
    if(inputMax < -1.0)
        inputRangeMax_ = -1.0;
    else if(inputMax > 1.0)
        inputRangeMax_ = 1.0;
    else
        inputRangeMax_ = inputMax;
    if(inputCenter < -1.0)
        inputRangeCenter_ = -1.0;
    else if(inputCenter > 1.0)
        inputRangeCenter_ = 1.0;
    else
        inputRangeCenter_ = inputCenter;
    outputRangeMin_ = outputMin;
    outputRangeMax_ = outputMax;
    outputDefault_ = outputDefault;
    
    // Update control
    if(midiConverter_ == 0)
        return;
    midiConverter_->removeAllControls();
    midiConverter_->addControl(controlName_.c_str(), 1, inputRangeMin_, inputRangeMax_, inputRangeCenter_, OscMidiConverter::kOutOfRangeClip);
}*/

void TouchkeyControlMappingFactory::setRangeInputMin(float inputMin) {
    if(inputMin < -1.0)
        inputRangeMin_ = -1.0;
    else if(inputMin > 1.0)
        inputRangeMin_ = 1.0;
    else
        inputRangeMin_ = inputMin;
    
    // Update control
    //if(midiConverter_ == 0)
    //    return;
    //midiConverter_->setControlMinValue(controlName_.c_str(), inputRangeMin_);
    setMidiParameters(midiControllerNumber_, inputRangeMin_, inputRangeMax_, inputRangeCenter_,
                      outputDefault_, outputRangeMin_, outputRangeMax_);
}

void TouchkeyControlMappingFactory::setRangeInputMax(float inputMax) {
    if(inputMax < -1.0)
        inputRangeMax_ = -1.0;
    else if(inputMax > 1.0)
        inputRangeMax_ = 1.0;
    else
        inputRangeMax_ = inputMax;
    
    // Update control
    //if(midiConverter_ == 0)
    //    return;
    //midiConverter_->setControlMaxValue(controlName_.c_str(), inputRangeMax_);
    setMidiParameters(midiControllerNumber_, inputRangeMin_, inputRangeMax_, inputRangeCenter_,
                      outputDefault_, outputRangeMin_, outputRangeMax_);
}

void TouchkeyControlMappingFactory::setRangeInputCenter(float inputCenter) {
    if(inputCenter < -1.0)
        inputRangeCenter_ = -1.0;
    else if(inputCenter > 1.0)
        inputRangeCenter_ = 1.0;
    else
        inputRangeCenter_ = inputCenter;
    
    // Update control
    //if(midiConverter_ == 0)
    //    return;
    //midiConverter_->setControlCenterValue(controlName_.c_str(), inputRangeCenter_);
    setMidiParameters(midiControllerNumber_, inputRangeMin_, inputRangeMax_, inputRangeCenter_,
                      outputDefault_, outputRangeMin_, outputRangeMax_);
}

void TouchkeyControlMappingFactory::setRangeOutputMin(float outputMin) {
    outputRangeMin_ = outputMin;
    
    setMidiParameters(midiControllerNumber_, inputRangeMin_, inputRangeMax_, inputRangeCenter_,
                      outputDefault_, outputRangeMin_, outputRangeMax_);
}

void TouchkeyControlMappingFactory::setRangeOutputMax(float outputMax) {
    outputRangeMax_ = outputMax;
    
    setMidiParameters(midiControllerNumber_, inputRangeMin_, inputRangeMax_, inputRangeCenter_,
                      outputDefault_, outputRangeMin_, outputRangeMax_);
}

void TouchkeyControlMappingFactory::setRangeOutputDefault(float outputDefault) {
    outputDefault_ = outputDefault;
    
    setMidiParameters(midiControllerNumber_, inputRangeMin_, inputRangeMax_, inputRangeCenter_,
                      outputDefault_, outputRangeMin_, outputRangeMax_);
}

void TouchkeyControlMappingFactory::setThreshold(float threshold) {
    threshold_ = threshold;
}

void TouchkeyControlMappingFactory::setIgnoresTwoFingers(bool ignoresTwo) {
    ignoresTwoFingers_ = ignoresTwo;
}

void TouchkeyControlMappingFactory::setIgnoresThreeFingers(bool ignoresThree) {
    ignoresThreeFingers_ = ignoresThree;
}

void TouchkeyControlMappingFactory::setDirection(int direction) {
    direction_ = direction;
}

// ***** GUI Support *****
MappingEditorComponent* TouchkeyControlMappingFactory::createBasicEditor() {
    return new TouchkeyControlMappingShortEditor(*this);
}

// ***** Private Methods *****

void TouchkeyControlMappingFactory::initializeMappingParameters(int noteNumber, TouchkeyControlMapping *mapping) {
    // Set parameters
    mapping->setInputParameter(inputParameter_, inputType_);
    mapping->setRange(inputRangeMin_, inputRangeMax_, outputRangeMin_, outputRangeMax_, outputDefault_);
    mapping->setThreshold(threshold_);
    mapping->setIgnoresMultipleFingers(ignoresTwoFingers_, ignoresThreeFingers_);
    mapping->setDirection(direction_);
}
