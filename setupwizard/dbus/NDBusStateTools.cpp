#include "NDBusStateTools.h"

NDBusStateTools *NDBusStateTools::_tools_instance = NULL;

NDBusStateTools::NDBusStateTools() :
	QObject()
{

}

NDBusStateTools::~NDBusStateTools()
{

}

NDBusStateTools *NDBusStateTools::getInstance()
{
	if (_tools_instance == NULL)
		_tools_instance = new NDBusStateTools;

    return _tools_instance;
}

bool NDBusStateTools::isSystemBusConnected()
{
    if (!QDBusConnection::systemBus().isConnected()) {
        fprintf(stderr, "Cannot connect to the D-BUS session bus.\n"
                "To start it, run:\n"
                "\teval `dbus-launch --auto-syntax`\n");
        return false;
    }

	return true;
}

void NDBusStateTools::reply(const QDBusMessage &msg)
{
	qDebug() << "reply" << msg.errorMessage();
}

bool NDBusStateTools::isSleeping (void)
{
	if (_connectionState == NM_STATE_ASLEEP) {
		return true;
	}

	return false;
}

bool NDBusStateTools::isConnecting (void)
{
	if (_connectionState == NM_STATE_CONNECTING) {
		return true;
	}

	return false;
}

bool NDBusStateTools::isConnected (void)
{
	if (_connectionState == NM_STATE_CONNECTED) {
		return true;
	}

	return false;
}

bool NDBusStateTools::isDisconnected (void)
{
	if (_connectionState == NM_STATE_DISCONNECTED) {
		return true;
	}

	return false;
}

const QString NDBusStateTools::stateToString() const
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

bool NDBusStateTools::isNetworkManagerRunning()
{
	return QDBusConnection::systemBus().interface()->isServiceRegistered(NM_DBUS_SERVICE);
}

bool NDBusStateTools::updateNMState()
{
	if (isSystemBusConnected() == false)
		return false;

	QDBusInterface iface(NM_DBUS_SERVICE, NM_DBUS_PATH, NM_DBUS_INTERFACE,
						 QDBusConnection::systemBus());

	if (iface.isValid()) {
		_connectionState = static_cast<NMState>(iface.call("state").arguments().at(0).toInt());
		return true;
	}

    fprintf(stderr, "%s\n",
            qPrintable(QDBusConnection::systemBus().lastError().message()));

	return false;
}

bool NDBusStateTools::getWirelessState()
{
	if (isSystemBusConnected() == false)
		return false;

	QDBusInterface iface(NM_DBUS_SERVICE, NM_DBUS_PATH, NM_DBUS_INTERFACE,
						 QDBusConnection::systemBus());

	if (iface.isValid())
        return iface.call("getWirelessEnabled").arguments().at(0).toBool();

    fprintf(stderr, "%s\n",
            qPrintable(QDBusConnection::systemBus().lastError().message()));

	return false;
}

bool NDBusStateTools::enableWireless(bool enable)
{
	if (isSystemBusConnected() == false)
		return false;

    QDBusInterface iface(NM_DBUS_SERVICE, NM_DBUS_PATH, NM_DBUS_INTERFACE,
						 QDBusConnection::systemBus());
    if (iface.isValid())
		return iface.callWithCallback("setWirelessEnabled", QList<QVariant>() << enable , this,
							   SLOT(reply(const QDBusMessage&)), NULL);

    fprintf(stderr, "%s\n",
            qPrintable(QDBusConnection::systemBus().lastError().message()));

	return false;
}

bool NDBusStateTools::switchState(NDBusStateTools::State state)
{
	if (isSystemBusConnected() == false)
		return false;

	QString method =
		state == Sleep ? "sleep" :
		state == Wake ? "wake" : "unknown";

    QDBusInterface iface(NM_DBUS_SERVICE, NM_DBUS_PATH, NM_DBUS_INTERFACE,
						 QDBusConnection::systemBus());
    if (iface.isValid())
        return iface.callWithCallback(method, QList<QVariant>(), this,
														   SLOT(reply(const QDBusMessage &)), NULL);

    fprintf(stderr, "%s\n",
            qPrintable(QDBusConnection::systemBus().lastError().message()));

	return false;
}
