/*
  TouchKeys: multi-touch musical keyboard control software
  Copyright (c) 2013 Andrew McPherson

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
  =====================================================================
 
  MainWindow.cpp: the control window, plus menu bar and Juce application methods
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"

//==============================================================================
MainWindow::MainWindow(MainApplicationController& controller)
: DocumentWindow ("TouchKeys", Colours::lightgrey, DocumentWindow::allButtons),
  controller_(controller)
{
    commandManager_.registerAllCommandsForTarget(this);
    commandManager_.registerAllCommandsForTarget(JUCEApplication::getInstance());
    
    // This lets the command manager use keypresses that arrive in our window to send
    // out commands
    addKeyListener(commandManager_.getKeyMappings());
    
    // Create the menu bar, either in the window or at the top of the screen
#if JUCE_MAC
    MenuBarModel::setMacMainMenu(this);
#else
    // Menu bar goes at the top of the window
    setMenuBar(this);
    
    // Window height should change to accommodate it
    Component *actualMenuBar = getMenuBarComponent();
    if(actualMenuBar != 0) {
        juce::Rectangle<int> r = actualMenuBar->getBounds();
        setSize(getWidth(), getHeight() + r.getHeight());
    }
#endif /* JUCE_MAC */
    
    // Tells our menu bar model that it should watch this command manager for
    // changes, and send change messages accordingly.
    setApplicationCommandManagerToWatch(&commandManager_);
    
    mainComponent_.setMainApplicationController(&controller_);
    setContentNonOwned(&mainComponent_, true);
    
    commandManager_.setFirstCommandTarget(this);
    
    // Start a timer that will keep the interface in sync with the application
    startTimer(50);
    
    centreWithSize (getWidth(), getHeight());
    setUsingNativeTitleBar(true);
    
    // Allow resizing to be larger vertically
    setResizable(true, true);
    setResizeLimits(getWidth(), getHeight(), getWidth(), 2048);
    
    setVisible (true);
}

MainWindow::~MainWindow() {
    // Delete the menu bar before exiting
#if JUCE_MAC
    MenuBarModel::setMacMainMenu(nullptr);
#else
    setMenuBar(nullptr);
#endif /* JUCE_MAC */
}

// Handle periodic GUI updates, keeping the GUI in sync with the underlying system
void MainWindow::timerCallback() {
    mainComponent_.synchronize();
}

// ***** Juce menu bar methods ****
StringArray MainWindow::getMenuBarNames() {
    const char* const names[] = { "File", "Edit", "Control", "Window", nullptr };
    
    return StringArray (names);
}

PopupMenu MainWindow::getMenuForIndex(int menuIndex, const String& menuName) {
    PopupMenu menu;
    
    if(menuIndex == 0) { // File
        menu.addCommandItem(&commandManager_, kCommandClearPreset);
        menu.addSeparator();
        menu.addCommandItem(&commandManager_, kCommandOpenPreset);
        menu.addCommandItem(&commandManager_, kCommandSavePreset);
#ifndef JUCE_MAC
        menu.addSeparator();
        menu.addCommandItem(&commandManager_, StandardApplicationCommandIDs::quit);
#endif
    }
    else if(menuIndex == 1) { // Edit
        menu.addCommandItem(&commandManager_, StandardApplicationCommandIDs::undo);
        menu.addCommandItem(&commandManager_, StandardApplicationCommandIDs::redo);
        menu.addSeparator();
        menu.addCommandItem(&commandManager_, StandardApplicationCommandIDs::cut);
        menu.addCommandItem(&commandManager_, StandardApplicationCommandIDs::copy);
        menu.addCommandItem(&commandManager_, StandardApplicationCommandIDs::paste);
        menu.addCommandItem(&commandManager_, StandardApplicationCommandIDs::del);
        menu.addSeparator();
        menu.addCommandItem(&commandManager_, StandardApplicationCommandIDs::selectAll);
    }
    else if(menuIndex == 2) { // Control
        menu.addCommandItem(&commandManager_, kCommandRescanDevices);
        menu.addSeparator();
        menu.addCommandItem(&commandManager_, kCommandLoggingStartStop);
        menu.addCommandItem(&commandManager_, kCommandLoggingPlay);
        menu.addSeparator();
        menu.addCommandItem(&commandManager_, kCommandEnableExperimentalMappings);
#ifdef ENABLE_TOUCHKEYS_SENSOR_TEST
        menu.addCommandItem(&commandManager_, kCommandTestTouchkeySensors);
#endif
    }
    else if(menuIndex == 3) { // Window
        menu.addCommandItem(&commandManager_, kCommandShowControlWindow);
        menu.addCommandItem(&commandManager_, kCommandShowKeyboardWindow);
    }
    
    return menu;
}

