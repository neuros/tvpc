#include "NNetworkTools.h"

NNetworkTools::NNetworkTools()
{
	_dbus = new NDBusConnection();
	if (_dbus->push(this) == true)
		qDebug() << "Successfully connected to the D-Bus system bus.\n";
	else
		return ;

	_state = NNetworkState::getInstance();
	_state->push (this);

	_manager = NNetworkManager::getInstance();
	_manager->push(this);

}

NNetworkTools::~NNetworkTools()
{
	_dbus->pop();
	delete _dbus;
	delete _state;
	delete _manager;
}

NDBusConnection *NNetworkTools::getDBus() const
{
	return _dbus;
}

NNetworkState *NNetworkTools::getState() const
{
	return _state;
}

NNetworkManager *NNetworkTools::getManager() const
{
	return _manager;
}
