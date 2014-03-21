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

  TouchkeyPitchBendMappingFactory.h: factory for the pitch-bend mapping,
  which handles changing pitch based on relative finger motion.
*/


#ifndef __TouchKeys__TouchkeyPitchBendMappingFactory__
#define __TouchKeys__TouchkeyPitchBendMappingFactory__


#include <iostream>

#include "../TouchkeyBaseMappingFactory.h"
#include "TouchkeyPitchBendMapping.h"

// Factory class to produce Touchkey pitch bend messages
// This class keeps track of all the active mappings and responds
// whenever touches or notes begin or end

class TouchkeyPitchBendMappingFactory : public TouchkeyBaseMappingFactory<TouchkeyPitchBendMapping> {
    
public:
    // ***** Constructor *****
    
	// Default constructor, containing a reference to the PianoKeyboard class.
    TouchkeyPitchBendMappingFactory(PianoKeyboard &keyboard, MidiKeyboardSegment& segment);
	
    // ***** Destructor *****
    
    ~TouchkeyPitchBendMappingFactory();
    
    // ***** Accessors / Modifiers *****
    
    virtual const std::string factoryTypeName() { return "Pitch\nBend"; }
    
    void setName(const string& name);
    
    // ***** Bend-Specific Methods *****
    
    float getBendRange() { return bendRangeSemitones_; }
    float getBendThresholdSemitones() { return bendThresholdSemitones_; }
    float getBendThresholdKeyLength() { return bendThresholdKeyLength_; }
    int getBendMode() { return bendMode_; }
    
    void setBendRange(float rangeSemitones, bool updateCurrent = false);
    void setBendThresholdSemitones(float thresholdSemitones);
    void setBendThresholdKeyLength(float thresholdKeyLength);
    void setBendThresholds(float thresholdSemitones, float thresholdKeyLength, bool updateCurrent = false);
    void setBendFixedEndpoints(float minimumDistanceToEnable, float bufferAtEnd);
    void setBendVariableEndpoints();
    void setBendIgnoresMultipleFingers(bool ignoresTwo, bool ignoresThree);
    
    // ***** GUI Support *****
    bool hasBasicEditor() { return true; }
    MappingEditorComponent* createBasicEditor();
    bool hasExtendedEditor() { return false; }
    MappingEditorComponent* createExtendedEditor() { return nullptr; }

    // ****** Preset Save/Load ******
    XmlElement* getPreset();
    bool loadPreset(XmlElement const* preset);
    
private:
    // ***** Private Methods *****
    void initializeMappingParameters(int noteNumber, TouchkeyPitchBendMapping *mapping);
    void setBendParameters();
    
    float bendRangeSemitones_;                          // Range of the pitch bend component
    float bendThresholdSemitones_;                      // Threshold for engaging pitch bend
    float bendThresholdKeyLength_;                      // Threshold in key length for engaging pitch bend
    int bendMode_;                                      // What mode the bend works in (fixed, variable, etc.)
    float fixedModeMinEnableDistance_;                  // Minimum distance to engage in fixed mode
    float fixedModeBufferDistance_;                     // Extra distance at end beyond which no bend happens
    bool bendIgnoresTwoFingers_;                        // Whether the pitch bends ignore two
    bool bendIgnoresThreeFingers_;                      // or three fingers on the key at once
};

#endif /* defined(__TouchKeys__TouchkeyPitchBendMappingFactory__) */
