#include "NDBusEncryption.h"
#include "NDBusNetwork.h"

NDBusEncryption::NDBusEncryption ()
{
	_we_cipher = -1;
	_network = NULL;
	_cipherList = NULL;
	_currentCipher = NULL;
}

NDBusEncryption::~NDBusEncryption ()
{
    clearCipherList();
}

bool NDBusEncryption::isValid (const QString & essid)
{
	bool    status = false;

	if ((essid.length () == 0) || (_secret.length () == 0) || (!_cipherList) || (_cipherList->empty ())) {
		qDebug() << "Encryption::isValid failed, bad inputs" ;
		qDebug() << "isValid, essid: " << essid << ", input: " << _secret << ", cipherlist: " << _cipherList
			  << endl;
		return status;
	}

	CipherList::iterator iter;
	for (iter = _cipherList->begin (); iter != _cipherList->end (); ++iter) {
		if (ieee_802_11_cipher_validate (*iter, essid.toAscii().data(), _secret.toAscii().data() ) == 0) {
			this->_currentCipher = *iter;
			setWeCipher (ieee_802_11_cipher_get_we_cipher (_currentCipher));

			status = true;
		}
	}

	return status;
}

void NDBusEncryption::setWeCipher(int we_cipher)
{
	_we_cipher = we_cipher;
}

int NDBusEncryption::getWeCipher() const
{
	return _we_cipher;
}

void NDBusEncryption::setSecret(const QString &secret)
{
	_secret = secret;
}

const QString NDBusEncryption::getSecret() const
{
	return _secret;
}

void NDBusEncryption::clearCipherList()
{
    if (_cipherList)
        for (CipherList::Iterator it = _cipherList->begin(); it != _cipherList->end(); ++it)
        {
            ieee_802_11_cipher_unref(*it);
            (*it) = NULL;
        }
    delete _cipherList;
}


void NDBusEncryption::setNetwork(NDBusNetwork *network)
{
	_network = network;
}

NDBusEncryptionNone::NDBusEncryptionNone ()
    : NDBusEncryption()
{

}

NDBusEncryptionNone::~NDBusEncryptionNone ()
{

}

bool NDBusEncryptionNone::isValid (const QString & essid)
{
	if (essid.length ())
		return true;
	else
		return false;
}

void NDBusEncryptionNone::setDefaults (void)
{
	return;
}


bool NDBusEncryptionNone::serialize (QDBusMessage& msg, const QString & essid)
{
	if (essid.isNull() || !_network)
		return false;

	msg.setArguments(QList<QVariant>() << qVariantFromValue(_network->getObjectPath()) <<
					 essid << IW_AUTH_CIPHER_NONE);

	return true;
}


/* EncryptionWEP */
NDBusEncryptionWEP::NDBusEncryptionWEP (WEPType type)
{
	setType (type);
	setDefaults ();
}

NDBusEncryptionWEP::~NDBusEncryptionWEP ()
{

}

void NDBusEncryptionWEP::setType( WEPType type )
{
	_type = type;

	clearCipherList();
	_cipherList = new CipherList ();

	if (_type == WEP_ASCII) {
		_cipherList->append (cipher_wep64_ascii_new  ());
		_cipherList->append (cipher_wep128_ascii_new  ());
	} else if (_type == WEP_HEX) {
		_cipherList->append (cipher_wep64_hex_new  ());
		_cipherList->append (cipher_wep128_hex_new  ());
	} else if (_type == WEP_PASSPHRASE) {
		_cipherList->append (cipher_wep64_passphrase_new  ());
		_cipherList->append (cipher_wep128_passphrase_new  ());
	}
}

void NDBusEncryptionWEP::setDefaults ()
{
	setMethod (WEP_OPEN_SYSTEM);
}

void NDBusEncryptionWEP::setMethod (WEPMethod method)
{
	_method = method;
}

NDBusEncryptionWEP::WEPMethod NDBusEncryptionWEP::getMethod (void)
{
	return _method;
}


bool NDBusEncryptionWEP::serialize (QDBusMessage& msg, const QString & essid)
{
	qDebug() << "serialize: msg: " << msg << " essid: " << essid <<" secret: " <<_secret <<
		" method: " << _method << endl;

	if (isValid(essid) == false)
		return false;

	if (_secret.isEmpty()) {
		if (essid.isEmpty())
			return false;

		IEEE_802_11_Cipher *fake_cipher = 0;
		const char *fake_key = "";

		switch (_we_cipher) {
			case IW_AUTH_CIPHER_WEP40:
				fake_cipher = _cipherList->first();
				break;
			case IW_AUTH_CIPHER_WEP104:
				fake_cipher = _cipherList->last();
				break;
		}

		if (fake_cipher) {

			msg.setArguments(QList<QVariant>() << qVariantFromValue(_network->getObjectPath())
							 << essid
							 << ieee_802_11_cipher_get_we_cipher (fake_cipher)
							 << fake_key
							 << _method
							 );
		}

	} else {

		if (essid.isEmpty() || !isValid(essid)) {
			return false;
		}

		char *key = ieee_802_11_cipher_hash(_currentCipher, essid.toUtf8().data(),
											 _secret.toUtf8().data());

		msg.setArguments(QList<QVariant>() << qVariantFromValue(_network->getObjectPath())
						 << essid
						 << ieee_802_11_cipher_get_we_cipher (_currentCipher)
						 << key
						 << _method
						 );
	}

	return true;
}

