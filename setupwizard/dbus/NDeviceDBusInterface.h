#ifndef _NDEVICE_DBUS_INTERFACE_H__
#define _NDEVICE_DBUS_INTERFACE_H__
#include "NDBusConnection.h"
#include "NDevice.h"
#include <hal/libhal.h>

class NNetworkTools;
class NNetwork;

class NDeviceDBusInterface
{
public:
	static void setHalDeviceInfo (NDevice *dev);

	static bool updateDevice(NDevice *device, const QString &signal = "");

	static bool updateActivationStage(NDevice *dev, NMActStage stage);
	static void setActiveNetwork(NNetwork *net, NDevice  *dev);
	static bool getDeviceDriver(NDevice *dev);

	static void push(NNetworkTools *ctx);
private:
	static void getHalProperty   (const QString&, const QString&, QString &);

	static NNetworkTools *_ctx;
};
#endif
