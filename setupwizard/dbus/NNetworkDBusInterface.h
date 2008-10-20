#ifndef _NNETWORK_DBUS_INTERFACE_H__
#define _NNETWORK_DBUS_INTERFACE_H__
#include "NNetwork.h"
#include "NDBusConnection.h"

class NNetworkTools;

class NNetworkDBusInterface
{
public:
	static void getProperties(const QString &path, NNetwork *network);

	static void push(NNetworkTools *ctx);
private:
	static NNetworkTools *_ctx;
};

#endif
