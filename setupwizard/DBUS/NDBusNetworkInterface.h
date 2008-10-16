#ifndef _DBUS_NETWORK_INTERFACE_H__
#define _DBUS_NETWORK_INTERFACE_H__
#include "NDBusBaseInterface.h"
#include "NDBusConnection.h"

class NDBusNetworkInterface : public NDBusBaseInterface
{
public:
	NDBusNetworkInterface(const NDBusConnection &con) :
		NDBusBaseInterface(con) { };
	const NWirelessDetailInfo getProperties(const QString &network) const;

	const QString getName(const QString &network) const;
	const QString getAddress(const QString &network) const;

	int getStrength(const QString &network) const;
	int getRate(const QString &network) const;
	int getMode(const QString &network) const;
	double getFrequency(const QString &network) const;
	bool getEncrypted(const QString &network) const;
};

#endif /* _DBUS_NETWORK_INTERFACE_H__ */

