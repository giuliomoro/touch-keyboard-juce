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

#include "TouchkeyReleaseAngleMappingExtendedEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TouchkeyReleaseAngleMappingExtendedEditor::TouchkeyReleaseAngleMappingExtendedEditor (TouchkeyReleaseAngleMappingFactory& factory)
    : factory_(factory)
{
    addAndMakeVisible (titleLabel = new Label ("title label",
                                               TRANS("Release Angle Mapping (Zone N, #M)")));
    titleLabel->setFont (Font (15.00f, Font::bold));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (presetLabel = new Label ("preset label",
                                                TRANS("Preset:")));
    presetLabel->setFont (Font (15.00f, Font::plain));
    presetLabel->setJustificationType (Justification::centredLeft);
    presetLabel->setEditable (false, false, false);
    presetLabel->setColour (TextEditor::textColourId, Colours::black);
    presetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (presetComboBox = new ComboBox ("parameter combo box"));
    presetComboBox->setEditableText (false);
    presetComboBox->setJustificationType (Justification::centredLeft);
    presetComboBox->setTextWhenNothingSelected (String::empty);
    presetComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    presetComboBox->addListener (this);

    addAndMakeVisible (presetLabel2 = new Label ("preset label",
                                                 TRANS("Window Length:")));
    presetLabel2->setFont (Font (15.00f, Font::plain));
    presetLabel2->setJustificationType (Justification::centredLeft);
    presetLabel2->setEditable (false, false, false);
    presetLabel2->setColour (TextEditor::textColourId, Colours::black);
    presetLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (windowLengthEditor = new TextEditor ("range low text editor"));
    windowLengthEditor->setMultiLine (false);
    windowLengthEditor->setReturnKeyStartsNewLine (false);
    windowLengthEditor->setReadOnly (false);
    windowLengthEditor->setScrollbarsShown (true);
    windowLengthEditor->setCaretVisible (true);
    windowLengthEditor->setPopupMenuEnabled (true);
    windowLengthEditor->setText (String::empty);

    addAndMakeVisible (presetLabel3 = new Label ("preset label",
                                                 TRANS("ms. before release")));
    presetLabel3->setFont (Font (15.00f, Font::plain));
    presetLabel3->setJustificationType (Justification::centredLeft);
    presetLabel3->setEditable (false, false, false);
    presetLabel3->setColour (TextEditor::textColourId, Colours::black);
    presetLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (presetLabel4 = new Label ("preset label",
                                                 TRANS("Release Moving Up")));
    presetLabel4->setFont (Font (15.00f, Font::bold));
    presetLabel4->setJustificationType (Justification::centredLeft);
    presetLabel4->setEditable (false, false, false);
    presetLabel4->setColour (TextEditor::textColourId, Colours::black);
    presetLabel4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (upMinSpeedEditor = new TextEditor ("up release speed editor"));
    upMinSpeedEditor->setMultiLine (false);
    upMinSpeedEditor->setReturnKeyStartsNewLine (false);
    upMinSpeedEditor->setReadOnly (false);
    upMinSpeedEditor->setScrollbarsShown (true);
    upMinSpeedEditor->setCaretVisible (true);
    upMinSpeedEditor->setPopupMenuEnabled (true);
    upMinSpeedEditor->setText (String::empty);

    addAndMakeVisible (presetLabel5 = new Label ("preset label",
                                                 TRANS("Min. release speed:")));
    presetLabel5->setFont (Font (15.00f, Font::plain));
    presetLabel5->setJustificationType (Justification::centredRight);
    presetLabel5->setEditable (false, false, false);
    presetLabel5->setColour (TextEditor::textColourId, Colours::black);
    presetLabel5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (upNote1Editor = new TextEditor ("up note 1 editor"));
    upNote1Editor->setMultiLine (false);
    upNote1Editor->setReturnKeyStartsNewLine (false);
    upNote1Editor->setReadOnly (false);
    upNote1Editor->setScrollbarsShown (true);
    upNote1Editor->setCaretVisible (true);
    upNote1Editor->setPopupMenuEnabled (true);
    upNote1Editor->setText (String::empty);

    addAndMakeVisible (presetLabel6 = new Label ("preset label",
                                                 TRANS("Send notes:")));
    presetLabel6->setFont (Font (15.00f, Font::plain));
    presetLabel6->setJustificationType (Justification::centredRight);
    presetLabel6->setEditable (false, false, false);
    presetLabel6->setColour (TextEditor::textColourId, Colours::black);
    presetLabel6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (upNote2Editor = new TextEditor ("up note 2 editor"));
    upNote2Editor->setMultiLine (false);
    upNote2Editor->setReturnKeyStartsNewLine (false);
    upNote2Editor->setReadOnly (false);
    upNote2Editor->setScrollbarsShown (true);
    upNote2Editor->setCaretVisible (true);
    upNote2Editor->setPopupMenuEnabled (true);
    upNote2Editor->setText (String::empty);

    addAndMakeVisible (upNote3Editor = new TextEditor ("up note 3 editor"));
    upNote3Editor->setMultiLine (false);
    upNote3Editor->setReturnKeyStartsNewLine (false);
    upNote3Editor->setReadOnly (false);
    upNote3Editor->setScrollbarsShown (true);
    upNote3Editor->setCaretVisible (true);
    upNote3Editor->setPopupMenuEnabled (true);
    upNote3Editor->setText (String::empty);

    addAndMakeVisible (presetLabel7 = new Label ("preset label",
                                                 TRANS("With velocities:")));
    presetLabel7->setFont (Font (15.00f, Font::plain));
    presetLabel7->setJustificationType (Justification::centredRight);
    presetLabel7->setEditable (false, false, false);
    presetLabel7->setColour (TextEditor::textColourId, Colours::black);
    presetLabel7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (upVelocity1Editor = new TextEditor ("up velocity 1 editor"));
    upVelocity1Editor->setMultiLine (false);
    upVelocity1Editor->setReturnKeyStartsNewLine (false);
    upVelocity1Editor->setReadOnly (false);
    upVelocity1Editor->setScrollbarsShown (true);
    upVelocity1Editor->setCaretVisible (true);
    upVelocity1Editor->setPopupMenuEnabled (true);
    upVelocity1Editor->setText (String::empty);

    addAndMakeVisible (upVelocity2Editor = new TextEditor ("up velocity 2 editor"));
    upVelocity2Editor->setMultiLine (false);
    upVelocity2Editor->setReturnKeyStartsNewLine (false);
    upVelocity2Editor->setReadOnly (false);
    upVelocity2Editor->setScrollbarsShown (true);
    upVelocity2Editor->setCaretVisible (true);
    upVelocity2Editor->setPopupMenuEnabled (true);
    upVelocity2Editor->setText (String::empty);

    addAndMakeVisible (upVelocity3Editor = new TextEditor ("up velocity 3 editor"));
    upVelocity3Editor->setMultiLine (false);
    upVelocity3Editor->setReturnKeyStartsNewLine (false);
    upVelocity3Editor->setReadOnly (false);
    upVelocity3Editor->setScrollbarsShown (true);
    upVelocity3Editor->setCaretVisible (true);
    upVelocity3Editor->setPopupMenuEnabled (true);
    upVelocity3Editor->setText (String::empty);

    addAndMakeVisible (presetLabel8 = new Label ("preset label",
                                                 TRANS("Release Moving Down")));
    presetLabel8->setFont (Font (15.00f, Font::bold));
    presetLabel8->setJustificationType (Justification::centredLeft);
    presetLabel8->setEditable (false, false, false);
    presetLabel8->setColour (TextEditor::textColourId, Colours::black);
    presetLabel8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (downMinSpeedEditor = new TextEditor ("down release speed editor"));
    downMinSpeedEditor->setMultiLine (false);
    downMinSpeedEditor->setReturnKeyStartsNewLine (false);
    downMinSpeedEditor->setReadOnly (false);
    downMinSpeedEditor->setScrollbarsShown (true);
    downMinSpeedEditor->setCaretVisible (true);
    downMinSpeedEditor->setPopupMenuEnabled (true);
    downMinSpeedEditor->setText (String::empty);

    addAndMakeVisible (presetLabel9 = new Label ("preset label",
                                                 TRANS("Min. release speed:")));
    presetLabel9->setFont (Font (15.00f, Font::plain));
    presetLabel9->setJustificationType (Justification::centredRight);
    presetLabel9->setEditable (false, false, false);
    presetLabel9->setColour (TextEditor::textColourId, Colours::black);
    presetLabel9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (downNote1Editor = new TextEditor ("down note 1 editor"));
    downNote1Editor->setMultiLine (false);
    downNote1Editor->setReturnKeyStartsNewLine (false);
    downNote1Editor->setReadOnly (false);
    downNote1Editor->setScrollbarsShown (true);
    downNote1Editor->setCaretVisible (true);
    downNote1Editor->setPopupMenuEnabled (true);
    downNote1Editor->setText (String::empty);

    addAndMakeVisible (presetLabel10 = new Label ("preset label",
                                                  TRANS("Send notes:")));
    presetLabel10->setFont (Font (15.00f, Font::plain));
    presetLabel10->setJustificationType (Justification::centredRight);
    presetLabel10->setEditable (false, false, false);
    presetLabel10->setColour (TextEditor::textColourId, Colours::black);
    presetLabel10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (downNote2Editor = new TextEditor ("down note 2 editor"));
    downNote2Editor->setMultiLine (false);
    downNote2Editor->setReturnKeyStartsNewLine (false);
    downNote2Editor->setReadOnly (false);
    downNote2Editor->setScrollbarsShown (true);
    downNote2Editor->setCaretVisible (true);
    downNote2Editor->setPopupMenuEnabled (true);
    downNote2Editor->setText (String::empty);

    addAndMakeVisible (downNote3Editor = new TextEditor ("down note 3 editor"));
    downNote3Editor->setMultiLine (false);
    downNote3Editor->setReturnKeyStartsNewLine (false);
    downNote3Editor->setReadOnly (false);
    downNote3Editor->setScrollbarsShown (true);
    downNote3Editor->setCaretVisible (true);
    downNote3Editor->setPopupMenuEnabled (true);
    downNote3Editor->setText (String::empty);

    addAndMakeVisible (presetLabel11 = new Label ("preset label",
                                                  TRANS("With velocities:")));
    presetLabel11->setFont (Font (15.00f, Font::plain));
    presetLabel11->setJustificationType (Justification::centredRight);
    presetLabel11->setEditable (false, false, false);
    presetLabel11->setColour (TextEditor::textColourId, Colours::black);
    presetLabel11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (downVelocity1Editor = new TextEditor ("down velocity 1 editor"));
    downVelocity1Editor->setMultiLine (false);
    downVelocity1Editor->setReturnKeyStartsNewLine (false);
    downVelocity1Editor->setReadOnly (false);
    downVelocity1Editor->setScrollbarsShown (true);
    downVelocity1Editor->setCaretVisible (true);
    downVelocity1Editor->setPopupMenuEnabled (true);
    downVelocity1Editor->setText (String::empty);

    addAndMakeVisible (downVelocity2Editor = new TextEditor ("down velocity 2 editor"));
    downVelocity2Editor->setMultiLine (false);
    downVelocity2Editor->setReturnKeyStartsNewLine (false);
    downVelocity2Editor->setReadOnly (false);
    downVelocity2Editor->setScrollbarsShown (true);
    downVelocity2Editor->setCaretVisible (true);
    downVelocity2Editor->setPopupMenuEnabled (true);
    downVelocity2Editor->setText (String::empty);

    addAndMakeVisible (downVelocity3Editor = new TextEditor ("down velocity 3 editor"));
    downVelocity3Editor->setMultiLine (false);
    downVelocity3Editor->setReturnKeyStartsNewLine (false);
    downVelocity3Editor->setReadOnly (false);
    downVelocity3Editor->setScrollbarsShown (true);
    downVelocity3Editor->setCaretVisible (true);
    downVelocity3Editor->setPopupMenuEnabled (true);
    downVelocity3Editor->setText (String::empty);

    addAndMakeVisible (upEnableButton = new ToggleButton ("up enable button"));
    upEnableButton->setButtonText (TRANS("Enable"));
    upEnableButton->addListener (this);

    addAndMakeVisible (downEnableButton = new ToggleButton ("down enable button"));
    downEnableButton->setButtonText (TRANS("Enable"));
    downEnableButton->addListener (this);


    //[UserPreSize]
    for(int i = 0; i < factory_.getNumConfigurations(); i++) {
        presetComboBox->addItem(factory_.getConfigurationName(i).c_str(), i+1);
    }
    
    windowLengthEditor->addListener(this);
    upMinSpeedEditor->addListener(this);
    downMinSpeedEditor->addListener(this);
    upNote1Editor->addListener(this);
    upNote2Editor->addListener(this);
    upNote3Editor->addListener(this);
    upVelocity1Editor->addListener(this);
    upVelocity2Editor->addListener(this);
    upVelocity3Editor->addListener(this);
    downNote1Editor->addListener(this);
    downNote2Editor->addListener(this);
    downNote3Editor->addListener(this);
    downVelocity1Editor->addListener(this);
    downVelocity2Editor->addListener(this);
    downVelocity3Editor->addListener(this);
    //[/UserPreSize]

    setSize (342, 328);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TouchkeyReleaseAngleMappingExtendedEditor::~TouchkeyReleaseAngleMappingExtendedEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    titleLabel = nullptr;
    presetLabel = nullptr;
    presetComboBox = nullptr;
    presetLabel2 = nullptr;
    windowLengthEditor = nullptr;
    presetLabel3 = nullptr;
    presetLabel4 = nullptr;
    upMinSpeedEditor = nullptr;
    presetLabel5 = nullptr;
    upNote1Editor = nullptr;
    presetLabel6 = nullptr;
    upNote2Editor = nullptr;
    upNote3Editor = nullptr;
    presetLabel7 = nullptr;
    upVelocity1Editor = nullptr;
    upVelocity2Editor = nullptr;
    upVelocity3Editor = nullptr;
    presetLabel8 = nullptr;
    downMinSpeedEditor = nullptr;
    presetLabel9 = nullptr;
    downNote1Editor = nullptr;
    presetLabel10 = nullptr;
    downNote2Editor = nullptr;
    downNote3Editor = nullptr;
    presetLabel11 = nullptr;
    downVelocity1Editor = nullptr;
    downVelocity2Editor = nullptr;
    downVelocity3Editor = nullptr;
    upEnableButton = nullptr;
    downEnableButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TouchkeyReleaseAngleMappingExtendedEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffd2d2d2));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TouchkeyReleaseAngleMappingExtendedEditor::resized()
{
    titleLabel->setBounds (8, 8, 424, 24);
    presetLabel->setBounds (8, 40, 56, 24);
    presetComboBox->setBounds (64, 40, 264, 24);
    presetLabel2->setBounds (8, 80, 112, 24);
    windowLengthEditor->setBounds (120, 80, 56, 24);
    presetLabel3->setBounds (176, 80, 136, 24);
    presetLabel4->setBounds (8, 112, 136, 24);
    upMinSpeedEditor->setBounds (144, 136, 56, 24);
    presetLabel5->setBounds (8, 136, 136, 24);
    upNote1Editor->setBounds (144, 160, 56, 24);
    presetLabel6->setBounds (8, 160, 136, 24);
    upNote2Editor->setBounds (208, 160, 56, 24);
    upNote3Editor->setBounds (272, 160, 56, 24);
    presetLabel7->setBounds (8, 184, 136, 24);
    upVelocity1Editor->setBounds (144, 184, 56, 24);
    upVelocity2Editor->setBounds (208, 184, 56, 24);
    upVelocity3Editor->setBounds (272, 184, 56, 24);
    presetLabel8->setBounds (8, 216, 160, 24);
    downMinSpeedEditor->setBounds (144, 240, 56, 24);
    presetLabel9->setBounds (8, 240, 136, 24);
    downNote1Editor->setBounds (144, 264, 56, 24);
    presetLabel10->setBounds (8, 264, 136, 24);
    downNote2Editor->setBounds (208, 264, 56, 24);
    downNote3Editor->setBounds (272, 264, 56, 24);
    presetLabel11->setBounds (8, 288, 136, 24);
    downVelocity1Editor->setBounds (144, 288, 56, 24);
    downVelocity2Editor->setBounds (208, 288, 56, 24);
    downVelocity3Editor->setBounds (272, 288, 56, 24);
    upEnableButton->setBounds (208, 112, 72, 24);
    downEnableButton->setBounds (208, 216, 72, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TouchkeyReleaseAngleMappingExtendedEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == presetComboBox)
    {
        //[UserComboBoxCode_presetComboBox] -- add your combo box handling code here..
        int index = presetComboBox->getSelectedItemIndex();
        factory_.setCurrentConfiguration(index);
        //[/UserComboBoxCode_presetComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void TouchkeyReleaseAngleMappingExtendedEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == upEnableButton)
    {
        //[UserButtonCode_upEnableButton] -- add your button handler code here..
        factory_.setUpMessagesEnabled(upEnableButton->getToggleState());
        //[/UserButtonCode_upEnableButton]
    }
    else if (buttonThatWasClicked == downEnableButton)
    {
        //[UserButtonCode_downEnableButton] -- add your button handler code here..
        factory_.setDownMessagesEnabled(downEnableButton->getToggleState());
        //[/UserButtonCode_downEnableButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TouchkeyReleaseAngleMappingExtendedEditor::textEditorReturnKeyPressed(TextEditor &editor)
{
    if(&editor == windowLengthEditor) {
        float windowLength = atof(windowLengthEditor->getText().toUTF8());
        factory_.setWindowSize(windowLength);
    }
    else if(&editor == upMinSpeedEditor) {
        float speed = atof(upMinSpeedEditor->getText().toUTF8());
        factory_.setUpMinimumAngle(speed);
    }
    else if(&editor == downMinSpeedEditor) {
        float speed = atof(downMinSpeedEditor->getText().toUTF8());
        factory_.setDownMinimumAngle(speed);
    }
    else {
        // All the other editors are int values
        int value = atoi(editor.getText().toUTF8());

        if(&editor == upNote1Editor)
            factory_.setUpNote(0, value);
        else if(&editor == upNote2Editor)
            factory_.setUpNote(1, value);
        else if(&editor == upNote3Editor)
            factory_.setUpNote(2, value);
        else if(&editor == upVelocity1Editor)
            factory_.setUpVelocity(0, value);
        else if(&editor == upVelocity2Editor)
            factory_.setUpVelocity(1, value);
        else if(&editor == upVelocity3Editor)
            factory_.setUpVelocity(2, value);
        else if(&editor == downNote1Editor)
            factory_.setDownNote(0, value);
        else if(&editor == downNote2Editor)
            factory_.setDownNote(1, value);
        else if(&editor == downNote3Editor)
            factory_.setDownNote(2, value);
        else if(&editor == downVelocity1Editor)
            factory_.setDownVelocity(0, value);
        else if(&editor == downVelocity2Editor)
            factory_.setDownVelocity(1, value);
        else if(&editor == downVelocity3Editor)
            factory_.setDownVelocity(2, value);
    }
}

void TouchkeyReleaseAngleMappingExtendedEditor::textEditorEscapeKeyPressed(TextEditor &editor)
{

}

void TouchkeyReleaseAngleMappingExtendedEditor::textEditorFocusLost(TextEditor &editor)
{
    textEditorReturnKeyPressed(editor);
}

void TouchkeyReleaseAngleMappingExtendedEditor::synchronize()
{
    // Set the title label
    titleLabel->setText(getDescriptionHelper("Release Angle Mapping"), dontSendNotification);

    // Update the editors to reflect the current status
    if(!windowLengthEditor->hasKeyboardFocus(true)) {
        float value = factory_.getWindowSize();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.0f", value);
#else
        snprintf(st, 16, "%.0f", value);
#endif
        windowLengthEditor->setText(st);
    }

    if(!upMinSpeedEditor->hasKeyboardFocus(true)) {
        float value = factory_.getUpMinimumAngle();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.2f", value);
#else
        snprintf(st, 16, "%.2f", value);
#endif

        upMinSpeedEditor->setText(st);
    }

    if(!downMinSpeedEditor->hasKeyboardFocus(true)) {
        float value = factory_.getDownMinimumAngle();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.2f", value);
#else
        snprintf(st, 16, "%.2f", value);
#endif

        downMinSpeedEditor->setText(st);
    }
    
    char st[16];
    
    if(!upNote1Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getUpNote(0));
        upNote1Editor->setText(st);
    }
    if(!upNote2Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getUpNote(1));
        upNote2Editor->setText(st);
    }
    if(!upNote3Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getUpNote(2));
        upNote3Editor->setText(st);
    }
    if(!upVelocity1Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getUpVelocity(0));
        upVelocity1Editor->setText(st);
    }
    if(!upVelocity2Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getUpVelocity(1));
        upVelocity2Editor->setText(st);
    }
    if(!upVelocity3Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getUpVelocity(2));
        upVelocity3Editor->setText(st);
    }
    if(!downNote1Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getDownNote(0));
        downNote1Editor->setText(st);
    }
    if(!downNote2Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getDownNote(1));
        downNote2Editor->setText(st);
    }
    if(!downNote3Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getDownNote(2));
        downNote3Editor->setText(st);
    }
    if(!downVelocity1Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getDownVelocity(0));
        downVelocity1Editor->setText(st);
    }
    if(!downVelocity2Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getDownVelocity(1));
        downVelocity2Editor->setText(st);
    }
    if(!downVelocity3Editor->hasKeyboardFocus(true)) {
        intToString(st, factory_.getDownVelocity(2));
        downVelocity3Editor->setText(st);
    }

    upEnableButton->setToggleState(factory_.getUpMessagesEnabled(), dontSendNotification);
    downEnableButton->setToggleState(factory_.getDownMessageEnabled(), dontSendNotification);

    int configuration = factory_.getCurrentConfiguration();
    if(configuration >= 0)
        presetComboBox->setSelectedItemIndex(configuration, dontSendNotification);
    else
        presetComboBox->setText("");
}

