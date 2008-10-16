#include "NDBusDeviceInterface.h"
#include <QDebug>

const QString NDBusDeviceInterface::getName(const QString &device) const
{
	return StringCall(NM_DBUS_SERVICE, device, NM_DBUS_INTERFACE_DEVICES, "getName");
}

const QString NDBusDeviceInterface::getHalUdi(const QString &device) const
{
	return StringCall(NM_DBUS_SERVICE, device, NM_DBUS_INTERFACE_DEVICES, "getHalUdi");
}

const QString NDBusDeviceInterface::getDriver(const QString &device) const
{
	return StringCall(NM_DBUS_SERVICE, device, NM_DBUS_INTERFACE_DEVICES, "getDriver");
}

const QString NDBusDeviceInterface::getHWAddress(const QString &device) const
{
    return StringCall(NM_DBUS_SERVICE, device, NM_DBUS_INTERFACE_DEVICES, "getHWAddress");
}

const QString NDBusDeviceInterface::getIP4Address(const QString &device) const
{
	dbus_uint32_t	uint32_ipaddr = UintCall(NM_DBUS_SERVICE,
											  device, NM_DBUS_INTERFACE_DEVICES, "getIP4Address");
	return QString::number(uint32_ipaddr & 0xFF) + "." + QString::number((uint32_ipaddr >> 8) & 0xFF)  + "."
		+ QString::number((uint32_ipaddr >>16) & 0xFF) + "." + QString::number((uint32_ipaddr>>24) &0xFF);
}


const QStringList NDBusDeviceInterface::getNetworks(const QString &device) const
{
	return StringListCall(NM_DBUS_SERVICE, device, NM_DBUS_INTERFACE, "getNetworks");
}

int NDBusDeviceInterface::getMode(const QString &device) const
{
	return IntCall(NM_DBUS_SERVICE, device, NM_DBUS_INTERFACE_DEVICES, "getMode");
}

bool NDBusDeviceInterface::getLinkActive(const QString &device) const
{
	return BoolCall(NM_DBUS_SERVICE, device, NM_DBUS_INTERFACE_DEVICES, 
					"getLinkActive") == TRUE ? true : false;
}

bool NDBusDeviceInterface::setLinkActive(const QString &device) const
{
	return BoolCall(NM_DBUS_SERVICE, device, NM_DBUS_INTERFACE_DEVICES,
					"setLinkActive") == TRUE ? true : false;
}

unsigned long NDBusDeviceInterface::getCapabilities(const QString &device) const
{
	return UintCall(NM_DBUS_SERVICE, device, NM_DBUS_INTERFACE_DEVICES,
					"getCapabilities");
}

NMDeviceType NDBusDeviceInterface::getType(const QString &device) const
{
	dbus_int32_t type = IntCall(NM_DBUS_SERVICE, device, NM_DBUS_INTERFACE_DEVICES,
								"getType");
	return( type == INVALID) ? DEVICE_TYPE_UNKNOWN : ((NMDeviceType)type);
}

NMState NDBusDeviceInterface::state() const
{
	dbus_uint32_t	uint32_state = UintCall(NM_DBUS_SERVICE, NM_DBUS_PATH,
											NM_DBUS_INTERFACE_DEVICES, "state");
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
	reply = dbus_connection_send_with_reply_and_block (connection.dbusConnection(), message, -1, &error);
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

const NNetworkProperty NDBusDeviceInterface::getProperties(const QString &device) const
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

	reply = dbus_connection_send_with_reply_and_block (connection.dbusConnection(), message, -1, NULL);
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
