#ifndef _NNETWORK_TOOLS_H__
#define _NNETWORK_TOOLS_H__
#include "NDBusConnection.h"
#include "NNetworkState.h"
#include "NNetworkManager.h"

class NNetworkTools
{
public:
	NNetworkTools();
	~NNetworkTools();

    NDBusConnection*     getDBus (void) const;
	NNetworkState *getState(void) const;
	NNetworkManager *getManager(void) const;

private:
	NDBusConnection*     _dbus;
	NNetworkState *_state;
	NNetworkManager *_manager;
};

#endif /* _NNETWORK_TOOLS_H__ */
