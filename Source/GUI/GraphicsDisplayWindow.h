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
#include "../MainApplicationController.h"
#include "../Display/OpenGLJuceCanvas.h"

//==============================================================================
/*
*/
class GraphicsDisplayWindow    : public DocumentWindow
{
public:
    GraphicsDisplayWindow(String name, MainApplicationController& controller)
    : DocumentWindow(name, Colours::lightgrey, DocumentWindow::allButtons),
      controller_(controller)
    {
        // Initialize an OpenGL graphics object as the content with a default size
        OpenGLJuceCanvas *canvas = new OpenGLJuceCanvas(controller_.keyboardDisplay());
        canvas->setSize(300,200);
        
        // Set properties
        setContentOwned(canvas, true);
        setUsingNativeTitleBar(true);
        setResizable(true, true);
        getConstrainer()->setFixedAspectRatio(controller_.keyboardDisplay().keyboardAspectRatio());
        setBoundsConstrained(getBounds());
        
        // Show window
        setVisible(true);
    }

    ~GraphicsDisplayWindow()
    {
    }
    
    void closeButtonPressed()
    {
        setVisible(false);
    }


private:
    MainApplicationController& controller_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicsDisplayWindow)
};

#endif  // TOUCHKEYS_NO_GUI

#endif  // __GRAPHICSDISPLAYWINDOW_H_AD5467BB__