void MainWindow::menuItemSelected(int menuItemID, int topLevelMenuIndex) {
    // TODO
}

// **** Command Manager methods *****

ApplicationCommandTarget* MainWindow::getNextCommandTarget() {
    return findFirstTargetParentComponent();
}

// this returns the set of all commands that this target can perform..
void MainWindow::getAllCommands(Array <CommandID>& commands) {
    // this returns the set of all commands that this target can perform..
    const CommandID ids[] = {
        // File
        kCommandClearPreset,
        kCommandOpenPreset,
        kCommandSavePreset,
        // Edit
        StandardApplicationCommandIDs::undo,
        StandardApplicationCommandIDs::redo,
        StandardApplicationCommandIDs::cut,
        StandardApplicationCommandIDs::copy,
        StandardApplicationCommandIDs::paste,
        StandardApplicationCommandIDs::del,
        StandardApplicationCommandIDs::selectAll,
        // Control
        kCommandRescanDevices,
        kCommandLoggingStartStop,
        kCommandLoggingPlay,
        kCommandEnableExperimentalMappings,
#ifdef ENABLE_TOUCHKEYS_SENSOR_TEST
        kCommandTestTouchkeySensors,
#endif
        // Window
        kCommandShowControlWindow,
        kCommandShowKeyboardWindow
    };
    
    commands.addArray (ids, numElementsInArray(ids));
}

