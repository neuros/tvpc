#ifndef _NNETWORK_MANAGER_H__
#define _NNETWORK_MANAGER_H__
#include "NDevice.h"

class NNetworkTools;

class NNetworkManager
{
public:
	NNetworkManager();
	~NNetworkManager();

	static NNetworkManager *getInstance(void);
	static void networkRefresh(void);

	NDeviceList getDevices(void);
	NDevice *getActiveDevice(void);
	NDevice *getDevice(const QString &obj_path);
	void setActiveDevice(NDevice *dev);

	void setupDevices(char **path, int num);
	void push(NNetworkTools *ctx);
private:
	static NNetworkManager *_device_instance;
	NNetworkTools *_ctx;

	NDeviceList  _device_list;

};
#endif /* _NNETWORK_MANAGER_H__ */
