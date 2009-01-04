#include "NDBusTools.h"
#include "NDBusStateTools.h"

NDBusTools *NDBusTools::_dbus_tools = NULL;

NDBusTools::NDBusTools() :
	QObject()
{

}

NDBusTools::~NDBusTools()
{
	if (_dbus_tools)
		delete _dbus_tools;
}

NDBusTools *NDBusTools::getInstance()
{
	if (_dbus_tools == NULL)
		_dbus_tools = new NDBusTools();

	return _dbus_tools;
}

NDBusDevice *NDBusTools::getWiredDevice()
{
	for (int i=0; i<_device_list.count(); i++) {
		if (_device_list.at(i)->isWired())
			return _device_list.at(i);
	}

	return NULL;
}

NDBusDevice *NDBusTools::getWirelessDevice()
{
	for (int i=0; i<_device_list.count(); i++) {
		if (_device_list.at(i)->isWireless())
			return _device_list.at(i);
	}

	return NULL;
}

NDBusDevice *NDBusTools::getActiveDevice()
{
	for (int i=0; i<_device_list.count(); i++){
			if (_device_list.at(i)->isActive())
				return _device_list.at(i);
    }

	return NULL;
}

NDBusDevice *NDBusTools::getDevice(const QDBusObjectPath &path)
{
	for (int i=0; i< _device_list.count(); i++) {
		if (_device_list.at(i)->getObjectPath().path() == path.path()) {
			return _device_list.at(i);
		}
	}

	return NULL;
}

const NDBusDeviceList NDBusTools::getDevices()
{
	return _device_list;
}

bool NDBusTools::activeDevice(NDBusDevice *dev)
{
	if (!dev)
		return false;

	if (NDBusStateTools::getInstance()->isSystemBusConnected() == false)
		return false;

	QDBusInterface iface(NM_DBUS_SERVICE, NM_DBUS_PATH, NM_DBUS_INTERFACE,
						 QDBusConnection::systemBus());

	if (iface.isValid()) {
		iface.call("setActiveDevice", dev->getObjectPath().path());
		return true;
	}

	return false;
}

bool NDBusTools::update()
{
	if (NDBusStateTools::getInstance()->isSystemBusConnected() == false)
		return false;

	QDBusInterface iface(NM_DBUS_SERVICE, NM_DBUS_PATH, NM_DBUS_INTERFACE,
						 QDBusConnection::systemBus());

	if (iface.isValid()) {
		QDBusReply< QList< QDBusObjectPath > > reply = iface.call("getDevices");
		if (reply.isValid()) {

			_device_list.clear();

			NDBusDevice *dev;

			QList<QDBusObjectPath> list = reply.value();
			for (int i=0; i<list.count(); i++) {
				dev = new NDBusDevice(list.at(i));
				dev->update();
				_device_list << dev;
			}

			return true;

 		} else {
			fprintf(stderr, "Call failed: %s\n", qPrintable(reply.error().message()));
		}
	}

	fprintf(stderr, "%s\n",
			qPrintable(QDBusConnection::systemBus().lastError().message()));

	return false;
}


