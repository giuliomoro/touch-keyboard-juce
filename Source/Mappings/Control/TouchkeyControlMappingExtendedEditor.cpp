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

#include "TouchkeyControlMappingExtendedEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TouchkeyControlMappingExtendedEditor::TouchkeyControlMappingExtendedEditor (TouchkeyControlMappingFactory& factory)
    : factory_(factory), typeWasAbsolute_(false)
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
                                                 "To Control:"));
    controlLabel->setFont (Font (15.00f, Font::plain));
    controlLabel->setJustificationType (Justification::centredRight);
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
    controlLabel3->setJustificationType (Justification::centredRight);
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

    addAndMakeVisible (rangeLabel3 = new Label ("range label",
                                                "Output Range:"));
    rangeLabel3->setFont (Font (15.00f, Font::plain));
    rangeLabel3->setJustificationType (Justification::centredLeft);
    rangeLabel3->setEditable (false, false, false);
    rangeLabel3->setColour (TextEditor::textColourId, Colours::black);
    rangeLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputRangeLowEditor = new TextEditor ("output range low text editor"));
    outputRangeLowEditor->setMultiLine (false);
    outputRangeLowEditor->setReturnKeyStartsNewLine (false);
    outputRangeLowEditor->setReadOnly (false);
    outputRangeLowEditor->setScrollbarsShown (true);
    outputRangeLowEditor->setCaretVisible (true);
    outputRangeLowEditor->setPopupMenuEnabled (true);
    outputRangeLowEditor->setText (String::empty);

    addAndMakeVisible (outputRangeHighEditor = new TextEditor ("output range hi text editor"));
    outputRangeHighEditor->setMultiLine (false);
    outputRangeHighEditor->setReturnKeyStartsNewLine (false);
    outputRangeHighEditor->setReadOnly (false);
    outputRangeHighEditor->setScrollbarsShown (true);
    outputRangeHighEditor->setCaretVisible (true);
    outputRangeHighEditor->setPopupMenuEnabled (true);
    outputRangeHighEditor->setText (String::empty);

    addAndMakeVisible (rangeLabel4 = new Label ("range label",
                                                "-"));
    rangeLabel4->setFont (Font (15.00f, Font::plain));
    rangeLabel4->setJustificationType (Justification::centredLeft);
    rangeLabel4->setEditable (false, false, false);
    rangeLabel4->setColour (TextEditor::textColourId, Colours::black);
    rangeLabel4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (controlLabel4 = new Label ("control label",
                                                  "Direction:"));
    controlLabel4->setFont (Font (15.00f, Font::plain));
    controlLabel4->setJustificationType (Justification::centredRight);
    controlLabel4->setEditable (false, false, false);
    controlLabel4->setColour (TextEditor::textColourId, Colours::black);
    controlLabel4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (directionComboBox = new ComboBox ("direction combo box"));
    directionComboBox->setEditableText (false);
    directionComboBox->setJustificationType (Justification::centredLeft);
    directionComboBox->setTextWhenNothingSelected (String::empty);
    directionComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    directionComboBox->addListener (this);

    addAndMakeVisible (titleLabel = new Label ("title label",
                                               "Control Mapping (Zone N, #M)"));
    titleLabel->setFont (Font (15.00f, Font::bold));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rangeLabel5 = new Label ("range label",
                                                "Threshold:"));
    rangeLabel5->setFont (Font (15.00f, Font::plain));
    rangeLabel5->setJustificationType (Justification::centredLeft);
    rangeLabel5->setEditable (false, false, false);
    rangeLabel5->setColour (TextEditor::textColourId, Colours::black);
    rangeLabel5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (thresholdEditor = new TextEditor ("threshold text editor"));
    thresholdEditor->setMultiLine (false);
    thresholdEditor->setReturnKeyStartsNewLine (false);
    thresholdEditor->setReadOnly (false);
    thresholdEditor->setScrollbarsShown (true);
    thresholdEditor->setCaretVisible (true);
    thresholdEditor->setPopupMenuEnabled (true);
    thresholdEditor->setText (String::empty);

    addAndMakeVisible (cc14BitButton = new ToggleButton ("new toggle button"));
    cc14BitButton->setButtonText ("Use 14-bit CC");
    cc14BitButton->addListener (this);

    addAndMakeVisible (ignore2FingersButton = new ToggleButton ("ignore 2 fingers toggle button"));
    ignore2FingersButton->setButtonText ("Ignore 2 Fingers");
    ignore2FingersButton->addListener (this);

    addAndMakeVisible (ignore3FingersButton = new ToggleButton ("ignore 3 fingers toggle button"));
    ignore3FingersButton->setButtonText ("Ignore 3 Fingers");
    ignore3FingersButton->addListener (this);

    addAndMakeVisible (controlLabel6 = new Label ("control label",
                                                  "Out of Range:"));
    controlLabel6->setFont (Font (15.00f, Font::plain));
    controlLabel6->setJustificationType (Justification::centredRight);
    controlLabel6->setEditable (false, false, false);
    controlLabel6->setColour (TextEditor::textColourId, Colours::black);
    controlLabel6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outOfRangeComboBox = new ComboBox ("out of range combo box"));
    outOfRangeComboBox->setEditableText (false);
    outOfRangeComboBox->setJustificationType (Justification::centredLeft);
    outOfRangeComboBox->setTextWhenNothingSelected (String::empty);
    outOfRangeComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    outOfRangeComboBox->addListener (this);

    addAndMakeVisible (rangeLabel6 = new Label ("range label",
                                                "Default Output:"));
    rangeLabel6->setFont (Font (15.00f, Font::plain));
    rangeLabel6->setJustificationType (Justification::centredLeft);
    rangeLabel6->setEditable (false, false, false);
    rangeLabel6->setColour (TextEditor::textColourId, Colours::black);
    rangeLabel6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputDefaultEditor = new TextEditor ("output default text editor"));
    outputDefaultEditor->setMultiLine (false);
    outputDefaultEditor->setReturnKeyStartsNewLine (false);
    outputDefaultEditor->setReadOnly (false);
    outputDefaultEditor->setScrollbarsShown (true);
    outputDefaultEditor->setCaretVisible (true);
    outputDefaultEditor->setPopupMenuEnabled (true);
    outputDefaultEditor->setText (String::empty);


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

    directionComboBox->addItem("Normal", TouchkeyControlMapping::kDirectionPositive);
    directionComboBox->addItem("Reverse", TouchkeyControlMapping::kDirectionNegative);
    directionComboBox->addItem("Always Positive", TouchkeyControlMapping::kDirectionBoth);

    outOfRangeComboBox->addItem("Ignore", OscMidiConverter::kOutOfRangeIgnore);
    outOfRangeComboBox->addItem("Clip", OscMidiConverter::kOutOfRangeClip);
    outOfRangeComboBox->addItem("Extrapolate", OscMidiConverter::kOutOfRangeExtrapolate);
    //[/UserPreSize]

    setSize (448, 248);


    //[Constructor] You can add your own custom stuff here..
    inputRangeLowEditor->addListener(this);
    inputRangeHighEditor->addListener(this);
    outputRangeLowEditor->addListener(this);
    outputRangeHighEditor->addListener(this);
    outputDefaultEditor->addListener(this);
    thresholdEditor->addListener(this);
    //[/Constructor]
}

