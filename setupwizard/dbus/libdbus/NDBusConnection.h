#ifndef _NDBUS_CONNECTION_H__
#define _NDBUS_CONNECTION_H__
#include <QDebug>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <NetworkManager.h>

class NNetworkTools;

class NDBusConnection
{
public:
	NDBusConnection(void);
	~NDBusConnection (void);

	bool registerObjectPath(void) const;
	bool addMatch(void);
	bool addFilter(void);
    bool open(void);
	void close(void);

	bool  push(NNetworkTools*);
	void pop(void);
    bool status(void) const {
		return _initialized;
	}

	static DBusHandlerResult nmd_dbus_filter (DBusConnection *connection, DBusMessage *message, void *user_data);
	DBusConnection *getConnection(void){
		return _dbus_connection;
	}
	static int triggerReconnect(void *user_data);
	static bool handleUpdateDeviceSignal( DBusMessage * msg );

private:
	bool dbusInit(void);
	static NNetworkTools *_ctx;
	static DBusConnection *_dbus_connection;
	bool _initialized;
};

#endif
