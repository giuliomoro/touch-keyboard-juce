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
 
  Main.cpp: main startup routines, connecting to Juce library
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainApplicationController.h"

#ifndef TOUCHKEYS_NO_GUI
#include "GUI/MainWindow.h"
#include "GUI/GraphicsDisplayWindow.h"
#include "Display/OpenGLJuceCanvas.h"

//==============================================================================
class TouchKeysApplication  : public JUCEApplication
{
public:
    //==============================================================================
    TouchKeysApplication() {}

    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed()       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) {
        // This method is where you should put your application's initialisation code..

        mainWindow_ = new MainWindow(controller_);
        keyboardDisplayWindow_ = new GraphicsDisplayWindow("TouchKeys Display", controller_.keyboardDisplay());
        
        controller_.setKeyboardDisplayWindow(keyboardDisplayWindow_);
    }

    void shutdown() {
        // Add your application's shutdown code here..
        mainWindow_ = nullptr; // (deletes our window)
        
        controller_.setKeyboardDisplayWindow(0);    // Delete display window and disconnect from controller
        keyboardDisplayWindow_ = nullptr;
    }

    //==============================================================================
    void systemRequestedQuit() {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

private:
    ScopedPointer<MainWindow> mainWindow_;
    ScopedPointer<GraphicsDisplayWindow> keyboardDisplayWindow_;
    MainApplicationController controller_;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (TouchKeysApplication)

#else // TOUCHKEYS_NO_GUI

#include <getopt.h>
#include <libgen.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

bool programShouldStop_ = false;

static struct option long_options[] = {
	{"help", no_argument, NULL, 'h'},
	{"list", no_argument, NULL, 'l'},
	{"touchkeys", required_argument, NULL, 't'},
    {"midi-input", required_argument, NULL, 'i'},
    {"midi-output", required_argument, NULL, 'o'},
    {"virtual-midi-output", no_argument, NULL, 'O'},
	{0,0,0,0}
};

void sigint_handler(int s){
    programShouldStop_ = true;
}

void usage(const char * processName)	// Print usage information and exit
{
	cerr << "Usage: " << processName << " [-h] [-l] [-t touchkeys] [-i MIDI-in] [-o MIDI-out]\n";
	cerr << "  -h:   Print this menu\n";
	cerr << "  -l:   List available TouchKeys and MIDI devices\n";
	cerr << "  -t:   Specify TouchKeys device path\n";
    cerr << "  -i:   Specify MIDI input device\n";
    cerr << "  -o:   Specify MIDI output device\n";
    cerr << "  -O:   Open virtual MIDI output\n";
}

void list_devices(MainApplicationController& controller)
{
    std::vector<std::string> touchkeysDevices(controller.availableTouchkeyDevices());
    std::vector<std::pair<int, std::string> > midiInputDevices(controller.availableMIDIInputDevices());
    std::vector<std::pair<int, std::string> > midiOutputDevices(controller.availableMIDIOutputDevices());
    
    cerr << "TouchKeys devices: \n";
    if(touchkeysDevices.empty())
        cerr << "  [none found]\n";
    else {
        for(std::vector<std::string>::iterator it = touchkeysDevices.begin(); it != touchkeysDevices.end(); ++it) {
            cerr << "  /dev/" << *it << "\n";
        }
    }

    cerr << "\nMIDI input devices: \n";
    if(midiInputDevices.empty())
        cerr << "  [none found]\n";
    else {
        for(std::vector<std::pair<int, std::string> >::iterator it = midiInputDevices.begin();
            it != midiInputDevices.end();
            ++it) {
            cerr << "  " << it->first << ": " << it->second << "\n";
        }
    }
    
    cerr << "\nMIDI output devices: \n";
    if(midiOutputDevices.empty())
        cerr << "  [none found]\n";
    else {
        for(std::vector<std::pair<int, std::string> >::iterator it = midiOutputDevices.begin();
            it != midiOutputDevices.end();
            ++it) {
            cerr << "  " << it->first << ": " << it->second << "\n";
        }
    }
}

int main (int argc, char* argv[])
{
    MainApplicationController controller;
    int ch, option_index;
    int midiInputNum = 0, midiOutputNum = 0;
    bool useVirtualMidiOutput = false;
    bool shouldStart = true;
    string touchkeysDevicePath;
    
	while((ch = getopt_long(argc, argv, "hli:o:t:O", long_options, &option_index)) != -1)
	{
        if(ch == 'l') { // List devices
            list_devices(controller);
            shouldStart = false;
            break;
        }
        else if(ch == 't') { // TouchKeys device
            touchkeysDevicePath = optarg;
        }
        else if(ch == 'i') { // MIDI input device
            midiInputNum = atoi(optarg);
        }
        else if(ch == 'o') { // MIDI output device
            midiOutputNum = atoi(optarg);
        }
        else if(ch == 'O') { // Virtual MIDI output
            useVirtualMidiOutput = true;
        }
        else {
            usage(basename(argv[0]));
            shouldStart = false;
            break;
		}
	}
    
    if(shouldStart) {
        // Main initialization: open TouchKeys and MIDI devices
        try {
            // Check whether TouchKeys device was specified. If not, take the first available one.
            /*if(touchkeysDevicePath == "") {
                std::vector<std::string> touchkeysDevices = controller.availableTouchkeyDevices();
                
                if(touchkeysDevices.empty()) {
                    cout << "No TouchKeys devices found. Check that the TouchKeys are connected.\n";
                    throw new exception;
                }
                else {
                    touchkeysDevicePath = "/dev/";
                    touchkeysDevicePath.append(touchkeysDevices[0]);
                }
            }*/
            
            // Open MIDI devices
            //cout << "Opening MIDI input device " << midiInputNum << endl;
            //controller.enableMIDIInputPort(midiInputNum);

            // TODO: enable multiple keyboard segments
            if(useVirtualMidiOutput) {
                cout << "Opening virtual MIDI output\n";
                controller.enableMIDIOutputVirtualPort(0, "TouchKeys");
            }
            else {
                cout << "Opening MIDI output device " << midiOutputNum << endl;
                controller.enableMIDIOutputPort(0, midiOutputNum);
            }
            
            // Start the TouchKeys
            cout << "Starting the TouchKeys on " << touchkeysDevicePath << " ... ";
            if(!controller.touchkeyDeviceStartupSequence(touchkeysDevicePath.c_str())) {
                cout << "failed: " << controller.touchkeyDeviceErrorMessage() << endl;
                throw new exception;
            }
            else
                cout << "succeeded!\n";
            
            // Set up interrupt catching so we can stop with Ctrl-C
            /*struct sigaction sigIntHandler;
            
            sigIntHandler.sa_handler = sigint_handler;
            sigemptyset(&sigIntHandler.sa_mask);
            sigIntHandler.sa_flags = 0;
            sigaction(SIGINT, &sigIntHandler, NULL);

            while(!programShouldStop_) {
                Thread::sleep(50);
            }*/
            
            Thread::sleep(1000);
            
            cout << "Cleaning up...\n";
        }
        catch(...) {
            
        }
    }
    
    // Clean up any MessageManager instance that JUCE creates
    DeletedAtShutdown::deleteAll();
    MessageManager::deleteInstance();
    return 0;
}

#endif // TOUCHKEYS_NO_GUI
