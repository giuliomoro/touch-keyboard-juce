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

  RawSensorDisplay.h: simple graph for showing raw TouchKeys sensor values
*/

#ifndef __touchkeys__RawSensorDisplay__
#define __touchkeys__RawSensorDisplay__

#include <iostream>
#include <vector>
//#include <OpenGL/gl.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../TouchKeys/PianoTypes.h"
#include "../Utility/Node.h"
#include "OpenGLDisplayBase.h"


// This class uses OpenGL to draw a bar graph of key sensor data,
// for the purpose of debugging and validating individual keys

class RawSensorDisplay : public OpenGLDisplayBase {
	// Internal data structures and constants
private:
    // Display margins
    static const float kDisplaySideMargin;
    static const float kDisplayBottomMargin;
    static const float kDisplayTopMargin;
    
    // Size of bar graphs and spacing
    static const float kDisplayBarWidth;
    static const float kDisplayBarSpacing;
    static const float kDisplayBarHeight;
    
	typedef struct {
		float x;
		float y;
	} Point;
	
public:
	RawSensorDisplay();
	
	// Setup methods for display size and keyboard range
	void setDisplaySize(float width, float height);
    float aspectRatio() { return totalDisplayWidth_ / totalDisplayHeight_; }
	
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
    void setDisplayData(std::vector<int> const& values);
    
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
    float yMin_, yMax_;                             // Range of the graph axes
    
	bool needsUpdate_;								// Whether the keyboard should be redrawn
	CriticalSection displayMutex_;					// Synchronize access between data and display threads
    std::vector<int> displayValues_;                // Values to display as a bar graph
};

#endif /* defined(__touchkeys__RawSensorDisplay__) */
