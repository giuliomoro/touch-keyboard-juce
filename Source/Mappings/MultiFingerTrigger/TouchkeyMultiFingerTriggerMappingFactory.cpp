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

  TouchkeyMultiFingerTriggerMappingFactory.cpp: factory for the multiple-
  finger trigger mapping, which performs actions when two or more fingers
  are added or removed from the key.
*/

#include "TouchkeyMultiFingerTriggerMappingFactory.h"

// ****** Preset Save/Load ******
XmlElement* TouchkeyMultiFingerTriggerMappingFactory::getPreset() {
    PropertySet properties;
    
    storeCommonProperties(properties);
    
    // No properties for now
    
    XmlElement* preset = properties.createXml("MappingFactory");
    preset->setAttribute("type", "MultiFingerTrigger");
    
    return preset;
}

bool TouchkeyMultiFingerTriggerMappingFactory::loadPreset(XmlElement const* preset) {
    if(preset == 0)
        return false;
    
    PropertySet properties;
    properties.restoreFromXml(*preset);
    
    if(!loadCommonProperties(properties))
        return false;
    
    // Nothing specific to do for now
    
    return true;
}
