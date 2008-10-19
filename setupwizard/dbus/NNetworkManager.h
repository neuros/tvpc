#ifndef _NNETWORK_MANAGER_H__
#define _NNETWORK_MANAGER_H__
#include <QDebug>
#include "NDBusConnection.h"
#include "NNetworkState.h"

class NNetworkManager
{
public:
	NNetworkManager(void);
    NDBusConnection*     getDBus (void);
	NNetworkState *getState(void);
	//NetworkManagerInfo* getNetworkManagerInfo (void);

private:
	NDBusConnection*     _dbus;
	NNetworkState*              _state;

	//NNetworkManagerInfo *_nmi;
};

#endif
