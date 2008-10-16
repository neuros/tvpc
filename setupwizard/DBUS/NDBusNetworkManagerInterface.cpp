#include "NDBusNetworkManagerInterface.h"

const QStringList NDBusNetworkManagerInterface::getDevices() const
{
	return StringListCall(NM_DBUS_SERVICE, NM_DBUS_PATH, NM_DBUS_INTERFACE, "getDevices");
}

