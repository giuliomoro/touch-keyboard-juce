/*
  ==============================================================================

    MappingExtendedEditorWindow.h
    Created: 18 Jun 2014 10:57:00am
    Author:  Andrew McPherson

  ==============================================================================
*/

#ifndef MAPPINGEXTENDEDEDITORWINDOW_H_INCLUDED
#define MAPPINGEXTENDEDEDITORWINDOW_H_INCLUDED

#ifndef TOUCHKEYS_NO_GUI

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../TouchKeys/MidiKeyboardSegment.h"
#include "../Mappings/MappingFactory.h"
#include "MappingListComponent.h"

//==============================================================================
/*
*/
class MappingExtendedEditorWindow    : public DocumentWindow
{
public:
    MappingExtendedEditorWindow(MappingListComponent& listComponent,
                                MidiKeyboardSegment& segment, MappingFactory& factory)
    : DocumentWindow("", Colours::lightgrey, DocumentWindow::minimiseButton | DocumentWindow::closeButton),
      listComponent_(listComponent), segment_(segment), factory_(factory), editor_(0)
    {
        setUsingNativeTitleBar(true);
        setResizable(false, false);
        
        if((segment_.indexOfMappingFactory(&factory_) >= 0) && factory_.hasExtendedEditor()) {
            editor_ = factory_.createExtendedEditor();
        
            // Set properties
            setContentOwned(editor_, true);
            
            // Start interface in sync
            editor_->synchronize();
        }
        
        // Show window
        setTopLeftPosition(60,60);
        setVisible(true);
    }

    ~MappingExtendedEditorWindow()
    {
    }

    // Method used by Juce timer which we will use for periodic UI updates
    // from the underlying system state
    void synchronize() {
        if(editor_ == 0)
            return;
        editor_->synchronize();
        setName(editor_->getDescription());
    }
    
    // Check whether this window still points to a valid mapping
    bool isValid() {
        if(segment_.indexOfMappingFactory(&factory_) < 0)
            return false;
        return true;
    }
    
    // Return the factory associated with this window
    MappingFactory *factory() {
        return &factory_;
    }
    
    void closeButtonPressed() {
        // Close the window and delete it
        listComponent_.closeExtendedEditorWindow(this);
    }
    
    void resized() {
        // This method is where you should set the bounds of any child
        // components that your component contains..
    }

private:
    MappingListComponent& listComponent_;
    MidiKeyboardSegment& segment_;
    MappingFactory& factory_;
    MappingEditorComponent *editor_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MappingExtendedEditorWindow)
};

#endif      // TOUCHKEYS_NO_GUI

#endif  // MAPPINGEXTENDEDEDITORWINDOW_H_INCLUDED
