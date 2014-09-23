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

  GraphicsDisplayWindow.h: window containing an OpenGL graphics display,
  for example the KeyboardDisplay visualization.
*/

#ifndef __GRAPHICSDISPLAYWINDOW_H_AD5467BB__
#define __GRAPHICSDISPLAYWINDOW_H_AD5467BB__

#ifndef TOUCHKEYS_NO_GUI

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Display/KeyboardDisplay.h"
#include "../Display/OpenGLJuceCanvas.h"

//==============================================================================
/*
*/
class GraphicsDisplayWindow    : public DocumentWindow
{
public:
    GraphicsDisplayWindow(String name, KeyboardDisplay& display)
    : DocumentWindow(name, Colours::lightgrey, DocumentWindow::allButtons, false),
      display_(display)
    {
        // Initialize an OpenGL graphics object as the content with a default size
        OpenGLJuceCanvas *canvas = new OpenGLJuceCanvas(display_);
        canvas->setSize(300,200);
        
        // Set properties
        setContentOwned(canvas, true);
        setUsingNativeTitleBar(true);
        setResizable(true, true);
        getConstrainer()->setFixedAspectRatio(display_.keyboardAspectRatio());
        setBoundsConstrained(getBounds());
        
        // Don't show window yet
        setVisible(false);
    }

    ~GraphicsDisplayWindow()
    {
    }
    
    void closeButtonPressed()
    {
        setVisible(false);
    }


private:
    KeyboardDisplay& display_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicsDisplayWindow)
};

#endif  // TOUCHKEYS_NO_GUI

#endif  // __GRAPHICSDISPLAYWINDOW_H_AD5467BB__
