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

#include "TouchkeyControlMappingShortEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TouchkeyControlMappingShortEditor::TouchkeyControlMappingShortEditor (TouchkeyControlMappingFactory& factory)
    : factory_(factory)
{
    addAndMakeVisible (inputRangeLowEditor = new TextEditor ("range low text editor"));
    inputRangeLowEditor->setMultiLine (false);
    inputRangeLowEditor->setReturnKeyStartsNewLine (false);
    inputRangeLowEditor->setReadOnly (false);
    inputRangeLowEditor->setScrollbarsShown (true);
    inputRangeLowEditor->setCaretVisible (true);
    inputRangeLowEditor->setPopupMenuEnabled (true);
    inputRangeLowEditor->setText (String::empty);

    addAndMakeVisible (rangeLabel = new Label ("range label",
                                               "Input Range:"));
    rangeLabel->setFont (Font (15.00f, Font::plain));
    rangeLabel->setJustificationType (Justification::centredLeft);
    rangeLabel->setEditable (false, false, false);
    rangeLabel->setColour (TextEditor::textColourId, Colours::black);
    rangeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (controlLabel2 = new Label ("control label",
                                                  "Parameter:"));
    controlLabel2->setFont (Font (15.00f, Font::plain));
    controlLabel2->setJustificationType (Justification::centredLeft);
    controlLabel2->setEditable (false, false, false);
    controlLabel2->setColour (TextEditor::textColourId, Colours::black);
    controlLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (parameterComboBox = new ComboBox ("parameter combo box"));
    parameterComboBox->setEditableText (false);
    parameterComboBox->setJustificationType (Justification::centredLeft);
    parameterComboBox->setTextWhenNothingSelected (String::empty);
    parameterComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    parameterComboBox->addListener (this);

    addAndMakeVisible (controlLabel3 = new Label ("control label",
                                                  "Type:"));
    controlLabel3->setFont (Font (15.00f, Font::plain));
    controlLabel3->setJustificationType (Justification::centredLeft);
    controlLabel3->setEditable (false, false, false);
    controlLabel3->setColour (TextEditor::textColourId, Colours::black);
    controlLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (typeComboBox = new ComboBox ("type combo box"));
    typeComboBox->setEditableText (false);
    typeComboBox->setJustificationType (Justification::centredLeft);
    typeComboBox->setTextWhenNothingSelected (String::empty);
    typeComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    typeComboBox->addListener (this);

    addAndMakeVisible (inputRangeHighEditor = new TextEditor ("range hi text editor"));
    inputRangeHighEditor->setMultiLine (false);
    inputRangeHighEditor->setReturnKeyStartsNewLine (false);
    inputRangeHighEditor->setReadOnly (false);
    inputRangeHighEditor->setScrollbarsShown (true);
    inputRangeHighEditor->setCaretVisible (true);
    inputRangeHighEditor->setPopupMenuEnabled (true);
    inputRangeHighEditor->setText (String::empty);

    addAndMakeVisible (rangeLabel2 = new Label ("range label",
                                                "-"));
    rangeLabel2->setFont (Font (15.00f, Font::plain));
    rangeLabel2->setJustificationType (Justification::centredLeft);
    rangeLabel2->setEditable (false, false, false);
    rangeLabel2->setColour (TextEditor::textColourId, Colours::black);
    rangeLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    parameterComboBox->addItem("X Position", TouchkeyControlMapping::kInputParameterXPosition);
    parameterComboBox->addItem("Y Position", TouchkeyControlMapping::kInputParameterYPosition);
    parameterComboBox->addItem("Contact Area", TouchkeyControlMapping::kInputParameterTouchSize);
    parameterComboBox->addItem("2-Finger Mean", TouchkeyControlMapping::kInputParameter2FingerMean);
    parameterComboBox->addItem("2-Finger Distance", TouchkeyControlMapping::kInputParameter2FingerDistance);

    typeComboBox->addItem("Absolute", TouchkeyControlMapping::kTypeAbsolute);
    typeComboBox->addItem("1st Touch Relative", TouchkeyControlMapping::kTypeFirstTouchRelative);
    typeComboBox->addItem("Note Onset Relative", TouchkeyControlMapping::kTypeNoteOnsetRelative);

    controlComboBox->addItem("Pitch Wheel", MidiKeyboardSegment::kControlPitchWheel);
    controlComboBox->addItem("Channel Pressure", MidiKeyboardSegment::kControlChannelAftertouch);
    controlComboBox->addItem("Poly Aftertouch", MidiKeyboardSegment::kControlPolyphonicAftertouch);
    for(int i = 1; i <= 119; i++) {
        controlComboBox->addItem(String(i), i);
    }
    //[/UserPreSize]

    setSize (328, 71);


    //[Constructor] You can add your own custom stuff here..
    inputRangeLowEditor->addListener(this);
    inputRangeHighEditor->addListener(this);
    //[/Constructor]
}

