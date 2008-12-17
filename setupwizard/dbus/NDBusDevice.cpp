#include "NDBusDevice.h"
#include "NDBusStateTools.h"
#include "NDBusNetwork.h"

class NDBusDevicePrivate
{
public:
	NDBusDevicePrivate() :   interface (""), obj_path (""),
						type (DEVICE_TYPE_UNKNOWN),  udi (""), active (false), act_stage (NM_ACT_STAGE_UNKNOWN),
						ipv4_address (""), subnetmask (""), broadcast (""), hw_address (""), route (""),
						pri_dns (""), sec_dns (""), strength (0), link_active (false), speed (0),
						capabilities (NM_DEVICE_CAP_NONE), active_net_path("")
						{}
	~NDBusDevicePrivate() {}
	QString      interface;
	QString      obj_path;
	NMDeviceType type;
	QString      udi;
	bool	     active;
	NMActStage   act_stage;  
	QString      ipv4_address;
	QString      subnetmask;
	QString      broadcast;
	QString      hw_address;
	QString      route;
	QString      pri_dns;
	QString      sec_dns;
	QString		 driver;
	int mode;
	int          strength;
	bool         link_active;
	int          speed;
	uint capabilities;
	unsigned int capabilities_type;
	QString  active_net_path;

	NDBusNetworkList  networks;
};


NDBusDevice::NDBusDevice(const QDBusObjectPath &path)
	: QObject()
{
	d = new NDBusDevicePrivate;

	_path = path;
}

NDBusDevice::~NDBusDevice()
{
	delete d;
}

void NDBusDevice::setInterface (const QString & interface)
{
	d->interface = interface;
	qDebug() << "d->interface = " << interface;

}

const QString NDBusDevice::getInterface () const
{
	return d->interface;
}

void NDBusDevice::setObjectPath (const QString & obj_path)
{
	d->obj_path = obj_path;
	qDebug() << "d->obj_path = " << obj_path;

}

const QDBusObjectPath NDBusDevice::getObjectPath () const
{
	return _path;
}

void NDBusDevice::setDriver(const QString &driver)
{
	d->driver = driver;
	qDebug() << "d->driver = " << driver;

}

const QString NDBusDevice::getDriver() const
{
	return d->driver;
}

const QString NDBusDevice::getActiveNetworkPath() const
{
	return d->active_net_path;
}

void NDBusDevice::setActiveNetworkPath(const QString &net_path)
{
	d->active_net_path = net_path;
	qDebug() << "d->active_net_path = " << net_path;

}

void NDBusDevice::setType (uint type)
{
	d->type = static_cast<NMDeviceType>(type);
	qDebug() << "d->type = " << type;

}

void NDBusDevice::setUdi (const QString & udi)
{
	d->udi = udi;
	qDebug() << "d->udi = " << udi;

}

const QString NDBusDevice::getUdi () const
{
	return d->udi;
}

void NDBusDevice::setActive (bool active)
{
	d->active = active;
	qDebug() << "d->active = " << active;

}

bool NDBusDevice::isActive () const
{
	return d->active;
}

void NDBusDevice::setActivationStage (int act_stage)
{
    d->act_stage = static_cast<NMActStage>(act_stage);
	qDebug() << "d->act_stage = " << act_stage;
}

NMActStage NDBusDevice::getActivationStage () const
{
	return d->act_stage;
}

void NDBusDevice::setIPv4Address (const QString& ipv4_address)
{
	d->ipv4_address = ipv4_address;
	qDebug() << "d->ipv4_address = " << ipv4_address;

}

const QString NDBusDevice::getIPv4Address () const
{
	return d->ipv4_address;
}

void NDBusDevice::setSubnetmask (const QString& subnetmask)
{
	d->subnetmask = subnetmask;
	qDebug() << "d->subnetmask = " << subnetmask;

}

const QString NDBusDevice::getSubnetmask () const
{
	return d->subnetmask;
}

void NDBusDevice::setBroadcast (const QString& broadcast)
{
	d->broadcast = broadcast;
	qDebug() << "d->broadcast = " << broadcast;

}

const QString NDBusDevice::getBroadcast () const
{
	return d->broadcast;
}

void NDBusDevice::setHardwareAddress (const QString& hw_address)
{
	d->hw_address = hw_address;
	qDebug() << "d->hw_address = " << hw_address;

}

const QString NDBusDevice::getHardwareAddress () const
{
	return d->hw_address;
}

void NDBusDevice::setRoute (const QString& route)
{
	d->route = route;
	qDebug() << "d->route = " << route;

}

const QString NDBusDevice::getRoute () const
{
	return d->route;
}

void NDBusDevice::setPrimaryDNS (const QString& pri_dns)
{
	d->pri_dns = pri_dns;
	qDebug() << "d->pri_dns = " << pri_dns;

}

const QString NDBusDevice::getPrimaryDNS () const
{
	return d->pri_dns;
}

void NDBusDevice::setSecondaryDNS (const QString& sec_dns)
{
	d->sec_dns = sec_dns;
	qDebug() << "d->sec_dns = " << sec_dns;

}

const QString NDBusDevice::getSecondaryDNS () const
{
	return d->sec_dns;
}