// This method is used when something needs to find out the details about one of the commands
// that this object can perform..
void MainWindow::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) {
    const String presetsCategory("Presets");
    const String editsCategory("Editing");
    const String controlCategory("Control");
    const String windowCategory("Window");
    
    switch (commandID) {
            
        // *** File Menu ***
        case kCommandClearPreset:
            result.setInfo("Clear Settings", "Clears the current settings", presetsCategory, 0);
            result.setTicked(false);
            result.setActive(true);
            break;
        case kCommandOpenPreset:
            result.setInfo("Open Preset...", "Opens an existing preset", presetsCategory, 0);
            result.setTicked(false);
            result.setActive(true);
            result.addDefaultKeypress ('O', ModifierKeys::commandModifier);
            break;
        case kCommandSavePreset:
            result.setInfo("Save Preset...", "Saves the current preset", presetsCategory, 0);
            result.setTicked(false);
            result.setActive(true);
            result.addDefaultKeypress ('S', ModifierKeys::commandModifier);
            break;
        // Quit command is handled by JuceApplication
            
        // *** Edit Menu ***
        case StandardApplicationCommandIDs::undo:
            result.setInfo("Undo", "Undo", editsCategory, 0);
            result.setTicked(false);
            result.setActive(false);
            result.addDefaultKeypress ('Z', ModifierKeys::commandModifier);
            break;
        case StandardApplicationCommandIDs::redo:
            result.setInfo("Redo", "Redo", editsCategory, 0);
            result.setTicked(false);
            result.setActive(false);
            result.addDefaultKeypress ('Z', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
            break;
        case StandardApplicationCommandIDs::cut:
            result.setInfo("Cut", "Cut", editsCategory, 0);
            result.setTicked(false);
            result.setActive(false);
            result.addDefaultKeypress ('X', ModifierKeys::commandModifier);
            break;
        case StandardApplicationCommandIDs::copy:
            result.setInfo("Copy", "Copy", editsCategory, 0);
            result.setTicked(false);
            result.setActive(false);
            result.addDefaultKeypress ('C', ModifierKeys::commandModifier);
            break;
        case StandardApplicationCommandIDs::paste:
            result.setInfo("Paste", "Paste", editsCategory, 0);
            result.setTicked(false);
            result.setActive(false);
            result.addDefaultKeypress ('V', ModifierKeys::commandModifier);
            break;
        case StandardApplicationCommandIDs::del:
            result.setInfo("Delete", "Delete", editsCategory, 0);
            result.setTicked(false);
            result.setActive(false);
            break;
        case StandardApplicationCommandIDs::selectAll:
            result.setInfo("Select All", "Select All", editsCategory, 0);
            result.setTicked(false);
            result.setActive(false);
            result.addDefaultKeypress ('A', ModifierKeys::commandModifier);
            break;
            
        // *** Control Menu ***
        case kCommandRescanDevices:
            result.setInfo("Rescan Devices", "Rescans available TouchKeys and MIDI devices", controlCategory, 0);
            result.setTicked(false);
            result.setActive(true);
            result.addDefaultKeypress ('R', ModifierKeys::commandModifier);
            break;
        case kCommandLoggingStartStop:
            result.setInfo("Record Log File", "Records TouchKeys and MIDI data to file", controlCategory, 0);
            result.setTicked(controller_.isLogging());
            result.setActive(true);
            break;
        case kCommandLoggingPlay:
            result.setInfo("Play Log...", "Plays TouchKeys and MIDI from file", controlCategory, 0);
            result.setTicked(false);
            result.setActive(false);
            break;
        case kCommandEnableExperimentalMappings:
            result.setInfo("Enable Experimental Mappings", "Enables mappings which are still experimental", controlCategory, 0);
            result.setTicked(controller_.experimentalMappingsEnabled());
            break;
#ifdef ENABLE_TOUCHKEYS_SENSOR_TEST
        case kCommandTestTouchkeySensors:
            result.setInfo("Test TouchKeys Sensors", "Enables a test of individual TouchKeys sensors", controlCategory, 0);
            result.setActive(controller_.availableTouchkeyDevices().size() > 0);
            result.setTicked(controller_.touchkeySensorTestIsRunning());
            break;
#endif
            
        // *** Window Menu ***
        case kCommandShowControlWindow:
            result.setInfo("TouchKeys Controls", "Show control and mapping window", windowCategory, 0);
            result.setTicked(false);
            result.addDefaultKeypress ('1', ModifierKeys::commandModifier);
            break;
        case kCommandShowKeyboardWindow:
            result.setInfo("Keyboard Display", "Show keyboard display", windowCategory, 0);
            result.setTicked(false);
            result.addDefaultKeypress ('2', ModifierKeys::commandModifier);
            break;
            
        default:
            break;
    };
}

bool MainWindow::perform(const InvocationInfo& info) {
    switch (info.commandID)
    {
        case kCommandClearPreset:
            // Display an alert to confirm the user wants to delete this mapping
            AlertWindow::showOkCancelBox (AlertWindow::QuestionIcon,
                                          "Clear settings",
                                          "Are you sure you want to clear all zones and mappings?",
                                          String::empty,
                                          String::empty,
                                          0,
                                          ModalCallbackFunction::forComponent(alertBoxResultChosen, this));
            break;
        case kCommandOpenPreset:
            controller_.loadPresetWithDialog();
            break;
        case kCommandSavePreset:
            controller_.savePresetWithDialog();
            break;
        case kCommandRescanDevices:
            controller_.tellDevicesToUpdate();
            break;
        case kCommandLoggingStartStop:
            if(controller_.isLogging())
                controller_.stopLogging();
            else
                controller_.startLogging();
            break;
        case kCommandLoggingPlay:
            // TODO
            break;
        case kCommandEnableExperimentalMappings:
            controller_.setExperimentalMappingsEnabled(!controller_.experimentalMappingsEnabled());
            break;
#ifdef ENABLE_TOUCHKEYS_SENSOR_TEST
        case kCommandTestTouchkeySensors:
            if(!controller_.touchkeySensorTestIsRunning())
                controller_.touchkeySensorTestStart(mainComponent_.currentTouchkeysSelectedPath().toUTF8(), controller_.touchkeyDeviceLowestMidiNote());
            else
                controller_.touchkeySensorTestStop();
            break;
#endif
        case kCommandShowControlWindow:
            toFront(true);
            break;
        case kCommandShowKeyboardWindow:
            controller_.showKeyboardDisplayWindow();
            break;

        default:
            return false;
    };
    
    return true;
}

// Called when user clicks a result in the alert box to confirm deletion
void MainWindow::alertBoxResultChosen(int result, MainWindow *item) {
    if(result != 0) {
        item->clearPreset();
    }
}
