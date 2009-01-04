#include "NDevice.h"
#include "NDeviceDBusInterface.h"

class DevicePrivate
{
public:
	DevicePrivate() :   interface (""), bustype (BUS_UNKNOWN), product (""), vendor (""), obj_path (""),
						type (DEVICE_TYPE_UNKNOWN),  udi (""), active (false), act_stage (NM_ACT_STAGE_UNKNOWN),
						ipv4_address (""), subnetmask (""), broadcast (""), hw_address (""), route (""),
						pri_dns (""), sec_dns (""), strength (0), link_active (false), speed (0),
						capabilities (NM_DEVICE_CAP_NONE), active_net_path("")
						{}
	~DevicePrivate() {}
	QString      interface;
	enum bustype bustype;
	QString      product;
	QString      vendor;
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
	unsigned int mode;
	int          strength;
	bool         link_active;
	int          speed;
	unsigned int capabilities;
	unsigned int capabilities_type;
	QString  active_net_path;

	NNetworkList  networkList;
};

NDevice::NDevice (const QString & obj_path) : QObject()
{
	d = new DevicePrivate;
	d->obj_path = obj_path;
}

NDevice::NDevice () : QObject()
{
	d = new DevicePrivate;
}

NDevice::~NDevice ()
{
	for ( NNetworkList::Iterator i = d->networkList.begin (); i != d->networkList.end (); ++i)
		delete *i;
	delete d;
}

void NDevice::setInterface (const QString & interface)
{
	d->interface = interface;
}

const QString NDevice::getInterface () const
{
	return d->interface;
}

void NDevice::setBustype (const QString & bus)
{
	if (QString::compare (bus, "pci") == 0)
		d->bustype = BUS_PCI;
	else if (QString::compare (bus, "usb") == 0)
		d->bustype = BUS_USB;
	else if (QString::compare (bus, "pcmcia") == 0)
		d->bustype = BUS_PCMCIA;
	else
		d->bustype = BUS_UNKNOWN;
}

bustype NDevice::getBustype () const
{
	return d->bustype;
}

void NDevice::setProduct (const QString & product)
{
	d->product = product;
}

const QString NDevice::getProduct () const
{
	return d->product;
}

void NDevice::setVendor (const QString & vendor)
{
	d->vendor = vendor;
}

const QString NDevice::getVendor () const
{
	return d->vendor;
}

void NDevice::setObjectPath (const QString & obj_path)
{
	d->obj_path = obj_path;
}

const QString NDevice::getObjectPath () const
{
	return d->obj_path;
}

void NDevice::setDriver(const QString &driver)
{
	d->driver = driver;
}

const QString NDevice::getDriver() const
{
	return d->driver;
}

const QString NDevice::getActiveNetworkPath() const
{
	return d->active_net_path;
}

void NDevice::setActiveNetworkPath(const QString &net_path)
{
	d->active_net_path = net_path;
}

void NDevice::setType (const NMDeviceType & type)
{
	/* Wireless devices need a list of networks */
	d->type = type;
}

void NDevice::setUdi (const QString & udi)
{
	d->udi = udi;
}

const QString NDevice::getUdi () const
{
	return d->udi;
}

void NDevice::setActive (bool active)
{
	d->active = active;
}

bool NDevice::isActive () const
{
	return d->active;
}

void NDevice::setActivationStage (const NMActStage & act_stage)
{
	d->act_stage = act_stage;
}

NMActStage NDevice::getActivationStage () const
{
	return d->act_stage;
}

void NDevice::setIPv4Address (const QString& ipv4_address)
{
	d->ipv4_address = ipv4_address;
}

const QString NDevice::getIPv4Address () const
{
	return d->ipv4_address;
}

void NDevice::setSubnetmask (const QString& subnetmask)
{
	d->subnetmask = subnetmask;
}

const QString NDevice::getSubnetmask () const
{
	return d->subnetmask;
}

void NDevice::setBroadcast (const QString& broadcast)
{
	d->broadcast = broadcast;
}

const QString NDevice::getBroadcast () const
{
	return d->broadcast;
}

void NDevice::setHardwareAddress (const QString& hw_address)
{
	d->hw_address = hw_address;
}

const QString NDevice::getHardwareAddress () const
{
	return d->hw_address;
}

void NDevice::setRoute (const QString& route)
{
	d->route = route;
}

const QString NDevice::getRoute () const
{
	return d->route;
}

void NDevice::setPrimaryDNS (const QString& pri_dns)
{
	d->pri_dns = pri_dns;
}

