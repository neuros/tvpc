#ifndef _NDBusDeviceInterface_H__
#define _NDBusDeviceInterface_H__
#include <QString>
#include <QStringList>
#include <QVariant>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <iwlib.h>
#include "NDBusConnection.h"
#include "NDBusCommon.h"

class NDBusDeviceInterface
{
public:
	NDBusDeviceInterface(const NDBusConnection &connection);
	bool isValid() const;
	const QString getDriverName(const QString &device) const;
	const QString getDeviceName(const QString &device) const;
	const QString getHalUdi(const QString &device) const;
	const QString getHWAddress(const QString &device) const;
	const QString getIP4Address(const QString &device) const;

	int getMode(const QString &device) const;
	NMDeviceType getDeviceType(const QString &device) const;
	unsigned long getCapabilities(const QString &device) const;

	bool getLinkActive(const QString &device) const;
	bool setLinkActive(const QString &device) const;

	NMState getNetworkManagerState() const;

	const QStringList getNetworks(const QString &device) const;
	const QStringList getDevices() const;
	const QString getActiveNetwork(const QString &device) const;

	const NNetworkProperty getDeviceDetail(const QString &device) const;
	const NWirelessDetailInfo getWirelessNetworkInfo(const QString &path) const;
private:
	const QStringList StringListCall(const QString &device, const QString &method) const;
	const QString StringCall(const QString &device, const QString &method) const;
	dbus_int32_t IntCall(const QString &device, const QString &method) const;
	dbus_uint32_t UintCall(const QString &device, const QString &method) const;
	dbus_bool_t boolCall(const QString &device, const QString &method) const;

	int err;
	NDBusConnection connection;
};
#endif