TouchkeyControlMappingShortEditor::~TouchkeyControlMappingShortEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    inputRangeLowEditor = nullptr;
    rangeLabel = nullptr;
    controlLabel = nullptr;
    controlComboBox = nullptr;
    controlLabel2 = nullptr;
    parameterComboBox = nullptr;
    controlLabel3 = nullptr;
    typeComboBox = nullptr;
    inputRangeHighEditor = nullptr;
    rangeLabel2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TouchkeyControlMappingShortEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TouchkeyControlMappingShortEditor::resized()
{
    inputRangeLowEditor->setBounds (80, 40, 40, 24);
    rangeLabel->setBounds (0, 40, 80, 24);
    controlLabel->setBounds (176, 8, 56, 24);
    controlComboBox->setBounds (232, 8, 88, 24);
    controlLabel2->setBounds (0, 8, 72, 24);
    parameterComboBox->setBounds (72, 8, 104, 24);
    controlLabel3->setBounds (184, 40, 56, 24);
    typeComboBox->setBounds (232, 40, 88, 24);
    inputRangeHighEditor->setBounds (136, 40, 40, 24);
    rangeLabel2->setBounds (120, 40, 16, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TouchkeyControlMappingShortEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == controlComboBox)
    {
        //[UserComboBoxCode_controlComboBox] -- add your combo box handling code here..
        int controller = controlComboBox->getSelectedId();
        factory_.setController(controller);
        //[/UserComboBoxCode_controlComboBox]
    }
    else if (comboBoxThatHasChanged == parameterComboBox)
    {
        //[UserComboBoxCode_parameterComboBox] -- add your combo box handling code here..
        int param = parameterComboBox->getSelectedId();
        factory_.setInputParameter(param);
        //[/UserComboBoxCode_parameterComboBox]
    }
    else if (comboBoxThatHasChanged == typeComboBox)
    {
        //[UserComboBoxCode_typeComboBox] -- add your combo box handling code here..
        int type = typeComboBox->getSelectedId();
        factory_.setInputType(type);
        //[/UserComboBoxCode_typeComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TouchkeyControlMappingShortEditor::textEditorReturnKeyPressed(TextEditor &editor)
{
    if(&editor == inputRangeLowEditor) {
        float range = atof(inputRangeLowEditor->getText().toUTF8());
        factory_.setRangeInputMin(range);
        factory_.setRangeInputCenter(range);
    }
    else if(&editor == inputRangeHighEditor) {
        float range = atof(inputRangeHighEditor->getText().toUTF8());
        factory_.setRangeInputMax(range);
    }
}

void TouchkeyControlMappingShortEditor::textEditorEscapeKeyPressed(TextEditor &editor)
{

}

void TouchkeyControlMappingShortEditor::textEditorFocusLost(TextEditor &editor)
{
    textEditorReturnKeyPressed(editor);
}

void TouchkeyControlMappingShortEditor::synchronize()
{
    // Update the editors to reflect the current status
    if(!inputRangeLowEditor->hasKeyboardFocus(true)) {
        float value = factory_.getRangeInputMin();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.2f", value);
#else
        snprintf(st, 16, "%.2f", value);
#endif
        inputRangeLowEditor->setText(st);
    }

    if(!inputRangeHighEditor->hasKeyboardFocus(true)) {
        float value = factory_.getRangeInputMax();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.2f", value);
#else
        snprintf(st, 16, "%.2f", value);
#endif

        inputRangeHighEditor->setText(st);
    }

    parameterComboBox->setSelectedId(factory_.getInputParameter(), dontSendNotification);
    typeComboBox->setSelectedId(factory_.getInputType(), dontSendNotification);
    controlComboBox->setSelectedId(factory_.getController(), dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TouchkeyControlMappingShortEditor"
                 componentName="" parentClasses="public MappingEditorComponent, public TextEditor::Listener"
                 constructorParams="TouchkeyControlMappingFactory&amp; factory"
                 variableInitialisers="factory_(factory)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="328"
                 initialHeight="71">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="range low text editor" id="db0f62c03a58af03" memberName="inputRangeLowEditor"
              virtualName="" explicitFocusOrder="0" pos="80 40 40 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="range label" id="1ca2d422f4c37b7f" memberName="rangeLabel"
         virtualName="" explicitFocusOrder="0" pos="0 40 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Range:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="control label" id="f953b12999632418" memberName="controlLabel"
         virtualName="" explicitFocusOrder="0" pos="176 8 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Control:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="control combo box" id="f1c84bb5fd2730fb" memberName="controlComboBox"
            virtualName="" explicitFocusOrder="0" pos="232 8 88 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="control label" id="5ef7c1b78fdcf616" memberName="controlLabel2"
         virtualName="" explicitFocusOrder="0" pos="0 8 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Parameter:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="parameter combo box" id="f12f6f6e31042be1" memberName="parameterComboBox"
            virtualName="" explicitFocusOrder="0" pos="72 8 104 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="control label" id="9ded92e82db31777" memberName="controlLabel3"
         virtualName="" explicitFocusOrder="0" pos="184 40 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="type combo box" id="82d38054016f6c4f" memberName="typeComboBox"
            virtualName="" explicitFocusOrder="0" pos="232 40 88 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="range hi text editor" id="c34ac3e87db289d1" memberName="inputRangeHighEditor"
              virtualName="" explicitFocusOrder="0" pos="136 40 40 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="range label" id="19e0ad80306cc4c0" memberName="rangeLabel2"
         virtualName="" explicitFocusOrder="0" pos="120 40 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="-" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
#endif  // TOUCHKEYS_NO_GUI
//[/EndFile]
