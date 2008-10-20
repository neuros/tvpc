#include "NNetwork.h"
#include "NNetworkDBusInterface.h"
#include "NDevice.h"

NNetwork::NNetwork (const QString & obj_path, NDevice *dev):/* _encryption (0),*/ _obj_path (obj_path), _essid (""),
	 _hw_address (""),
		  _strength (0), _frequency (0), _rate (0), _active( false ), _mode (0),
		  _capabilities( NM_DEVICE_CAP_NONE ),  _dev(dev)
{
	//qDebug() << obj_path;
	//_encryption = new EncryptionNone ();
	//_encryption->setNNetwork(this);
	//_dirty = true;
}

NNetwork::~NNetwork ()
{
	//delete _encryption;
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

// void NNetwork::insertHardwareAddress (const QString & hw_address, bool isActiveAddress)
// {
// 	if ( hw_address != "00:00:00:00:00:00" ) {
// 		if ( _hw_addresses.find( hw_address ) == _hw_addresses.end() ) {
// 			_hw_addresses.append( hw_address );
// 			_dirty = true;
// 		}
// 		if ( isActiveAddress) {
// 			_active_hw_address = hw_address;
// 		}
// 	}
// }

// void
// NNetwork::removeHardwareAddress (const QString & hw_address)
// {
// 	QStringList::Iterator it = _hw_addresses.find( hw_address );
// 	if ( it != _hw_addresses.end() ) {
// 		_hw_addresses.remove( it );
// 		_dirty = true;
// 	}
// }

// const QStringList NNetwork::getHardwareAddresses () const
// {
// 	return _hw_addresses;
// }

// const QString NNetwork::getActiveHardwareAddress()
// {
// 	if (_active_hw_address.isEmpty())
// 		return _hw_addresses.first();
// 	else
// 		return _active_hw_address;
// }

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

// Encryption*
// NNetwork::getEncryption (void) const
// {
// 	return _encryption;
// }
//
// void
// NNetwork::setEncryption (Encryption* encryption)
// {
// 	_encryption = encryption;
// 	_dirty = true;
// 	if ( _encryption )
// 		_encryption->setNNetwork(this);
// }
//
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

void NNetwork::updateNetworkInfo()
{
	NNetworkDBusInterface::getProperties(_obj_path, this);
}

void NNetwork::push(NNetworkTools *ctx)
{
	_ctx = ctx;
	NNetworkDBusInterface::push(ctx);
}

