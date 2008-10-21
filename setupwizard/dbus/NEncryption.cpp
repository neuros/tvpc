#include "NEncryption.h"
NEncryption::NEncryption ()
{
	_we_cipher = -1;
	_network = NULL;
	_cipherList = NULL;
	_currentCipher = NULL;
}

NEncryption::~NEncryption ()
{
    clearCipherList();
}

bool NEncryption::isValid (const QString & essid)
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

void NEncryption::setWeCipher(int we_cipher)
{
	_we_cipher = we_cipher;
}

int NEncryption::getWeCipher() const
{
	return _we_cipher;
}

void NEncryption::setSecret(const QString &secret)
{
	_secret = secret;
}

const QString NEncryption::getSecret() const
{
	return _secret;
}

void NEncryption::clearCipherList()
{
    if (_cipherList)
        for (CipherList::Iterator it = _cipherList->begin(); it != _cipherList->end(); ++it)
        {
            ieee_802_11_cipher_unref(*it);
            (*it) = NULL;
        }
    delete _cipherList;
}


void NEncryption::setNetwork(NNetwork *network)
{
	_network = network;
}

NEncryptionNone::NEncryptionNone ()
    : NEncryption()
{

}

NEncryptionNone::~NEncryptionNone ()
{

}

bool NEncryptionNone::isValid (const QString & essid)
{
	if (essid.length ())
		return true;
	else
		return false;
}

void NEncryptionNone::setDefaults (void)
{
	return;
}


bool NEncryptionNone::serialize (DBusMessage* msg, const QString & essid)
{
	bool status = false;

	if (!msg || essid.isNull())
		return false;

	status = nmu_security_serialize_none_with_cipher (msg);

	return status;
}

bool NEncryptionNone::deserialize( DBusMessageIter *, int we_cipher )
{
	return ( we_cipher == IW_AUTH_CIPHER_NONE );
}


/* EncryptionWEP */
NEncryptionWEP::NEncryptionWEP (WEPType type)
{
	setType (type);
	setDefaults ();
}

NEncryptionWEP::~NEncryptionWEP ()
{

}

void NEncryptionWEP::setType( WEPType type )
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

void NEncryptionWEP::setDefaults ()
{
	setMethod (WEP_OPEN_SYSTEM);
}

void NEncryptionWEP::setMethod (WEPMethod method)
{
	_method = method;
}

WEPMethod NEncryptionWEP::getMethod (void)
{
	return _method;
}


bool NEncryptionWEP::serialize (DBusMessage* msg, const QString & essid)
{
	qDebug() << "serialize: msg: " << msg << " essid: " << essid <<" secret: " <<_secret << 
		" method: " << _method << endl;
	bool status = false;

	if (isValid(essid) == false)
		return status;
	/*
	 * There are two possibilities: we can serialize Encryption with or without a key.
	 * In the latter case, if we have a key in the secure storage, we can send the rest
	 * of the data to NM and supply a key on demand. This will show NM that we know
	 * the network we are connecting to and there is no need to ask user for a new key.
	 */
	if (_secret.isEmpty() ) {
		if ( !msg || essid.isEmpty() )
			return false;

		/*
		 * We only need to pass we_cipher remembered since the last connection.
		 * Unfortunately, libnm-util functions accept only IEEE_802_11_Cipher object
		 * so we need to construct one with required we_cipher value.
		 */
		IEEE_802_11_Cipher *fake_cipher = 0;
		const char *fake_key = "";

		/*
		 * WEP ciphers differ only by key length regardless of type so we can use
		 * the corresponding _cipherList item as a fake cipher
		 */
		switch (_we_cipher)
		{
			case IW_AUTH_CIPHER_WEP40:
				fake_cipher = _cipherList->first();
				break;
			case IW_AUTH_CIPHER_WEP104:
				fake_cipher = _cipherList->last();
				break;
		}

		if (fake_cipher)
			status = nmu_security_serialize_wep_with_cipher (msg, fake_cipher, essid.toUtf8().data(), 
															 fake_key, _method);
	} else {
		if (!msg || essid.isEmpty() || !isValid( essid ) ) {
			return false;
		}

		status = nmu_security_serialize_wep_with_cipher (msg, _currentCipher, essid.toUtf8().data(), 
														 _secret.toUtf8().data(), _method);
	}

	return status;
}

bool NEncryptionWEP::deserialize( DBusMessageIter * iter, int we_cipher )
{
	char* key = 0;
	int   keyLen, authAlg;

	if ( iter == 0 )
		return false;
	if ( !( we_cipher == NM_AUTH_TYPE_WEP40 || we_cipher == NM_AUTH_TYPE_WEP104 ) )
		return false;

	if ( !nmu_security_deserialize_wep( iter, &key, &keyLen, &authAlg ) )
		return false;

	if ( !( authAlg == IW_AUTH_ALG_OPEN_SYSTEM || authAlg == IW_AUTH_ALG_SHARED_KEY ) )
		return false;

	setMethod( (WEPMethod) authAlg );
	setWeCipher( we_cipher );

	return true;
}




