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

  KeyboardDisplay.h: displays the keyboard state, including active MIDI
  notes and current touch position and size.
*/

#ifndef KEYBOARD_DISPLAY_H
#define KEYBOARD_DISPLAY_H

#include <iostream>
#include <map>
//#include <OpenGL/gl.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../TouchKeys/KeyTouchFrame.h"
#include "OpenGLDisplayBase.h"


// This class uses OpenGL to implement the actual drawing of the piano keyboard graphics.
// Graphics include the current state of each key and the touches on the surface.

class KeyboardDisplay : public OpenGLDisplayBase {
	// Internal data structures and constants
private:
    // Display dimensions, normalized to the width of one white key
 
    static const float kWhiteKeyFrontWidth;
    static const float kBlackKeyWidth;
    static const float kWhiteKeyFrontLength;
    static const float kWhiteKeyBackLength;
    static const float kBlackKeyLength;
    static const float kInterKeySpacing;
    static const float kAnalogSliderVerticalSpacing;
    static const float kAnalogSliderLength;
    static const float kAnalogSliderWidth;
    static const float kAnalogSliderMinimumValue;
    static const float kAnalogSliderMaximumValue;
    static const float kAnalogSliderZeroLocation;
    static const float kAnalogSliderOneLocation;
    
    // Individual geometry for C, D, E, F, G, A, B, c'
    
    static const float kWhiteKeyBackOffsets[9];
    static const float kWhiteKeyBackWidths[9];
    
    // Display margins
    
    static const float kDisplaySideMargin;
    static const float kDisplayBottomMargin;
    static const float kDisplayTopMargin;
    
    // Key shape constants
    
    static const int kShapeForNote[12];
    static const int kWhiteToChromatic[7];
    static const float kWhiteKeyFrontBackCutoff;
    
    // Touch constants
    static const float kDisplayMinTouchSize;
    static const float kDisplayTouchSizeScaler;
    
    
	typedef struct {
        bool  active;
		float locH;
		float locV1;
		float locV2;
		float locV3;
		float size1;
		float size2;
		float size3;
	} TouchInfo;
	
	typedef struct {
		float x;
		float y;
	} Point;
	
public:
	KeyboardDisplay();
	
	// Setup methods for display size and keyboard range
	void setKeyboardRange(int lowest, int highest);
	float keyboardAspectRatio() { return totalDisplayWidth_ / totalDisplayHeight_; }
	void setDisplaySize(float width, float height);
	
	// Drawing methods
	bool needsRender() { return needsUpdate_; }
	void render();
	
	// Interaction methods
	void mouseDown(float x, float y);
	void mouseDragged(float x, float y);
	void mouseUp(float x, float y);
	void rightMouseDown(float x, float y);
	void rightMouseDragged(float x, float y);
	void rightMouseUp(float x, float y);
	
	// Take action associated with clicking a key.  These are called within the mouse
	// methods but may also be called externally.
	void keyClicked(int key);
	void keyRightClicked(int key);
	
	// State-change methods
	void setTouchForKey(int key, const KeyTouchFrame& touch);
	void clearTouchForKey(int key);
	void clearAllTouches();
    void setAnalogCalibrationStatusForKey(int key, bool isCalibrated);
	void setAnalogValueForKey(int key, float value);
    void clearAnalogData();
    void setMidiActive(int key, bool active);
    void clearMidiData();
    
    void setAnalogSensorsPresent(bool present) { analogSensorsPresent_ = present; }
	void setTouchSensorPresentForKey(int key, bool present);
	void setTouchSensingEnabled(bool enabled);
	
private:
	void drawWhiteKey(float x, float y, int shape, bool first, bool last, bool highlighted);
	void drawBlackKey(float x, float y, bool highlighted);
	
	void drawWhiteTouch(float x, float y, int shape, float touchLocH, float touchLocV, float touchSize);
	void drawBlackTouch(float x, float y, float touchLocH, float touchLocV, float touchSize);
    
    void drawAnalogSlider(float x, float y, bool calibrated, bool whiteKey, float value);
	
	// Indicate the shape of the given MIDI note.  0-6 for white keys C-B, -1 for black keys.
	// We handle unusual shaped keys at the top or bottom of the keyboard separately.
	
	int keyShape(int key) { 
		if(key < 0) return -1;
		return kShapeForNote[key % 12]; 
	}
	
	void refreshViewport();
	
	// Conversion from internal coordinate space to external pixel values and back
	Point screenToInternal(Point& inPoint);
	Point internalToScreen(Point& inPoint);
	
	// Figure out which key (if any) the current point corresponds to
	int keyForLocation(Point& internalPoint);
		
private:
	
	int lowestMidiNote_, highestMidiNote_;			// Which keys should be displayed (use MIDI note numbers)	
	float totalDisplayWidth_, totalDisplayHeight_;	// Size of the internal view (centered around origin)
    float displayPixelWidth_, displayPixelHeight_;	// Pixel resolution of the surrounding window
	bool needsUpdate_;								// Whether the keyboard should be redrawn
	int currentHighlightedKey_;						// What key is being clicked on at the moment
	bool touchSensingEnabled_;						// Whether touch-sensitive keys are being used
	bool touchSensingPresentOnKey_[128];			// Whether the key with this MIDI note has a touch sensor
    
    bool analogSensorsPresent_;                     // Whether the given device has analog sensors at all
    bool analogValueIsCalibratedForKey_[128];       // Whether the analog sensor is calibrated on this key
    float analogValueForKey_[128];                  // Latest analog sensor value for each key
    bool midiActiveForKey_[128];                    // Whether the MIDI note is on for each key
	
    TouchInfo currentTouches_[128];                 // Touch data for each key
    TouchInfo currentTouchesMirror_[128];           // Mirror of the above, used for active display
	//std::map<int, TouchInfo> currentTouches_;		// Collection of current touch data
	CriticalSection displayMutex_;					// Synchronize access between data and display threads
};

#endif /* KEYBOARD_DISPLAY_H */