//
// /* EncryptionWPAPersonal */
// NDBusEncryptionWPAPersonal::NDBusEncryptionWPAPersonal ()
// {
// 	_cipherList = new CipherList ();
//         _cipherList->append (cipher_wpa_psk_hex_new ());
//         _cipherList->append (cipher_wpa_psk_passphrase_new ());
// 	setDefaults ();
// }
//
// NDBusEncryptionWPAPersonal::~NDBusEncryptionWPAPersonal ()
// {
//
// }
//
// bool NDBusEncryptionWPAPersonal::serialize (DBusMessage* msg, const QString & essid)
// {
// 	//kdDebug() << k_funcinfo << essid << endl;
// 	bool status = false;
//
// 	/*
// 	 * There are two possibilities: we can serialize Encryption with or without a key.
// 	 * In the latter case, if we have a key in the secure storage, we can send the rest
// 	 * of the data to NM and supply a key on demand. This will show NM that we know
// 	 * the network we are connecting to and there is no need to ask user for a new key.
// 	 */
// 	if (_secret.isEmpty() ) {
// 		if ( !msg || essid.isEmpty() )
// 			return false;
// 		/*
// 		 * We only need to pass we_cipher remembered since the last connection.
// 		 * Unfortunately, libnm-util functions accept only IEEE_802_11_Cipher object
// 		 * so we need to construct one with required we_cipher value.
// 		 */
// 		IEEE_802_11_Cipher *fake_cipher = 0;
// 		const char *fake_key = "";
//
// 		/*
// 		 * In case of WPA Personal, we can create any cipher_wpa_psk object we like
// 		 * and set the required we_cipher via set_we_cipher method.
// 		 */
// 		if ( _we_cipher != -1 ) {
// 			fake_cipher = cipher_wpa_psk_hex_new();
// 			cipher_wpa_psk_hex_set_we_cipher(fake_cipher, _we_cipher);
// 			status = nmu_security_serialize_wpa_psk_with_cipher (msg, fake_cipher, essid.toUtf8().data(), fake_key,
// 									     _version, IW_AUTH_KEY_MGMT_PSK);
// 			ieee_802_11_cipher_unref(fake_cipher);
// 		}
// 	} else {
// 		if ( !msg || !essid.isNull() || !isValid( essid ) )
// 			return false;
//
// 		status = nmu_security_serialize_wpa_psk_with_cipher (msg, _currentCipher, essid.toUtf8().data(),
// 								     _secret.toUtf8().data(), _version, IW_AUTH_KEY_MGMT_PSK);
// 	}
//
// 	return status;
// }
//
// bool NDBusEncryptionWPAPersonal::deserialize( DBusMessageIter * iter, int we_cipher )
// {
// 	char* key = 0;
// 	int   keyLen, wpaVersion, keyManagement;
//
// 	if ( !iter )
// 		return false;
// 	if ( !(we_cipher == NM_AUTH_TYPE_WPA_PSK_TKIP || we_cipher == NM_AUTH_TYPE_WPA_PSK_CCMP ||
// 	       we_cipher == NM_AUTH_TYPE_WPA_PSK_AUTO) )
// 		return false;
//
// 	if (!nmu_security_deserialize_wpa_psk (iter, &key, &keyLen, &wpaVersion, &keyManagement) )
// 		return false;
//
// 	if ( !(wpaVersion == IW_AUTH_WPA_VERSION_WPA || wpaVersion == IW_AUTH_WPA_VERSION_WPA2 ) )
// 		return false;
//
// 	if ( keyManagement != IW_AUTH_KEY_MGMT_PSK )
// 		return false;
//
// 	setVersion( (WPAVersion)wpaVersion );
// 	setWeCipher( we_cipher );
//
// 	// we don't store this key, as it is the hashed version
// 	return true;
// }
//
// void NDBusEncryptionWPAPersonal::setDefaults (void)
// {
// 	/* Once NM can default to "no default protocol" change this */
// 	setProtocol (WPA_AUTO);
// 	setVersion  (WPA1);
// }
//
// void NDBusEncryptionWPAPersonal::setProtocol (WPAProtocol protocol)
// {
// 	_protocol = protocol;
//
// 	/* switch ciphers to match with protocol */
// 	cipher_wpa_psk_hex_set_we_cipher        (_cipherList->at(0), _protocol);
// 	cipher_wpa_psk_passphrase_set_we_cipher (_cipherList->at(1), _protocol);
// }
//
// WPAProtocol NDBusEncryptionWPAPersonal::getProtocol (void)
// {
// 	return _protocol;
// }
//
// void NDBusEncryptionWPAPersonal::setVersion (WPAVersion version)
// {
// 	_version = version;
// }
//
// WPAVersion NDBusEncryptionWPAPersonal::getVersion (void)
// {
// 	return _version;
// }
//