// Return a human-readable description of this mapping for the window
String TouchkeyReleaseAngleMappingExtendedEditor::getDescription() {
    return getDescriptionHelper("Release Angle");
}

// Return a human-readable description of this mapping for the window
String TouchkeyReleaseAngleMappingExtendedEditor::getDescriptionHelper(String baseName) {
    String desc = baseName;

    desc += " (Zone ";

    int zone = factory_.segment().outputPort();
    desc += zone;
    desc += ", #";

    int mappingNumber = factory_.segment().indexOfMappingFactory(&factory_);
    desc += mappingNumber;
    desc += ")";

    return desc;
}

// Cross-platform helper function to deal with weird Visual Studio definitions...
void TouchkeyReleaseAngleMappingExtendedEditor::intToString(char *st, int value) {
#ifdef _MSC_VER
    _snprintf_s(st, 16, _TRUNCATE, "%d", value);
#else
    snprintf(st, 16, "%d", value);
#endif
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TouchkeyReleaseAngleMappingExtendedEditor"
                 componentName="" parentClasses="public MappingEditorComponent, public TextEditor::Listener"
                 constructorParams="TouchkeyReleaseAngleMappingFactory&amp; factory"
                 variableInitialisers="factory_(factory)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="342"
                 initialHeight="328">
  <BACKGROUND backgroundColour="ffd2d2d2"/>
  <LABEL name="title label" id="2346b62ce034bea2" memberName="titleLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 424 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Release Angle Mapping (Zone N, #M)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="33"/>
  <LABEL name="preset label" id="5ef7c1b78fdcf616" memberName="presetLabel"
         virtualName="" explicitFocusOrder="0" pos="8 40 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Preset:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="parameter combo box" id="f12f6f6e31042be1" memberName="presetComboBox"
            virtualName="" explicitFocusOrder="0" pos="64 40 264 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="preset label" id="6c7fb9cdad1ef615" memberName="presetLabel2"
         virtualName="" explicitFocusOrder="0" pos="8 80 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Window Length:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="range low text editor" id="db0f62c03a58af03" memberName="windowLengthEditor"
              virtualName="" explicitFocusOrder="0" pos="120 80 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="preset label" id="bf72fc0576275cec" memberName="presetLabel3"
         virtualName="" explicitFocusOrder="0" pos="176 80 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="ms. before release" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="preset label" id="737ac0c84cd35f2a" memberName="presetLabel4"
         virtualName="" explicitFocusOrder="0" pos="8 112 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Release Moving Up" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="33"/>
  <TEXTEDITOR name="up release speed editor" id="6d12507cf2b05308" memberName="upMinSpeedEditor"
              virtualName="" explicitFocusOrder="0" pos="144 136 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="preset label" id="4bf2ba2e74c7f918" memberName="presetLabel5"
         virtualName="" explicitFocusOrder="0" pos="8 136 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min. release speed:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="up note 1 editor" id="48bc9cb4bc2b66d7" memberName="upNote1Editor"
              virtualName="" explicitFocusOrder="0" pos="144 160 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="preset label" id="e98f51307ccd3213" memberName="presetLabel6"
         virtualName="" explicitFocusOrder="0" pos="8 160 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Send notes:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="up note 2 editor" id="a1078ce66401fa26" memberName="upNote2Editor"
              virtualName="" explicitFocusOrder="0" pos="208 160 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="up note 3 editor" id="3b6be211e2c57644" memberName="upNote3Editor"
              virtualName="" explicitFocusOrder="0" pos="272 160 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="preset label" id="cd890cf41d7607bd" memberName="presetLabel7"
         virtualName="" explicitFocusOrder="0" pos="8 184 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="With velocities:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="up velocity 1 editor" id="47d3d530ed72615a" memberName="upVelocity1Editor"
              virtualName="" explicitFocusOrder="0" pos="144 184 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="up velocity 2 editor" id="ff6d7b8e5b4a5bd6" memberName="upVelocity2Editor"
              virtualName="" explicitFocusOrder="0" pos="208 184 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="up velocity 3 editor" id="65dabffb4ac41d8d" memberName="upVelocity3Editor"
              virtualName="" explicitFocusOrder="0" pos="272 184 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="preset label" id="f8444692065e742a" memberName="presetLabel8"
         virtualName="" explicitFocusOrder="0" pos="8 216 160 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Release Moving Down" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="33"/>
  <TEXTEDITOR name="down release speed editor" id="4d87b35c1bd38cfd" memberName="downMinSpeedEditor"
              virtualName="" explicitFocusOrder="0" pos="144 240 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="preset label" id="cfa916d2ffe4090d" memberName="presetLabel9"
         virtualName="" explicitFocusOrder="0" pos="8 240 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min. release speed:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="down note 1 editor" id="fe8e24594d26ec2d" memberName="downNote1Editor"
              virtualName="" explicitFocusOrder="0" pos="144 264 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="preset label" id="56bc59cd5ceb0e2" memberName="presetLabel10"
         virtualName="" explicitFocusOrder="0" pos="8 264 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Send notes:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="down note 2 editor" id="e0088e60d93fd53" memberName="downNote2Editor"
              virtualName="" explicitFocusOrder="0" pos="208 264 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="down note 3 editor" id="23571b41edd72631" memberName="downNote3Editor"
              virtualName="" explicitFocusOrder="0" pos="272 264 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="preset label" id="a62bc5524128106c" memberName="presetLabel11"
         virtualName="" explicitFocusOrder="0" pos="8 288 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="With velocities:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="down velocity 1 editor" id="f4a94019655ea3ab" memberName="downVelocity1Editor"
              virtualName="" explicitFocusOrder="0" pos="144 288 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="down velocity 2 editor" id="b2c75ef9c586a2e2" memberName="downVelocity2Editor"
              virtualName="" explicitFocusOrder="0" pos="208 288 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="down velocity 3 editor" id="96bf0ea9075d357f" memberName="downVelocity3Editor"
              virtualName="" explicitFocusOrder="0" pos="272 288 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="up enable button" id="d3cb9267f9296315" memberName="upEnableButton"
                virtualName="" explicitFocusOrder="0" pos="208 112 72 24" buttonText="Enable"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="down enable button" id="59af46c3b5431919" memberName="downEnableButton"
                virtualName="" explicitFocusOrder="0" pos="208 216 72 24" buttonText="Enable"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
#endif      // TOUCHKEYS_NO_GUI
//[/EndFile]
