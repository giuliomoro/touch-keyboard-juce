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

  KeyPositionGraphDisplay.h: implements a graph of key position over time
  for a specific key press, which is useful for analysis of continuous key
  position.
*/

#ifndef __touchkeys__KeyPositionGraphDisplay__
#define __touchkeys__KeyPositionGraphDisplay__

#include <iostream>
#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../TouchKeys/PianoTypes.h"
#include "../Utility/Node.h"
#include "OpenGLDisplayBase.h"



// This class uses OpenGL to handle drawing of a graph showing key position
// over time, for debugging or analysis purposes.

class KeyPositionGraphDisplay : public OpenGLDisplayBase {
	// Internal data structures and constants
private:
    // Display margins
    static const float kDisplaySideMargin;
    static const float kDisplayBottomMargin;
    static const float kDisplayTopMargin;
    
    // Size of the graph area
    static const float kDisplayGraphWidth;
    static const float kDisplayGraphHeight;
    
	typedef struct {
		float x;
		float y;
	} Point;
	
public:
	KeyPositionGraphDisplay();
	
	// Setup methods for display size and keyboard range
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
    
    // Data update methods
    void copyKeyDataFromBuffer(Node<key_position>& keyBuffer, const Node<key_position>::size_type startIndex,
                               const Node<key_position>::size_type endIndex);
    void setKeyPressStart(key_position position, timestamp_type timestamp) {
        pressStartTimestamp_ = timestamp;
        pressStartPosition_ = position;
        needsUpdate_ = true;
    }
    void setKeyPressFinish(key_position position, timestamp_type timestamp) {
        pressFinishTimestamp_ = timestamp;
        pressFinishPosition_ = position;
        needsUpdate_ = true;
    }
    void setKeyReleaseStart(key_position position, timestamp_type timestamp) {
        releaseStartTimestamp_ = timestamp;
        releaseStartPosition_ = position;
        needsUpdate_ = true;
    }
    void setKeyReleaseFinish(key_position position, timestamp_type timestamp) {
        releaseFinishTimestamp_ = timestamp;
        releaseFinishPosition_ = position;
        needsUpdate_ = true;
    }
    
private:
    // Convert mathematical XY coordinate space to drawing positions
    float graphToDisplayX(float x);
    float graphToDisplayY(float y);
    
	void refreshViewport();
	
	// Conversion from internal coordinate space to external pixel values and back
	Point screenToInternal(Point& inPoint);
	Point internalToScreen(Point& inPoint);
	
    
private:
	float displayPixelWidth_, displayPixelHeight_;	// Pixel resolution of the surrounding window
	float totalDisplayWidth_, totalDisplayHeight_;	// Size of the internal view (centered around origin)
    float xMin_, xMax_, yMin_, yMax_;               // Coordinates for the graph axes

	bool needsUpdate_;								// Whether the keyboard should be redrawn
	CriticalSection displayMutex_;					// Synchronize access between data and display threads
    
    std::vector<key_position> keyPositions_;        // Positions (0-1 normalized) of the key
    std::vector<timestamp_type> keyTimestamps_;     // Timestamps corresponding to the above positions
    
    // Details on features of key motion: start, end, release, etc.
    key_position pressStartPosition_, pressFinishPosition_;
    timestamp_type pressStartTimestamp_, pressFinishTimestamp_;
    key_position releaseStartPosition_, releaseFinishPosition_;
    timestamp_type releaseStartTimestamp_, releaseFinishTimestamp_;
};


#endif /* defined(__touchkeys__KeyPositionGraphDisplay__) */
