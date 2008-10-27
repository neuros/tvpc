#include "NNetworkManager.h"
#include "NNetworkManagerDBusInterface.h"

NNetworkManager *NNetworkManager::_device_instance = NULL;

NNetworkManager::NNetworkManager()
{

}

NNetworkManager::~NNetworkManager()
{
	for (int i=0; i<_device_list.count(); i++)
		delete _device_list.at(i);
}

NDeviceList NNetworkManager::getDevices()
{
	//NNetworkManagerDBusInterface::getDevices();
	return _device_list;
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
//	dev->setActive(true);
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

void NNetworkManager::setupDevices(char **path, int num)
{
	NDevice *dev;

	/* free previous devices */
	for (int i=0; i<_device_list.count(); i++)
		delete _device_list.at(i);

	_device_list.clear();

	for (int i=0; i<num; i++) {
			dev = new NDevice(path[i]);
			dev->push(_ctx);
			_device_list << dev;
	}
}

void NNetworkManager::push(NNetworkTools *ctx)
{
	_ctx = ctx;
	NNetworkManagerDBusInterface::push(ctx);
}
