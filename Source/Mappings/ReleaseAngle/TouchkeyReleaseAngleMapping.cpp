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

  TouchkeyReleaseAngleMapping.cpp: per-note mapping for the release angle
  mapping, which measures the speed of finger motion along the key at
  the time of MIDI note off.
*/

#include "TouchkeyReleaseAngleMapping.h"
#include "../MappingFactory.h"
#include "../../TouchKeys/MidiOutputController.h"
#include "../MappingScheduler.h"

// Class constants
const int TouchkeyReleaseAngleMapping::kDefaultFilterBufferLength = 30;
const timestamp_diff_type TouchkeyReleaseAngleMapping::kDefaultMaxLookbackTime = milliseconds_to_timestamp(100);

// Main constructor takes references/pointers from objects which keep track
// of touch location, continuous key position and the state detected from that
// position. The PianoKeyboard object is strictly required as it gives access to
// Scheduler and OSC methods. The others are optional since any given system may
// contain only one of continuous key position or touch sensitivity
TouchkeyReleaseAngleMapping::TouchkeyReleaseAngleMapping(PianoKeyboard &keyboard, MappingFactory *factory, int noteNumber, Node<KeyTouchFrame>* touchBuffer,
                                                         Node<key_position>* positionBuffer, KeyPositionTracker* positionTracker)
: TouchkeyBaseMapping(keyboard, factory, noteNumber, touchBuffer, positionBuffer, positionTracker, false),
  pastSamples_(kDefaultFilterBufferLength), maxLookbackTime_(kDefaultMaxLookbackTime)
{
}

// Copy constructor
/*TouchkeyReleaseAngleMapping::TouchkeyReleaseAngleMapping(TouchkeyReleaseAngleMapping const& obj)
: TouchkeyBaseMapping(obj), pastSamples_(obj.pastSamples_), maxLookbackTime_(obj.maxLookbackTime_)
{
}*/

// Reset state back to defaults
void TouchkeyReleaseAngleMapping::reset() {
    ScopedLock sl(sampleBufferMutex_);
    
    TouchkeyBaseMapping::reset();
    pastSamples_.clear();
}

// Resend all current parameters
void TouchkeyReleaseAngleMapping::resend() {
    // Message is only sent at release; resend may not apply here.
}

// This method receives data from the touch buffer or possibly the continuous key angle (not used here)
void TouchkeyReleaseAngleMapping::triggerReceived(TriggerSource* who, timestamp_type timestamp) {
    if(who == touchBuffer_) {
        ScopedLock sl(sampleBufferMutex_);
        
        // Save the latest frame, even if it is an empty touch (we need to know what happened even
        // after the touch ends since the MIDI off may come later)
        if(!touchBuffer_->empty())
            pastSamples_.insert(touchBuffer_->latest(), touchBuffer_->latestTimestamp());
    }
}

// Mapping method. This actually does the real work of sending OSC data in response to the
// latest information from the touch sensors or continuous key angle
timestamp_type TouchkeyReleaseAngleMapping::performMapping() {
    // Nothing to do here until note is released.
    // Register for the next update by returning its timestamp
    // TODO: do we even need this? Check Mapping::engage() and Mapping::disengage()
    timestamp_type currentTimestamp = keyboard_.schedulerCurrentTimestamp();
    nextScheduledTimestamp_ = currentTimestamp + updateInterval_;
    return nextScheduledTimestamp_;
}

