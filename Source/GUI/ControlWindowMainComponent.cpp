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
#include "KeyboardZoneComponent.h"
//[/Headers]

#include "ControlWindowMainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ControlWindowMainComponent::ControlWindowMainComponent ()
    : controller_(0)
{
    addAndMakeVisible (dataLoggingGroupComponent = new GroupComponent ("MIDI input group",
                                                                       "Data Logging"));

    addAndMakeVisible (midiInputGroupComponent = new GroupComponent ("MIDI input group",
                                                                     "MIDI Input"));

    addAndMakeVisible (midiInputDeviceComboBox = new ComboBox ("MIDI input combo box"));
    midiInputDeviceComboBox->setEditableText (false);
    midiInputDeviceComboBox->setJustificationType (Justification::centredLeft);
    midiInputDeviceComboBox->setTextWhenNothingSelected (String::empty);
    midiInputDeviceComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    midiInputDeviceComboBox->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          "Device:"));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            "TouchKeys"));

    addAndMakeVisible (label2 = new Label ("new label",
                                           "Device:\n"));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (touchkeyDeviceComboBox = new ComboBox ("TouchKeys combo box"));
    touchkeyDeviceComboBox->setEditableText (false);
    touchkeyDeviceComboBox->setJustificationType (Justification::centredLeft);
    touchkeyDeviceComboBox->setTextWhenNothingSelected (String::empty);
    touchkeyDeviceComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    touchkeyDeviceComboBox->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           "Status:\n"));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (touchkeyStartButton = new TextButton ("TouchKeys start button"));
    touchkeyStartButton->setButtonText ("Start");
    touchkeyStartButton->addListener (this);

    addAndMakeVisible (touchkeyStatusLabel = new Label ("TouchKeys status label",
                                                        "not running"));
    touchkeyStatusLabel->setFont (Font (15.00f, Font::plain));
    touchkeyStatusLabel->setJustificationType (Justification::centredLeft);
    touchkeyStatusLabel->setEditable (false, false, false);
    touchkeyStatusLabel->setColour (TextEditor::textColourId, Colours::black);
    touchkeyStatusLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscGroupComponent = new GroupComponent ("OSC group",
                                                               "OSC Output"));

    addAndMakeVisible (label7 = new Label ("new label",
                                           "Host:"));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscHostTextEditor = new TextEditor ("new text editor"));
    oscHostTextEditor->setMultiLine (false);
    oscHostTextEditor->setReturnKeyStartsNewLine (false);
    oscHostTextEditor->setReadOnly (false);
    oscHostTextEditor->setScrollbarsShown (true);
    oscHostTextEditor->setCaretVisible (true);
    oscHostTextEditor->setPopupMenuEnabled (true);
    oscHostTextEditor->setText ("127.0.0.1");

    addAndMakeVisible (label8 = new Label ("new label",
                                           "Port:"));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscPortTextEditor = new TextEditor ("new text editor"));
    oscPortTextEditor->setMultiLine (false);
    oscPortTextEditor->setReturnKeyStartsNewLine (false);
    oscPortTextEditor->setReadOnly (false);
    oscPortTextEditor->setScrollbarsShown (true);
    oscPortTextEditor->setCaretVisible (true);
    oscPortTextEditor->setPopupMenuEnabled (true);
    oscPortTextEditor->setText ("8000");

    addAndMakeVisible (oscEnableButton = new ToggleButton ("OSC enable button"));
    oscEnableButton->setButtonText ("Enable OSC output");
    oscEnableButton->addListener (this);

    addAndMakeVisible (oscEnableRawButton = new ToggleButton ("OSC enable raw button"));
    oscEnableRawButton->setButtonText ("Send raw frames");
    oscEnableRawButton->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           "Lowest Octave:"));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (touchkeyOctaveComboBox = new ComboBox ("TouchKeys octave box"));
    touchkeyOctaveComboBox->setEditableText (false);
    touchkeyOctaveComboBox->setJustificationType (Justification::centredLeft);
    touchkeyOctaveComboBox->setTextWhenNothingSelected (String::empty);
    touchkeyOctaveComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    touchkeyOctaveComboBox->addListener (this);

    addAndMakeVisible (loggingButton = new TextButton ("logging button"));
    loggingButton->setButtonText ("Start Logging");
    loggingButton->addListener (this);

    addAndMakeVisible (oscInputGroupComponent = new GroupComponent ("MIDI input group",
                                                                    "OSC Input"));

    addAndMakeVisible (oscInputEnableButton = new ToggleButton ("OSC input enable button"));
    oscInputEnableButton->setButtonText ("Enable OSC input");
    oscInputEnableButton->addListener (this);

    addAndMakeVisible (label6 = new Label ("new label",
                                           "Port:"));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscInputPortTextEditor = new TextEditor ("new text editor"));
    oscInputPortTextEditor->setMultiLine (false);
    oscInputPortTextEditor->setReturnKeyStartsNewLine (false);
    oscInputPortTextEditor->setReadOnly (false);
    oscInputPortTextEditor->setScrollbarsShown (true);
    oscInputPortTextEditor->setCaretVisible (true);
    oscInputPortTextEditor->setPopupMenuEnabled (true);
    oscInputPortTextEditor->setText ("8001");

    addAndMakeVisible (playLogButton = new TextButton ("play log button"));
    playLogButton->setButtonText ("Play Log...");
    playLogButton->addListener (this);

    addAndMakeVisible (keyboardZoneTabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    keyboardZoneTabbedComponent->setTabBarDepth (30);
    keyboardZoneTabbedComponent->setCurrentTabIndex (-1);

    addAndMakeVisible (addZoneButton = new TextButton ("add zone button"));
    addZoneButton->setButtonText ("Add");
    addZoneButton->addListener (this);

    addAndMakeVisible (removeZoneButton = new TextButton ("remove zone button"));
    removeZoneButton->setButtonText ("Del");
    removeZoneButton->addListener (this);

    addAndMakeVisible (touchkeyAutodetectButton = new TextButton ("TouchKeys autodetect button"));
    touchkeyAutodetectButton->setButtonText ("Detect");
    touchkeyAutodetectButton->addListener (this);


    //[UserPreSize]
    lastSelectedMidiInputID_ = -1;
    lastSegmentUniqueIdentifier_ = -1;

    // Add octave labels to combo box
    for(int i = 0; i <= kTouchkeysMaxOctave; i++) {
        touchkeyOctaveComboBox->addItem("C" + String(i), i + kTouchkeysComponentComboBoxOffset);
    }
    //[/UserPreSize]

    setSize (872, 444);


    //[Constructor] You can add your own custom stuff here..
    oscHostTextEditor->addListener(this);
    oscPortTextEditor->addListener(this);
    oscInputPortTextEditor->addListener(this);
    //[/Constructor]
}

