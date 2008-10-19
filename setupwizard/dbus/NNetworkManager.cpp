#include "NNetworkManager.h"

NNetworkManager::NNetworkManager()
{
	_dbus = new NDBusConnection();
	if (_dbus->push(this) == false) {
	//	QTimer::singleShot(3000, _dbus, SLOT(reconnect()));
	} else
		qDebug() << "Successfully connected to the D-Bus system bus.\n";


	_state = NNetworkState::getInstance();
	_state->push (this);

}

NDBusConnection *NNetworkManager::getDBus()
{
	return _dbus;
}

NNetworkState *NNetworkManager::getState()
{
	return _state;
}
