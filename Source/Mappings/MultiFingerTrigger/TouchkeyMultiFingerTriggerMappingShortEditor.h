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

#ifndef __JUCE_HEADER_575F04D6673EEA8A__
#define __JUCE_HEADER_575F04D6673EEA8A__

//[Headers]     -- You can add your own extra header files here --
#ifndef TOUCHKEYS_NO_GUI

#include "JuceHeader.h"
#include "TouchkeyMultiFingerTriggerMappingFactory.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TouchkeyMultiFingerTriggerMappingShortEditor  : public MappingEditorComponent,
                                                      public TextEditor::Listener,
                                                      public ComboBox::Listener,
                                                      public Button::Listener
{
private:
    static const int kNoteSame;
    static const int kNoteOffset;
    
public:
    //==============================================================================
    TouchkeyMultiFingerTriggerMappingShortEditor (TouchkeyMultiFingerTriggerMappingFactory& factory);
    ~TouchkeyMultiFingerTriggerMappingShortEditor();

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
    TouchkeyMultiFingerTriggerMappingFactory& factory_;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> controlLabel;
    ScopedPointer<ComboBox> touchesComboBox;
    ScopedPointer<Label> controlLabel2;
    ScopedPointer<ComboBox> tapsComboBox;
    ScopedPointer<Label> controlLabel3;
    ScopedPointer<ComboBox> noteComboBox;
    ScopedPointer<ToggleButton> sendOnReleaseButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TouchkeyMultiFingerTriggerMappingShortEditor)
};

//[EndFile] You can add extra defines here...
#endif      // TOUCHKEYS_NO_GUI
//[/EndFile]

#endif   // __JUCE_HEADER_575F04D6673EEA8A__