void NDBusDevice::setMode (int mode)
{
	d->mode = mode;
	qDebug() << "d->mode = " << mode;

}

unsigned int NDBusDevice::getMode () const
{
	return d->mode;
}

NMDeviceType NDBusDevice::getType () const
{
	return d->type;
}

void NDBusDevice::setStrength (int strength)
{
	d->strength = strength;
	qDebug() << "d->strength = " << strength;

}

int NDBusDevice::getStrength () const
{
	return d->strength;
}

void NDBusDevice::setLinkActive (bool link_active)
{
	d->link_active = link_active;
	qDebug() << "d->link_active = " << link_active;

}

bool NDBusDevice::getLinkActive () const
{
	return d->link_active;
}

void NDBusDevice::setSpeed (int speed)
{
	d->speed = speed;
	qDebug() << "d->speed = " << speed;

}

int NDBusDevice::getSpeed () const
{
	return d->speed;
}


void NDBusDevice::setCapabilities (uint capabilities)
{
	d->capabilities = capabilities;
	qDebug() << "d->capabilities = " << capabilities;

}

unsigned int NDBusDevice::getCapabilities () const
{
	return d->capabilities;
}

bool NDBusDevice::hasCarrierDetect () const
{
	return d->capabilities & NM_DEVICE_CAP_CARRIER_DETECT;
}

void NDBusDevice::setCapabilitiesType (uint capabilities_type)
{
	d->capabilities_type = capabilities_type;
	qDebug() << "d->capabilities_type = " << capabilities_type;
}

void NDBusDevice::setupNetworks(const QStringList &networks)
{
	qDebug() << "d->networks = " << networks;

	d->networks.clear();

	NDBusNetwork *net;
	QStringList::const_iterator iterator;
	for (iterator=networks.constBegin(); iterator!=networks.constEnd(); iterator++) {
		net = new NDBusNetwork(QDBusObjectPath(*iterator), this);
		net->update();
		d->networks << net;
	}
}

NDBusNetworkList NDBusDevice::getNetworks() const
{
	return d->networks;
}

NDBusNetwork *NDBusDevice::getNetwork(const QDBusObjectPath &obj_path) const
{
	if (d->networks.isEmpty ())
		return NULL;

	NDBusNetworkList::const_iterator iterator;

	for (iterator= d->networks.constBegin (); iterator != d->networks.constEnd (); ++iterator)
		if ((*iterator)->getObjectPath ().path() == obj_path.path())
			return *iterator;

	return NULL;
}

NDBusNetwork *NDBusDevice::getActiveNetwork() const
{
	if (d->networks.isEmpty())
		return NULL;

	NDBusNetworkList::const_iterator iterator;

	for (iterator= d->networks.constBegin (); iterator != d->networks.constEnd (); ++iterator)
		if ((*iterator)->isActive())
			return *iterator;

	return NULL;
}

void NDBusDevice::activeNetwork(NDBusNetwork *net)
{
	//NDeviceDBusInterface::setActiveNetwork(net, this);
}


unsigned int NDBusDevice::getCapabilitiesType () const
{
	return d->capabilities_type;
}

bool NDBusDevice::isWireless () const
{
	return ( d->type == DEVICE_TYPE_802_11_WIRELESS);
}

bool NDBusDevice::isWired () const
{
	return ( d->type == DEVICE_TYPE_802_3_ETHERNET);
}

bool NDBusDevice::isValid() const
{
	return _path.path().isEmpty();
}

bool NDBusDevice::update()
{
	if (NDBusStateTools::getInstance()->isSystemBusConnected() == false)
		return false;

	QDBusInterface iface(NM_DBUS_SERVICE, _path.path(), NM_DBUS_INTERFACE_DEVICES,
						 QDBusConnection::systemBus());

	if (iface.isValid()) {
		QDBusMessage msg = iface.call("getProperties");

		QDBusReply< QDBusObjectPath > reply = msg;
		if (reply.isValid())
			this->setObjectPath (reply.value().path());

		QList<QVariant> args = msg.arguments();

		if (args.count() < 21)
			return false;

		this->setInterface (args.at(1).toString());
        this->setType (args.at(2).toUInt());
        this->setUdi (args.at(3).toString());
		this->setActive (args.at(4).toBool());
		this->setActivationStage (args.at(5).toInt());
		this->setIPv4Address (args.at(6).toString());
		this->setSubnetmask (args.at(7).toString());
		this->setBroadcast (args.at(8).toString());
		this->setHardwareAddress (args.at(9).toString());
		this->setRoute (args.at(10).toString());
		this->setPrimaryDNS (args.at(11).toString());
		this->setSecondaryDNS (args.at(12).toString());
		this->setMode (args.at(13).toInt());
		this->setStrength (args.at(14).toInt());
		this->setLinkActive (args.at(15).toBool());
		this->setSpeed (args.at(16).toInt());
		this->setCapabilities (args.at(17).toUInt());
		this->setCapabilitiesType (args.at(18).toUInt());
		this->setActiveNetworkPath(args.at(19).toString());
		if (this->isWireless())
			this->setupNetworks(args.at(20).toStringList());
	}

	fprintf(stderr, "%s\n",
            qPrintable(QDBusConnection::systemBus().lastError().message()));

	return false;


}

