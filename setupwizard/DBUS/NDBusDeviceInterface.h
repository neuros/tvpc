#ifndef _NDBusDeviceInterface_H__
#define _NDBusDeviceInterface_H__
#include "NDBusConnection.h"
#include "NDBusBaseInterface.h"

class NDBusDeviceInterface : public NDBusBaseInterface
{
public:
	NDBusDeviceInterface(const NDBusConnection &connection) :
		NDBusBaseInterface(connection){};
	const QString getDriver(const QString &device) const;
	const QString getName(const QString &device) const;
	const QString getHalUdi(const QString &device) const;
	const QString getHWAddress(const QString &device) const;
	const QString getIP4Address(const QString &device) const;

	int getMode(const QString &device) const;
	NMDeviceType getType(const QString &device) const;
	unsigned long getCapabilities(const QString &device) const;

	bool getLinkActive(const QString &device) const;
	bool setLinkActive(const QString &device) const;

	NMState state() const;

	const QStringList getNetworks(const QString &device) const;
	const QString getActiveNetwork(const QString &device) const;

	const NNetworkProperty getProperties(const QString &device) const;
};
#endif
