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

  TouchkeyMultiFingerTriggerMapping.cpp: per-note mapping for the multiple-
  finger trigger mapping, which performs actions when two or more fingers
  are added or removed from the key.
*/

#include "TouchkeyMultiFingerTriggerMapping.h"
#include "../../TouchKeys/MidiOutputController.h"

// Class constants
const int TouchkeyMultiFingerTriggerMapping::kDefaultFilterBufferLength = 30;
const int TouchkeyMultiFingerTriggerMapping::kDefaultNumTouchesForTrigger = 2;
const int TouchkeyMultiFingerTriggerMapping::kDefaultNumFramesForTrigger = 2;
const int TouchkeyMultiFingerTriggerMapping::kDefaultNumConsecutiveTapsForTrigger = 1;
const timestamp_diff_type TouchkeyMultiFingerTriggerMapping::kDefaultMaxTapSpacing = milliseconds_to_timestamp(500.0);

// Main constructor takes references/pointers from objects which keep track
// of touch location, continuous key position and the state detected from that
// position. The PianoKeyboard object is strictly required as it gives access to
// Scheduler and OSC methods. The others are optional since any given system may
// contain only one of continuous key position or touch sensitivity
TouchkeyMultiFingerTriggerMapping::TouchkeyMultiFingerTriggerMapping(PianoKeyboard &keyboard, MappingFactory *factory, int noteNumber, Node<KeyTouchFrame>* touchBuffer,
                                                         Node<key_position>* positionBuffer, KeyPositionTracker* positionTracker)
: TouchkeyBaseMapping(keyboard, factory, noteNumber, touchBuffer, positionBuffer, positionTracker),
numTouchesForTrigger_(kDefaultNumTouchesForTrigger), numFramesForTrigger_(kDefaultNumFramesForTrigger),
numConsecutiveTapsForTrigger_(kDefaultNumConsecutiveTapsForTrigger), maxTapSpacing_(kDefaultMaxTapSpacing),
needsMidiNoteOn_(true), pastSamples_(kDefaultFilterBufferLength)
{
    reset();
}

// Reset state back to defaults
void TouchkeyMultiFingerTriggerMapping::reset() {
    ScopedLock sl(sampleBufferMutex_);
    
    TouchkeyBaseMapping::reset();
    pastSamples_.clear();
    
    lastNumActiveTouches_ = 0;
    lastActiveTouchLocations_[0] = lastActiveTouchLocations_[1] = lastActiveTouchLocations_[2] = 0;
    framesCount_ = 0;
    tapsCount_ = 0;
    hasGeneratedTap_ = false;
    lastTapStartTimestamp_ = missing_value<timestamp_type>::missing();
    hasTriggered_ = false;
}

// Resend all current parameters
void TouchkeyMultiFingerTriggerMapping::resend() {
    // Message is only sent at release; resend may not apply here.
}

// This method receives data from the touch buffer or possibly the continuous key angle (not used here)
void TouchkeyMultiFingerTriggerMapping::triggerReceived(TriggerSource* who, timestamp_type timestamp) {
    if(needsMidiNoteOn_ && !noteIsOn_) {
        framesCount_ = 0;
        hasGeneratedTap_ = false;
        return;
    }
    
    if(who == touchBuffer_) {
        if(!touchBuffer_->empty()) {
            // Find the current number of touches
            KeyTouchFrame frame  = touchBuffer_->latest();
            int count = frame.count;
            
            if(count < numTouchesForTrigger_) {
                framesCount_ = 0;
                hasGeneratedTap_ = false;
                if(hasTriggered_) {
                    generateTriggerOff(timestamp);
                    hasTriggered_ = false;
                }
            }
            else if(count == numTouchesForTrigger_) {
                framesCount_++;
                if(framesCount_ >= numFramesForTrigger_ && !hasGeneratedTap_) {
                    // Enough frames have elapsed to consider this a tap
                    // Figure out if it is a multiple consecutive tap or the first
                    // of a set.
                    if(!missing_value<timestamp_diff_type>::isMissing(lastTapStartTimestamp_)) {
                        if(timestamp - lastTapStartTimestamp_ < maxTapSpacing_) {
                            tapsCount_++;
                        }
                        else
                            tapsCount_ = 1;
                    }
                    else
                        tapsCount_ = 1;
                    
                    std::cout << "Tap " << tapsCount_ << std::endl;
                    
                    // Check if the right number of taps has elapsed
                    if(tapsCount_ >= numConsecutiveTapsForTrigger_ && !hasTriggered_) {
                        hasTriggered_ = true;
                        
                        // Find the ID of the newest touch and compare its location
                        // to the immediately preceding touch(es) to find the distance
                        int newest = 0, oldest = 0, newestId = -1, oldestId = 1000000;
                        for(int i = 0; i < count; i++) {
                            if(frame.ids[i] > newestId) {
                                newest = i;
                                newestId = frame.ids[i];
                            }
                            if(frame.ids[i] < oldestId) {
                                oldest = i;
                                oldestId = frame.ids[i];
                            }
                        }

                        // Find the distance between the point before this tap and the
                        // point that was added to create the tap. If this is a 3-touch
                        // tap, find the distance between the farthest two points, with
                        // the direction determined by which end is older.
                        float distance = frame.locs[newest] - frame.locs[oldest];
                        if(count == 3) {
                            if(fabsf(frame.locs[2] - frame.locs[0]) > fabsf(distance)) {
                                if(frame.ids[2] > frame.ids[0])
                                    distance = frame.locs[2] - frame.locs[0];
                                else
                                    distance = frame.locs[0] - frame.locs[2];
                            }
                        }
                        
                        // Generate the trigger. If a multi-tap gesture, also indicate the timing
                        if(numConsecutiveTapsForTrigger_ <= 1)
                            generateTriggerOn(timestamp, 0, distance);
                        else
                            generateTriggerOn(timestamp, timestamp - lastTapStartTimestamp_, distance);
                    }
                    
                    hasGeneratedTap_ = true;
                    lastTapStartTimestamp_ = timestamp;
                }
            }
        
            // Save the count locations for next time
            lastNumActiveTouches_ = frame.count;
            for(int i = 0; i < count; i++) {
                lastActiveTouchLocations_[i] = frame.locs[i];
            }
        }
    }
}

