#include "NDBusNetworkInterface.h"

const NWirelessDetailInfo NDBusNetworkInterface::getProperties(const QString &network) const
{
	NWirelessDetailInfo info;
	DBusMessage *		message = NULL;
	DBusMessage *		reply = NULL;

	if(network.isNull() || !connection.isValid())
		return info;

	if (!(message = dbus_message_new_method_call (NM_DBUS_SERVICE, network.toAscii().data(),
												  NM_DBUS_INTERFACE_DEVICES, "getProperties")))
	{
		fprintf (stderr, "detail_network(): couldn't create new dbus message.\n");
		return info;
	}

	reply = dbus_connection_send_with_reply_and_block (connection.dbusConnection(), message, -1, NULL);
	dbus_message_unref (message);
	if (!reply)
	{
		fprintf (stderr, "detail_network(): didn't get a reply from NetworkManager for device %s.\n", network.toAscii().data());
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
		fprintf (stderr, "detail_network(): unexpected reply from NetworkManager for device %s.\n", network.toAscii().data());

	dbus_message_unref (reply);

	return info;
}


const QString NDBusNetworkInterface::getName(const QString &network) const
{
	return StringCall(NM_DBUS_SERVICE, network, NM_DBUS_INTERFACE_DEVICES,
					  "getName");
}

const QString NDBusNetworkInterface::getAddress(const QString &network) const
{
	return StringCall(NM_DBUS_SERVICE, network, NM_DBUS_INTERFACE_DEVICES,
					  "getAddress");
}

int NDBusNetworkInterface::getStrength(const QString &network) const
{
	return IntCall(NM_DBUS_SERVICE, network, NM_DBUS_INTERFACE_DEVICES,
				   "getStrength");
}

double NDBusNetworkInterface::getFrequency(const QString &network) const
{
	return DoubleCall(NM_DBUS_SERVICE, network, NM_DBUS_INTERFACE_DEVICES,
					  "getFrequency");
}

int NDBusNetworkInterface::getRate(const QString &network) const
{
	return IntCall(NM_DBUS_SERVICE, network, NM_DBUS_INTERFACE_DEVICES,
				   "getRate");
}

bool NDBusNetworkInterface::getEncrypted(const QString &network) const
{
	return BoolCall(NM_DBUS_SERVICE, network, NM_DBUS_INTERFACE_DEVICES,
				   "getEncrypted");
}

int NDBusNetworkInterface::getMode(const QString &network) const
{
	return IntCall(NM_DBUS_SERVICE, network, NM_DBUS_INTERFACE_DEVICES,
				   "getMode");
}






