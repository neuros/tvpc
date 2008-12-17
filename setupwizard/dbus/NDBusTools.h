#ifndef _NDBUS_TOOLS_H__
#define _NDBUS_TOOLS_H__
#include <QtDBus/QtDBus>
#include <NetworkManager.h>
#include <QObject>
#include <QDBusObjectPath>
#include "NDBusDevice.h"

class NDBusTools : QObject
{
	Q_OBJECT
public:
	NDBusTools();
	~NDBusTools();

	static NDBusTools *getInstance();

	const NDBusDeviceList getDevices();
	NDBusDevice *getWirelessDevice(void);
	NDBusDevice *getActiveDevice(void);
	NDBusDevice *getDevice(const QDBusObjectPath&);

	bool activeDevice(NDBusDevice *dev);
	bool update();
private:
	static NDBusTools *_dbus_tools;

	NDBusDeviceList _device_list;
};

#endif // _NDBUS_TOOLS_H__
