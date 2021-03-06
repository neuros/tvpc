#ifndef _NSTATE_DBUS_INTERFACE_H__
#define _NSTATE_DBUS_INTERFACE_H__
#include "NDBusConnection.h"
class NNetworkTools;

class NStateDBusInterface
{
public:
	static void enableWireless(bool enable);
	static void switchMode (const char *method);
	static bool isNetworkManagerRunning  (void);

	static void setState(NMState);
	static void getState(void);

	static void setWirelessState(bool);
	static void getWirelessState(void);

	static void push                    (NNetworkTools*);

private:
	static NNetworkTools* _ctx;
};

#endif /* _NSTATE_DBUS_INTERFACE_H__ */
