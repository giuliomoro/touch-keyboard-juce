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

  TouchkeyMultiFingerTriggerMapping.h: per-note mapping for the multiple-
  finger trigger mapping, which performs actions when two or more fingers
  are added or removed from the key.
*/

#ifndef __TouchKeys__TouchkeyMultiFingerTriggerMapping__
#define __TouchKeys__TouchkeyMultiFingerTriggerMapping__

#include "../TouchkeyBaseMapping.h"

// This class handles the detection of finger motion specifically at
// note release, which can be used to trigger specific release effects.

class TouchkeyMultiFingerTriggerMapping : public TouchkeyBaseMapping {
private:
    // Default values
    /*constexpr static const int kDefaultFilterBufferLength = 30;
    constexpr static const int kDefaultNumTouchesForTrigger = 2;
    constexpr static const int kDefaultNumFramesForTrigger = 2;
    constexpr static const int kDefaultNumConsecutiveTapsForTrigger = 1;
    constexpr static const timestamp_diff_type kDefaultMaxTapSpacing = milliseconds_to_timestamp(500.0);*/
    static const int kDefaultFilterBufferLength;
    static const int kDefaultNumTouchesForTrigger;
    static const int kDefaultNumFramesForTrigger;
    static const int kDefaultNumConsecutiveTapsForTrigger;
    static const timestamp_diff_type kDefaultMaxTapSpacing;

public:
	// ***** Constructors *****
	
	// Default constructor, passing the buffer on which to trigger
	TouchkeyMultiFingerTriggerMapping(PianoKeyboard &keyboard, MappingFactory *factory, int noteNumber, Node<KeyTouchFrame>* touchBuffer,
                                      Node<key_position>* positionBuffer, KeyPositionTracker* positionTracker);
	
    // ***** Modifiers *****
    
    // Reset the state back initial values
    void reset();
    
    // Resend the current state of all parameters
    void resend();
    
	// ***** Evaluators *****
    
    // This method receives triggers whenever events occur in the touch data or the
    // continuous key position (state changes only). It alters the behavior and scheduling
    // of the mapping but does not itself send OSC messages
	void triggerReceived(TriggerSource* who, timestamp_type timestamp);
	
    // This method handles the OSC message transmission. It should be run in the Scheduler
    // thread provided by PianoKeyboard.
    timestamp_type performMapping();
    
    // ***** Specific Methods *****

    
private:
    // ***** Private Methods *****
    // Generate the multi-finger trigger
    void generateTriggerOn(timestamp_type timestamp, timestamp_diff_type timeBetweenTaps, float distanceBetweenPoints);
    void generateTriggerOff(timestamp_type timestamp);
    
    void midiNoteOffReceived(int channel);
    
	// ***** Member Variables *****
    
    // Parameters
    int numTouchesForTrigger_;                  // How many touches are needed for a trigger
    int numFramesForTrigger_;                   // How many consecutive frames with these touches are needed to trigger
    int numConsecutiveTapsForTrigger_;          // How many taps with this number of touches are needed to trigger
    timestamp_diff_type maxTapSpacing_;         // How far apart the taps can come and be considered a multi-tap gesture
    bool needsMidiNoteOn_;                      // Whether the MIDI note has to be on for this gesture to trigger
    
    int lastNumActiveTouches_;                  // How many touches were active before
    float lastActiveTouchLocations_[3];         // Where (Y coord.) the active touches were last frame
    int framesCount_;                           // How many frames have met the current number of active touches
    int tapsCount_;                             // How many taps we've registered so far
    bool hasGeneratedTap_;                      // Whether we've generated a tap with this number of touches yet
    timestamp_type lastTapStartTimestamp_;      // When the last tap ended
    bool hasTriggered_;                         // Whether we've generated a trigger
    
    Node<KeyTouchFrame> pastSamples_;           // Locations of touch
    CriticalSection sampleBufferMutex_;         // Mutex to protect threaded access to sample buffer
};


#endif /* defined(__TouchKeys__TouchkeyMultiFingerTriggerMapping__) */
