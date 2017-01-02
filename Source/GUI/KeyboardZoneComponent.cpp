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

#include "KeyboardZoneComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
KeyboardZoneComponent::KeyboardZoneComponent ()
    : controller_(0), keyboardSegment_(0)
{
    addAndMakeVisible (mappingListComponent = new MappingListComponent());
    addAndMakeVisible (midiOutputGroupComponent = new GroupComponent ("MIDI input group",
                                                                      "MIDI Output"));

    addAndMakeVisible (midiOutputDeviceComboBox = new ComboBox ("MIDI input combo box"));
    midiOutputDeviceComboBox->setEditableText (false);
    midiOutputDeviceComboBox->setJustificationType (Justification::centredLeft);
    midiOutputDeviceComboBox->setTextWhenNothingSelected (String::empty);
    midiOutputDeviceComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    midiOutputDeviceComboBox->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           "Device:"));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label5 = new Label ("new label",
                                           "Mode:"));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midiOutputModeComboBox = new ComboBox ("MIDI input combo box"));
    midiOutputModeComboBox->setEditableText (false);
    midiOutputModeComboBox->setJustificationType (Justification::centredLeft);
    midiOutputModeComboBox->setTextWhenNothingSelected (String::empty);
    midiOutputModeComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    midiOutputModeComboBox->addListener (this);

    addAndMakeVisible (midiOutputVoiceStealingButton = new ToggleButton ("Voice stealing button"));
    midiOutputVoiceStealingButton->setButtonText ("Voice stealing");
    midiOutputVoiceStealingButton->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           "Channels:"));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midiOutputChannelLowEditor = new TextEditor ("new text editor"));
    midiOutputChannelLowEditor->setMultiLine (false);
    midiOutputChannelLowEditor->setReturnKeyStartsNewLine (false);
    midiOutputChannelLowEditor->setReadOnly (false);
    midiOutputChannelLowEditor->setScrollbarsShown (true);
    midiOutputChannelLowEditor->setCaretVisible (true);
    midiOutputChannelLowEditor->setPopupMenuEnabled (true);
    midiOutputChannelLowEditor->setText (String::empty);

    addAndMakeVisible (midiOutputChannelHighEditor = new TextEditor ("new text editor"));
    midiOutputChannelHighEditor->setMultiLine (false);
    midiOutputChannelHighEditor->setReturnKeyStartsNewLine (false);
    midiOutputChannelHighEditor->setReadOnly (false);
    midiOutputChannelHighEditor->setScrollbarsShown (true);
    midiOutputChannelHighEditor->setCaretVisible (true);
    midiOutputChannelHighEditor->setPopupMenuEnabled (true);
    midiOutputChannelHighEditor->setText (String::empty);

    addAndMakeVisible (label3 = new Label ("new label",
                                           "to"));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midiOutputGroupComponent2 = new GroupComponent ("MIDI input group",
                                                                       "Range"));

    addAndMakeVisible (label7 = new Label ("new label",
                                           "to"));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rangeLowComboBox = new ComboBox ("range low combo box"));
    rangeLowComboBox->setEditableText (true);
    rangeLowComboBox->setJustificationType (Justification::centredLeft);
    rangeLowComboBox->setTextWhenNothingSelected (String::empty);
    rangeLowComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    rangeLowComboBox->addListener (this);

    addAndMakeVisible (rangeHighComboBox = new ComboBox ("range high combo combo box"));
    rangeHighComboBox->setEditableText (true);
    rangeHighComboBox->setJustificationType (Justification::centredLeft);
    rangeHighComboBox->setTextWhenNothingSelected (String::empty);
    rangeHighComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    rangeHighComboBox->addListener (this);

    addAndMakeVisible (label6 = new Label ("new label",
                                           "Transpose:"));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midiOutputTransposeEditor = new TextEditor ("transposition text editor"));
    midiOutputTransposeEditor->setMultiLine (false);
    midiOutputTransposeEditor->setReturnKeyStartsNewLine (false);
    midiOutputTransposeEditor->setReadOnly (false);
    midiOutputTransposeEditor->setScrollbarsShown (true);
    midiOutputTransposeEditor->setCaretVisible (true);
    midiOutputTransposeEditor->setPopupMenuEnabled (true);
    midiOutputTransposeEditor->setText (String::empty);

    addAndMakeVisible (label8 = new Label ("new label",
                                           "Mappings:"));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (addMappingButton = new TextButton ("add mapping button"));
    addMappingButton->setButtonText ("Add Mapping...");
    addMappingButton->addListener (this);

    addAndMakeVisible (label9 = new Label ("new label",
                                           "Pitchwheel range:"));
    label9->setFont (Font (15.00f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pitchWheelRangeEditor = new TextEditor ("pitch wheel range editor"));
    pitchWheelRangeEditor->setMultiLine (false);
    pitchWheelRangeEditor->setReturnKeyStartsNewLine (false);
    pitchWheelRangeEditor->setReadOnly (false);
    pitchWheelRangeEditor->setScrollbarsShown (true);
    pitchWheelRangeEditor->setCaretVisible (true);
    pitchWheelRangeEditor->setPopupMenuEnabled (true);
    pitchWheelRangeEditor->setText (String::empty);

    addAndMakeVisible (keyboardControllersButton = new TextButton ("keyboard controllers button"));
    keyboardControllersButton->setButtonText (" Controllers...");
    keyboardControllersButton->addListener (this);


    //[UserPreSize]
    // Add modes to MIDI mode toggle box
    midiOutputModeComboBox->addItem("Passthrough", MidiKeyboardSegment::ModePassThrough + kMidiOutputModeComboBoxOffset);
    midiOutputModeComboBox->addItem("Monophonic", MidiKeyboardSegment::ModeMonophonic + kMidiOutputModeComboBoxOffset);
    midiOutputModeComboBox->addItem("Polyphonic", MidiKeyboardSegment::ModePolyphonic + kMidiOutputModeComboBoxOffset);

    // Populate the range combo boxes with notes of the 88-key keyboard
    for(int note = 12; note <= 127; note++) {
        rangeLowComboBox->addItem(MainApplicationController::midiNoteName(note).c_str(), note);
        rangeHighComboBox->addItem(MainApplicationController::midiNoteName(note).c_str(), note);
    }

    lastSelectedMidiOutputID_ = kInvalidMidiOutputId;

    //[/UserPreSize]

    setSize (552, 400);


    //[Constructor] You can add your own custom stuff here..
    midiOutputChannelLowEditor->addListener(this);
    midiOutputChannelHighEditor->addListener(this);
    midiOutputTransposeEditor->addListener(this);
    pitchWheelRangeEditor->addListener(this);
    addMappingButton->setTriggeredOnMouseDown(true);
    keyboardControllersButton->setTriggeredOnMouseDown(true);
    //[/Constructor]
}