void TouchkeyReleaseAngleMapping::processRelease(timestamp_type timestamp) {
    if(!noteIsOn_) {
        return;
    }
    
    sampleBufferMutex_.enter();
    
    // Look backwards from the current timestamp to find the velocity
    float calculatedVelocity = missing_value<float>::missing();
    bool touchWasOn = false;
    
    
    //std::cout << "processRelease begin = " << pastSamples_.beginIndex() << " end = " << pastSamples_.endIndex() << "\n";
    
    if(!pastSamples_.empty()) {
        Node<KeyTouchFrame>::size_type index = pastSamples_.endIndex() - 1;
        Node<KeyTouchFrame>::size_type mostRecentTouchPresentIndex = pastSamples_.endIndex() - 1;
        while(index >= pastSamples_.beginIndex()) {
            //std::cout << "examining sample " << index << " with " << pastSamples_[index].count << " touches and time diff " << timestamp - pastSamples_.timestampAt(index) << "\n";
            if(timestamp - pastSamples_.timestampAt(index) >= maxLookbackTime_)
                break;
            if(pastSamples_[index].count == 0) {
                if(touchWasOn) {
                    // We found a break in the touch; stop here. But don't stop
                    // if the first frames we consider have no touches.
                    if(index < pastSamples_.endIndex() - 1)
                        index++;
                    break;
                }
            }
            else if(!touchWasOn) {
                mostRecentTouchPresentIndex = index;
                touchWasOn = true;
            }
            // Can't decrement past 0 in an unsigned type
            if(index == 0)
                break;
            index--;
        }
        
        // If we fell off the beginning of the buffer, back up.
        if(index < pastSamples_.beginIndex())
            index =  pastSamples_.beginIndex();
        
        //std::cout << "done\n";
        
        // Need at least two points for this calculation to work
        timestamp_type endingTimestamp = pastSamples_.timestampAt(mostRecentTouchPresentIndex);
        timestamp_type startingTimestamp = pastSamples_.timestampAt(index);
        if(endingTimestamp - startingTimestamp > 0) {
            float endingPosition = pastSamples_[mostRecentTouchPresentIndex].locs[0];
            float startingPosition = pastSamples_[index].locs[0];
            calculatedVelocity = (endingPosition - startingPosition) / (endingTimestamp - startingTimestamp);
        }
        else { // DEBUG
            std::cout << "Found 0 timestamp difference on key release (indices " << index << " and " << pastSamples_.endIndex() - 1 << "\n";
        }
    }
    else
        std::cout << "Found empty touch buffer on key release\n";
    
    sampleBufferMutex_.exit();
    
    if(!missing_value<float>::isMissing(calculatedVelocity)) {
        std::cout << "Found release velocity " << calculatedVelocity << " on note " << noteNumber_ << std::endl;
        sendReleaseAngleMessage(calculatedVelocity);
    }

    
    // Check if we're suppose to clean up now
    finished_ = true;
    if(finishRequested_)
        acknowledgeFinish();
    // KLUDGE
}

#define TROMBONE
void TouchkeyReleaseAngleMapping::sendReleaseAngleMessage(float releaseAngle, bool force) {
    if(force || !suspended_) {
        keyboard_.sendMessage("/touchkeys/releaseangle", "if", noteNumber_, releaseAngle, LO_ARGS_END);
        
#ifdef TROMBONE
        // KLUDGE: figure out how to do this more elegantly
        if(keyboard_.midiOutputController() != 0) {
            if(releaseAngle > 1.0) {
                keyboard_.midiOutputController()->sendNoteOn(0, 0, 36, 64);
                keyboard_.midiOutputController()->sendNoteOn(0, 0, 31, 96);
                keyboard_.midiOutputController()->sendNoteOff(0, 0, 31);
                keyboard_.midiOutputController()->sendNoteOff(0, 0, 36);
            }
            else if(releaseAngle < -1.5) {
                keyboard_.midiOutputController()->sendNoteOn(0, 0, 36, 64);
                keyboard_.midiOutputController()->sendNoteOn(0, 0, 33, 80);
                keyboard_.midiOutputController()->sendNoteOff(0, 0, 33);
                keyboard_.midiOutputController()->sendNoteOff(0, 0, 36);
            }
        }
#elif defined(TRUMPET)
        if(keyboard_.midiOutputController() != 0) {
            if(releaseAngle > 1.0) {
                keyboard_.midiOutputController()->sendNoteOn(0, 0, 48, 64);
                keyboard_.midiOutputController()->sendNoteOn(0, 0, 42, 96);
                //keyboard_.midiOutputController()->sendNoteOff(0, 0, 42);
                keyboard_.midiOutputController()->sendNoteOff(0, 0, 48);
                keyboard_.scheduleEvent(this, boost::bind(&TouchkeyReleaseAngleMapping::releaseKeySwitch, this),
                                        keyboard_.schedulerCurrentTimestamp() + milliseconds_to_timestamp(250));
            }
            else if(releaseAngle < -1.5) {
                keyboard_.midiOutputController()->sendNoteOn(0, 0, 48, 64);
                keyboard_.midiOutputController()->sendNoteOn(0, 0, 46, 96);
                //keyboard_.midiOutputController()->sendNoteOff(0, 0, 47);
                keyboard_.midiOutputController()->sendNoteOff(0, 0, 48);
                keyboard_.scheduleEvent(this, boost::bind(&TouchkeyReleaseAngleMapping::releaseKeySwitch, this),
                                        keyboard_.schedulerCurrentTimestamp() + milliseconds_to_timestamp(250));
            }
            else {
                // Check if we're suppose to clean up now
                finished_ = true;
                if(finishRequested_)
                    acknowledgeFinish();
            }
        }
#endif
    }
}

timestamp_type TouchkeyReleaseAngleMapping::releaseKeySwitch() {
    keyboard_.midiOutputController()->sendNoteOff(0, 0, 42);
    keyboard_.midiOutputController()->sendNoteOff(0, 0, 46);
    
    // Check if we're suppose to clean up now
    /*finished_ = true;
    if(finishRequested_)
        acknowledgeFinish();*/
    
    return 0;
}