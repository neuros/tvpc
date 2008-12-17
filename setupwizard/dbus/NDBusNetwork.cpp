#include "NDBusNetwork.h"
#include "NDBusStateTools.h"
#include "NDBusDevice.h"

class NDBusNetworkPrivate
{
public:
	NDBusNetworkPrivate() : strength(0), frequency(0),
		rate(0), active(false), mode(0), capabilities(0), hidden(false)
	{}
	~NDBusNetworkPrivate(){}

	QString obj_path;
	QString      essid;
	QString	  hw_address;
	int          strength;
	double      frequency;
	int          rate;
	bool         active;
	int          mode;
	int          capabilities;
	bool       hidden;
};

void NDBusNetwork::setObjectPath (const QString & obj_path)
{
	qDebug() << "n->obj_path = " << obj_path;

	n->obj_path = obj_path;
}

void NDBusNetwork::setObjectPath (const QDBusObjectPath & obj_path)
{
	_path = obj_path;
}


const QDBusObjectPath NDBusNetwork::getObjectPath () const
{
	return _path;
}

void NDBusNetwork::setEssid (const QString & essid)
{
	qDebug() << "n->essid = " << essid;

    n->essid = essid;
}

const QString NDBusNetwork::getEssid () const
{
	return n->essid;
}

void NDBusNetwork::setHardwareAddress(const QString &hw_address)
{
	qDebug() << "n->hw_address = " << hw_address;

    n->hw_address = hw_address;
}

const QString NDBusNetwork::getHardwareAddress() const
{
	return n->hw_address;
}

void NDBusNetwork::setStrength (int strength)
{
	qDebug() << "n->strength = " << strength;

    n->strength = strength;
}

int NDBusNetwork::getStrength () const
{
	return n->strength;
}

void NDBusNetwork::setFrequency (double frequency)
{
	qDebug() << "n->frequency = " << frequency;

	n->frequency = frequency;
}

double NDBusNetwork::getFrequency () const
{
	return n->frequency;
}

void NDBusNetwork::setRate (int rate)
{
	qDebug() << "n->rate = " << rate;

	n->rate = rate;
}

int NDBusNetwork::getRate () const
{
	return n->rate;
}

void NDBusNetwork::setMode (int mode)
{
	qDebug() << "n->mode = " << mode;

	n->mode = mode;
}

int NDBusNetwork::getMode () const
{
	return n->mode;
}

void NDBusNetwork::setCapabilities (int capabilties)
{
	qDebug() << "n->capabilties = " << capabilties;

	n->capabilities = capabilties;
}

int NDBusNetwork::getCapabilities () const
{
	return n->capabilities;
}

void NDBusNetwork::setActive (bool active)
{
	qDebug() << "n->active = " << active;

    n->active = active;
}

bool NDBusNetwork::isActive () const
{
	return n->active;
}

bool NDBusNetwork::isHidden () const
{
	return n->hidden;
}

void NDBusNetwork::setHidden (bool hidden)
{
	qDebug() << "n->hidden = " << hidden;

	n->hidden = hidden;
}

bool NDBusNetwork::isEncrypted () const
{
	if (n->capabilities & NM_802_11_CAP_PROTO_NONE)
		return false;
	else
		return true;
}

const QStringList NDBusNetwork::getEncryptionProtocol () const
{
	QStringList encryptionProtocol;

	if (n->capabilities & NM_802_11_CAP_PROTO_WEP)
		encryptionProtocol.append ("WEP");
	if (n->capabilities & NM_802_11_CAP_PROTO_WPA)
		encryptionProtocol.append ("WPA");
	if (n->capabilities & NM_802_11_CAP_PROTO_WPA2)
		encryptionProtocol.append ("WPA2");

	return encryptionProtocol;
}

void NDBusNetwork::setDevice(NDBusDevice *dev)
{
	_dev = dev;
}

NDBusDevice *NDBusNetwork::getDevice() const
{
	return _dev;
}

NDBusNetwork::NDBusNetwork(const QDBusObjectPath &path, NDBusDevice *dev)
	: QObject(), _path(path), _dev(dev)
{
	n = new NDBusNetworkPrivate;
}

NDBusNetwork::~NDBusNetwork()
{
	delete n;
}

bool NDBusNetwork::update()
{
	if (NDBusStateTools::getInstance()->isSystemBusConnected() == false)
		return false;

	QDBusInterface iface(NM_DBUS_SERVICE, _path.path(), NM_DBUS_INTERFACE_DEVICES,
						 QDBusConnection::systemBus());

	QDBusMessage msg = iface.call("getProperties");

	QDBusReply< QDBusObjectPath > reply = msg;
	if (reply.isValid()) {
		this->setObjectPath(reply.value().path());

		if (_dev && n->obj_path == _dev->getActiveNetworkPath())
			this->setActive(true);
		else
			this->setActive(false);

		QList<QVariant> args = msg.arguments();
		if (args.count() < 9)
			return false;

		this->setEssid(args.at(1).toString());
		this->setHardwareAddress (args.at(2).toString());
		this->setStrength (args.at(3).toInt());
		this->setFrequency (args.at(4).toDouble());
		this->setRate (args.at(5).toInt());
		this->setMode (args.at(6).toInt());
		this->setCapabilities (args.at(7).toInt());
		this->setHidden (!args.at(8).toBool());
	}

	return true;
}
