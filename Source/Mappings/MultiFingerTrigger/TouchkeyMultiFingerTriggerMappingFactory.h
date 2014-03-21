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

  TouchkeyMultiFingerTriggerMappingFactory.h: factory for the multiple-
  finger trigger mapping, which performs actions when two or more fingers
  are added or removed from the key.
*/


#ifndef __TouchKeys__TouchkeyMultiFingerTriggerMappingFactory__
#define __TouchKeys__TouchkeyMultiFingerTriggerMappingFactory__

#include "../TouchkeyBaseMappingFactory.h"
#include "TouchkeyMultiFingerTriggerMapping.h"

class TouchkeyMultiFingerTriggerMappingFactory : public TouchkeyBaseMappingFactory<TouchkeyMultiFingerTriggerMapping> {
private:
  
public:
    // ***** Constructor *****
    
	// Default constructor, containing a reference to the PianoKeyboard class.
    TouchkeyMultiFingerTriggerMappingFactory(PianoKeyboard &keyboard, MidiKeyboardSegment& segment)
    : TouchkeyBaseMappingFactory<TouchkeyMultiFingerTriggerMapping>(keyboard, segment) {}
	
    // ***** Destructor *****
    
    ~TouchkeyMultiFingerTriggerMappingFactory() {}
    
    // ***** Accessors / Modifiers *****
    
    virtual const std::string factoryTypeName() { return "Multi-Finger\nTrigger"; }
    
    // ****** Preset Save/Load ******
    XmlElement* getPreset();
    bool loadPreset(XmlElement const* preset);
};

#endif /* defined(__TouchKeys__TouchkeyMultiFingerTriggerMappingFactory__) */