const QString NDevice::getPrimaryDNS () const
{
	return d->pri_dns;
}

void NDevice::setSecondaryDNS (const QString& sec_dns)
{
	d->sec_dns = sec_dns;
}

const QString NDevice::getSecondaryDNS () const
{
	return d->sec_dns;
}

void NDevice::setMode (unsigned int mode)
{
	d->mode = mode;
}

unsigned int NDevice::getMode () const
{
	return d->mode;
}

NMDeviceType NDevice::getType () const
{
	return d->type;
}

void NDevice::setStrength (int strength)
{
	d->strength = strength;
}

int NDevice::getStrength () const
{
	return d->strength;
}

void NDevice::setLinkActive (bool link_active)
{
	d->link_active = link_active;
}

bool NDevice::getLinkActive () const
{
	return d->link_active;
}

void NDevice::setSpeed (int speed)
{
	d->speed = speed;
}

int NDevice::getSpeed () const
{
	return d->speed;
}


void NDevice::setCapabilities (unsigned int capabilities)
{
	d->capabilities = capabilities;
}

unsigned int NDevice::getCapabilities () const
{
	return d->capabilities;
}

bool NDevice::hasCarrierDetect () const
{
	return d->capabilities & NM_DEVICE_CAP_CARRIER_DETECT;
}

void NDevice::setCapabilitiesType (unsigned int capabilities_type)
{
	d->capabilities_type = capabilities_type;
}

unsigned int NDevice::getCapabilitiesType () const
{
	return d->capabilities_type;
}

bool NDevice::isWireless () const
{
	return ( d->type == DEVICE_TYPE_802_11_WIRELESS);
}

bool NDevice::isWired () const
{
	return ( d->type == DEVICE_TYPE_802_3_ETHERNET);
}

void NDevice::updateDeviceInfo()
{
	NDeviceDBusInterface::updateDevice(this, "");
}

NNetworkList NDevice::getNetworks() const
{
	return d->networkList;
}

NNetwork *NDevice::getNetwork(const QString &obj_path) const
{
	NNetworkList::iterator i;

	if (d->networkList.isEmpty ())
		return NULL;

	for (i = d->networkList.begin (); i != d->networkList.end (); ++i)
		if ((*i)->getObjectPath () == obj_path)
			return *i;

	return NULL;
}

NNetwork *NDevice::getActiveNetwork() const
{
	if (d->networkList.isEmpty())
		return NULL;

	for (int i=0; i<d->networkList.count(); i++)
		if (d->networkList.at(i)->isActive())
			return d->networkList.at(i);

	return NULL;
}

void NDevice::activeNetwork(NNetwork *net)
{
	NDeviceDBusInterface::setActiveNetwork(net, this);
}

void NDevice::setupNetworks(char **networks, int num_networks)
{
	NNetwork *net;

	for (int i=0; i<d->networkList.count(); i++)
		delete d->networkList.at(i);

	d->networkList.clear();

	for (int i=0; i<num_networks; i++) {
		net = new NNetwork(networks[i], this);
		net->push(_ctx);
		d->networkList << net;
	}
}

void NDevice::emitStrengthChange( NDevice * dev )
{
	emit strengthChange(dev);
}

void NDevice:: emitCarrierOn( NDevice * dev )
{
	emit carrierOn( dev );
}
void NDevice:: emitCarrierOff( NDevice * dev )
{
	emit carrierOff( dev );
}
void NDevice:: emitAdded( NDevice * dev )
{
	emit added( dev );
}
void NDevice:: emitRemoved( NDevice * dev )
{
	emit removed( dev );
}
void NDevice:: emitNoLongerActive( NDevice * dev )
{
	emit noLongerActive( dev );
}
void NDevice:: emitActive( NDevice * dev )
{
	emit active( dev );
}
void NDevice:: emitActivating( NDevice * dev )
{
	emit activating( dev );
}
void NDevice::emitNetworkFound( NDevice * dev )
{
	emit networkFound( dev );
}

void NDevice::emitNetworkDisappeared( NDevice * dev )
{
	emit networkDisappeared( dev );
}


void NDevice::emitStatusChanged(NDevice *dev)
{
	emit statusChanged(dev);
}

void NDevice::emitNetworkStrengthChange(NNetwork *net)
{
	emit networkStrengthChange(net);
}

void NDevice::push(NNetworkTools *ctx)
{
	_ctx = ctx;
	NDeviceDBusInterface::push(ctx);
	NDeviceDBusInterface::updateDevice(this,  "");
}

