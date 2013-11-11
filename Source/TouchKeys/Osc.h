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
 
  Osc.h: classes for handling reception and transmission of OSC messages,
  using the liblo library.
*/

#ifndef OSC_H
#define OSC_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "../JuceLibraryCode/JuceHeader.h"
#include "lo/lo.h"

using namespace std;

class OscMessageSource;

// This is an abstract base class implementing a single function oscHandlerMethod().  Objects that
// want to register to receive OSC messages should inherit from OscHandler.  Notice that all listener
// add/remove methods are private or protected.  The subclass of OscHandler should add any relevant 
// listeners, or optionally expose a public interface to add listeners.  (Never call the methods in
// OscMessageSource externally.)

class OscHandler
{
public:
	OscHandler() : oscController_(NULL) {}
	
	// The OSC controller will call this method when it gets a matching message that's been registered
	virtual bool oscHandlerMethod(const char *path, const char *types, int numValues, lo_arg **values, void *data) = 0;
	void setOscController(OscMessageSource *c) { oscController_ = c; }
	
	virtual ~OscHandler();	// In the destructor, remove all OSC listeners
protected:
	bool addOscListener(const string& path);
	bool removeOscListener(const string& path);
	bool removeAllOscListeners();
	
	OscMessageSource *oscController_;
	set<string> oscListenerPaths_;
};

// Base class for anything that acts as a source of OSC messages.  Could be
// received externally or internally generated.

class OscMessageSource
{
	friend class OscHandler;
	
public:
	OscMessageSource() {}
	
protected:
	bool addListener(const string& path, OscHandler *object);		// Add a listener object for a specific path
	bool removeListener(const string& path, OscHandler *object);	// Remove a listener object	from a specific path
	bool removeListener(OscHandler *object);						// Remove a listener object from all paths
	
    void updateListeners();                                         // Propagate changes to the listeners to the main object
    
	//ReadWriteLock oscListenerMutex_;                // This mutex protects the OSC listener table from being modified mid-message
	CriticalSection oscListenerMutex_;                // This mutex protects the OSC listener table from being modified mid-message
    CriticalSection oscUpdaterMutex_;                 // This mutex controls the insertion of objects in add/removeListener
    
	multimap<string, OscHandler*> noteListeners_;	// Map from OSC path name to handler (possibly multiple handlers per object)
    multimap<string, OscHandler*> noteListenersToAdd_;    // Collection of listeners to add on the next cycle
    multimap<string, OscHandler*> noteListenersToRemove_; // Collection of listeners to remove on the next cycle
    set<OscHandler*> noteListenersForBlanketRemoval_;     // Collection of listeners to remove from all paths
};

// This class specifically implements OSC messages coming from external sources

class OscReceiver : public OscMessageSource
{
public:
	OscReceiver(lo_server_thread thread, const char *prefix) {
		oscServerThread_ = thread;
		globalPrefix_.assign(prefix);
		useThru_ = false;
		lo_server_thread_add_method(thread, NULL, NULL, OscReceiver::staticHandler, (void *)this);
	}	
	
	void setThruAddress(lo_address thruAddr, const char *prefix) {
		thruAddress_ = thruAddr;
		thruPrefix_.assign(prefix);
		useThru_ = true;
	}
	
	// staticHandler() is called by liblo with new OSC messages.  Its only function is to pass control
	// to the object-specific handler method, which has access to all internal variables.
	
	int handler(const char *path, const char *types, lo_arg **argv, int argc, lo_message msg, void *data);
	static int staticHandler(const char *path, const char *types, lo_arg **argv, int argc, lo_message msg, void *userData) {
		return ((OscReceiver *)userData)->handler(path, types, argv, argc, msg, userData);
	}	
	
	~OscReceiver() {
		lo_server_thread_del_method(oscServerThread_, NULL, NULL);
	}	
	
private:
	lo_server_thread oscServerThread_;		// Thread that handles received OSC messages
	
	// OSC thru
	bool useThru_;							// Whether or not we retransmit any messages
	lo_address thruAddress_;				// Address to which we retransmit
	string thruPrefix_;						// Prefix that must be matched to be retransmitted
	
	// State variables
	string globalPrefix_;					// Prefix for all OSC paths	
};

class OscTransmitter
{
public:
	OscTransmitter() : enabled_(true), debugMessages_(false) {}
    
    // Enable or disable transmission
    void setEnabled(bool enable) { enabled_ = enable; }
    bool enabled() { return enabled_; }
	
	// Add and remove addresses to send to
	int addAddress(const char * host, const char * port, int proto = LO_UDP);
	void removeAddress(int index);
	void clearAddresses();
    vector<lo_address> addresses() { return addresses_; }
	
	void sendMessage(const char * path, const char * type, ...);
	void sendMessage(const char * path, const char * type, const lo_message& message);
	void sendByteArray(const char * path, const unsigned char * data, int length);
	
	void setDebugMessages(bool debug) { debugMessages_ = debug; }
	
	~OscTransmitter();
	
private:
	vector<lo_address> addresses_;
    bool enabled_;
	bool debugMessages_;
};

#endif // OSC_H