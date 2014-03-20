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
 
  MainWindow.h: the control window, plus menu bar and Juce application methods
*/

#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include "ControlWindowMainComponent.h"
#include "../MainApplicationController.h"

//==============================================================================
/*
 */

class MainWindow    : public DocumentWindow, public Timer,
                      public MenuBarModel, public ApplicationCommandTarget
{
private:
    // Commands this application responds to
    enum CommandIDs
    {
        // File menu
        kCommandNewPreset    = 0x2001,
        kCommandOpenPreset,
        kCommandSavePreset,
        kCommandSavePresetAs,
        
        // Edit menu
        // (all standard)
        
        // Control menu
        kCommandRescanDevices = 0x2020,
        kCommandLoggingStartStop,
        kCommandLoggingPlay,
        kCommandEnableExperimentalMappings,
        kCommandTestTouchkeySensors,
        
        // Window menu
        kCommandShowControlWindow = 0x2030,
        kCommandShowKeyboardWindow
    };
    
public:
    MainWindow(MainApplicationController& controller);
    ~MainWindow();
    
    void closeButtonPressed()
    {
        // This is called when the user tries to close this window. Here, we'll just
        // ask the app to quit when this happens, but you can change this to do
        // whatever you need.
        JUCEApplication::getInstance()->systemRequestedQuit();
    }
    
    // Method used by Juce timer which we will use for periodic UI updates
    // from the underlying system state, in a configuration similar to how the
    // Juce audio plugins work
    void timerCallback();
    
    // ***** Menu Bar methods *****
    
    StringArray getMenuBarNames();
    PopupMenu getMenuForIndex (int menuIndex, const String& menuName);
    void menuItemSelected (int menuItemID, int topLevelMenuIndex);
    
    // ***** Application Command Manager methods *****
    
    // this will return the next parent component that is an ApplicationCommandTarget (in this
    // case, there probably isn't one, but it's best to use this method in your own apps).
    ApplicationCommandTarget* getNextCommandTarget();
    
    // this returns the set of all commands that this target can perform..
    void getAllCommands (Array <CommandID>& commands);
    
    // This method is used when something needs to find out the details about one of the commands
    // that this object can perform..
    void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result);
    
    // Perform a command
    bool perform (const InvocationInfo& info);
    
    /* Note: Be careful if you override any DocumentWindow methods - the base
     class uses a lot of them, so by overriding you might break its functionality.
     It's best to do all your work in your content component instead, but if
     you really have to override any DocumentWindow methods, make sure your
     subclass also calls the superclass's method.
     */
    
private:
    // The command manager object used to dispatch command events
    MainApplicationController& controller_;
    ApplicationCommandManager commandManager_;    
    ControlWindowMainComponent mainComponent_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};


#endif  // MAINWINDOW_H_INCLUDED
