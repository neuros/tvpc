#ifndef _NDBUS_NETWORKMANAGER_INTERFACE_H__
#define _NDBUS_NETWORKMANAGER_INTERFACE_H__
#include "NDBusBaseInterface.h"
#include "NDBusConnection.h"
class NDBusNetworkManagerInterface : public NDBusBaseInterface
{
public:
	NDBusNetworkManagerInterface(const NDBusConnection &con) :
		NDBusBaseInterface(con) { };
	const QStringList getDevices() const;
};

#endif
