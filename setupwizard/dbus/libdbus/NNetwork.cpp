#include "NNetwork.h"
#include "NNetworkDBusInterface.h"
#include "NDevice.h"

NNetwork::NNetwork (const QString & obj_path, NDevice *dev):QObject(), 
	_obj_path (obj_path), _essid (""), _hw_address (""),
		  _strength (0), _frequency (0), _rate (0), _active( false ), _mode (0),
		  _capabilities( NM_DEVICE_CAP_NONE ),  _dev(dev)
{
	_encryption = new NEncryptionNone ();
	_encryption->setNetwork(this);

	connect(this, SIGNAL(strengthChange(NNetwork *)),
			dev, SLOT(emitNetworkStrengthChange(NNetwork *)));
}

NNetwork::~NNetwork ()
{
	delete _encryption;
}

void NNetwork::setDevice(NDevice *dev)
{
	_dev = dev;
}

NDevice *NNetwork::getDevice() const
{
	return _dev;
}

void NNetwork::setObjectPath (const QString & obj_path)
{
	_obj_path = obj_path;
}

const QString NNetwork::getObjectPath () const
{
	return _obj_path;
}

void NNetwork::setEssid (const QString & essid)
{
    _essid = essid;
}

const QString NNetwork::getEssid () const
{
	return _essid;
}

void NNetwork::setHardwareAddress(const QString &hw_address)
{
    _hw_address = hw_address;
}

const QString NNetwork::getHardwareAddress() const
{
	return _hw_address;
}

void NNetwork::setStrength (int strength)
{
    _strength = strength;
}

int NNetwork::getStrength () const
{
	return _strength;
}

void NNetwork::setFrequency (double frequency)
{
	_frequency = frequency;
}

double NNetwork::getFrequency () const
{
	return _frequency;
}

void NNetwork::setRate (int rate)
{
	_rate = rate;
}

int NNetwork::getRate () const
{
	return _rate;
}

void NNetwork::setMode (int mode)
{
	_mode = mode;
}

int NNetwork::getMode () const
{
	return _mode;
}

void NNetwork::setCapabilities (int capabilties)
{
	_capabilities = capabilties;
}

int NNetwork::getCapabilities () const
{
	return _capabilities;
}

void NNetwork::setActive (bool active)
{
    _active = active;
}

bool NNetwork::isActive () const
{
	return _active;
}

NEncryption* NNetwork::getEncryption (void) const
{
	return _encryption;
}

void NNetwork::setEncryption (NEncryption* encryption)
{
	if (_encryption)
		delete _encryption;

	_encryption = encryption;
	if ( _encryption )
		_encryption->setNetwork(this);
}

const QStringList NNetwork::getEncryptionProtocol () const
{
	QStringList encryptionProtocol;

	if (_capabilities & NM_802_11_CAP_PROTO_WEP)
		encryptionProtocol.append ("WEP");
	if (_capabilities & NM_802_11_CAP_PROTO_WPA)
		encryptionProtocol.append ("WPA");
	if (_capabilities & NM_802_11_CAP_PROTO_WPA2)
		encryptionProtocol.append ("WPA2");

	return encryptionProtocol;
}

bool NNetwork::isEncrypted () const
{
	if (_capabilities & NM_802_11_CAP_PROTO_NONE) {
		return false;
	} else {
		return true;
	}
}

bool NNetwork::isHidden () const
{
	return _hidden;
}

void NNetwork::setHidden (bool hidden)
{
	_hidden = hidden;
}

void NNetwork::emitStrengthChange(NNetwork *net)
{
	emit strengthChange(net);
}

void NNetwork::push(NNetworkTools *ctx)
{
	_ctx = ctx;
	NNetworkDBusInterface::push(ctx);
	NNetworkDBusInterface::updateNetwork(this);
}

