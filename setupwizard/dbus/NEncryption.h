#ifndef _NENCRYPT_H__
#define _NENCRYPT_H__
#include "NDBusConnection.h"
#include <NetworkManager/NetworkManager.h>
#include <iwlib.h>
#include <NetworkManager/cipher.h>
#include <NetworkManager/cipher-wep-ascii.h>
#include <NetworkManager/cipher-wep-hex.h>
#include <NetworkManager/cipher-wep-passphrase.h>
#include <NetworkManager/cipher-wpa-psk-hex.h>
#include <NetworkManager/cipher-wpa-psk-passphrase.h>
#include <NetworkManager/dbus-helpers.h>

class NNetwork;

typedef QList<IEEE_802_11_Cipher*> CipherList;

class NEncryption
{
public:
	NEncryption ();
	virtual ~NEncryption ();

	/* either passphrase or key */
	void      setSecret (const QString&);
	const QString getSecret (void) const;

	/* for all sub-classes but EncryptionNone */
	virtual bool isValid (const QString &);
	virtual bool serialize (DBusMessage*, const QString &) = 0;
	virtual bool deserialize( DBusMessageIter *, int we_cipher ) = 0;
	virtual void setDefaults (void) = 0;
  
	int     getWeCipher(void) const;
	void   setWeCipher(int we_cipher);

protected:
	friend class NNetwork;

	void setNetwork(NNetwork *network);
	void clearCipherList();
	  
	QString           _secret;
	IEEE_802_11_Cipher* _currentCipher;
	CipherList*         _cipherList;
	NNetwork*            _network;
	int                 _we_cipher;
};

/* EncryptionNone */
class NEncryptionNone : public NEncryption
{
public:
	NEncryptionNone  ();
	~NEncryptionNone ();
  
	/* overwrite Encryption::isValid () */
	bool isValid     (const QString & ssid);
	virtual bool serialize   (DBusMessage*, const QString &);
	virtual bool deserialize( DBusMessageIter *, int we_cipher );
	void setDefaults (void);
};

enum WEPMethod {
	WEP_OPEN_SYSTEM = IW_AUTH_ALG_OPEN_SYSTEM,
	WEP_SHARED_KEY  = IW_AUTH_ALG_SHARED_KEY
};

class NEncryptionWEP : public NEncryption
{
public:
	/* EncryptionWEP */
	enum WEPType {
		WEP_ASCII      = 0,
		WEP_HEX        = 1,
		WEP_PASSPHRASE = 3
	};

	NEncryptionWEP  (WEPType);
	~NEncryptionWEP ();

	void      setMethod (WEPMethod);
	WEPMethod getMethod (void);
	void      setType(WEPType );

	bool serialize   (DBusMessage*, const QString &);
	virtual bool deserialize( DBusMessageIter *, int we_cipher );
	void setDefaults (void);

private:
	WEPType   _type;
	WEPMethod _method;
};


/* Used by both, Personal and Enterprise */
enum WPAProtocol {
	WPA_AUTO     = NM_AUTH_TYPE_WPA_PSK_AUTO, /* WPA Personal */
	WPA_TKIP     = NM_AUTH_TYPE_WPA_PSK_TKIP, /* WPA Personal */
	WPA_CCMP_AES = NM_AUTH_TYPE_WPA_PSK_CCMP, /* WPA Personal */
	WPA_EAP      = NM_AUTH_TYPE_WPA_EAP       /* WPA Enterprise */
};

enum WPAVersion {
	WPA1 = IW_AUTH_WPA_VERSION_WPA, /* WPA Personal and Enterprise */
	WPA2 = IW_AUTH_WPA_VERSION_WPA2 /* WPA Personal and Enterprise */
};


/* EncryptionWPAPersonal */
/* Have not been tested. */
class NEncryptionWPAPersonal : public NEncryption
{
public:
	NEncryptionWPAPersonal  ();
	~NEncryptionWPAPersonal ();

	void         setVersion (WPAVersion);
	void         setProtocol (WPAProtocol);
	WPAProtocol  getProtocol (void);
	WPAVersion   getVersion (void);

	bool serialize   (DBusMessage*, const QString &);
	virtual bool deserialize( DBusMessageIter *, int we_cipher );
	void setDefaults (void);

private:
	WPAProtocol _protocol;
	WPAVersion  _version;
};

#endif /* _NENCRYPT_H__ */