ControlWindowMainComponent::~ControlWindowMainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    dataLoggingGroupComponent = nullptr;
    midiInputGroupComponent = nullptr;
    midiInputDeviceComboBox = nullptr;
    label = nullptr;
    groupComponent = nullptr;
    label2 = nullptr;
    touchkeyDeviceComboBox = nullptr;
    label3 = nullptr;
    touchkeyStartButton = nullptr;
    touchkeyStatusLabel = nullptr;
    oscGroupComponent = nullptr;
    label7 = nullptr;
    oscHostTextEditor = nullptr;
    label8 = nullptr;
    oscPortTextEditor = nullptr;
    oscEnableButton = nullptr;
    oscEnableRawButton = nullptr;
    label4 = nullptr;
    touchkeyOctaveComboBox = nullptr;
    loggingButton = nullptr;
    oscInputGroupComponent = nullptr;
    oscInputEnableButton = nullptr;
    label6 = nullptr;
    oscInputPortTextEditor = nullptr;
    playLogButton = nullptr;
    keyboardZoneTabbedComponent = nullptr;
    addZoneButton = nullptr;
    removeZoneButton = nullptr;
    touchkeyAutodetectButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ControlWindowMainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffd2d2d2));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ControlWindowMainComponent::resized()
{
    dataLoggingGroupComponent->setBounds (8, 392, 304, 64);
    midiInputGroupComponent->setBounds (8, 144, 304, 64);
    midiInputDeviceComboBox->setBounds (72, 168, 224, 24);
    label->setBounds (16, 168, 55, 24);
    groupComponent->setBounds (8, 8, 304, 128);
    label2->setBounds (16, 32, 55, 24);
    touchkeyDeviceComboBox->setBounds (72, 32, 224, 24);
    label3->setBounds (16, 96, 55, 24);
    touchkeyStartButton->setBounds (216, 96, 79, 24);
    touchkeyStatusLabel->setBounds (72, 96, 136, 24);
    oscGroupComponent->setBounds (8, 288, 304, 96);
    label7->setBounds (16, 344, 55, 24);
    oscHostTextEditor->setBounds (64, 344, 128, 24);
    label8->setBounds (200, 344, 40, 24);
    oscPortTextEditor->setBounds (240, 344, 56, 24);
    oscEnableButton->setBounds (24, 312, 144, 24);
    oscEnableRawButton->setBounds (176, 312, 144, 24);
    label4->setBounds (16, 64, 104, 24);
    touchkeyOctaveComboBox->setBounds (120, 64, 88, 24);
    loggingButton->setBounds (24, 416, 128, 24);
    oscInputGroupComponent->setBounds (8, 216, 304, 64);
    oscInputEnableButton->setBounds (24, 240, 152, 24);
    label6->setBounds (200, 240, 40, 24);
    oscInputPortTextEditor->setBounds (240, 240, 56, 24);
    playLogButton->setBounds (168, 416, 128, 24);
    keyboardZoneTabbedComponent->setBounds (320, 0, 552, 464);
    addZoneButton->setBounds (776, 4, 38, 20);
    removeZoneButton->setBounds (824, 4, 38, 20);
    touchkeyAutodetectButton->setBounds (216, 64, 79, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ControlWindowMainComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    if(controller_ == 0)
        return;
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == midiInputDeviceComboBox)
    {
        //[UserComboBoxCode_midiInputDeviceComboBox] -- add your combo box handling code here..

        // Look up the selected ID, remembering that Juce indices start at 1 and the first of
        // these is "Disabled"
        int selection = midiInputDeviceComboBox->getSelectedId() - kMidiInputDeviceComboBoxOffset;
        if(selection == 1 - kMidiInputDeviceComboBoxOffset) {   // Disabled
            if(controller_->midiTouchkeysStandaloneModeIsEnabled())
                controller_->midiTouchkeysStandaloneModeDisable();
            controller_->disableAllMIDIInputPorts();
        }
        else if(selection == 2 - kMidiInputDeviceComboBoxOffset) {  // Standalone mode
            controller_->disableAllMIDIInputPorts();
            controller_->midiTouchkeysStandaloneModeEnable();
        }
        else if(selection >= 0 && selection < midiInputDeviceIDs_.size()) {
            int deviceId = midiInputDeviceIDs_[selection];
            if(controller_->midiTouchkeysStandaloneModeIsEnabled())
                controller_->midiTouchkeysStandaloneModeDisable();
            controller_->disableAllMIDIInputPorts();
            controller_->enableMIDIInputPort(deviceId);
        }
        //[/UserComboBoxCode_midiInputDeviceComboBox]
    }
    else if (comboBoxThatHasChanged == touchkeyDeviceComboBox)
    {
        //[UserComboBoxCode_touchkeyDeviceComboBox] -- add your combo box handling code here..
        // Nothing to do here right away -- wait until start button is pressed
        //[/UserComboBoxCode_touchkeyDeviceComboBox]
    }
    else if (comboBoxThatHasChanged == touchkeyOctaveComboBox)
    {
        //[UserComboBoxCode_touchkeyOctaveComboBox] -- add your combo box handling code here..
        int octave = touchkeyOctaveComboBox->getSelectedId() - kTouchkeysComponentComboBoxOffset;

        // Convert octave number to MIDI note (C4 = 60)
        if(controller_ != 0)
            controller_->touchkeyDeviceSetLowestMidiNote((octave + 1)*12);
        //[/UserComboBoxCode_touchkeyOctaveComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void ControlWindowMainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if(controller_ == 0)
        return;
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == touchkeyStartButton)
    {
        //[UserButtonCode_touchkeyStartButton] -- add your button handler code here..
#ifdef ENABLE_TOUCHKEYS_SENSOR_TEST
        if(controller_->touchkeySensorTestIsRunning()) {
            // TouchKeys were performing a sensor test. Stop the test.
            controller_->touchkeySensorTestStop();
        }
        else if(controller_->touchkeyDeviceIsRunning()) {
#else
        if(controller_->touchkeyDeviceIsRunning()) {  
#endif
            // TouchKeys were running. Stop and close.
            controller_->closeTouchkeyDevice();
        }
        else {
            // TouchKeys weren't running. Open and start.
            String devName = controller_->touchkeyDevicePrefix().c_str();
            devName += touchkeyDeviceComboBox->getText();

            // This will attempt to start the device and update the state accordingly
            controller_->touchkeyDeviceStartupSequence(devName.toUTF8());
        }
        //[/UserButtonCode_touchkeyStartButton]
    }
    else if (buttonThatWasClicked == oscEnableButton)
    {
        //[UserButtonCode_oscEnableButton] -- add your button handler code here..
        controller_->oscTransmitSetEnabled(oscEnableButton->getToggleState());
        //[/UserButtonCode_oscEnableButton]
    }
    else if (buttonThatWasClicked == oscEnableRawButton)
    {
        //[UserButtonCode_oscEnableRawButton] -- add your button handler code here..
        controller_->oscTransmitSetRawDataEnabled(oscEnableRawButton->getToggleState());
        //[/UserButtonCode_oscEnableRawButton]
    }
    else if (buttonThatWasClicked == loggingButton)
    {
        //[UserButtonCode_loggingButton] -- add your button handler code here..
        if(controller_->isLogging())
            controller_->stopLogging();
        else
            controller_->startLogging();
        //[/UserButtonCode_loggingButton]
    }
    else if (buttonThatWasClicked == oscInputEnableButton)
    {
        //[UserButtonCode_oscInputEnableButton] -- add your button handler code here..
        controller_->oscReceiveSetEnabled(oscInputEnableButton->getToggleState());
        //[/UserButtonCode_oscInputEnableButton]
    }
    else if (buttonThatWasClicked == playLogButton)
    {
        //[UserButtonCode_playLogButton] -- add your button handler code here..
        //[/UserButtonCode_playLogButton]
    }
    else if (buttonThatWasClicked == addZoneButton)
    {
        //[UserButtonCode_addZoneButton] -- add your button handler code here..
        controller_->midiSegmentAdd();
        //[/UserButtonCode_addZoneButton]
    }
    else if (buttonThatWasClicked == removeZoneButton)
    {
        //[UserButtonCode_removeZoneButton] -- add your button handler code here..
        int tabIndex = keyboardZoneTabbedComponent->getCurrentTabIndex();
        if(tabIndex != 0) {
            KeyboardZoneComponent* selectedComponent = static_cast<KeyboardZoneComponent*> (keyboardZoneTabbedComponent->getTabContentComponent(tabIndex));
            controller_->midiSegmentRemove(selectedComponent->keyboardSegment());
        }
        //[/UserButtonCode_removeZoneButton]
    }
    else if (buttonThatWasClicked == touchkeyAutodetectButton)
    {
        //[UserButtonCode_touchkeyAutodetectButton] -- add your button handler code here..
        if(controller_->touchkeyDeviceIsAutodetecting())
            controller_->touchkeyDeviceStopAutodetecting();
        else
            controller_->touchkeyDeviceAutodetectLowestMidiNote();
        //[/UserButtonCode_touchkeyAutodetectButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void ControlWindowMainComponent::textEditorReturnKeyPressed(TextEditor &editor)
{
    if(controller_ == 0)
        return;
    if(&editor == oscHostTextEditor || &editor == oscPortTextEditor)
        updateOscHostPort();
    else if(&editor == oscInputPortTextEditor) {
        int port = atoi(oscInputPortTextEditor->getText().toUTF8());
        controller_->oscReceiveSetPort(port);
    }
}

void ControlWindowMainComponent::textEditorEscapeKeyPressed(TextEditor &editor)
{
    // Nothing to do here
}

void ControlWindowMainComponent::textEditorFocusLost(TextEditor &editor)
{
    textEditorReturnKeyPressed(editor);
}

// Update list of TouchKeys and MIDI input devices
void ControlWindowMainComponent::updateInputDeviceList()
{
    if(controller_ == 0)
        return;

    // *** TouchKeys devices ***
    vector<string> tkdevices = controller_->availableTouchkeyDevices();
    vector<string>::iterator tkit;
    int counter;

    touchkeyDeviceComboBox->clear();

    if(tkdevices.size() == 0) {
        touchkeyDeviceComboBox->addItem("No devices", 1);
        touchkeyDeviceComboBox->setSelectedId(1, dontSendNotification);
        touchkeyDeviceComboBox->setEnabled(false);
        touchkeyStartButton->setEnabled(false);
    }
    else {
        counter = 1;
        for(tkit = tkdevices.begin(); tkit != tkdevices.end(); ++tkit) {
            touchkeyDeviceComboBox->addItem(tkit->c_str(), counter++);
        }
        touchkeyDeviceComboBox->setSelectedId(1, dontSendNotification);
        touchkeyDeviceComboBox->setEnabled(true);
        touchkeyStartButton->setEnabled(true);
    }

    // *** MIDI input devices ***
    vector<pair<int, string> > devices = controller_->availableMIDIInputDevices();
    vector<pair<int, string> >::iterator it;

    midiInputDeviceComboBox->clear();
    midiInputDeviceIDs_.clear();
    midiInputDeviceComboBox->addItem("Disabled", 1);
    midiInputDeviceComboBox->addItem("TouchKeys Standalone", 2);
    counter = kMidiInputDeviceComboBoxOffset;
    for(it = devices.begin(); it != devices.end(); ++it) {
        midiInputDeviceComboBox->addItem((*it).second.c_str(), counter);
        midiInputDeviceIDs_.push_back(it->first);
        counter++;
    }
}

void ControlWindowMainComponent::updateOscHostPort()
{
    if(controller_ == 0)
        return;

    String oscHost = oscHostTextEditor->getText();
    String oscPort = oscPortTextEditor->getText();
    controller_->oscTransmitClearAddresses();
    controller_->oscTransmitAddAddress(oscHost.toUTF8(), oscPort.toUTF8());
}

// Synchronize the UI state with the underlying state of the controller
void ControlWindowMainComponent::synchronize() {
    if(controller_ == 0)
        return;

    // Update TouchKeys status
#ifdef ENABLE_TOUCHKEYS_SENSOR_TEST
    if(controller_->touchkeySensorTestIsRunning()) {
        touchkeyStartButton->setButtonText("Stop");
        touchkeyStatusLabel->setText("Testing", dontSendNotification);
    }
    else if(controller_->touchkeyDeviceIsRunning()) {
#else
    if(controller_->touchkeyDeviceIsRunning()) {
#endif
        touchkeyStartButton->setButtonText("Stop");
        touchkeyStatusLabel->setText("Running", dontSendNotification);
    }
    else if(controller_->touchkeyDeviceErrorOccurred()) {
        touchkeyStartButton->setButtonText("Start");
        touchkeyStatusLabel->setText(controller_->touchkeyDeviceErrorMessage().c_str(), dontSendNotification);
    }
    else {
        touchkeyStartButton->setButtonText("Start");
        touchkeyStatusLabel->setText("Not running", dontSendNotification);
    }

    // Update MIDI input status
    if(controller_->midiTouchkeysStandaloneModeIsEnabled()) {
        midiInputDeviceComboBox->setSelectedId(2, dontSendNotification);
    }
    else {
        const std::vector<int>& selectedMidiInputDevices(controller_->selectedMIDIInputPorts());
        if(selectedMidiInputDevices.empty()) {
            midiInputDeviceComboBox->setSelectedId(1, dontSendNotification);
        }
        else if(selectedMidiInputDevices.front() != lastSelectedMidiInputID_){
            // Input has changed from before. Find it in vector
            // If there is more than one selected ID, we will only take the first one for
            // the current UI. This affects the display but not the functionality.
            for(int i = 0; i < midiInputDeviceIDs_.size(); i++) {
                if(midiInputDeviceIDs_[i] == selectedMidiInputDevices.front()) {
                    midiInputDeviceComboBox->setSelectedId(i + kMidiInputDeviceComboBoxOffset, dontSendNotification);
                    break;
                }
            }
            // ...and cache this as the last ID so we don't search again next time
            lastSelectedMidiInputID_ = selectedMidiInputDevices.front();
        }
    }

    // Update OSC status
    oscEnableButton->setToggleState(controller_->oscTransmitEnabled(), dontSendNotification);
    oscEnableRawButton->setToggleState(controller_->oscTransmitRawDataEnabled(), dontSendNotification);
    oscInputEnableButton->setToggleState(controller_->oscReceiveEnabled(), dontSendNotification);

    // Update the OSC fields only if the text editors aren't active
    if(!oscHostTextEditor->hasKeyboardFocus(true) && !oscPortTextEditor->hasKeyboardFocus(true)) {
        const std::vector<lo_address>& oscAddresses = controller_->oscTransmitAddresses();
        if(oscAddresses.empty()) {
            oscHostTextEditor->setText("", false);
            oscPortTextEditor->setText("", false);
        }
        else {
            // Take the first address to display in the text editor. As with MIDI input,
            // this doesn't affect the functionality, only the UI display.
            lo_address firstAddress = oscAddresses.front();

            oscHostTextEditor->setText(lo_address_get_hostname(firstAddress), false);
            oscPortTextEditor->setText(lo_address_get_port(firstAddress), false);
        }
    }
    if(!oscInputPortTextEditor->hasKeyboardFocus(true)) {
        int port = controller_->oscReceivePort();
        oscInputPortTextEditor->setText(String(port), false);
    }

    // Set the octave button
    int octave = (controller_->touchkeyDeviceLowestMidiNote() / 12) - 1;
    if(octave >= 0 && octave <= kTouchkeysMaxOctave)
        touchkeyOctaveComboBox->setSelectedId(octave + kTouchkeysComponentComboBoxOffset, dontSendNotification);

    // Enable or disable the autodetect button depending on the device status
    if(!controller_->touchkeyDeviceIsRunning()) {
        touchkeyAutodetectButton->setEnabled(false);
    }
    else if(controller_->touchkeyDeviceIsAutodetecting()) {
        touchkeyAutodetectButton->setEnabled(true);
        touchkeyAutodetectButton->setButtonText("Cancel");
    }
    else {
        touchkeyAutodetectButton->setEnabled(true);
        touchkeyAutodetectButton->setButtonText("Detect");
    }

    // Set the text on the logging button
    if(controller_->isLogging()) {
        loggingButton->setButtonText("Stop Logging");
    }
    else
        loggingButton->setButtonText("Start Logging");

    // Update segments list if it has changed
    if(lastSegmentUniqueIdentifier_ != controller_->midiSegmentUniqueIdentifier())
        updateKeyboardSegments();

    // Synchronize every tab component
    for(int tab = 0; tab < keyboardZoneTabbedComponent->getNumTabs(); tab++) {
        KeyboardZoneComponent *component = static_cast<KeyboardZoneComponent*> (keyboardZoneTabbedComponent->getTabContentComponent(tab));
        component->synchronize();
    }

    // Update add/remove buttons
    if(keyboardZoneTabbedComponent->getCurrentTabIndex() <= 0) {
        removeZoneButton->setEnabled(false);
    }
    else {
        removeZoneButton->setEnabled(true);
    }
    if(controller_->midiSegmentsCount() >= 8)
        addZoneButton->setEnabled(false);
    else
        addZoneButton->setEnabled(true);
}

// Return the currently selected TouchKeys string
String ControlWindowMainComponent::currentTouchkeysSelectedPath()
{
    String devName = controller_->touchkeyDevicePrefix().c_str();
    devName += touchkeyDeviceComboBox->getText();
    
    return devName;
}

// Update the state of the keyboard segment tab bar. Called only when segments change
void ControlWindowMainComponent::updateKeyboardSegments()
{
    if(controller_ == 0)
        return;
    // Update the identifier to say we've matched the current state of the segments
    lastSegmentUniqueIdentifier_ = controller_->midiSegmentUniqueIdentifier();

    // Save the current selected index in case we later remove it
    int currentlySelectedIndex = keyboardZoneTabbedComponent->getCurrentTabIndex();
    KeyboardZoneComponent* currentlySelectedComponent = static_cast<KeyboardZoneComponent*> (keyboardZoneTabbedComponent->getTabContentComponent(currentlySelectedIndex));
    MidiKeyboardSegment* currentlySelectedSegment = 0;
    if(currentlySelectedComponent != 0)
        currentlySelectedSegment = currentlySelectedComponent->keyboardSegment();
    bool selectedNewTab = false;

    // First, go through the segments and create tabs as needed
    int maxNumSegments = controller_->midiSegmentsCount();
    for(int i = 0; i < maxNumSegments; i++) {
        MidiKeyboardSegment* segment = controller_->midiSegment(i);
        bool matched = false;
        if(segment == 0)
            continue;
        // Look for this segment among the tabs we already have
        for(int tab = 0; tab < keyboardZoneTabbedComponent->getNumTabs(); tab++) {
            KeyboardZoneComponent *component = static_cast<KeyboardZoneComponent*> (keyboardZoneTabbedComponent->getTabContentComponent(tab));
            if(component->keyboardSegment() == segment) {
                // Found it...
                matched = true;
                break;
            }
        }
        // If we didn't find it, add a tab for this segment
        if(!matched) {
            KeyboardZoneComponent *newComponent = new KeyboardZoneComponent();
            newComponent->setMainApplicationController(controller_);
            newComponent->setKeyboardSegment(segment);

            char name[16];
#ifdef _MSC_VER
			_snprintf_s(name, 16, _TRUNCATE, "Zone %d", segment->outputPort());
#else
            snprintf(name, 16, "Zone %d", segment->outputPort());
#endif

            // Add the component, telling the tab manager to take charge of deleting it at the end
            keyboardZoneTabbedComponent->addTab(name, Colours::lightgrey, newComponent, true);
            keyboardZoneTabbedComponent->setCurrentTabIndex(keyboardZoneTabbedComponent->getNumTabs() - 1);
            selectedNewTab = true;

            //std::cout << "Adding tab for segment " << segment << endl;
        }
    }

    // Now go through the other way and remove tabs that are no longer needed
    // Iterate through each tab: find a match in the segments
    int tab = 0;
    while(tab < keyboardZoneTabbedComponent->getNumTabs()) {
        KeyboardZoneComponent *component = static_cast<KeyboardZoneComponent*> (keyboardZoneTabbedComponent->getTabContentComponent(tab));
        MidiKeyboardSegment *segment = component->keyboardSegment();
        bool matched = false;

        for(int i = 0; i < maxNumSegments; i++) {
            if(segment == controller_->midiSegment(i)) {
                matched = true;
                break;
            }
        }
        if(segment == 0 || !matched) {
            //std::cout << "Removing tab for nonexistent segment " << segment << endl;

            if(currentlySelectedSegment == segment) {
                // The currently selected tab has been removed. Select the prior one.
                if(currentlySelectedIndex > 0)
                    keyboardZoneTabbedComponent->setCurrentTabIndex(currentlySelectedIndex - 1);
                else
                    keyboardZoneTabbedComponent->setCurrentTabIndex(0);
            }

            // This tab holds a nonexistent segment and should be removed
            keyboardZoneTabbedComponent->removeTab(tab);

            // And we have to start over again since the tab indexing has changed
            tab = 0;
        }
        else    // Found a match: check the next tab
            tab++;
        // Eventually, we get to the end of the list of tabs an we know every existing tab matches a segment
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ControlWindowMainComponent"
                 componentName="" parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="controller_(0)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="872" initialHeight="444">
  <BACKGROUND backgroundColour="ffd2d2d2"/>
  <GROUPCOMPONENT name="MIDI input group" id="87491da999138aa9" memberName="dataLoggingGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 392 304 64" title="Data Logging"/>
  <GROUPCOMPONENT name="MIDI input group" id="ce80a86ee6475cd9" memberName="midiInputGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 144 304 64" title="MIDI Input"/>
  <COMBOBOX name="MIDI input combo box" id="def32c74505cfa50" memberName="midiInputDeviceComboBox"
            virtualName="" explicitFocusOrder="0" pos="72 168 224 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="ad7bc4640d8023b7" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 168 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Device:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="new group" id="9106305fd2211185" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 8 304 128" title="TouchKeys"/>
  <LABEL name="new label" id="944877a84dcfc602" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="16 32 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Device:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="TouchKeys combo box" id="871223bdcad0e693" memberName="touchkeyDeviceComboBox"
            virtualName="" explicitFocusOrder="0" pos="72 32 224 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="1cdf89082d95c72c" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="16 96 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Status:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="TouchKeys start button" id="1bb1c69c957fc984" memberName="touchkeyStartButton"
              virtualName="" explicitFocusOrder="0" pos="216 96 79 24" buttonText="Start"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="TouchKeys status label" id="c91b132696e6ba1d" memberName="touchkeyStatusLabel"
         virtualName="" explicitFocusOrder="0" pos="72 96 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="not running" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="OSC group" id="8268119e22809825" memberName="oscGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 288 304 96" title="OSC Output"/>
  <LABEL name="new label" id="896c0c48a1cf50a" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="16 344 55 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Host:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="84778d0bbebedd36" memberName="oscHostTextEditor"
              virtualName="" explicitFocusOrder="0" pos="64 344 128 24" initialText="127.0.0.1"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="157c85bf83a7f936" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="200 344 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Port:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="7c21f0c238812d11" memberName="oscPortTextEditor"
              virtualName="" explicitFocusOrder="0" pos="240 344 56 24" initialText="8000"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="OSC enable button" id="ccd52591cfd0b632" memberName="oscEnableButton"
                virtualName="" explicitFocusOrder="0" pos="24 312 144 24" buttonText="Enable OSC output"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="OSC enable raw button" id="4aaf8f80edaff24" memberName="oscEnableRawButton"
                virtualName="" explicitFocusOrder="0" pos="176 312 144 24" buttonText="Send raw frames"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="c5873c6498f8156d" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="16 64 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Lowest Octave:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="TouchKeys octave box" id="36ace32027c81d30" memberName="touchkeyOctaveComboBox"
            virtualName="" explicitFocusOrder="0" pos="120 64 88 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="logging button" id="44705422dd1cb795" memberName="loggingButton"
              virtualName="" explicitFocusOrder="0" pos="24 416 128 24" buttonText="Start Logging"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GROUPCOMPONENT name="MIDI input group" id="bb54712f78382055" memberName="oscInputGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 216 304 64" title="OSC Input"/>
  <TOGGLEBUTTON name="OSC input enable button" id="22a196770a440560" memberName="oscInputEnableButton"
                virtualName="" explicitFocusOrder="0" pos="24 240 152 24" buttonText="Enable OSC input"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="c680c2da87cdcbf2" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="200 240 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Port:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="d4a91e8bff5b6bc9" memberName="oscInputPortTextEditor"
              virtualName="" explicitFocusOrder="0" pos="240 240 56 24" initialText="8001"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="play log button" id="44858f01a66d263d" memberName="playLogButton"
              virtualName="" explicitFocusOrder="0" pos="168 416 128 24" buttonText="Play Log..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TABBEDCOMPONENT name="keyboard zone tabbed component" id="33da3d6583cdacbf" memberName="keyboardZoneTabbedComponent"
                   virtualName="" explicitFocusOrder="0" pos="320 0 552 464" orientation="top"
                   tabBarDepth="30" initialTab="-1"/>
  <TEXTBUTTON name="add zone button" id="1d2fa7fd74f31315" memberName="addZoneButton"
              virtualName="" explicitFocusOrder="0" pos="776 4 38 20" buttonText="Add"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="remove zone button" id="7865f7787a191e0e" memberName="removeZoneButton"
              virtualName="" explicitFocusOrder="0" pos="824 4 38 20" buttonText="Del"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="TouchKeys autodetect button" id="6e19894bc11d0276" memberName="touchkeyAutodetectButton"
              virtualName="" explicitFocusOrder="0" pos="216 64 79 24" buttonText="Detect"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