// Mapping method. This actually does the real work of sending OSC data in response to the
// latest information from the touch sensors or continuous key angle
timestamp_type TouchkeyMultiFingerTriggerMapping::performMapping() {
    // Nothing to do here until note is released.
    // Register for the next update by returning its timestamp
    // TODO: do we even need this? Check Mapping::engage() and Mapping::disengage()
    timestamp_type currentTimestamp = keyboard_.schedulerCurrentTimestamp();
    nextScheduledTimestamp_ = currentTimestamp + updateInterval_;
    return nextScheduledTimestamp_;
}

void TouchkeyMultiFingerTriggerMapping::generateTriggerOn(timestamp_type timestamp, timestamp_diff_type timeBetweenTaps, float distanceBetweenPoints) {
    std::cout << "Trigger distance = " << distanceBetweenPoints << " timing = " << timeBetweenTaps << std::endl;
    // KLUDGE
    if(!suspended_) {
#if 0
        if(distanceBetweenPoints > 0.35) {
            //keyboard_.sendMessage("/touchkeys/pitchbend", "if", noteNumber_, 2.0, LO_ARGS_END);
            int ch = keyboard_.key(noteNumber_)->midiChannel();
            int vel = keyboard_.key(noteNumber_)->midiVelocity();
            keyboard_.midiOutputController()->sendNoteOn(0, ch, noteNumber_ + 14, vel);
            //keyboard_.midiOutputController()->sendNoteOff(0, ch, noteNumber_ + 12, vel);
        }
        else {
            //keyboard_.sendMessage("/touchkeys/pitchbend", "if", noteNumber_, 1.0, LO_ARGS_END);
            int ch = keyboard_.key(noteNumber_)->midiChannel();
            int vel = keyboard_.key(noteNumber_)->midiVelocity();
            keyboard_.midiOutputController()->sendNoteOn(0, ch, noteNumber_ + 13, vel);
            //keyboard_.midiOutputController()->sendNoteOff(0, ch, noteNumber_ + 12, vel);
        }
#elif 0
        int ch = keyboard_.key(noteNumber_)->midiChannel();
        keyboard_.midiOutputController()->sendControlChange(0, ch, 73, 127);
#else
        keyboard_.midiOutputController()->sendNoteOn(0, keyboard_.key(noteNumber_)->midiChannel(), noteNumber_, 127);
#endif
    }
}

void TouchkeyMultiFingerTriggerMapping::generateTriggerOff(timestamp_type timestamp) {
    std::cout << "Trigger off\n";
    if(!suspended_) {
#if 0
        //eyboard_.sendMessage("/touchkeys/pitchbend", "if", noteNumber_, 0.0, LO_ARGS_END);
        int ch = keyboard_.key(noteNumber_)->midiChannel();
        int vel = keyboard_.key(noteNumber_)->midiVelocity();
        keyboard_.midiOutputController()->sendNoteOn(0, ch, noteNumber_ + 12, vel);
        //keyboard_.midiOutputController()->sendNoteOff(0, ch, noteNumber_ + 13, vel);
        //keyboard_.midiOutputController()->sendNoteOff(0, ch, noteNumber_ + 14, vel);
#elif 0
        int ch = keyboard_.key(noteNumber_)->midiChannel();
        keyboard_.midiOutputController()->sendControlChange(0, ch, 73, 0);
#else
        keyboard_.midiOutputController()->sendNoteOn(0, keyboard_.key(noteNumber_)->midiChannel(), noteNumber_, 127);
#endif
    }
}

// MIDI note-off message received
void TouchkeyMultiFingerTriggerMapping::midiNoteOffReceived(int channel) {
    int ch = keyboard_.key(noteNumber_)->midiChannel();
    keyboard_.midiOutputController()->sendControlChange(0, ch, 73, 0);
}
