#include "NDBusBaseInterface.h"
#include <QDebug>

NDBusBaseInterface::NDBusBaseInterface(const NDBusConnection &connection)
{
	DBusError				 error;
	dbus_bool_t			 success = FALSE;
    DBusObjectPathVTable	 vtable = { NULL, NULL, NULL, NULL, NULL, NULL };
	
	dbus_error_init (&error);
	dbus_bus_request_name (connection.connection, NM_DBUS_SERVICE, 0, &error);
	if (dbus_error_is_set (&error)) {
		qDebug() << "Could not acquire its service.  dbus_bus_request_name() says:"  << error.message;
		err = -1;
		return;
	}

	success = dbus_connection_register_object_path (connection.connection, NM_DBUS_PATH, &vtable, NULL);
 	if (!success) {
 		printf("Could not register a handler for NetworkManager.  Not enough memory?\n");
 		err = -2;
		return;
 	}

	this->connection = connection;
	err = 0;
	return;
}

bool NDBusBaseInterface::isValid() const
{
	return err == 0 ? true : false;
}

const QStringList NDBusBaseInterface::StringListCall(const QString &server,
													 const QString &device, const QString &interface, const QString &method) const
{
	QStringList list;

	DBusMessage *	message = NULL;
	DBusMessage *	reply = NULL;
	DBusError		error;
	char **		paths = NULL;
	int			num = -1;
	int			i;

	if (device.isNull() || method.isNull() || !connection.isValid() || server.isNull() ||
		interface.isNull())
		return list;

	if (!(message = dbus_message_new_method_call (
		server.toAscii().data(), device.toAscii().data(),
		interface.toAscii().data(), method.toAscii().data())))
	{
		fprintf (stderr, "print_devices(): couldn't create new dbus message.\n");
		return list;
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (connection.connection, message, -1, &error);
	dbus_message_unref (message);
	if (!reply)
	{
		fprintf (stderr, "print_devices(): didn't get a reply from NetworkManager.\n");
		if (dbus_error_is_set (&error))
		{
			if (dbus_error_has_name (&error, NM_DBUS_NO_DEVICES_ERROR))
				fprintf (stderr, "There are no available network devices.\n");
		}
		else
			fprintf (stderr, "print_devices(): NetworkManager returned an error: '%s'\n", error.message);
		return list;
	}

	if (!dbus_message_get_args (reply, NULL, DBUS_TYPE_ARRAY, DBUS_TYPE_OBJECT_PATH, &paths, &num, DBUS_TYPE_INVALID))
	{
		fprintf (stderr, "print_devices(): unexpected reply from NetworkManager.\n");
		dbus_message_unref (reply);
		return list;
	}

	for (i=0; i<num; i++)
		list << paths[i];

	dbus_free_string_array (paths);
	dbus_message_unref (reply);

	return list;
	
}

double NDBusBaseInterface::DoubleCall(const QString &server, const QString &device,
	  						const QString &interface, const QString &method) const
{
	DBusMessage *	message;
	DBusMessage *	reply;
	double		val = 0;
	DBusError		error;

	if (device.isNull() || !connection.isValid() || method.isNull() || server.isNull() || interface.isNull())
		return 0;

	if (!(message = dbus_message_new_method_call (server.toAscii().data(), device.toAscii().data(), 
												  interface.toAscii().data(), method.toAscii().data())))
	{
		printf ("%s(): Couldn't allocate the dbus message", __func__);
		return 0;
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (connection.connection, message, -1, &error);
	dbus_message_unref (message);
	if (dbus_error_is_set (&error))
		dbus_error_free (&error);
	else if (reply)
	{
		if (dbus_message_get_args (reply, NULL, DBUS_TYPE_DOUBLE, &val, DBUS_TYPE_INVALID))
		dbus_message_unref (reply);
	}

	return val;

}


dbus_uint32_t NDBusBaseInterface::UintCall(const QString &server,
										   const QString &device, const QString &interface,
										   const QString &method) const
{
	DBusMessage *	message;
	DBusMessage *	reply;
	dbus_uint32_t		val = INVALID;
	DBusError		error;

	if (device.isNull() || !connection.isValid() || method.isNull() || server.isNull() ||
		interface.isNull())
		return INVALID;

	if (!(message = dbus_message_new_method_call (server.toAscii().data(), device.toAscii().data(), 
												  interface.toAscii().data(), method.toAscii().data())))
	{
		printf ("%s(): Couldn't allocate the dbus message", __func__);
		return INVALID;
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (connection.connection, message, -1, &error);
	dbus_message_unref (message);
	if (dbus_error_is_set (&error))
		dbus_error_free (&error);
	else if (reply)
	{
		if (dbus_message_get_args (reply, NULL, DBUS_TYPE_UINT32, &val, DBUS_TYPE_INVALID))
		dbus_message_unref (reply);
	}

	return val;
}

dbus_int32_t NDBusBaseInterface::IntCall(const QString &server,
										 const QString &device, const QString &interface,
										 const QString &method) const
{
	DBusMessage *	message;
	DBusMessage *	reply;
	dbus_int32_t		val =INVALID;
	DBusError		error;

	if (device.isNull() || !connection.isValid() || method.isNull() || server.isNull() || interface.isNull())
		return INVALID;

	if (!(message = dbus_message_new_method_call (server.toAscii().data(), device.toAscii().data(), 
												  interface.toAscii().data(), method.toAscii().data())))
	{
		printf ("%s(): Couldn't allocate the dbus message", __func__);
		return INVALID;
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (connection.connection, message, -1, &error);
	dbus_message_unref (message);
	if (dbus_error_is_set (&error))
		dbus_error_free (&error);
	else if (reply)
	{
		if (dbus_message_get_args (reply, NULL, DBUS_TYPE_INT32, &val, DBUS_TYPE_INVALID))
		dbus_message_unref (reply);
	}

	return val;
	
}

dbus_bool_t NDBusBaseInterface::BoolCall(const QString &server,
										 const QString &device, const QString &interface,
										 const QString &method) const
{
	DBusMessage *	message;
	DBusMessage *	reply;
	dbus_bool_t		val = FALSE;
	DBusError		error;

	if (device.isNull() || !connection.isValid() || method.isNull() || server.isNull() || interface.isNull())
		return INVALID;

	if (!(message = dbus_message_new_method_call (server.toAscii().data(), device.toAscii().data(), 
												  interface.toAscii().data(), method.toAscii().data())))
	{
		printf ("%s(): Couldn't allocate the dbus message", __func__);
		return INVALID;
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (connection.connection, message, -1, &error);
	dbus_message_unref (message);
	if (dbus_error_is_set (&error))
		dbus_error_free (&error);
	else if (reply)
	{
		if (dbus_message_get_args (reply, NULL, DBUS_TYPE_BOOLEAN, &val, DBUS_TYPE_INVALID))
		dbus_message_unref (reply);
	}

	return val;
	
}

const QString NDBusBaseInterface::StringCall(const QString &server,
											 const QString &device, const QString &interface,
											 const QString &method) const
{
	DBusMessage *	message;
	DBusMessage *	reply;
	char *		val = NULL;
	DBusError		error;

	if (device.isNull() || !connection.isValid() || method.isNull() || server.isNull() || interface.isNull())
		return QString();

	if (!(message = dbus_message_new_method_call (server.toAscii().data(), device.toAscii().data(), 
												  interface.toAscii().data(), method.toAscii().data())))
	{
		printf ("%s(): Couldn't allocate the dbus message", __func__);
		return QString();
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (connection.connection, message, -1, &error);
	dbus_message_unref (message);
	if (dbus_error_is_set (&error)){
		printf("error happens\n");
			dbus_error_free (&error);
	}
	else if (reply)
	{
		if (dbus_message_get_args (reply, NULL, DBUS_TYPE_STRING, &val, DBUS_TYPE_INVALID))
			val = g_strdup (val);
		dbus_message_unref (reply);
	}

	return QString(val);
	
}

