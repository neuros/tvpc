#include "NNetworkState.h"
#include "NStateDBusInterface.h"

NNetworkState *NNetworkState::_instance = NULL;

NNetworkState::NNetworkState(void)
	: QObject()
{
	_connectionState = NM_STATE_UNKNOWN;
	_dialupActive = false;
	_waitingForKey = false;
	_wirelessEnabled = false;
}

NNetworkState::~NNetworkState(void)
{

}

NNetworkState *NNetworkState::getInstance(void)
{
	if (_instance)
		return _instance;
	return (_instance = new NNetworkState());
}

bool NNetworkState::isNetworkManagerRunning()
{
	return NStateDBusInterface::isNetworkManagerRunning();
}

bool NNetworkState::isSleeping (void)
{
	if (_connectionState == NM_STATE_ASLEEP) {
		return true;
	}

	return false;
}

bool NNetworkState::isConnecting (void)
{
	if (_connectionState == NM_STATE_CONNECTING) {
		return true;
	}

	return false;
}

bool NNetworkState::isConnected (void)
{
	if (_connectionState == NM_STATE_CONNECTED) {
		return true;
	}

	return false;
}

bool NNetworkState::isDisconnected (void)
{
	if (_connectionState == NM_STATE_DISCONNECTED) {
		return true;
	}

	return false;
}

bool NNetworkState::isWirelessEnabled (void)
{
	return _wirelessEnabled;
}

bool NNetworkState::isWaitingForKey(void)
{
	return _waitingForKey;
}

bool NNetworkState::isDialupActive(void)
{
	return _dialupActive;
}

void NNetworkState::setWaitingForKey(bool state)
{
	_waitingForKey = state;
}

void NNetworkState::setDialupState(bool state)
{
	_dialupActive = state;
}

void NNetworkState::setOfflineMode(bool set)
{
	if (set)
		NStateDBusInterface::switchMode ("sleep");
	else {
		NStateDBusInterface::switchMode ("wake");
        /* FIXME: to keep the context menu up to date, we're already setting
		   NM's state to NM_STATE_CONNECTING before it tells us. */
		_connectionState = NM_STATE_CONNECTING;
	}
}

void NNetworkState::setWirelessState (bool state)
{
	NStateDBusInterface::enableWireless(state);
	NStateDBusInterface::getWirelessState ();
}

NMState NNetworkState::getConnectionState ()
{
	return _connectionState;
}


void NNetworkState::setState (NMState nmstate)
{
	if (_connectionState == nmstate)
		return;

	_connectionState = nmstate;
	emit connectionStateChanged ();
	switch ( _connectionState )
	{
		case NM_STATE_ASLEEP:
			emit sleeping();
			break;
		case NM_STATE_CONNECTING:
			emit connecting();
			break;
		case NM_STATE_CONNECTED:
			emit connected();
			break;
		case NM_STATE_DISCONNECTED:
			emit disconnected();
			break;
		default:
			break;
	}
}

void NNetworkState::updateWirelessState (bool state)
{
	_wirelessEnabled = state;
}

const QString NNetworkState::stateToString() const
{
	QString stateString;
	switch ( _connectionState )
	{
		case NM_STATE_UNKNOWN:
			stateString = "NM_STATE_UNKNOWN";
			break;
		case NM_STATE_ASLEEP:
			stateString = "NM_STATE_ASLEEP";
			break;
		case NM_STATE_CONNECTING:
			stateString = "NM_STATE_CONNECTING";
			break;
		case NM_STATE_CONNECTED:
			stateString = "NM_STATE_CONNECTED";
			break;
		case NM_STATE_DISCONNECTED:
			stateString = "NM_STATE_DISCONNECTED";
			break;
	}
	return stateString;
}

void NNetworkState::push(NNetworkManager *ctx)
{
	_ctx = ctx;
	NStateDBusInterface::push (ctx);

	/* get NetworkManager state */
	NStateDBusInterface::getState ();
	NStateDBusInterface::getWirelessState ();
}
