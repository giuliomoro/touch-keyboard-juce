/*
  ==============================================================================

    PreferencesWindow.h
    Created: 17 Jun 2014 11:22:44pm
    Author:  Andrew McPherson

  ==============================================================================
*/

#ifndef PREFERENCESWINDOW_H_INCLUDED
#define PREFERENCESWINDOW_H_INCLUDED

#ifndef TOUCHKEYS_NO_GUI

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PreferencesComponent.h"
#include "../MainApplicationController.h"

//==============================================================================
/*
*/
class PreferencesWindow : public DocumentWindow, public Timer
{
public:
    PreferencesWindow(MainApplicationController& controller)
    : DocumentWindow("Preferences", Colours::lightgrey, DocumentWindow::allButtons, false)
    {
        // Make a new preferences component
        preferencesComponent_ = new PreferencesComponent();
        preferencesComponent_->setMainApplicationController(&controller);
        
        // Set properties
        setContentOwned(preferencesComponent_, true);
        setUsingNativeTitleBar(true);
        setResizable(false, false);
        
        // Don't show window yet
        setTopLeftPosition(60,60);
        setVisible(false);
        
        // Start a timer that will keep the interface in sync with the application
        startTimer(50);
    }

    ~PreferencesWindow()
    {
    }
    
    // Method used by Juce timer which we will use for periodic UI updates
    // from the underlying system state
    void timerCallback() {
        preferencesComponent_->synchronize();
    }
    
    void closeButtonPressed()
    {
        setVisible(false);
    }

private:
    PreferencesComponent *preferencesComponent_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreferencesWindow)
};

#endif      // TOUCHKEYS_NO_GUI

#endif  // PREFERENCESWINDOW_H_INCLUDED
