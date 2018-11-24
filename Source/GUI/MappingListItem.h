/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_8369B097DBF9195A__
#define __JUCE_HEADER_8369B097DBF9195A__

//[Headers]     -- You can add your own extra header files here --
#ifndef TOUCHKEYS_NO_GUI

#include "JuceHeader.h"
#include "../Mappings/MappingFactory.h"

class MappingListComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MappingListItem  : public Component,
                         public Button::Listener
{
public:
    //==============================================================================
    MappingListItem (MappingListComponent& listComponent);
    ~MappingListItem();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    static void alertBoxResultChosen(int result, MappingListItem *item);
    void deleteMapping();

    MappingFactory* mappingFactory() { return factory_; }
    void setMappingFactory(MappingFactory *factory);
    void synchronize();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MappingFactory *factory_;
    MappingListComponent& listComponent_;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ToggleButton> bypassToggleButton;
    ScopedPointer<TextButton> showDetailsButton;
    ScopedPointer<Label> mappingTypeLabel;
    ScopedPointer<MappingEditorComponent> mappingShortEditorComponent;
    ScopedPointer<Label> noSettingsLabel;
    ScopedPointer<TextButton> deleteButton;
    Path internalPath1;
    Path internalPath2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MappingListItem)
};

//[EndFile] You can add extra defines here...
#endif // TOUCHKEYS_NO_GUI
//[/EndFile]

#endif   // __JUCE_HEADER_8369B097DBF9195A__
