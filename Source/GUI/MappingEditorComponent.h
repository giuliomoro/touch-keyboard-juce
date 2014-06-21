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

  MappingEditorComponent.h: Juce Component subclass from which all
  mapping editors inherit.
*/


#ifndef __MAPPINGEDITORCOMPONENT_H_C93E7296__
#define __MAPPINGEDITORCOMPONENT_H_C93E7296__

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MappingEditorComponent    : public Component
{
public:
    MappingEditorComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    virtual ~MappingEditorComponent()
    {
    }
    
    // Method to synchronize the GUI state to the underlying
    // state of the mapping. Implemented in the subclass.
    virtual void synchronize() {}
    
    // Get a human-readable name for the mapping
    // Generally, extended editors should implement this but short editors
    // don't need to
    virtual String getDescription() { return "Mapping"; }

    virtual void paint (Graphics& g)
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (Colours::white);   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::lightblue);
        g.setFont (14.0f);
        g.drawText ("MappingEditorComponent", getLocalBounds(),
                    Justification::centred, true);   // draw some placeholder text
    }

    virtual void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MappingEditorComponent)
};


#endif  // __MAPPINGEDITORCOMPONENT_H_C93E7296__
