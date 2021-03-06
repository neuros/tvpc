#include "NNetworkManager.h"
#include "NNetworkManagerDBusInterface.h"

NNetworkManager *NNetworkManager::_device_instance = NULL;

NNetworkManager::NNetworkManager() :
	QObject()
{

}

NNetworkManager::~NNetworkManager()
{
	for (int i=0; i<_device_list.count(); i++)
		delete _device_list.at(i);
}

NDeviceList NNetworkManager::getDevices()
{
	return _device_list;
}

NDevice *NNetworkManager::getWirelessDevice()
{
	for (int i=0; i<_device_list.count(); i++) {
		if (_device_list.at(i)->isWireless())
			return _device_list.at(i);
	}
	return NULL;
}

NDevice *NNetworkManager::getActiveDevice()
{
	for (int i=0; i<_device_list.count(); i++){
			if (_device_list.at(i)->isActive())
				return _device_list.at(i);
	
	}
	return NULL;
}

void NNetworkManager::setActiveDevice(NDevice *dev)
{
	NNetworkManagerDBusInterface::activateDevice(dev);
}

NNetworkManager *NNetworkManager::getInstance()
{
	if (_device_instance == NULL)
		_device_instance = new NNetworkManager();
	return _device_instance;
}

void NNetworkManager::networkRefresh()
{
	NNetworkManagerDBusInterface::getDevices();
}

NDevice *NNetworkManager::getDevice(const QString &obj_path)
{
	for (int i=0; i< _device_list.count(); i++) {
		if (_device_list.at(i)->getObjectPath() == obj_path) {
			return _device_list.at(i);
		}
	}

	return NULL;
}

void NNetworkManager::emitNetworkStrengthChange(NNetwork *net)
{
	emit networkStrengthChange(net);
}

void NNetworkManager::emitNetworkInfoRefresh(NDevice *dev)
{
	emit networkInfoRefresh(dev);
}

void NNetworkManager::setupDevices(char **path, int num)
{
	NDevice *dev;

	/* free previous devices */
	for (int i=0; i<_device_list.count(); i++)
		delete _device_list.at(i);

	_device_list.clear();

	for (int i=0; i<num; i++) {
			dev = new NDevice(path[i]);
			connect(dev, SIGNAL(networkStrengthChange(NNetwork *)),
					this, SLOT(emitNetworkStrengthChange(NNetwork *)));
			connect(dev, SIGNAL(networkDisappeared(NDevice *)),
					this, SLOT(emitNetworkInfoRefresh(NDevice *)));
			connect(dev, SIGNAL(networkFound(NDevice *)),
					this, SLOT(emitNetworkInfoRefresh(NDevice *)));

			dev->push(_ctx);
			_device_list << dev;
	}
}

void NNetworkManager::push(NNetworkTools *ctx)
{
	_ctx = ctx;
	NNetworkManagerDBusInterface::push(ctx);
}
