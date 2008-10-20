#ifndef _NNETWORK_MANAGER_DBUS_INTERFACE_H__
#define _NNETWORK_MANAGER_DBUS_INTERFACE_H__
#include "NDBusConnection.h"
#include "NDevice.h"

class NNetworkTools;

class NNetworkManagerDBusInterface
{
public:
	static void push(NNetworkTools *);
	static void getDevices();
	static void activateDevice (NDevice* dev);

private:
	static void setupDevices(char **path, int num);

	static NNetworkTools *_ctx;
};

#endif /* _NNETWORK_MANAGER_DBUS_INTERFACE_H__ */
