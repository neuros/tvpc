#ifndef _NDBUSCONNECTION_H__
#define _NDBUSCONNECTION_H__
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <stdio.h>
#include "NDBusCommon.h"

class NDBusConnection
{
	friend class NDBusBaseInterface;
public:
	static NDBusConnection systemBus();
	static NDBusConnection sessionBus();
	bool isConnected() const;
	bool isValid() const {
		return connection != NULL;
	}
	DBusConnection *dbusConnection() const {
		return connection;
	}
protected:
	DBusConnection	*connection;
	virtual DBusBusType getBusType() const {
		return DBUS_BUS_SYSTEM;
	}

	DBusConnection *getConnection();
};

class NSystemBus : public NDBusConnection
{
public:
	NSystemBus();
private:
	DBusBusType getBusType() const {
		return DBUS_BUS_SYSTEM;
	}
};

class NSessionBus : public NDBusConnection
{
public:
	NSessionBus();
private:
	DBusBusType getBusType() const {
		return DBUS_BUS_SESSION;
	}
};
 
#endif /* _NDBUSCONNECTION_H__ */
