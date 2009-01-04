#ifndef _NNETWORK_DBUS_INTERFACE_H__
#define _NNETWORK_DBUS_INTERFACE_H__
#include "NNetwork.h"
#include "NDBusConnection.h"

class NNetworkTools;

class NNetworkDBusInterface
{
public:
	static void updateNetwork(NNetwork *network);

	static bool updateNetworkStrength(NNetwork *net, int strength);
	static void push(NNetworkTools *ctx);
private:
	static NNetworkTools *_ctx;
};

#endif
