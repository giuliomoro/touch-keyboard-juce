/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_3E71655728420A1E__
#define __JUCE_HEADER_3E71655728420A1E__

//[Headers]     -- You can add your own extra header files here --
#ifndef TOUCHKEYS_NO_GUI

#include "JuceHeader.h"
#include "TouchkeyKeyDivisionMappingFactory.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TouchkeyKeyDivisionMappingShortEditor  : public MappingEditorComponent,
                                               public TextEditor::Listener,
                                               public ComboBoxListener,
                                               public ButtonListener
{
public:
    //==============================================================================
    TouchkeyKeyDivisionMappingShortEditor (TouchkeyKeyDivisionMappingFactory& factory);
    ~TouchkeyKeyDivisionMappingShortEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void synchronize();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    TouchkeyKeyDivisionMappingFactory& factory_;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> tuningComboBox;
    ScopedPointer<Label> tuningLabel;
    ScopedPointer<Label> controlLabel;
    ScopedPointer<ComboBox> controlComboBox;
    ScopedPointer<ToggleButton> retriggerButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TouchkeyKeyDivisionMappingShortEditor)
};

//[EndFile] You can add extra defines here...
#endif  // TOUCHKEYS_NO_GUI
//[/EndFile]

#endif   // __JUCE_HEADER_3E71655728420A1E__
