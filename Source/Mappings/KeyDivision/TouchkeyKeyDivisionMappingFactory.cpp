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

  TouchkeyKeyDivisionMappingFactory.cpp: factory for the split-key mapping
  which triggers different actions or pitches depending on where the key
  was struck.
*/

#include "TouchkeyKeyDivisionMappingFactory.h"

const float TouchkeyKeyDivisionMappingFactory::kDefaultPitchWheelRangeSemitones = 2.0;

// Yarman-24 Turkish microtonal tuning:
/*      1/1	RAST		C
 84.360	Nim Zengule	C#/Db
 145.112	Zengule		Cᵻ/Dƀ
 192.180	Dik Zengule	Dd
 9/8	DUGAH		D
 292.180	Kurdi		D#/Eb
 60/49	Dik Kurdi	Dᵻ/Eƀ
 364.735	Nerm Segah	Ed
 5/4	SEGAH		E
 415.677	Buselik		E‡
 4/3	CHARGAH		F
 584.359	Nim Hijaz	F#/Gb
 635.300	Hijaz/Saba	Fᵻ/Gƀ
 696.090	Dik Hijaz/Saba	Gd
 3/2	NEVA		G
 788.270	Nim Hisar	G#/Ab
 854.924	Hisar		Gᵻ/Aƀ
 888.270	Dik Hisar	Ad
 27/16	HUSEYNI		A	440hz
 16/9	Ajem		A#/Bb
 11/6	Dik Ajem	Aᵻ/Bƀ
 1074.547	Nerm Evdj	Bd
 15/8	EVDJ		B
 1125.488	Mahur		B‡
 2/1	GERDANIYE	C */
/*const float TouchkeyKeyDivisionMappingFactory::kDefaultTuningsCents[24] = {
    0, 84.36, 145.112, 192.18, 203.9, 292.18, 350.62, 364.74, 386.31, 415.677, 498.04, 584.359,
    635.3, 696.09, 701.95, 788.27, 854.92, 888.27, 905.87, 996.1, 1049.36, 1074.55, 1088.27, 1125.488
};*/

// Yarman-24c Turkish microtonal tuning:
/*   0:          1/1           C    Dbb   unison, perfect prime    RAST ♥
 1:         83.059 cents   C#   Db    				nim zengule
 2:        143.623 cents					zengule
 3:        191.771 cents   C##  Dd				dik zengule
 4:          9/8           D    Ebb   major whole tone		DÜGAH ♥
 5:        292.413 cents   D#   Eb				kürdi
 6:        348.343 cents   D#|  Eb-				dik kürdi
 7:        362.503 cents					nerm segah
 8:        156/125 cents   E					SEGAH ♥
 9:        415.305 cents   E| 					Buselik
 10:          4/3           F    Gbb   perfect fourth		ÇARGAH ♥
 11:        581.382 cents   F#   Gb				nim hicaz
 12:        634.184 cents					hicaz
 13:        695.885 cents   F##  Gd				dik hicaz
 14:          3/2           G    Abb   perfect fifth		NEVA ♥
 15:        788.736 cents   G#   Ab				nim hisar
 16:        853.063 cents					hisar
 17:        887.656 cents   G##  Ad				dik hisar
 18:         27/16          A    Bbb   Pyth. major sixth	HÜSEYNİ ♥
 19:         16/9           A#   Bb    Pyth. minor seventh	acem
 20:       1043.623 cents   A#|  Bb-				dik acem
 21:       1071.942 cents					nerm eviç
 22:        234/125 cents   B					EVİÇ ♥
 23:       1124.744 cents   B|					mahur
 24:          2/1           C    Dbb   octave			GERDANİYE ♥
*/

/*const float TouchkeyKeyDivisionMappingFactory::kDefaultTuningsCents[24] = {
    0, 83.059, 143.623, 191.771, 203.9, 292.413, 348.343, 362.503, 383.54, 415.305, 498.04, 581.382,
    634.184, 695.885, 701.95, 788.736, 853.063, 887.656, 905.87, 996.1, 1043.623, 1071.942, 1085.49, 1124.744
};*/

/* Yarman-24c as above but arranged for performance */
const float TouchkeyKeyDivisionMappingFactory::kDefaultTuningsCents[24] = {
    0, (1124.744 - 1200.0), 83.059, 143.623, 203.9, 191.771, 292.413, 348.343,
    383.54, 362.503, 498.04, 415.305, 581.382, 634.184, 695.885, 648.682,
    788.736, 853.063, 905.87, 887.656, 996.1, 1043.623, 1085.49, 1071.942,
};

