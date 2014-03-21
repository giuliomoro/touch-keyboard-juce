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

  TouchkeyReleaseAngleMappingFactory.cpp: factory for the release angle
  mapping, which measures the speed of finger motion along the key at
  the time of MIDI note off.
*/

#include "TouchkeyReleaseAngleMappingFactory.h"

// Class constants
const timestamp_diff_type TouchkeyReleaseAngleMappingFactory::kDefaultMaxLookbackTime = milliseconds_to_timestamp(100);


TouchkeyReleaseAngleMappingFactory::TouchkeyReleaseAngleMappingFactory(PianoKeyboard &keyboard, MidiKeyboardSegment& segment)
: TouchkeyBaseMappingFactory<TouchkeyReleaseAngleMapping>(keyboard, segment) {}

// ****** Preset Save/Load ******
XmlElement* TouchkeyReleaseAngleMappingFactory::getPreset() {
    PropertySet properties;
    
    storeCommonProperties(properties);
    
    // No properties for now
    
    XmlElement* preset = properties.createXml("MappingFactory");
    preset->setAttribute("type", "ReleaseAngle");
    
    return preset;
}

bool TouchkeyReleaseAngleMappingFactory::loadPreset(XmlElement const* preset) {
    if(preset == 0)
        return false;
    
    PropertySet properties;
    properties.restoreFromXml(*preset);
    
    if(!loadCommonProperties(properties))
        return false;
    
    // Nothing specific to do for now
    
    return true;
}

// MIDI note ended: see whether the mapping was suspended and if not, execute the angle calculation
void TouchkeyReleaseAngleMappingFactory::midiNoteOff(int noteNumber, bool touchIsOn, bool keyMotionActive,
                                                     Node<KeyTouchFrame>* touchBuffer,
                                                     Node<key_position>* positionBuffer,
                                                     KeyPositionTracker* positionTracker) {
    if(mappings_.count(noteNumber) != 0) {
        mappings_[noteNumber]->processRelease(keyboard_.schedulerCurrentTimestamp());
    }
    
    // Call base class method
    TouchkeyBaseMappingFactory<TouchkeyReleaseAngleMapping>::midiNoteOff(noteNumber, touchIsOn, keyMotionActive, touchBuffer, positionBuffer, positionTracker);
}
