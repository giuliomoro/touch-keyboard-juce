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

#ifndef __JUCE_HEADER_FBFB213EC27EA3A0__
#define __JUCE_HEADER_FBFB213EC27EA3A0__

//[Headers]     -- You can add your own extra header files here --
#ifndef TOUCHKEYS_NO_GUI

#include "JuceHeader.h"
#include "TouchkeyPitchBendMappingFactory.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TouchkeyPitchBendMappingShortEditor  : public MappingEditorComponent,
                                             public TextEditor::Listener,
                                             public ComboBoxListener
{
public:
    //==============================================================================
    TouchkeyPitchBendMappingShortEditor (TouchkeyPitchBendMappingFactory& factory);
    ~TouchkeyPitchBendMappingShortEditor();

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
    TouchkeyPitchBendMappingFactory& factory_;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> rangeEditor;
    ScopedPointer<Label> rangeLabel;
    ScopedPointer<TextEditor> thresholdEditor;
    ScopedPointer<Label> thresholdLabel;
    ScopedPointer<Label> controlLabel;
    ScopedPointer<ComboBox> endpointsComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TouchkeyPitchBendMappingShortEditor)
};

//[EndFile] You can add extra defines here...
#endif      // TOUCHKEYS_NO_GUI
//[/EndFile]

#endif   // __JUCE_HEADER_FBFB213EC27EA3A0__
