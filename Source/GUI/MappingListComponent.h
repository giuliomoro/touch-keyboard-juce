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

  MappingListComponent.h: manages a ListBox to display the current
  mappigns associated with a keyboard segment.
*/

#ifndef TOUCHKEYS_NO_GUI

#ifndef __MAPPINGLISTCOMPONENT_H_51502151__
#define __MAPPINGLISTCOMPONENT_H_51502151__

#include <vector>
#include <list>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../MainApplicationController.h"
#include "../TouchKeys/MidiKeyboardSegment.h"
#include "MappingListItem.h"
#include "../Mappings/MappingFactory.h"

class MappingExtendedEditorWindow;

//==============================================================================
/*
*/
class MappingListComponent    : public Component, public ListBoxModel
{
public:
    MappingListComponent();
    ~MappingListComponent();

    //void paint (Graphics&);
    void resized();
    
    // *** Mapping management methods ***
    
    // Attach the user interface to the controller and vice-versa
    void setMainApplicationController(MainApplicationController *controller) {
        controller_ = controller;
        if(keyboardSegment_ != 0)
            listBox_.updateContent();
    }
    void setKeyboardSegment(MidiKeyboardSegment *segment) {
        keyboardSegment_ = segment;
        if(controller_ != 0)
            listBox_.updateContent();
    }
    
    // Add or delete a mapping based on a Factory class created elsewhere
    void addMapping(MappingFactory* factory);
    void deleteMapping(MappingFactory* factory);
    
    // Return which segment this component refers to
    int segmentNumber() {
        if(keyboardSegment_ == 0)
            return -1;
        return keyboardSegment_->outputPort();
    }

    // *** ListBox methods ***
    int getNumRows();
    void paintListBoxItem(int rowNumber,
                          Graphics& g,
                          int width, int height,
                          bool rowIsSelected) {}
    Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate);

    // *** UI management methods ***
    // Return whether a given component is selected or not (called by MappingListItem)
    bool isComponentSelected(Component *component);
    
    // Update UI state to reflect underlying system state
    void synchronize();
    
    // *** Extended editor window methods ***
    // Open an extended editor window for the given component
    void openExtendedEditorWindow(MappingFactory *factory);
    
    // Close an extended editor window and remove it from the list
    void closeExtendedEditorWindow(MappingExtendedEditorWindow *window);
    
    // Find an extended editor window for a given factory, if it exists
    MappingExtendedEditorWindow *extendedEditorWindowForFactory(MappingFactory *factory);
    
private:
    // Sync the UI for the extended editor windows
    void synchronizeExtendedEditorWindows();
    
    // Internal helper function for closing window
    void closeExtendedEditorWindowHelper(MappingExtendedEditorWindow *window);
    
    // Find the invalid editor windows and clsoe them
    void updateExtendedEditorWindows();
    
    // Close all extended editor windows
    void clearExtendedEditorWindows();
    
    ListBox listBox_;
    MainApplicationController *controller_;
    MidiKeyboardSegment *keyboardSegment_;
    
    CriticalSection extendedEditorWindowsMutex_;
    list<MappingExtendedEditorWindow*> extendedEditorWindows_;
    
    int lastMappingFactoryIdentifier_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MappingListComponent)
};


#endif  // __MAPPINGLISTCOMPONENT_H_51502151__

#endif  // TOUCHKEYS_NO_GUI