KeyboardZoneComponent::~KeyboardZoneComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    mappingListComponent = nullptr;
    midiOutputGroupComponent = nullptr;
    midiOutputDeviceComboBox = nullptr;
    label4 = nullptr;
    label5 = nullptr;
    midiOutputModeComboBox = nullptr;
    midiOutputVoiceStealingButton = nullptr;
    label2 = nullptr;
    midiOutputChannelLowEditor = nullptr;
    midiOutputChannelHighEditor = nullptr;
    label3 = nullptr;
    midiOutputGroupComponent2 = nullptr;
    label7 = nullptr;
    rangeLowComboBox = nullptr;
    rangeHighComboBox = nullptr;
    label6 = nullptr;
    midiOutputTransposeEditor = nullptr;
    label8 = nullptr;
    addMappingButton = nullptr;
    label9 = nullptr;
    pitchWheelRangeEditor = nullptr;
    keyboardControllersButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void KeyboardZoneComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffd2d2d2));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void KeyboardZoneComponent::resized()
{
    mappingListComponent->setBounds (0, 168, 552, 260);
    midiOutputGroupComponent->setBounds (200, 8, 344, 128);
    midiOutputDeviceComboBox->setBounds (264, 32, 264, 24);
    label4->setBounds (208, 32, 55, 24);
    label5->setBounds (208, 64, 55, 24);
    midiOutputModeComboBox->setBounds (264, 64, 152, 24);
    midiOutputVoiceStealingButton->setBounds (424, 64, 112, 24);
    label2->setBounds (208, 96, 56, 24);
    midiOutputChannelLowEditor->setBounds (264, 96, 32, 24);
    midiOutputChannelHighEditor->setBounds (320, 96, 32, 24);
    label3->setBounds (296, 96, 32, 24);
    midiOutputGroupComponent2->setBounds (8, 8, 184, 128);
    label7->setBounds (88, 32, 32, 24);
    rangeLowComboBox->setBounds (24, 32, 64, 24);
    rangeHighComboBox->setBounds (112, 32, 64, 24);
    label6->setBounds (392, 96, 80, 24);
    midiOutputTransposeEditor->setBounds (472, 96, 56, 24);
    label8->setBounds (8, 144, 88, 24);
    addMappingButton->setBounds (440, 144, 104, 20);
    label9->setBounds (24, 68, 104, 24);
    pitchWheelRangeEditor->setBounds (128, 68, 48, 24);
    keyboardControllersButton->setBounds (24, 100, 152, 20);
    
    //[UserResized] Add your own custom resize handling here..
    
    // Resize the mapping list to fit the bottom of the window
    juce::Rectangle<int> const& ourBounds = getBounds();
    juce::Rectangle<int> mappingBounds = mappingListComponent->getBounds();
    mappingBounds.setHeight(ourBounds.getHeight() - mappingBounds.getY());
    mappingListComponent->setBounds(mappingBounds);
    
    //[/UserResized]
}

void KeyboardZoneComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    if(keyboardSegment_ == 0 || controller_ == 0)
        return;
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == midiOutputDeviceComboBox)
    {
        //[UserComboBoxCode_midiOutputDeviceComboBox] -- add your combo box handling code here..

        // Look up the selected ID, remembering that Juce indices start at 1 and the first of
        // these is "Disabled" followed by "Virtual Output Port"
        int selection = midiOutputDeviceComboBox->getSelectedId() - kMidiOutputDeviceComboBoxOffset;
        if(selection == 1 - kMidiOutputDeviceComboBoxOffset) {   // Disabled
            controller_->disableMIDIOutputPort(keyboardSegment_->outputPort());
        }
        else if(selection == 2 - kMidiOutputDeviceComboBoxOffset) { // Virtual output
#ifndef JUCE_WINDOWS
            char st[20];
            snprintf(st, 20, "TouchKeys %d", keyboardSegment_->outputPort());
            controller_->enableMIDIOutputVirtualPort(keyboardSegment_->outputPort(), st);
#endif
        }
        else if(selection >= 0 && selection < midiOutputDeviceIDs_.size()) {
            int deviceId = midiOutputDeviceIDs_[selection];
            controller_->enableMIDIOutputPort(keyboardSegment_->outputPort(), deviceId);
        }
        //[/UserComboBoxCode_midiOutputDeviceComboBox]
    }
    else if (comboBoxThatHasChanged == midiOutputModeComboBox)
    {
        //[UserComboBoxCode_midiOutputModeComboBox] -- add your combo box handling code here..
        int mode = midiOutputModeComboBox->getSelectedId() - kMidiOutputModeComboBoxOffset;
        keyboardSegment_->setMode(mode);
        //[/UserComboBoxCode_midiOutputModeComboBox]
    }
    else if (comboBoxThatHasChanged == rangeLowComboBox)
    {
        //[UserComboBoxCode_rangeLowComboBox] -- add your combo box handling code here..
        updateSegmentRange();
        //[/UserComboBoxCode_rangeLowComboBox]
    }
    else if (comboBoxThatHasChanged == rangeHighComboBox)
    {
        //[UserComboBoxCode_rangeHighComboBox] -- add your combo box handling code here..
        updateSegmentRange();
        //[/UserComboBoxCode_rangeHighComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void KeyboardZoneComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if(keyboardSegment_ == 0)
        return;
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == midiOutputVoiceStealingButton)
    {
        //[UserButtonCode_midiOutputVoiceStealingButton] -- add your button handler code here..
        bool stealing = midiOutputVoiceStealingButton->getToggleState();
        keyboardSegment_->setVoiceStealingEnabled(stealing);
        //[/UserButtonCode_midiOutputVoiceStealingButton]
    }
    else if (buttonThatWasClicked == addMappingButton)
    {
        //[UserButtonCode_addMappingButton] -- add your button handler code here..
        createMappingListPopup();
        //[/UserButtonCode_addMappingButton]
    }
    else if (buttonThatWasClicked == keyboardControllersButton)
    {
        //[UserButtonCode_keyboardControllersButton] -- add your button handler code here..
        createKeyboardControllerPopup();
        //[/UserButtonCode_keyboardControllersButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void KeyboardZoneComponent::textEditorReturnKeyPressed(TextEditor &editor)
{
    if(keyboardSegment_ == 0)
        return;

    if(&editor == midiOutputChannelLowEditor ||
       &editor == midiOutputChannelHighEditor) {
        // Change range of MIDI output channels
        int rangeLow = atoi(midiOutputChannelLowEditor->getText().toUTF8());
        int rangeHigh = atoi(midiOutputChannelHighEditor->getText().toUTF8());
        if(rangeHigh > 16)
            rangeHigh = 16;
        if(rangeLow > 16)
            rangeLow = 16;
        if(rangeHigh < 1)
            rangeHigh = 1;
        if(rangeLow < 1)
            rangeLow = 1;
        keyboardSegment_->setOutputChannelLowest(rangeLow - 1); // 1-16 --> 0-15 indexing

        int polyphony = rangeHigh - rangeLow + 1;
        if(polyphony < 1)
            polyphony = 1;
        keyboardSegment_->setPolyphony(polyphony);
    }
    else if(&editor == midiOutputTransposeEditor) {
        // Change output transposition (limiting possible range to +/- 4 octaves)
        int transpose = atoi(midiOutputTransposeEditor->getText().toUTF8());
        if(transpose < -48)
            transpose = -48;
        if(transpose > 48)
            transpose = 48;
        keyboardSegment_->setOutputTransposition(transpose);
    }
    else if(&editor == pitchWheelRangeEditor) {
        float range = atof(pitchWheelRangeEditor->getText().toUTF8());
        keyboardSegment_->setMidiPitchWheelRange(range);
    }
}

void KeyboardZoneComponent::textEditorEscapeKeyPressed(TextEditor &editor)
{

}

void KeyboardZoneComponent::textEditorFocusLost(TextEditor &editor)
{
    textEditorReturnKeyPressed(editor);
}

// Update state of GUI to reflect underlying controller
void KeyboardZoneComponent::synchronize(bool forceUpdates)
{
    if(keyboardSegment_ == 0 || controller_ == 0)
        return;

    if(forceUpdates) {
        // Update the controls to reflect the current state
        updateOutputDeviceList();
    }

    // Update note ranges
    std::pair<int, int> range = keyboardSegment_->noteRange();
    if(!rangeLowComboBox->hasKeyboardFocus(true) || forceUpdates) {
        if(range.first < 12 || range.first > 127) {
            rangeLowComboBox->setText(String(range.first));
        }
        else
            rangeLowComboBox->setSelectedId(range.first, dontSendNotification);
    }
    if(!rangeHighComboBox->hasKeyboardFocus(true) || forceUpdates) {
        if(range.second < 12 || range.second > 127) {
            rangeHighComboBox->setText(String(range.second));
        }
        else
            rangeHighComboBox->setSelectedId(range.second, dontSendNotification);
    }

    // Update MIDI output status
    int selectedMidiOutputDevice = controller_->selectedMIDIOutputPort(keyboardSegment_->outputPort());
    if(selectedMidiOutputDevice != lastSelectedMidiOutputID_ || forceUpdates) {
        if(selectedMidiOutputDevice == MidiOutputController::kMidiOutputNotOpen)
            midiOutputDeviceComboBox->setSelectedId(1, dontSendNotification);
#ifndef JUCE_WINDOWS
        else if(selectedMidiOutputDevice == MidiOutputController::kMidiVirtualOutputPortNumber)
            midiOutputDeviceComboBox->setSelectedId(2, dontSendNotification);
#endif
        else {
            // Find the output device in the vector
            for(int i = 0; i < midiOutputDeviceIDs_.size(); i++) {
                if(midiOutputDeviceIDs_[i] == selectedMidiOutputDevice) {
                    midiOutputDeviceComboBox->setSelectedId(i + kMidiOutputDeviceComboBoxOffset, dontSendNotification);
                    break;
                }
            }
        }
        lastSelectedMidiOutputID_ = selectedMidiOutputDevice;
    }

    // Update the mode and the peripheral controls that go with it
    int selectedMidiOutputMode = keyboardSegment_->mode();
    midiOutputModeComboBox->setSelectedId(selectedMidiOutputMode + kMidiOutputModeComboBoxOffset, dontSendNotification);

    if(selectedMidiOutputMode == MidiKeyboardSegment::ModePolyphonic) {
        midiOutputVoiceStealingButton->setEnabled(true);
        midiOutputVoiceStealingButton->setToggleState(keyboardSegment_->voiceStealingEnabled(), dontSendNotification);
    }
    else {
        midiOutputVoiceStealingButton->setEnabled(false);
        midiOutputVoiceStealingButton->setToggleState(false, dontSendNotification);
    }

    // Update text editors
    if(!pitchWheelRangeEditor->hasKeyboardFocus(true) || forceUpdates) {
        float value = keyboardSegment_->midiPitchWheelRange();
        char st[16];
#ifdef _MSC_VER
		_snprintf_s(st, 16, _TRUNCATE, "%.1f", value);
#else
        snprintf(st, 16, "%.1f", value);
#endif
        pitchWheelRangeEditor->setText(st);
    }
    if(!midiOutputChannelLowEditor->hasKeyboardFocus(true) || forceUpdates) {
        int rangeLow = keyboardSegment_->outputChannelLowest() + 1; // 0-15 --> 1-16
        midiOutputChannelLowEditor->setText(String(rangeLow));
    }
    if(!midiOutputTransposeEditor->hasKeyboardFocus(true) || forceUpdates) {
        int transpose = keyboardSegment_->outputTransposition();
        midiOutputTransposeEditor->setText(String(transpose));
    }

    if(selectedMidiOutputMode == MidiKeyboardSegment::ModePolyphonic) {
        midiOutputChannelHighEditor->setEnabled(true);
        if(!midiOutputChannelHighEditor->hasKeyboardFocus(true) || forceUpdates) {
            int rangeHigh = keyboardSegment_->polyphony() + keyboardSegment_->outputChannelLowest();
            midiOutputChannelHighEditor->setText(String(rangeHigh));
        }
    }
    else {
        midiOutputChannelHighEditor->setEnabled(false);
        midiOutputChannelHighEditor->setText("", false);
    }

    // Update buttons
    //useAftertouchButton->setToggleState(keyboardSegment_->usesKeyboardChannnelPressure(), dontSendNotification);
    //usePitchWheelButton->setToggleState(keyboardSegment_->usesKeyboardPitchWheel(), dontSendNotification);
    //useControllersButton->setToggleState(keyboardSegment_->usesKeyboardMIDIControllers(), dontSendNotification);

    // Update the mapping list
    mappingListComponent->synchronize();
}

// Update the range of the keyboard segment
void KeyboardZoneComponent::updateSegmentRange()
{
    int selectionLow = rangeLowComboBox->getSelectedId();
    int noteLow = -1;
    if(selectionLow == 0) {
        // Not one of the predefined values that's selected. Parse the string.
        noteLow = MainApplicationController::midiNoteNumberForName((const char *)(rangeLowComboBox->getText().toUTF8()));
    }
    else {
        noteLow = selectionLow;
    }

    if(noteLow < 0 || noteLow > 127) {
        // Out of range: keep the old value
        noteLow = keyboardSegment_->noteRange().first;
    }

    int selectionHigh = rangeHighComboBox->getSelectedId();
    int noteHigh = -1;
    if(selectionHigh == 0) {
        // Not one of the predefined values that's selected. Parse the string.
        noteHigh = MainApplicationController::midiNoteNumberForName((const char *)(rangeHighComboBox->getText().toUTF8()));
    }
    else {
        noteHigh = selectionHigh;
    }

    if(noteHigh < 0 || noteHigh > 127) {
        // Out of range: keep the old value
        noteHigh = keyboardSegment_->noteRange().second;
    }

    if(noteHigh < noteLow)
        noteHigh = noteLow;
    keyboardSegment_->setNoteRange(noteLow, noteHigh);
}

// Update the combo box with the current output devices
void KeyboardZoneComponent::updateOutputDeviceList()
{
    if(controller_ == 0 || keyboardSegment_ == 0)
        return;

    // *** MIDI output devices ***
    vector<pair<int, string> > devices = controller_->availableMIDIOutputDevices();
    vector<pair<int, string> >::iterator it;

    midiOutputDeviceComboBox->clear();
    midiOutputDeviceIDs_.clear();
    midiOutputDeviceComboBox->addItem("Disabled", 1);
#ifndef JUCE_WINDOWS
    char virtualPortName[24];
    snprintf(virtualPortName, 24, "Virtual Port (%d)", keyboardSegment_->outputPort());
	midiOutputDeviceComboBox->addItem(virtualPortName, 2);
#endif

    // Check whether the currently selected ID still exists while
    // we build the list
    bool lastSelectedDeviceExists = false;
    int counter = kMidiOutputDeviceComboBoxOffset;
    for(it = devices.begin(); it != devices.end(); ++it) {
        if(it->first < 0)
            continue;
        midiOutputDeviceComboBox->addItem((*it).second.c_str(), counter);
        midiOutputDeviceIDs_.push_back(it->first);
        if(it->first == lastSelectedMidiOutputID_)
            lastSelectedDeviceExists = true;
        counter++;
    }

    if(!lastSelectedDeviceExists && lastSelectedMidiOutputID_ != kInvalidMidiOutputId) {
#ifndef JUCE_WINDOWS
        if(lastSelectedMidiOutputID_ != MidiOutputController::kMidiVirtualOutputPortNumber)
            controller_->disableMIDIOutputPort(keyboardSegment_->outputPort());
#else   // No virtual port on Windows
        controller_->disableMIDIOutputPort(keyboardSegment_->outputPort());
#endif
    }
}

// Create a popup menu containing a list of mapping factories
void KeyboardZoneComponent::createMappingListPopup()
{
    if(controller_ == 0)
        return;

    PopupMenu menu;

    for(int i = 0; i < MidiKeyboardSegment::numberOfMappingFactories(); i++) {
        if(controller_->experimentalMappingsEnabled() || !MidiKeyboardSegment::mappingIsExperimental(i))
            menu.addItem(i + 1, MidiKeyboardSegment::mappingFactoryNameForIndex(i));
    }

    menu.showMenuAsync(PopupMenu::Options().withTargetComponent(addMappingButton),
                       ModalCallbackFunction::forComponent(staticMappingChosenCallback, this));
}

// Create a popup menu allowing selection of which controllers to retransmit
void KeyboardZoneComponent::createKeyboardControllerPopup()
{
    if(controller_ == 0 || keyboardSegment_ == 0)
        return;

    PopupMenu menu;

    menu.addItem(kKeyboardControllerSendPitchWheelRange, "Send Pitchwheel Range RPN", true, false);
    menu.addSeparator();
    menu.addItem(MidiKeyboardSegment::kControlPitchWheel, "Retransmit from Keyboard:", false);
    menu.addSeparator();
    menu.addItem(MidiKeyboardSegment::kControlPitchWheel, "Pitch Wheel", true, keyboardSegment_->usesKeyboardPitchWheel());
    menu.addItem(MidiKeyboardSegment::kControlChannelAftertouch, "Aftertouch", true, keyboardSegment_->usesKeyboardChannnelPressure());
    menu.addItem(1, "CC 1 (Mod Wheel)", true, keyboardSegment_->usesKeyboardModWheel());
    menu.addItem(kKeyboardControllerRetransmitPedals, "Pedals", true, keyboardSegment_->usesKeyboardPedals());
    menu.addItem(kKeyboardControllerRetransmitOthers, "Other Controllers", true, keyboardSegment_->usesKeyboardMIDIControllers());

    menu.showMenuAsync(PopupMenu::Options().withTargetComponent(keyboardControllersButton),
                       ModalCallbackFunction::forComponent(staticKeyboardControllerChosenCallback, this));
}

// Called from the popup menu, indicating the selected item
void KeyboardZoneComponent::mappingChosenCallback(int result)
{
    if(controller_ == 0 || keyboardSegment_ == 0)
        return;

    // Items are numbered from 1 in the menu but from 0 in the array in the controller
    if(result >= 1) {
        MappingFactory *newFactory = keyboardSegment_->createMappingFactoryForIndex(result - 1);

        if(newFactory != 0) {
            keyboardSegment_->addMappingFactory(newFactory, true);
        }
    }
}

// Called from the popup menu, indicated selected controller
void KeyboardZoneComponent::keyboardControllerChosenCallback(int result)
{
    if(controller_ == 0 || keyboardSegment_ == 0)
        return;

    // Enable or disable retransmitting specific messages
    if(result == MidiKeyboardSegment::kControlPitchWheel) {
        keyboardSegment_->setUsesKeyboardPitchWheel(!keyboardSegment_->usesKeyboardPitchWheel());
    }
    else if(result == MidiKeyboardSegment::kControlChannelAftertouch) {
        keyboardSegment_->setUsesKeyboardChannelPressure(!keyboardSegment_->usesKeyboardChannnelPressure());
    }
    else if(result == 1) { // ModWheel == CC 1
        keyboardSegment_->setUsesKeyboardModWheel(!keyboardSegment_->usesKeyboardModWheel());
    }
    else if(result == kKeyboardControllerRetransmitPedals) {
        keyboardSegment_->setUsesKeyboardPedals(!keyboardSegment_->usesKeyboardPedals());
    }
    else if(result == kKeyboardControllerRetransmitOthers) {
        keyboardSegment_->setUsesKeyboardMIDIControllers(!keyboardSegment_->usesKeyboardMIDIControllers());
    }
    else if(result == kKeyboardControllerSendPitchWheelRange) {
        // Send a MIDI RPN message now to update the pitch wheel range
        keyboardSegment_->sendMidiPitchWheelRange();
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="KeyboardZoneComponent" componentName=""
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="controller_(0), keyboardSegment_(0)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="552" initialHeight="400">
  <BACKGROUND backgroundColour="ffd2d2d2"/>
  <JUCERCOMP name="mapping list" id="4d5d007374cdad00" memberName="mappingListComponent"
             virtualName="MappingListComponent" explicitFocusOrder="0" pos="0 168 552 260"
             sourceFile="" constructorParams=""/>
  <GROUPCOMPONENT name="MIDI input group" id="49eee95279c0cc95" memberName="midiOutputGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="200 8 344 128" title="MIDI Output"/>
  <COMBOBOX name="MIDI input combo box" id="244410f02f6c1c72" memberName="midiOutputDeviceComboBox"
            virtualName="" explicitFocusOrder="0" pos="264 32 264 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="e9b3daa69a8ac5c" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="208 32 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Device:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c578e3610ba16aaf" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="208 64 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mode:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="MIDI input combo box" id="b129ec2d38f47a91" memberName="midiOutputModeComboBox"
            virtualName="" explicitFocusOrder="0" pos="264 64 152 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="Voice stealing button" id="62c82600413ca060" memberName="midiOutputVoiceStealingButton"
                virtualName="" explicitFocusOrder="0" pos="424 64 112 24" buttonText="Voice stealing"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="afb5095c42b66671" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="208 96 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Channels:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="8fba4a69492a2f4f" memberName="midiOutputChannelLowEditor"
              virtualName="" explicitFocusOrder="0" pos="264 96 32 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="21b3096394683581" memberName="midiOutputChannelHighEditor"
              virtualName="" explicitFocusOrder="0" pos="320 96 32 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="f6b023e6043849e7" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="296 96 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="to" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="MIDI input group" id="388fb821de641818" memberName="midiOutputGroupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="8 8 184 128" title="Range"/>
  <LABEL name="new label" id="bff0e81cc2020a66" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="88 32 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="to" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="range low combo box" id="86999fb7f9fe9c2" memberName="rangeLowComboBox"
            virtualName="" explicitFocusOrder="0" pos="24 32 64 24" editable="1"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="range high combo combo box" id="7cba07ed947e85b2" memberName="rangeHighComboBox"
            virtualName="" explicitFocusOrder="0" pos="112 32 64 24" editable="1"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="fd730bc972dffbdb" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="392 96 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Transpose:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="transposition text editor" id="6f96be1359a01685" memberName="midiOutputTransposeEditor"
              virtualName="" explicitFocusOrder="0" pos="472 96 56 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="759d38e4603010a8" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="8 144 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mappings:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="add mapping button" id="a5fd2f0afd2d74b2" memberName="addMappingButton"
              virtualName="" explicitFocusOrder="0" pos="440 144 104 20" buttonText="Add Mapping..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="dbad09f5c5953d5f" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="24 68 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitchwheel range:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="pitch wheel range editor" id="593d42c6501420c1" memberName="pitchWheelRangeEditor"
              virtualName="" explicitFocusOrder="0" pos="128 68 48 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="keyboard controllers button" id="a1ebab19a3375b93" memberName="keyboardControllersButton"
              virtualName="" explicitFocusOrder="0" pos="24 100 152 20" buttonText=" Controllers..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
#endif      // TOUCHKEYS_NO_GUI
//[/EndFile]
