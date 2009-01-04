#ifndef _NDBUS_NETWORK_H__
#define _NDBUS_NETWORK_H__
#include <QtDBus/QtDBus>
#include <QObject>
#include "NDBusEncryption.h"

class NDBusDevice;
class NDBusNetworkPrivate;

class NDBusNetwork : QObject
{
	Q_OBJECT
public:
	NDBusNetwork(const QDBusObjectPath &path, NDBusDevice *dev);
	~NDBusNetwork();

	void	setDevice(NDBusDevice *);
	void	setObjectPath(const QDBusObjectPath&);

	const QStringList getEncryptionProtocol(void) const;
    const QDBusObjectPath		getObjectPath(void) const;
	const QString     getEssid(void) const;
	const QString     getHardwareAddress(void) const;
	NDBusEncryption* getEncryption (void) const;
	void	setEncryption (NDBusEncryption*);

	double      getFrequency(void) const;
	int		getStrength(void) const;
	int		getRate(void) const;
	int		getMode(void) const;
	int		getCapabilities(void) const;
	bool	  isActive(void) const;
	bool	  isEncrypted(void) const;
	bool	  isHidden(void) const;
	NDBusDevice *getDevice(void) const;

	bool update();
private:
	void	setObjectPath(const QString&);
	void	setEssid(const QString&);
	void	setHardwareAddress (const QString&);
	void	setStrength(int);
	void	setFrequency(double);
	void	setRate(int);
	void	setMode(int);
	void	setCapabilities(int);
	void	setActive(bool);
	void	setHidden(bool);

private:
	QDBusObjectPath _path;

	NDBusEncryption *_encryption;

	NDBusDevice *_dev;

	NDBusNetworkPrivate *n;
};

typedef QList<NDBusNetwork *> NDBusNetworkList;

#endif // _NDBUS_NETWORK_H__
