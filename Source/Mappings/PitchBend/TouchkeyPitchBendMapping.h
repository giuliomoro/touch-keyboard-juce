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

  TouchkeyPitchBendMapping.h: per-note mapping for the pitch-bend mapping,
  which handles changing pitch based on relative finger motion.
*/

#ifndef __touchkeys__TouchkeyPitchBendMapping__
#define __touchkeys__TouchkeyPitchBendMapping__



#include <map>
#include <boost/bind.hpp>
#include "../TouchkeyBaseMapping.h"
#include "../../Utility/IIRFilter.h"

// This class handles the detection and mapping of vibrato gestures
// based on Touchkey data. It outputs MIDI or OSC messages that
// can be used to affect the pitch of the active note.

class TouchkeyPitchBendMapping : public TouchkeyBaseMapping {
    friend class TouchkeyVibratoMappingFactory;
    friend class TouchkeyPitchBendMappingFactory;
    

public:
    enum {
        kPitchBendModeVariableEndpoints = 1,
        kPitchBendModeFixedEndpoints
    };
    
private:
    // Useful constants for mapping MRP messages
    
    static const int kDefaultMIDIChannel;
    static const int kDefaultFilterBufferLength;
    
    static const float kDefaultBendRangeSemitones;
    static const float kDefaultBendThresholdSemitones;
    static const float kDefaultBendThresholdKeyLength;
    static const float kDefaultSnapZoneSemitones;
    static const int kDefaultPitchBendMode;
    static const float kDefaultFixedModeEnableDistance;
    static const float kDefaultFixedModeBufferDistance;
    
    static const bool kDefaultIgnoresTwoFingers;
    static const bool kDefaultIgnoresThreeFingers;


public:
	// ***** Constructors *****
	
	// Default constructor, passing the buffer on which to trigger
	TouchkeyPitchBendMapping(PianoKeyboard &keyboard, MappingFactory *factory, int noteNumber, Node<KeyTouchFrame>* touchBuffer,
                           Node<key_position>* positionBuffer, KeyPositionTracker* positionTracker);
	
	// Copy constructor
	//TouchkeyPitchBendMapping(TouchkeyPitchBendMapping const& obj);
    
    // ***** Destructor *****
    
    ~TouchkeyPitchBendMapping();
	
    // ***** Modifiers *****
    
    // Reset the state back initial values
	void reset();
    
    // Resend the current state of all parameters
    void resend();
    
    // Parameters for pitch bend algorithm
    void setRange(float rangeSemitones);
    void setThresholds(float thresholdSemitones, float thresholdKeyLength);
    void setFixedEndpoints(float minimumDistanceToEnable, float bufferAtEnd);
    void setVariableEndpoints();
    
    // Whether we ignore two or three finger touches for calculating pitch bends
    void setIgnoresMultipleFingers(bool ignoresTwo, bool ignoresThree);
    
	// ***** Evaluators *****
    
    // This method receives triggers whenever events occur in the touch data or the
    // continuous key position (state changes only). It alters the behavior and scheduling
    // of the mapping but does not itself send OSC messages
	void triggerReceived(TriggerSource* who, timestamp_type timestamp);
	
    // This method handles the OSC message transmission. It should be run in the Scheduler
    // thread provided by PianoKeyboard.
    timestamp_type performMapping();
    
private:
    // ***** Private Methods *****
    void midiNoteOnReceived(int channel, int velocity);
    void midiNoteOffReceived(int channel);
    
    void resetDetectionState();
    void clearBuffers();
    
    void engageSnapping();
    void disengageSnapping();
    
    void updateCombinedThreshold();
    void sendPitchBendMessage(float pitchBendSemitones, bool force = false);
    
	// ***** Member Variables *****
    
    bool bendIsEngaged_;                        // Whether the pitch bend is currently engaged
    bool snapIsEngaged_;                        // Whether the note is currently being snapped to nearest semitone
    
    float thresholdSemitones_;                  // Minimum motion in semitones before bend engages
    float thresholdKeyLength_;                  // Minimum motion as a function of key length
    float thresholdCombinedMax_;                // Whichever is greater of the above two
    float snapZoneSemitones_;                   // How wide the snap area is around each semitone
    int bendMode_;                              // What mode the bend works in (fixed, variable, etc.)
    float fixedModeMinEnableDistance_;          // Minimum distance to engage in fixed mode
    float fixedModeBufferDistance_;             // Extra distance at end beyond which no bend happens
    bool ignoresTwoFingers_;                    // Whether this mapping supresses all messages when two
    bool ignoresThreeFingers_;                  // or three fingers are present
    
    float onsetLocationX_, onsetLocationY_;     // Where the touch began at MIDI note on
    float lastX_, lastY_;                       // Where the touch was at the last frame we received
    int idOfCurrentTouch_;                      // Which touch ID we're currently following
    timestamp_type lastTimestamp_;              // When the last data point arrived
    Node<float>::size_type lastProcessedIndex_; // Index of the last filtered position sample we've handled
    
    float bendScalerPositive_, bendScalerNegative_; // Translation between position and semitones for upward and downward motions
    
    float currentSnapDestinationSemitones_;     // Where the pitch would snap to if snapping was engaged
    
    float bendRangeSemitones_;                  // Amount of pitch bend in one direction at maximum
    float lastPitchBendSemitones_;              // The last pitch bend value we sent out
    
    Node<float> rawDistance_;                   // Distance from onset location
    CriticalSection distanceAccessMutex_;       // Mutex protecting access to the distance buffer
};


#endif /* defined(__touchkeys__TouchkeyPitchBendMapping__) */
