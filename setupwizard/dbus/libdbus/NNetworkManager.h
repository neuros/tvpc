#ifndef _NNETWORK_MANAGER_H__
#define _NNETWORK_MANAGER_H__
#include "NDevice.h"

class NNetworkTools;

class NNetworkManager : public QObject
{
	Q_OBJECT
public:
	NNetworkManager();
	~NNetworkManager();

	static NNetworkManager *getInstance(void);
	static void networkRefresh(void);

	NDeviceList getDevices(void);
	NDevice *getWirelessDevice(void);
	NDevice *getActiveDevice(void);
	NDevice *getDevice(const QString &obj_path);
	void setActiveDevice(NDevice *dev);

	void setupDevices(char **path, int num);
	void push(NNetworkTools *ctx);

private slots:
	void emitNetworkStrengthChange(NNetwork *);
	void emitNetworkInfoRefresh(NDevice *);
signals:
	void networkStrengthChange(NNetwork *);
	void networkInfoRefresh(NDevice *);
private:
	static NNetworkManager *_device_instance;
	NNetworkTools *_ctx;

	NDeviceList  _device_list;

};
#endif /* _NNETWORK_MANAGER_H__ */
