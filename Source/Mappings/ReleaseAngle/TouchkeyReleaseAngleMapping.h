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

  TouchkeyReleaseAngleMapping.h: per-note mapping for the release angle
  mapping, which measures the speed of finger motion along the key at
  the time of MIDI note off.
*/

#ifndef __TouchKeys__TouchkeyReleaseAngleMapping__
#define __TouchKeys__TouchkeyReleaseAngleMapping__

#include "../TouchkeyBaseMapping.h"

// This class handles the detection of finger motion specifically at
// note release, which can be used to trigger specific release effects.

class TouchkeyReleaseAngleMapping : public TouchkeyBaseMapping {
private:
    // Default values
    /*constexpr static const int kDefaultFilterBufferLength = 30;
    constexpr static const timestamp_diff_type kDefaultMaxLookbackTime = milliseconds_to_timestamp(100);*/
    
    static const int kDefaultFilterBufferLength;
    static const timestamp_diff_type kDefaultMaxLookbackTime;
    
public:
	// ***** Constructors *****
	
	// Default constructor, passing the buffer on which to trigger
	TouchkeyReleaseAngleMapping(PianoKeyboard &keyboard, MappingFactory *factory, int noteNumber, Node<KeyTouchFrame>* touchBuffer,
                                Node<key_position>* positionBuffer, KeyPositionTracker* positionTracker);
	
	// Copy constructor
	//TouchkeyReleaseAngleMapping(TouchkeyReleaseAngleMapping const& obj);
	
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
    // Process the release by calculating the angle
    void processRelease(timestamp_type timestamp);
    
    timestamp_type releaseKeySwitch();
    
private:
    // ***** Private Methods *****
    
    void sendReleaseAngleMessage(float releaseAngle, bool force = false);
    
	// ***** Member Variables *****
    
    Node<KeyTouchFrame> pastSamples_;           // Locations of touch
    timestamp_diff_type maxLookbackTime_;       // How long to look backwards to find release velocity
    CriticalSection sampleBufferMutex_;         // Mutex to protect threaded access to sample buffer
};

#endif /* defined(__TouchKeys__TouchkeyReleaseAngleMapping__) */
