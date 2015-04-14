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

#include "TouchkeyMultiFingerTriggerMappingShortEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const int TouchkeyMultiFingerTriggerMappingShortEditor::kNoteSame = 256;
const int TouchkeyMultiFingerTriggerMappingShortEditor::kNoteOffset = 1;
//[/MiscUserDefs]

//==============================================================================
TouchkeyMultiFingerTriggerMappingShortEditor::TouchkeyMultiFingerTriggerMappingShortEditor (TouchkeyMultiFingerTriggerMappingFactory& factory)
    : factory_(factory)
{
    addAndMakeVisible (controlLabel = new Label ("control label",
                                                 "Touches:"));
    controlLabel->setFont (Font (15.00f, Font::plain));
    controlLabel->setJustificationType (Justification::centredRight);
    controlLabel->setEditable (false, false, false);
    controlLabel->setColour (TextEditor::textColourId, Colours::black);
    controlLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (touchesComboBox = new ComboBox ("control combo box"));
    touchesComboBox->setEditableText (false);
    touchesComboBox->setJustificationType (Justification::centredLeft);
    touchesComboBox->setTextWhenNothingSelected (String::empty);
    touchesComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    touchesComboBox->addListener (this);

    addAndMakeVisible (controlLabel2 = new Label ("control label",
                                                  "Repeat Taps:"));
    controlLabel2->setFont (Font (15.00f, Font::plain));
    controlLabel2->setJustificationType (Justification::centredLeft);
    controlLabel2->setEditable (false, false, false);
    controlLabel2->setColour (TextEditor::textColourId, Colours::black);
    controlLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (tapsComboBox = new ComboBox ("control combo box"));
    tapsComboBox->setEditableText (false);
    tapsComboBox->setJustificationType (Justification::centredLeft);
    tapsComboBox->setTextWhenNothingSelected (String::empty);
    tapsComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    tapsComboBox->addListener (this);

    addAndMakeVisible (controlLabel3 = new Label ("control label",
                                                  "Note:"));
    controlLabel3->setFont (Font (15.00f, Font::plain));
    controlLabel3->setJustificationType (Justification::centredRight);
    controlLabel3->setEditable (false, false, false);
    controlLabel3->setColour (TextEditor::textColourId, Colours::black);
    controlLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (noteComboBox = new ComboBox ("control combo box"));
    noteComboBox->setEditableText (false);
    noteComboBox->setJustificationType (Justification::centredLeft);
    noteComboBox->setTextWhenNothingSelected (String::empty);
    noteComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    noteComboBox->addListener (this);

    addAndMakeVisible (sendOnReleaseButton = new ToggleButton ("new toggle button"));
    sendOnReleaseButton->setButtonText ("Also send on release");
    sendOnReleaseButton->addListener (this);


    //[UserPreSize]
    for(int i = 1; i <= 3; i++) {
        touchesComboBox->addItem(String(i), i);
    }
    for(int i = 1; i <= 5; i++) {
        tapsComboBox->addItem(String(i), i);
    }
    noteComboBox->addItem("Same", kNoteSame);
    for(int i = 0; i <= 127; i++) {
        noteComboBox->addItem(String(i), i + kNoteOffset);
    }
    //[/UserPreSize]

    setSize (328, 71);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TouchkeyMultiFingerTriggerMappingShortEditor::~TouchkeyMultiFingerTriggerMappingShortEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    controlLabel = nullptr;
    touchesComboBox = nullptr;
    controlLabel2 = nullptr;
    tapsComboBox = nullptr;
    controlLabel3 = nullptr;
    noteComboBox = nullptr;
    sendOnReleaseButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TouchkeyMultiFingerTriggerMappingShortEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TouchkeyMultiFingerTriggerMappingShortEditor::resized()
{
    controlLabel->setBounds (8, 8, 64, 24);
    touchesComboBox->setBounds (72, 8, 80, 24);
    controlLabel2->setBounds (160, 8, 80, 24);
    tapsComboBox->setBounds (240, 8, 80, 24);
    controlLabel3->setBounds (8, 40, 64, 24);
    noteComboBox->setBounds (72, 40, 80, 24);
    sendOnReleaseButton->setBounds (168, 40, 152, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TouchkeyMultiFingerTriggerMappingShortEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == touchesComboBox)
    {
        //[UserComboBoxCode_touchesComboBox] -- add your combo box handling code here..
        factory_.setTouchesForTrigger(touchesComboBox->getSelectedId());
        //[/UserComboBoxCode_touchesComboBox]
    }
    else if (comboBoxThatHasChanged == tapsComboBox)
    {
        //[UserComboBoxCode_tapsComboBox] -- add your combo box handling code here..
        factory_.setConsecutiveTapsForTrigger(tapsComboBox->getSelectedId());
        //[/UserComboBoxCode_tapsComboBox]
    }
    else if (comboBoxThatHasChanged == noteComboBox)
    {
        //[UserComboBoxCode_noteComboBox] -- add your combo box handling code here..
        int note = noteComboBox->getSelectedId();
        if(note == kNoteSame)
            note = -1;
        else
            note -= kNoteOffset;
        factory_.setTriggerOnNoteNumber(note);
        factory_.setTriggerOffNoteNumber(note);
        //[/UserComboBoxCode_noteComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void TouchkeyMultiFingerTriggerMappingShortEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == sendOnReleaseButton)
    {
        //[UserButtonCode_sendOnReleaseButton] -- add your button handler code here..
        if(sendOnReleaseButton->getToggleState()) {
            factory_.setTriggerOffAction(TouchkeyMultiFingerTriggerMapping::kActionNoteOn);
        }
        else {
            factory_.setTriggerOffAction(TouchkeyMultiFingerTriggerMapping::kActionNone);
        }
        //[/UserButtonCode_sendOnReleaseButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TouchkeyMultiFingerTriggerMappingShortEditor::synchronize() {
    touchesComboBox->setSelectedId(factory_.getTouchesForTrigger(), dontSendNotification);
    tapsComboBox->setSelectedId(factory_.getConsecutiveTapsForTrigger(), dontSendNotification);
    
    int note = factory_.getTriggerOnNoteNumber();
    if(note < 0)
        noteComboBox->setSelectedId(kNoteSame, dontSendNotification);
    else
        noteComboBox->setSelectedId(note + kNoteOffset, dontSendNotification);
    
    if(factory_.getTriggerOffAction() == TouchkeyMultiFingerTriggerMapping::kActionNoteOn)
        sendOnReleaseButton->setToggleState(true, dontSendNotification);
    else
        sendOnReleaseButton->setToggleState(false, dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TouchkeyMultiFingerTriggerMappingShortEditor"
                 componentName="" parentClasses="public MappingEditorComponent, public TextEditor::Listener"
                 constructorParams="TouchkeyMultiFingerTriggerMappingFactory&amp; factory"
                 variableInitialisers="factory_(factory)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="328"
                 initialHeight="71">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="control label" id="f953b12999632418" memberName="controlLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Touches:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <COMBOBOX name="control combo box" id="f1c84bb5fd2730fb" memberName="touchesComboBox"
            virtualName="" explicitFocusOrder="0" pos="72 8 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="control label" id="e3b829a3e4774248" memberName="controlLabel2"
         virtualName="" explicitFocusOrder="0" pos="160 8 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Repeat Taps:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="control combo box" id="26848818ea1ea5ea" memberName="tapsComboBox"
            virtualName="" explicitFocusOrder="0" pos="240 8 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="control label" id="858bbbef4bfb2c55" memberName="controlLabel3"
         virtualName="" explicitFocusOrder="0" pos="8 40 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Note:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <COMBOBOX name="control combo box" id="cb809b358724b54b" memberName="noteComboBox"
            virtualName="" explicitFocusOrder="0" pos="72 40 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="f75c92be72563883" memberName="sendOnReleaseButton"
                virtualName="" explicitFocusOrder="0" pos="168 40 152 24" buttonText="Also send on release"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
#endif      // TOUCHKEYS_NO_GUI
//[/EndFile]
