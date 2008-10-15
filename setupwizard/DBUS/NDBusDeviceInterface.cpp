#include "NDBusDeviceInterface.h"
#include <QDebug>
#define INVALID  ~0

NDBusDeviceInterface::NDBusDeviceInterface(const NDBusConnection &connection)
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

bool NDBusDeviceInterface::isValid() const
{
	return err == 0 ? true : false;
}

const QString NDBusDeviceInterface::StringCall(const QString &path, const QString &method) const
{
	DBusMessage *	message;
	DBusMessage *	reply;
	char *		val = NULL;
	DBusError		error;

	if (path.isNull() || !connection.isValid() || method.isNull())
		return QString();

	if (!(message = dbus_message_new_method_call (NM_DBUS_SERVICE, path.toAscii().data(), 
												  NM_DBUS_INTERFACE_DEVICES, method.toAscii().data())))
	{
		printf ("%s(): Couldn't allocate the dbus message", __func__);
		return QString();
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (connection.connection, message, -1, &error);
	dbus_message_unref (message);
	if (dbus_error_is_set (&error))
		dbus_error_free (&error);
	else if (reply)
	{
		if (dbus_message_get_args (reply, NULL, DBUS_TYPE_STRING, &val, DBUS_TYPE_INVALID))
			val = g_strdup (val);
		dbus_message_unref (reply);
	}

	return QString(val);
	
}

const QStringList NDBusDeviceInterface::StringListCall(const QString &device, const QString &method) const
{
	QStringList list;

	DBusMessage *	message = NULL;
	DBusMessage *	reply = NULL;
	DBusError		error;
	char **		paths = NULL;
	int			num = -1;
	int			i;

	if (device.isNull() || method.isNull() || !connection.isValid())
		return list;

	if (!(message = dbus_message_new_method_call (
		NM_DBUS_SERVICE, device.toAscii().data(), NM_DBUS_INTERFACE, method.toAscii().data())))
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

dbus_uint32_t NDBusDeviceInterface::UintCall(const QString &device, const QString &method) const
{
	DBusMessage *	message;
	DBusMessage *	reply;
	dbus_uint32_t		val = INVALID;
	DBusError		error;

	if (device.isNull() || !connection.isValid() || method.isNull())
		return INVALID;

	if (!(message = dbus_message_new_method_call (NM_DBUS_SERVICE, device.toAscii().data(), 
												  NM_DBUS_INTERFACE_DEVICES, method.toAscii().data())))
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

dbus_int32_t NDBusDeviceInterface::IntCall(const QString &device, const QString &method) const
{
	DBusMessage *	message;
	DBusMessage *	reply;
	dbus_int32_t		val =INVALID;
	DBusError		error;

	if (device.isNull() || !connection.isValid() || method.isNull())
		return INVALID;

	if (!(message = dbus_message_new_method_call (NM_DBUS_SERVICE, device.toAscii().data(), 
												  NM_DBUS_INTERFACE_DEVICES, method.toAscii().data())))
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

dbus_bool_t NDBusDeviceInterface::boolCall(const QString &device, const QString &method) const
{
	DBusMessage *	message;
	DBusMessage *	reply;
	dbus_bool_t		val = FALSE;
	DBusError		error;

	if (device.isNull() || !connection.isValid() || method.isNull())
		return INVALID;

	if (!(message = dbus_message_new_method_call (NM_DBUS_SERVICE, device.toAscii().data(), 
												  NM_DBUS_INTERFACE_DEVICES, method.toAscii().data())))
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


const QString NDBusDeviceInterface::getDeviceName(const QString &device) const
{
	return StringCall(device, "getName");
}

const QString NDBusDeviceInterface::getHalUdi(const QString &device) const
{
	return StringCall(device, "getHalUdi");
}

const QString NDBusDeviceInterface::getDriverName(const QString &device) const
{
	return StringCall(device, "getDriver");
}

const QString NDBusDeviceInterface::getHWAddress(const QString &device) const
{
    return StringCall(device, "getHWAddress");
}

const QString NDBusDeviceInterface::getIP4Address(const QString &device) const
{
	dbus_uint32_t	uint32_ipaddr = UintCall(device, "getIP4Address");
	return QString::number(uint32_ipaddr & 0xFF) + "." + QString::number((uint32_ipaddr >> 8) & 0xFF)  + "."
		+ QString::number((uint32_ipaddr >>16) & 0xFF) + "." + QString::number((uint32_ipaddr>>24) &0xFF);
}


const QStringList NDBusDeviceInterface::getNetworks(const QString &device) const
{
	return StringListCall(device, "getNetworks");
}

const QStringList NDBusDeviceInterface::getDevices() const
{
	return StringListCall(NM_DBUS_PATH, "getDevices");
}

int NDBusDeviceInterface::getMode(const QString &device) const
{
	return IntCall(device, "getMode");
}

bool NDBusDeviceInterface::getLinkActive(const QString &device) const
{
	return boolCall(device, "getLinkActive") == TRUE ? true : false;
}

bool NDBusDeviceInterface::setLinkActive(const QString &device) const
{
	return boolCall(device, "setLinkActive") == TRUE ? true : false;
}

unsigned long NDBusDeviceInterface::getCapabilities(const QString &device) const
{
	return UintCall(device, "getCapabilities");
}

NMDeviceType NDBusDeviceInterface::getDeviceType(const QString &device) const
{
	dbus_int32_t type = IntCall(device, "getType");
	return( type == INVALID) ? DEVICE_TYPE_UNKNOWN : ((NMDeviceType)type);
}

NMState NDBusDeviceInterface::getNetworkManagerState() const
{
	dbus_uint32_t	uint32_state = UintCall(NM_DBUS_PATH, "state");
	return (uint32_state == (dbus_uint32_t)INVALID) ? NM_STATE_UNKNOWN : ((NMState)uint32_state);
}


const QString NDBusDeviceInterface::getActiveNetwork(const QString &device) const
{
	DBusMessage *	message;
	DBusMessage *	reply;
	char *		val = NULL;
	DBusError		error;

	if (device.isNull() || !connection.isValid())
		return QString();

	if (!(message = dbus_message_new_method_call (NM_DBUS_SERVICE, device.toAscii().data(), 
												  NM_DBUS_INTERFACE_DEVICES, "getActiveNetwork")))
	{
		printf ("%s(): Couldn't allocate the dbus message", __func__);
		return QString();
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (connection.connection, message, -1, &error);
	dbus_message_unref (message);
	if (dbus_error_is_set (&error))
		dbus_error_free (&error);
	else if (reply)
	{
		if (dbus_message_get_args (reply, NULL, DBUS_TYPE_OBJECT_PATH, &val, DBUS_TYPE_INVALID))
			val = g_strdup (val);
		dbus_message_unref (reply);
	}

	return QString(val);
	
}


const NWirelessDetailInfo NDBusDeviceInterface::getWirelessNetworkInfo(const QString &path) const
{
	NWirelessDetailInfo info;
	DBusMessage *		message = NULL;
	DBusMessage *		reply = NULL;

	if(path.isNull() || !connection.isValid())
		return info;

	if (!(message = dbus_message_new_method_call (NM_DBUS_SERVICE, path.toAscii().data(),
												  NM_DBUS_INTERFACE_DEVICES, "getProperties")))
	{
		fprintf (stderr, "detail_network(): couldn't create new dbus message.\n");
		return info;
	}

	reply = dbus_connection_send_with_reply_and_block (connection.connection, message, -1, NULL);
	dbus_message_unref (message);
	if (!reply)
	{
		fprintf (stderr, "detail_network(): didn't get a reply from NetworkManager for device %s.\n", path.toAscii().data());
		return info;
	}

	if (dbus_message_get_args (reply, NULL,	DBUS_TYPE_OBJECT_PATH, &info.op,
									DBUS_TYPE_STRING,  &info.essid,
									DBUS_TYPE_STRING,  &info.hw_addr,
									DBUS_TYPE_INT32,   &info.strength,
									DBUS_TYPE_DOUBLE,  &info.freq,
									DBUS_TYPE_INT32,   &info.rate,
									DBUS_TYPE_INT32,   &info.mode,
									DBUS_TYPE_INT32,   &info.capabilities,
									DBUS_TYPE_BOOLEAN, &info.broadcast,
									DBUS_TYPE_INVALID))
	{
	}
	else
		fprintf (stderr, "detail_network(): unexpected reply from NetworkManager for device %s.\n", path.toAscii().data());

	dbus_message_unref (reply);

	return info;
}

const NNetworkProperty NDBusDeviceInterface::getDeviceDetail(const QString &device) const
{
	DBusMessage *		message = NULL;
	DBusMessage *		reply = NULL;

	NNetworkProperty property;
	if (device.isNull())
		return NNetworkProperty();

	if (!(message = dbus_message_new_method_call (NM_DBUS_SERVICE, device.toAscii().data(), 
												  NM_DBUS_INTERFACE_DEVICES, "getProperties")))
	{
		fprintf (stderr, "detail_device(): couldn't create new dbus message.\n");
		return NNetworkProperty();
	}

	reply = dbus_connection_send_with_reply_and_block (connection.connection, message, -1, NULL);
	dbus_message_unref (message);
	if (!reply)
	{
		fprintf (stderr, "detail_device(): didn't get a reply from NetworkManager for device %s.\n", device.toAscii().data());
		return NNetworkProperty();
	}

	if (dbus_message_get_args (reply, NULL,	DBUS_TYPE_OBJECT_PATH, &property.op,
									DBUS_TYPE_STRING, &property.iface,
									DBUS_TYPE_UINT32, &property.type,
									DBUS_TYPE_STRING, &property.udi,
									DBUS_TYPE_BOOLEAN,&property.active,
									DBUS_TYPE_UINT32, &property.act_stage,
									DBUS_TYPE_STRING, &property.ip4_address,
									DBUS_TYPE_STRING, &property.subnetmask,
									DBUS_TYPE_STRING, &property.broadcast,
									DBUS_TYPE_STRING, &property.hw_addr,
									DBUS_TYPE_STRING, &property.route,
									DBUS_TYPE_STRING, &property.primary_dns,
									DBUS_TYPE_STRING, &property.secondary_dns,
									DBUS_TYPE_INT32,  &property.mode,
									DBUS_TYPE_INT32,  &property.strength,
									DBUS_TYPE_BOOLEAN,&property.link_active,
									DBUS_TYPE_INT32,  &property.speed,
									DBUS_TYPE_UINT32, &property.caps,
									DBUS_TYPE_UINT32, &property.type_caps,
									DBUS_TYPE_STRING, &property.active_network_path,
									DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &property.networks, &property.num_networks,
									DBUS_TYPE_INVALID))
	{
		dbus_message_unref (reply);
		return property;
 	}
 	else
 		fprintf (stderr, "detail_device(): unexpected reply from NetworkManager for device %s.\n", device.toAscii().data());

	dbus_message_unref (reply);
	return NNetworkProperty();
}
