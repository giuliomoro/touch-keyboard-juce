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

#ifndef __JUCE_HEADER_24D73157539FBFD0__
#define __JUCE_HEADER_24D73157539FBFD0__

//[Headers]     -- You can add your own extra header files here --
#ifndef TOUCHKEYS_NO_GUI

#include "JuceHeader.h"
#include "TouchkeyReleaseAngleMappingFactory.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TouchkeyReleaseAngleMappingExtendedEditor  : public MappingEditorComponent,
                                                   public TextEditor::Listener,
                                                   public ComboBox::Listener,
                                                   public Button::Listener
{
public:
    //==============================================================================
    TouchkeyReleaseAngleMappingExtendedEditor (TouchkeyReleaseAngleMappingFactory& factory);
    ~TouchkeyReleaseAngleMappingExtendedEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorTextChanged(TextEditor &editor) {}
    void textEditorReturnKeyPressed(TextEditor &editor);
    void textEditorEscapeKeyPressed(TextEditor &editor);
    void textEditorFocusLost(TextEditor &editor);

    void synchronize();
    String getDescription();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void intToString(char *st, int value);
    
    String getDescriptionHelper(String baseName);

    TouchkeyReleaseAngleMappingFactory& factory_;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> titleLabel;
    ScopedPointer<Label> presetLabel;
    ScopedPointer<ComboBox> presetComboBox;
    ScopedPointer<Label> presetLabel2;
    ScopedPointer<TextEditor> windowLengthEditor;
    ScopedPointer<Label> presetLabel3;
    ScopedPointer<Label> presetLabel4;
    ScopedPointer<TextEditor> upMinSpeedEditor;
    ScopedPointer<Label> presetLabel5;
    ScopedPointer<TextEditor> upNote1Editor;
    ScopedPointer<Label> presetLabel6;
    ScopedPointer<TextEditor> upNote2Editor;
    ScopedPointer<TextEditor> upNote3Editor;
    ScopedPointer<Label> presetLabel7;
    ScopedPointer<TextEditor> upVelocity1Editor;
    ScopedPointer<TextEditor> upVelocity2Editor;
    ScopedPointer<TextEditor> upVelocity3Editor;
    ScopedPointer<Label> presetLabel8;
    ScopedPointer<TextEditor> downMinSpeedEditor;
    ScopedPointer<Label> presetLabel9;
    ScopedPointer<TextEditor> downNote1Editor;
    ScopedPointer<Label> presetLabel10;
    ScopedPointer<TextEditor> downNote2Editor;
    ScopedPointer<TextEditor> downNote3Editor;
    ScopedPointer<Label> presetLabel11;
    ScopedPointer<TextEditor> downVelocity1Editor;
    ScopedPointer<TextEditor> downVelocity2Editor;
    ScopedPointer<TextEditor> downVelocity3Editor;
    ScopedPointer<ToggleButton> upEnableButton;
    ScopedPointer<ToggleButton> downEnableButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TouchkeyReleaseAngleMappingExtendedEditor)
};

//[EndFile] You can add extra defines here...
#endif      // TOUCHKEYS_NO_GUI
//[/EndFile]

#endif   // __JUCE_HEADER_24D73157539FBFD0__