/*const float TouchkeyKeyDivisionMappingFactory::kDefaultTuningsCents[24] = {
    0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700,
    750, 800, 850, 900, 950, 1000, 1050, 1100, 1150
};*/

/*const float TouchkeyKeyDivisionMappingFactory::kDefaultTuningsCents[36] = {
    0, 33.3, 66.6, 100, 133.3, 166.6, 200, 233.3, 266.6, 300, 333.3, 366.6,
    400, 433.3, 466.6, 500, 533.3, 566.6, 600, 633.3, 666.6, 700, 733.3, 766.6,
    800, 833.3, 866.6, 900, 933.3, 966.6, 1000, 1033.3, 1066.6, 1100, 1133.3, 1166.6
};*/

/* As arranged:
 *
 *   B|  Db/  Dd  Eb/  Ed  E|  Gb/  Gd  Ab/  Ad  Bb/  Bd
 *   C   C#   D   D#   E   F   F#   G   G#   A   A#   B
 */

TouchkeyKeyDivisionMappingFactory::TouchkeyKeyDivisionMappingFactory(PianoKeyboard &keyboard, MidiKeyboardSegment& segment)
: TouchkeyBaseMappingFactory<TouchkeyKeyDivisionMapping>(keyboard, segment),
  pitchWheelRangeSemitones_(kDefaultPitchWheelRangeSemitones),
  numSegmentsPerKey_(TouchkeyKeyDivisionMapping::kDefaultNumberOfSegments),
  timeout_(TouchkeyKeyDivisionMapping::kDefaultDetectionTimeout),
  detectionParameter_(TouchkeyKeyDivisionMapping::kDefaultDetectionParameter),
  retriggerable_(false),
  retriggerNumFrames_(TouchkeyKeyDivisionMapping::kDefaultRetriggerNumFrames),
  retriggerKeepsVelocity_(true),
  referenceNote_(0), globalOffsetCents_(0)
{
    //setName("/touchkeys/segmentpitch");
    setBendParameters();
}

void TouchkeyKeyDivisionMappingFactory::setMIDIPitchWheelRange(float maxBendSemitones) {
    if(maxBendSemitones <= 0)
        return;
    pitchWheelRangeSemitones_ = maxBendSemitones;
    
    setBendParameters();
}

void TouchkeyKeyDivisionMappingFactory::setName(const string& name) {
    TouchkeyBaseMappingFactory<TouchkeyKeyDivisionMapping>::setName(name);
    setBendParameters();
}

// Set the initial parameters for a new mapping
void TouchkeyKeyDivisionMappingFactory::initializeMappingParameters(int noteNumber, TouchkeyKeyDivisionMapping *mapping) {
    // KLUDGE: testing Maqam tunings. Go from absolute tunings in cents to pitch bends in semitones
    float tunings[2];
    int index = (noteNumber + 12 - referenceNote_) % 12;
    float standardTuning = (float)index * 100.0;
    tunings[0] = (kDefaultTuningsCents[index*2] - standardTuning + globalOffsetCents_) * .01;
    tunings[1] = (kDefaultTuningsCents[index*2 + 1] - standardTuning + globalOffsetCents_) * .01;
    mapping->setSegmentPitchBends(tunings, 2);
    /*float tunings[3];
    int index = (noteNumber + 12 - referenceNote_) % 12;
    float standardTuning = (float)index * 100.0;
    tunings[0] = (kDefaultTuningsCents[index*3] - standardTuning + globalOffsetCents_) * .01;
    tunings[1] = (kDefaultTuningsCents[index*3 + 1] - standardTuning + globalOffsetCents_) * .01;
    tunings[2] = (kDefaultTuningsCents[index*3 + 2] - standardTuning + globalOffsetCents_) * .01;
    mapping->setSegmentPitchBends(tunings, 3);*/

    
    mapping->setNumberOfSegments(numSegmentsPerKey_);
    mapping->setTimeout(timeout_);
    mapping->setDetectionParameter(detectionParameter_);
    mapping->setRetriggerable(retriggerable_, retriggerNumFrames_, retriggerKeepsVelocity_);
}

void TouchkeyKeyDivisionMappingFactory::setBendParameters() {
    setMidiParameters(MidiKeyboardSegment::kControlPitchWheel, -pitchWheelRangeSemitones_, pitchWheelRangeSemitones_, 0.0);
    
    if(midiConverter_ != 0) {
        midiConverter_->setMidiPitchWheelRange(pitchWheelRangeSemitones_);
        midiConverter_->listenToIncomingControl(MidiKeyboardSegment::kControlPitchWheel);
    }
}