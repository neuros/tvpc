#ifndef _NDEVICE_DBUS_INTERFACE_H__
#define _NDEVICE_DBUS_INTERFACE_H__
#include "NDBusConnection.h"
#include "NDevice.h"
#include <hal/libhal.h>

class NNetworkTools;

class NDeviceDBusInterface
{
public:
	static void setHalDeviceInfo (NDevice *dev);

	static void getProperties(const QString &path, NDevice *device);

	static void push(NNetworkTools *ctx);
private:
	static void getHalProperty   (const QString&, const QString&, QString &);

	static NNetworkTools *_ctx;
};
#endif
