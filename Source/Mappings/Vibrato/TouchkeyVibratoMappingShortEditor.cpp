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

//[Headers] You can add your own extra header files here...
#ifndef TOUCHKEYS_NO_GUI
//[/Headers]

#include "TouchkeyVibratoMappingShortEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TouchkeyVibratoMappingShortEditor::TouchkeyVibratoMappingShortEditor (TouchkeyVibratoMappingFactory& factory)
    : factory_(factory)
{
    addAndMakeVisible (rangeEditor = new TextEditor ("range text editor"));
    rangeEditor->setMultiLine (false);
    rangeEditor->setReturnKeyStartsNewLine (false);
    rangeEditor->setReadOnly (false);
    rangeEditor->setScrollbarsShown (true);
    rangeEditor->setCaretVisible (true);
    rangeEditor->setPopupMenuEnabled (true);
    rangeEditor->setText (String::empty);

    addAndMakeVisible (rangeLabel = new Label ("range label",
                                               "Range:"));
    rangeLabel->setFont (Font (15.00f, Font::plain));
    rangeLabel->setJustificationType (Justification::centredLeft);
    rangeLabel->setEditable (false, false, false);
    rangeLabel->setColour (TextEditor::textColourId, Colours::black);
    rangeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (thresholdEditor = new TextEditor ("threshold text editor"));
    thresholdEditor->setMultiLine (false);
    thresholdEditor->setReturnKeyStartsNewLine (false);
    thresholdEditor->setReadOnly (false);
    thresholdEditor->setScrollbarsShown (true);
    thresholdEditor->setCaretVisible (true);
    thresholdEditor->setPopupMenuEnabled (true);
    thresholdEditor->setText (String::empty);

    addAndMakeVisible (thresholdLabel = new Label ("threshold label",
                                                   "Threshold:"));
    thresholdLabel->setFont (Font (15.00f, Font::plain));
    thresholdLabel->setJustificationType (Justification::centredLeft);
    thresholdLabel->setEditable (false, false, false);
    thresholdLabel->setColour (TextEditor::textColourId, Colours::black);
    thresholdLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (controlLabel = new Label ("control label",
                                                 "Control:"));
    controlLabel->setFont (Font (15.00f, Font::plain));
    controlLabel->setJustificationType (Justification::centredLeft);
    controlLabel->setEditable (false, false, false);
    controlLabel->setColour (TextEditor::textColourId, Colours::black);
    controlLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (controlComboBox = new ComboBox ("control combo box"));
    controlComboBox->setEditableText (false);
    controlComboBox->setJustificationType (Justification::centredLeft);
    controlComboBox->setTextWhenNothingSelected (String::empty);
    controlComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    controlComboBox->addListener (this);


    //[UserPreSize]
    // Populate controllers field
    controlComboBox->addItem("Pitch Wheel", MidiKeyboardSegment::kControlPitchWheel);
    for(int i = 1; i <= 120; i++) {
        controlComboBox->addItem(String(i), i);
    }
    //[/UserPreSize]

    setSize (328, 71);


    //[Constructor] You can add your own custom stuff here..
    rangeEditor->addListener(this);
    thresholdEditor->addListener(this);
    //[/Constructor]
}

TouchkeyVibratoMappingShortEditor::~TouchkeyVibratoMappingShortEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    rangeEditor = nullptr;
    rangeLabel = nullptr;
    thresholdEditor = nullptr;
    thresholdLabel = nullptr;
    controlLabel = nullptr;
    controlComboBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TouchkeyVibratoMappingShortEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TouchkeyVibratoMappingShortEditor::resized()
{
    rangeEditor->setBounds (64, 8, 88, 24);
    rangeLabel->setBounds (8, 8, 56, 24);
    thresholdEditor->setBounds (232, 8, 88, 24);
    thresholdLabel->setBounds (160, 8, 72, 24);
    controlLabel->setBounds (8, 40, 56, 24);
    controlComboBox->setBounds (64, 40, 88, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TouchkeyVibratoMappingShortEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == controlComboBox)
    {
        //[UserComboBoxCode_controlComboBox] -- add your combo box handling code here..
        int control = controlComboBox->getSelectedId();
        factory_.setVibratoControl(control);
        //[/UserComboBoxCode_controlComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TouchkeyVibratoMappingShortEditor::textEditorReturnKeyPressed(TextEditor &editor)
{
    if(&editor == rangeEditor) {
        float range = atof(rangeEditor->getText().toUTF8());
        factory_.setVibratoRange(range);
    }
    else if(&editor == thresholdEditor) {
        float threshold = atof(thresholdEditor->getText().toUTF8());
        factory_.setVibratoThreshold(threshold);
    }
}

void TouchkeyVibratoMappingShortEditor::textEditorEscapeKeyPressed(TextEditor &editor)
{

}

void TouchkeyVibratoMappingShortEditor::textEditorFocusLost(TextEditor &editor)
{
    textEditorReturnKeyPressed(editor);
}

void TouchkeyVibratoMappingShortEditor::synchronize()
{
    // Update the editors to reflect the current status
    if(!rangeEditor->hasKeyboardFocus(true)) {
        float value = factory_.getVibratoRange();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.2f", value);
#else
        snprintf(st, 16, "%.2f", value);
#endif

        rangeEditor->setText(st);
    }

    if(!thresholdEditor->hasKeyboardFocus(true)) {
        float value = factory_.getVibratoThreshold();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.2f", value);
#else
        snprintf(st, 16, "%.2f", value);
#endif

        thresholdEditor->setText(st);
    }

    controlComboBox->setSelectedId(factory_.getVibratoControl(), dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TouchkeyVibratoMappingShortEditor"
                 componentName="" parentClasses="public MappingEditorComponent, public TextEditor::Listener"
                 constructorParams="TouchkeyVibratoMappingFactory&amp; factory"
                 variableInitialisers="factory_(factory)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="328"
                 initialHeight="71">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="range text editor" id="db0f62c03a58af03" memberName="rangeEditor"
              virtualName="" explicitFocusOrder="0" pos="64 8 88 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="range label" id="1ca2d422f4c37b7f" memberName="rangeLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Range:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="threshold text editor" id="854a054d84eaf552" memberName="thresholdEditor"
              virtualName="" explicitFocusOrder="0" pos="232 8 88 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="threshold label" id="864de4f55b5481ee" memberName="thresholdLabel"
         virtualName="" explicitFocusOrder="0" pos="160 8 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Threshold:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="control label" id="f953b12999632418" memberName="controlLabel"
         virtualName="" explicitFocusOrder="0" pos="8 40 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Control:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="control combo box" id="f1c84bb5fd2730fb" memberName="controlComboBox"
            virtualName="" explicitFocusOrder="0" pos="64 40 88 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
#endif      // TOUCHKEYS_NO_GUI
//[/EndFile]
