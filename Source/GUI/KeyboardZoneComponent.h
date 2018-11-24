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

#ifndef __JUCE_HEADER_E3CF42F64919BE28__
#define __JUCE_HEADER_E3CF42F64919BE28__

//[Headers]     -- You can add your own extra header files here --
#ifndef TOUCHKEYS_NO_GUI

#include "JuceHeader.h"
#include "MappingListComponent.h"
#include "../MainApplicationController.h"
#include "../TouchKeys/MidiKeyboardSegment.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class KeyboardZoneComponent  : public Component,
                               public TextEditor::Listener,
                               public ComboBox::Listener,
                               public Button::Listener
{
public:
    //==============================================================================
    KeyboardZoneComponent ();
    ~KeyboardZoneComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setMainApplicationController(MainApplicationController *controller) {
        // Attach the user interface to the controller and vice-versa
        controller_ = controller;
        mappingListComponent->setMainApplicationController(controller_);
        if(controller_ != 0) {
            synchronize(true);
        }
    }

    void setKeyboardSegment(MidiKeyboardSegment *segment, int zone) {
        keyboardSegment_ = segment;
        keyboardZone_ = zone;
        mappingListComponent->setKeyboardSegment(keyboardSegment_);
        if(controller_ != 0) {
            synchronize(true);
        }
    }

    MidiKeyboardSegment* keyboardSegment() {
        return keyboardSegment_;
    }
    int keyboardZone() { return keyboardZone_; }

    // TextEditor listener methods
    void textEditorTextChanged(TextEditor &editor) {}
    void textEditorReturnKeyPressed(TextEditor &editor);
    void textEditorEscapeKeyPressed(TextEditor &editor);
    void textEditorFocusLost(TextEditor &editor);

    // Synchronize UI state to match underlying state of the back end
    void synchronize(bool forceUpdates = false);

    // Update the range of the keyboard segment
    void updateSegmentRange();

    static void staticMappingChosenCallback(int result, KeyboardZoneComponent* component) {
        if (result != 0 && component != 0)
            component->mappingChosenCallback(result);
    }
    void mappingChosenCallback(int result);

    static void staticKeyboardControllerChosenCallback(int result, KeyboardZoneComponent* component) {
        if (result != 0 && component != 0)
            component->keyboardControllerChosenCallback(result);
    }
    void keyboardControllerChosenCallback(int result);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    enum {
        kInvalidMidiOutputId = -100
    };
    
    enum {
        // Offsets between Juce UI IDs and positions in vector
        kMidiOutputDeviceComboBoxOffset = 3,
        kMidiOutputModeComboBoxOffset = 1
    };

    enum {
        // Special commands for keyboard controller popup button
        kKeyboardControllerRetransmitOthers = 2000,
        kKeyboardControllerSendPitchWheelRange,
        kKeyboardControllerRetransmitPedals
    };

    // Update list of MIDI output devices
    void updateOutputDeviceList();

    // Create popup menu for mapping list
    void createMappingListPopup();

    // Create popup menu for keyboard controller retransmission
    void createKeyboardControllerPopup();

    MainApplicationController *controller_; // Pointer to the main application controller
    MidiKeyboardSegment *keyboardSegment_;  // Pointer to the segment this component controls
    int keyboardZone_;                      // Which zone this corresponds to (for UI sync purposes)
    std::vector<int> midiOutputDeviceIDs_;
    int lastSelectedMidiOutputID_;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MappingListComponent> mappingListComponent;
    ScopedPointer<GroupComponent> midiOutputGroupComponent;
    ScopedPointer<ComboBox> midiOutputDeviceComboBox;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> label5;
    ScopedPointer<ComboBox> midiOutputModeComboBox;
    ScopedPointer<ToggleButton> midiOutputVoiceStealingButton;
    ScopedPointer<Label> label2;
    ScopedPointer<TextEditor> midiOutputChannelLowEditor;
    ScopedPointer<TextEditor> midiOutputChannelHighEditor;
    ScopedPointer<Label> label3;
    ScopedPointer<GroupComponent> midiOutputGroupComponent2;
    ScopedPointer<Label> label7;
    ScopedPointer<ComboBox> rangeLowComboBox;
    ScopedPointer<ComboBox> rangeHighComboBox;
    ScopedPointer<Label> label6;
    ScopedPointer<TextEditor> midiOutputTransposeEditor;
    ScopedPointer<Label> label8;
    ScopedPointer<TextButton> addMappingButton;
    ScopedPointer<Label> label9;
    ScopedPointer<TextEditor> pitchWheelRangeEditor;
    ScopedPointer<TextButton> keyboardControllersButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardZoneComponent)
};

//[EndFile] You can add extra defines here...
#endif      // TOUCHKEYS_NO_GUI
//[/EndFile]

#endif   // __JUCE_HEADER_E3CF42F64919BE28__
