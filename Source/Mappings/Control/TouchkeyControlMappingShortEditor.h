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

#ifndef __JUCE_HEADER_61C9A7081A6F3E0__
#define __JUCE_HEADER_61C9A7081A6F3E0__

//[Headers]     -- You can add your own extra header files here --
#ifndef TOUCHKEYS_NO_GUI

#include "JuceHeader.h"
#include "TouchkeyControlMappingFactory.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TouchkeyControlMappingShortEditor  : public MappingEditorComponent,
                                           public TextEditor::Listener,
                                           public ComboBox::Listener
{
public:
    //==============================================================================
    TouchkeyControlMappingShortEditor (TouchkeyControlMappingFactory& factory);
    ~TouchkeyControlMappingShortEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    // TextEditor listener methods
    void textEditorTextChanged(TextEditor &editor) {}
    void textEditorReturnKeyPressed(TextEditor &editor);
    void textEditorEscapeKeyPressed(TextEditor &editor);
    void textEditorFocusLost(TextEditor &editor);

    void synchronize();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    TouchkeyControlMappingFactory& factory_;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> inputRangeLowEditor;
    ScopedPointer<Label> rangeLabel;
    ScopedPointer<Label> controlLabel;
    ScopedPointer<ComboBox> controlComboBox;
    ScopedPointer<Label> controlLabel2;
    ScopedPointer<ComboBox> parameterComboBox;
    ScopedPointer<Label> controlLabel3;
    ScopedPointer<ComboBox> typeComboBox;
    ScopedPointer<TextEditor> inputRangeHighEditor;
    ScopedPointer<Label> rangeLabel2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TouchkeyControlMappingShortEditor)
};

//[EndFile] You can add extra defines here...
#endif      // TOUCHKEYS_NO_GUI
//[/EndFile]

#endif   // __JUCE_HEADER_61C9A7081A6F3E0__
