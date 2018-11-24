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

#ifndef __JUCE_HEADER_248C56742F074362__
#define __JUCE_HEADER_248C56742F074362__

//[Headers]     -- You can add your own extra header files here --
#ifndef TOUCHKEYS_NO_GUI
#include "JuceHeader.h"

class MainApplicationController;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PreferencesComponent  : public Component,
                              public ComboBox::Listener,
                              public Button::Listener
{
public:
    //==============================================================================
    PreferencesComponent ();
    ~PreferencesComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    void setMainApplicationController(MainApplicationController *controller) {
        // Attach the user interface to the controller and vice-versa
        controller_ = controller;
    }

    // Synchronize UI state to match underlying state of the back end
    void synchronize(bool forceUpdates = false);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    enum {
        kStartupPresetNone = 1,
        kStartupPresetVibratoPitchBend,
        kStartupPresetLastSaved,
        kStartupPresetChoose
    };

    MainApplicationController *controller_; // Pointer to the main application controller

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> startupPresetComboBox;
    ScopedPointer<Label> label4;
    ScopedPointer<ToggleButton> startTouchKeysButton;
    ScopedPointer<ToggleButton> autodetectButton;
    ScopedPointer<TextButton> defaultsButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreferencesComponent)
};

//[EndFile] You can add extra defines here...
#endif          // TOUCHKEYS_NO_GUI
//[/EndFile]

#endif   // __JUCE_HEADER_248C56742F074362__
