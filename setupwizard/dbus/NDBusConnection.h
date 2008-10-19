#ifndef _NDBUS_CONNECTION_H__
#define _NDBUS_CONNECTION_H__
#include <QObject>
#include <QDebug>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <NetworkManager.h>

class NNetworkManager;

class NDBusConnection
{
public:
	NDBusConnection(void);
	~NDBusConnection (void);

	bool registerObjectPath(void) const;
	bool addFilter(void);
	bool addMatch(void);
    bool open(void);
	void close(void);

	bool  push(NNetworkManager*);
	void pop(void);
    bool status(void) const {
		return _initialized;
	}

	DBusConnection *getConnection(void){
		return _dbus_connection;
	}
private:
	static NNetworkManager *_ctx;
	static DBusConnection *_dbus_connection;
	bool _initialized;

	//static DBusHandlerResult filterFunction                   (DBusConnection*, DBusMessage*, void*);
};

#endif