#include "NDBusConnection.h"

NNetworkTools* NDBusConnection::_ctx = NULL;
DBusConnection*  NDBusConnection::_dbus_connection = NULL;

NDBusConnection::NDBusConnection(void)
{

}

NDBusConnection::~NDBusConnection()
{

}

bool NDBusConnection::open ()
{
	bool status;
	DBusError error;
	
	dbus_error_init (&error);

	_dbus_connection = NULL;
	_dbus_connection = dbus_bus_get (DBUS_BUS_SYSTEM, &error);
	if ((_dbus_connection == NULL) || (dbus_error_is_set (&error))) {
		qDebug() << "Connection to D-Bus system message bus failed:\n" << error.message;
		status = false;
		goto out;
	} else {
		dbus_connection_set_exit_on_disconnect (_dbus_connection, false);

		status = true;
		goto out;
	}

out:
	if (dbus_error_is_set (&error)) {
		dbus_error_free (&error);
	}

	return status;
}

void NDBusConnection::close (void)
{
	/* DBusConnection::open () calls dbus_bus_get (), we need to unref the connection */
	dbus_connection_unref (_dbus_connection);
}

void NDBusConnection::pop(void)
{
	this->_initialized = false;
	this->close();
}

bool NDBusConnection::registerObjectPath () const
{
	DBusError				 error;
	dbus_bool_t			 success = FALSE;
    DBusObjectPathVTable	 vtable = { NULL, NULL, NULL, NULL, NULL, NULL };

	dbus_error_init (&error);
	dbus_bus_request_name (_dbus_connection, NM_DBUS_SERVICE, 0, &error);
	if (dbus_error_is_set (&error)) {
		qDebug() << "Could not acquire its service.  dbus_bus_request_name() says:"  << error.message;
		return false;
	}

	success = dbus_connection_register_object_path (_dbus_connection, NM_DBUS_PATH, &vtable, NULL);
 	if (!success) {
 		printf("Could not register a handler for NetworkManager.  Not enough memory?\n");
		return false;
 	}

	return true;
}

bool NDBusConnection::addMatch (void)
{
	bool status;
	DBusError error;

	dbus_error_init (&error);

	/* Match for DBUS_INTERFACE_DBUS */
	dbus_bus_add_match (NDBusConnection::_dbus_connection, "type='signal',"
							      "interface='" DBUS_INTERFACE_DBUS "',"
							      "sender='" DBUS_SERVICE_DBUS "'",
							      &error);	
	if (dbus_error_is_set (&error)) {
		printf ("Error adding match, %s: %s\n", error.name, error.message);
		dbus_error_free (&error);
		status = false;
		goto out;
	}

	/* Match for NM_DBUS_INTERFACE */
	dbus_bus_add_match (NDBusConnection::_dbus_connection, "type='signal',"
							      "interface='" NM_DBUS_INTERFACE "',"
							      "path='" NM_DBUS_PATH "',"
							      "sender='" NM_DBUS_SERVICE "'",
							      &error);

	if (dbus_error_is_set (&error)) {
		printf ("Error adding match, %s: %s\n", error.name, error.message);
		dbus_error_free (&error);
		status = false;
		goto out;
	}

	status = true;

out:
	if (dbus_error_is_set (&error)) {
		dbus_error_free (&error);
	}

	return status;
}



bool NDBusConnection::push(NNetworkTools *ctx)
{
	NDBusConnection::_ctx = ctx;

	if (this->open () == false) {
		goto out;
	}

	if (this->registerObjectPath () == false) {
		printf ("Register object path failed. Bailing out.\n");
		goto out;
	}

	if (this->addMatch () == false) {
		printf ("Adding matches failed. Bailing out.\n");
		goto out;
	}

	_initialized = true;

out:
	return status ();

}
