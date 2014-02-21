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

  MappingListComponent.cpp: manages a ListBox to display the current
  mappigns associated with a keyboard segment.
*/

#ifndef TOUCHKEYS_NO_GUI

#include "../JuceLibraryCode/JuceHeader.h"
#include "MappingListComponent.h"

//==============================================================================
MappingListComponent::MappingListComponent() : controller_(0), keyboardSegment_(0),
  lastMappingFactoryIdentifier_(-1) {
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(&listBox_);
    listBox_.setModel(this);
    listBox_.setColour(ListBox::outlineColourId, Colours::grey);
    listBox_.setOutlineThickness(1);
    listBox_.setRowHeight(72);
}

MappingListComponent::~MappingListComponent() {}

#if 0
void MappingListComponent::paint (Graphics& g) {
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
    g.drawText ("MappingListComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}
#endif

void MappingListComponent::resized() {
    // This method is where you should set the bounds of any child
    // components that your component contains..
    listBox_.setBoundsInset (BorderSize<int> (4));
}

// Delete the given factory from the mapping list
void MappingListComponent::deleteMapping(MappingFactory* factory) {
    if(keyboardSegment_ == 0 || factory == 0)
        return;
    keyboardSegment_->removeMappingFactory(factory);
}

int MappingListComponent::getNumRows() {
    if(controller_ == 0 || keyboardSegment_ == 0)
        return 0;
    return keyboardSegment_->mappingFactories().size();
}

// Given a row number and a possibly an existing component, return the component
// that should be drawn in this row of the list. Whenever a new component is created,
// the existing one should be deleted by this method (according to Juce docs).
Component* MappingListComponent::refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) {
    if(keyboardSegment_ == 0)
        return 0;

    //std::cout << "refreshing component for row " << rowNumber << " (given " << existingComponentToUpdate << ")\n";
    if(rowNumber < 0 || rowNumber >= getNumRows()) {
        if(existingComponentToUpdate != 0)
            delete existingComponentToUpdate;
        return 0;
    }
    
    // Get the current component for the row, creating it if it doesn't exist
    MappingListItem *listItem = static_cast<MappingListItem*>(existingComponentToUpdate);
    if(listItem == 0) {
        listItem = new MappingListItem(*this);
        listItem->setMappingFactory(keyboardSegment_->mappingFactories()[rowNumber]);
        //std::cout << "item " << listItem << " was updated to factory " << keyboardSegment_->mappingFactories()[rowNumber] << std::endl;
    }
    else {
        // Component exists; does it still point to a factory?
        if(rowNumber >= keyboardSegment_->mappingFactories().size()) {
            //std::cout << "Deleting component " << listItem << std::endl;
            delete listItem;
            return 0;
        }
        else if(keyboardSegment_->mappingFactories()[rowNumber] != listItem->mappingFactory()) {
            //std::cout << "Changing item " << listItem << " to point to factory " << keyboardSegment_->mappingFactories()[rowNumber] << std::endl;
            listItem->setMappingFactory(keyboardSegment_->mappingFactories()[rowNumber]);
        }
    }
    
    return listItem;
}

// Return whether a given component is selected or not (called by MappingListItem)
bool MappingListComponent::isComponentSelected(Component *component) {
    int rowNumber = listBox_.getRowNumberOfComponent(component);
    if(rowNumber < 0)
        return false;
    return listBox_.isRowSelected(rowNumber);
}


void MappingListComponent::synchronize()
{
    if(keyboardSegment_ != 0) {
        if(lastMappingFactoryIdentifier_ != keyboardSegment_->mappingFactoryUniqueIdentifier()) {
            lastMappingFactoryIdentifier_ = keyboardSegment_->mappingFactoryUniqueIdentifier();
            listBox_.updateContent();
        }
    }
    
    for(int i = 0; i < getNumRows(); i++) {
        MappingListItem *listItem = static_cast<MappingListItem*>(listBox_.getComponentForRowNumber(i));
        if(listItem != 0)
            listItem->synchronize();
    }
}

#endif  // TOUCHKEYS_NO_GUI
