#include "NDBusConnection.h"

DBusConnection *NDBusConnection::getConnection()
{
	DBusConnection *con = NULL;

	DBusError				 error;

	dbus_error_init (&error);
	con = dbus_bus_get (getBusType(), &error);
	if (con == NULL)
		fprintf (stderr, "Error connecting to system bus: %s\n", error.message);

	dbus_error_free(&error);

	return con;
}

NDBusConnection NDBusConnection::sessionBus()
{
	return *new NSessionBus;
}

NDBusConnection NDBusConnection::systemBus()
{
	return *new NSystemBus;
}

bool NDBusConnection::isConnected() const
{
	return connection != NULL;
}

NSystemBus::NSystemBus()
{
	connection = getConnection();
}

NSessionBus::NSessionBus()
{
	connection = getConnection();
}