TouchkeyControlMappingExtendedEditor::~TouchkeyControlMappingExtendedEditor()
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
    rangeLabel3 = nullptr;
    outputRangeLowEditor = nullptr;
    outputRangeHighEditor = nullptr;
    rangeLabel4 = nullptr;
    controlLabel4 = nullptr;
    directionComboBox = nullptr;
    titleLabel = nullptr;
    rangeLabel5 = nullptr;
    thresholdEditor = nullptr;
    cc14BitButton = nullptr;
    ignore2FingersButton = nullptr;
    ignore3FingersButton = nullptr;
    controlLabel6 = nullptr;
    outOfRangeComboBox = nullptr;
    rangeLabel6 = nullptr;
    outputDefaultEditor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TouchkeyControlMappingExtendedEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffd2d2d2));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TouchkeyControlMappingExtendedEditor::resized()
{
    inputRangeLowEditor->setBounds (112, 72, 56, 24);
    rangeLabel->setBounds (8, 72, 104, 24);
    controlLabel->setBounds (256, 40, 64, 24);
    controlComboBox->setBounds (320, 40, 112, 24);
    controlLabel2->setBounds (8, 40, 72, 24);
    parameterComboBox->setBounds (80, 40, 160, 24);
    controlLabel3->setBounds (264, 104, 56, 24);
    typeComboBox->setBounds (320, 104, 112, 24);
    inputRangeHighEditor->setBounds (184, 72, 56, 24);
    rangeLabel2->setBounds (168, 72, 16, 24);
    rangeLabel3->setBounds (8, 104, 96, 24);
    outputRangeLowEditor->setBounds (112, 104, 56, 24);
    outputRangeHighEditor->setBounds (184, 104, 56, 24);
    rangeLabel4->setBounds (168, 104, 16, 24);
    controlLabel4->setBounds (248, 136, 72, 24);
    directionComboBox->setBounds (320, 136, 112, 24);
    titleLabel->setBounds (8, 8, 424, 24);
    rangeLabel5->setBounds (8, 168, 72, 24);
    thresholdEditor->setBounds (112, 168, 56, 24);
    cc14BitButton->setBounds (320, 72, 112, 24);
    ignore2FingersButton->setBounds (8, 192, 128, 24);
    ignore3FingersButton->setBounds (8, 216, 128, 24);
    controlLabel6->setBounds (216, 168, 104, 24);
    outOfRangeComboBox->setBounds (320, 168, 112, 24);
    rangeLabel6->setBounds (8, 136, 96, 24);
    outputDefaultEditor->setBounds (112, 136, 56, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TouchkeyControlMappingExtendedEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
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
    else if (comboBoxThatHasChanged == directionComboBox)
    {
        //[UserComboBoxCode_directionComboBox] -- add your combo box handling code here..
        int direction = directionComboBox->getSelectedId();
        factory_.setDirection(direction);
        //[/UserComboBoxCode_directionComboBox]
    }
    else if (comboBoxThatHasChanged == outOfRangeComboBox)
    {
        //[UserComboBoxCode_outOfRangeComboBox] -- add your combo box handling code here..
        int behavior = outOfRangeComboBox->getSelectedId();
        factory_.setOutOfRangeBehavior(behavior);
        //[/UserComboBoxCode_outOfRangeComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void TouchkeyControlMappingExtendedEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == cc14BitButton)
    {
        //[UserButtonCode_cc14BitButton] -- add your button handler code here..
        factory_.setUses14BitControl(cc14BitButton->getToggleState());
        //[/UserButtonCode_cc14BitButton]
    }
    else if (buttonThatWasClicked == ignore2FingersButton)
    {
        //[UserButtonCode_ignore2FingersButton] -- add your button handler code here..
        factory_.setIgnoresTwoFingers(ignore2FingersButton->getToggleState());
        //[/UserButtonCode_ignore2FingersButton]
    }
    else if (buttonThatWasClicked == ignore3FingersButton)
    {
        //[UserButtonCode_ignore3FingersButton] -- add your button handler code here..
        factory_.setIgnoresThreeFingers(ignore3FingersButton->getToggleState());
        //[/UserButtonCode_ignore3FingersButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TouchkeyControlMappingExtendedEditor::textEditorReturnKeyPressed(TextEditor &editor)
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
    else if(&editor == outputRangeLowEditor) {
        float range = atof(outputRangeLowEditor->getText().toUTF8());
        factory_.setRangeOutputMin(range);
    }
    else if(&editor == outputRangeHighEditor) {
        float range = atof(outputRangeHighEditor->getText().toUTF8());
        factory_.setRangeOutputMax(range);
    }
    else if(&editor == outputDefaultEditor) {
        float range = atof(outputDefaultEditor->getText().toUTF8());
        factory_.setRangeOutputDefault(range);
    }
    else if(&editor == thresholdEditor) {
        float thresh = atof(thresholdEditor->getText().toUTF8());
        factory_.setThreshold(thresh);
    }
}

void TouchkeyControlMappingExtendedEditor::textEditorEscapeKeyPressed(TextEditor &editor)
{

}

void TouchkeyControlMappingExtendedEditor::textEditorFocusLost(TextEditor &editor)
{
    textEditorReturnKeyPressed(editor);
}

void TouchkeyControlMappingExtendedEditor::synchronize()
{
    // Set the title label
    titleLabel->setText(getDescriptionHelper("Control Mapping"), dontSendNotification);

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

    if(!outputRangeLowEditor->hasKeyboardFocus(true)) {
        float value = factory_.getRangeOutputMin();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.2f", value);
#else
        snprintf(st, 16, "%.2f", value);
#endif

        outputRangeLowEditor->setText(st);
    }

    if(!outputRangeHighEditor->hasKeyboardFocus(true)) {
        float value = factory_.getRangeOutputMax();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.2f", value);
#else
        snprintf(st, 16, "%.2f", value);
#endif

        outputRangeHighEditor->setText(st);
    }
    
    if(!outputDefaultEditor->hasKeyboardFocus(true)) {
        float value = factory_.getRangeOutputDefault();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.2f", value);
#else
        snprintf(st, 16, "%.2f", value);
#endif
        
        outputDefaultEditor->setText(st);
    }

    if(factory_.getInputType() == TouchkeyControlMapping::kTypeFirstTouchRelative
       || factory_.getInputType() == TouchkeyControlMapping::kTypeNoteOnsetRelative) {
        thresholdEditor->setEnabled(true);
        if(!thresholdEditor->hasKeyboardFocus(true)) {
            float value = factory_.getThreshold();
            char st[16];
#ifdef _MSC_VER
            _snprintf_s(st, 16, _TRUNCATE, "%.2f", value);
#else
            snprintf(st, 16, "%.2f", value);
#endif

            thresholdEditor->setText(st);
        }

        if(typeWasAbsolute_) {
            // Add all three direction items
            directionComboBox->clear();
            directionComboBox->addItem("Normal", TouchkeyControlMapping::kDirectionPositive);
            directionComboBox->addItem("Reverse", TouchkeyControlMapping::kDirectionNegative);
            directionComboBox->addItem("Always Positive", TouchkeyControlMapping::kDirectionBoth);
        }

        typeWasAbsolute_ = false;
    }
    else {
        thresholdEditor->setEnabled(false);
        thresholdEditor->setText("", false);

        if(!typeWasAbsolute_) {
            // Add only one direction item
            directionComboBox->clear();
            directionComboBox->addItem("Normal", TouchkeyControlMapping::kDirectionPositive);
        }

        typeWasAbsolute_ = true;
    }

    if(factory_.getController() == MidiKeyboardSegment::kControlPitchWheel) {
        cc14BitButton->setEnabled(false);
        cc14BitButton->setToggleState(true, dontSendNotification);
    }
    else if(factory_.getController() == MidiKeyboardSegment::kControlPolyphonicAftertouch ||
            factory_.getController() == MidiKeyboardSegment::kControlChannelAftertouch) {
        cc14BitButton->setEnabled(false);
        cc14BitButton->setToggleState(false, dontSendNotification);
    }
    else {
        cc14BitButton->setEnabled(true);
        cc14BitButton->setToggleState(factory_.getUses14BitControl(), dontSendNotification);
    }
    ignore2FingersButton->setToggleState(factory_.getIgnoresTwoFingers(), dontSendNotification);
    ignore3FingersButton->setToggleState(factory_.getIgnoresThreeFingers(), dontSendNotification);

    parameterComboBox->setSelectedId(factory_.getInputParameter(), dontSendNotification);
    typeComboBox->setSelectedId(factory_.getInputType(), dontSendNotification);
    controlComboBox->setSelectedId(factory_.getController(), dontSendNotification);
    directionComboBox->setSelectedId(factory_.getDirection(), dontSendNotification);
    outOfRangeComboBox->setSelectedId(factory_.getOutOfRangeBehavior(), dontSendNotification);
}

// Return a human-readable description of this mapping for the window
String TouchkeyControlMappingExtendedEditor::getDescription() {
    return getDescriptionHelper("Control");
}

// Return a human-readable description of this mapping for the window
String TouchkeyControlMappingExtendedEditor::getDescriptionHelper(String baseName) {
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

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TouchkeyControlMappingExtendedEditor"
                 componentName="" parentClasses="public MappingEditorComponent, public TextEditor::Listener"
                 constructorParams="TouchkeyControlMappingFactory&amp; factory"
                 variableInitialisers="factory_(factory)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="448"
                 initialHeight="248">
  <BACKGROUND backgroundColour="ffd2d2d2"/>
  <TEXTEDITOR name="range low text editor" id="db0f62c03a58af03" memberName="inputRangeLowEditor"
              virtualName="" explicitFocusOrder="0" pos="112 72 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="range label" id="1ca2d422f4c37b7f" memberName="rangeLabel"
         virtualName="" explicitFocusOrder="0" pos="8 72 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Range:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="control label" id="f953b12999632418" memberName="controlLabel"
         virtualName="" explicitFocusOrder="0" pos="256 40 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="To Control:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="control combo box" id="f1c84bb5fd2730fb" memberName="controlComboBox"
            virtualName="" explicitFocusOrder="0" pos="320 40 112 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="control label" id="5ef7c1b78fdcf616" memberName="controlLabel2"
         virtualName="" explicitFocusOrder="0" pos="8 40 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Parameter:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="parameter combo box" id="f12f6f6e31042be1" memberName="parameterComboBox"
            virtualName="" explicitFocusOrder="0" pos="80 40 160 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="control label" id="9ded92e82db31777" memberName="controlLabel3"
         virtualName="" explicitFocusOrder="0" pos="264 104 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <COMBOBOX name="type combo box" id="82d38054016f6c4f" memberName="typeComboBox"
            virtualName="" explicitFocusOrder="0" pos="320 104 112 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="range hi text editor" id="c34ac3e87db289d1" memberName="inputRangeHighEditor"
              virtualName="" explicitFocusOrder="0" pos="184 72 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="range label" id="19e0ad80306cc4c0" memberName="rangeLabel2"
         virtualName="" explicitFocusOrder="0" pos="168 72 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="-" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="range label" id="24ab2fe34fec697f" memberName="rangeLabel3"
         virtualName="" explicitFocusOrder="0" pos="8 104 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Range:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="output range low text editor" id="15865c99a3cac858" memberName="outputRangeLowEditor"
              virtualName="" explicitFocusOrder="0" pos="112 104 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="output range hi text editor" id="6f3a73d113c72696" memberName="outputRangeHighEditor"
              virtualName="" explicitFocusOrder="0" pos="184 104 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="range label" id="a86c42d542ee8780" memberName="rangeLabel4"
         virtualName="" explicitFocusOrder="0" pos="168 104 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="-" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="control label" id="ff30dace0846c523" memberName="controlLabel4"
         virtualName="" explicitFocusOrder="0" pos="248 136 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Direction:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <COMBOBOX name="direction combo box" id="c46a92a83dfb204b" memberName="directionComboBox"
            virtualName="" explicitFocusOrder="0" pos="320 136 112 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="title label" id="2346b62ce034bea2" memberName="titleLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 424 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Control Mapping (Zone N, #M)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="33"/>
  <LABEL name="range label" id="41edb21ea9cb0304" memberName="rangeLabel5"
         virtualName="" explicitFocusOrder="0" pos="8 168 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Threshold:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="threshold text editor" id="48a7ef0bf62a7fe6" memberName="thresholdEditor"
              virtualName="" explicitFocusOrder="0" pos="112 168 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="f75c92be72563883" memberName="cc14BitButton"
                virtualName="" explicitFocusOrder="0" pos="320 72 112 24" buttonText="Use 14-bit CC"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="ignore 2 fingers toggle button" id="ec82d35a4bbc6688" memberName="ignore2FingersButton"
                virtualName="" explicitFocusOrder="0" pos="8 192 128 24" buttonText="Ignore 2 Fingers"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="ignore 3 fingers toggle button" id="9b08149fc48c8b0" memberName="ignore3FingersButton"
                virtualName="" explicitFocusOrder="0" pos="8 216 128 24" buttonText="Ignore 3 Fingers"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="control label" id="668b66775f7ab754" memberName="controlLabel6"
         virtualName="" explicitFocusOrder="0" pos="216 168 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Out of Range:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <COMBOBOX name="out of range combo box" id="6c7a92d782955f43" memberName="outOfRangeComboBox"
            virtualName="" explicitFocusOrder="0" pos="320 168 112 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="range label" id="6f03f49baf05157b" memberName="rangeLabel6"
         virtualName="" explicitFocusOrder="0" pos="8 136 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Default Output:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="output default text editor" id="403f9ffcb91633fd" memberName="outputDefaultEditor"
              virtualName="" explicitFocusOrder="0" pos="112 136 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
#endif  // TOUCHKEYS_NO_GUI
//[/EndFile]
