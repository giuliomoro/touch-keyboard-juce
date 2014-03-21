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

  TouchkeyReleaseAngleMappingFactory.h: factory for the release angle
  mapping, which measures the speed of finger motion along the key at
  the time of MIDI note off.
*/

#ifndef __TouchKeys__TouchkeyReleaseAngleMappingFactory__
#define __TouchKeys__TouchkeyReleaseAngleMappingFactory__

#include "../TouchkeyBaseMappingFactory.h"
#include "TouchkeyReleaseAngleMapping.h"

class TouchkeyReleaseAngleMappingFactory : public TouchkeyBaseMappingFactory<TouchkeyReleaseAngleMapping> {
private:
    //constexpr static const timestamp_diff_type kDefaultMaxLookbackTime = milliseconds_to_timestamp(100);
    static const timestamp_diff_type kDefaultMaxLookbackTime;
    
public:
    // ***** Constructor *****
    
	// Default constructor, containing a reference to the PianoKeyboard class.
    TouchkeyReleaseAngleMappingFactory(PianoKeyboard &keyboard, MidiKeyboardSegment& segment);
	
    // ***** Destructor *****
    
    ~TouchkeyReleaseAngleMappingFactory() {}
    
    // ***** Accessors / Modifiers *****
    virtual const std::string factoryTypeName() { return "Release\nAngle"; }
    
    // ****** Preset Save/Load ******
    XmlElement* getPreset();
    bool loadPreset(XmlElement const* preset);
    
    // ***** State Updaters *****
    
    // Override the MIDI note off method to process the release angle
    void midiNoteOff(int noteNumber, bool touchIsOn, bool keyMotionActive,
                     Node<KeyTouchFrame>* touchBuffer,
                     Node<key_position>* positionBuffer,
                     KeyPositionTracker* positionTracker);
    
};

#endif /* defined(__TouchKeys__TouchkeyReleaseAngleMappingFactory__) */
