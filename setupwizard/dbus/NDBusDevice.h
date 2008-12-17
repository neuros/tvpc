#ifndef _NDBUS_DEVICE_H__
#define _NDBUS_DEVICE_H__
#include <QtDBus/QtDBus>
#include <QObject>
#include <NetworkManager.h>
#include "NDBusNetwork.h"

class NDBusDevicePrivate;

class NDBusDevice : public QObject
{
	Q_OBJECT

public:

	NDBusDevice(const QDBusObjectPath &);
	NDBusDevice() {};
	NDBusDevice(const NDBusDevice&);
	~NDBusDevice();

	NDBusNetworkList getNetworks(void) const;
	NDBusNetwork *getActiveNetwork(void) const;
	NDBusNetwork *getNetwork(const QDBusObjectPath &) const;
	void activeNetwork(NDBusNetwork *net);


	const QString      getInterface        (void) const;
	const QDBusObjectPath	  getObjectPath() const;
    NMDeviceType   getType             (void) const;
	const QString      getUdi              (void) const;
	bool         			  isActive            (void) const;
	NMActStage   	   getActivationStage  (void) const;
	const QString      getIPv4Address      (void) const;
	const QString      getSubnetmask       (void) const ;
	const QString      getBroadcast        (void) const;
	const QString      getHardwareAddress  (void) const;
	const QString      getRoute            (void) const;
	const QString      getPrimaryDNS       (void) const;
	const QString      getSecondaryDNS     (void) const;
	const QString	   getActiveNetworkPath(void) const;
	const QString	   getDriver			(void) const;
	unsigned int       getMode             (void) const;
	bool                       getLinkActive       (void) const;
	int           				 getSpeed            (void) const;
	unsigned int 	   getCapabilities     (void) const;
	unsigned int 	   getCapabilitiesType (void) const;
	bool         hasCarrierDetect    (void) const;
	bool        isWired        (void) const;
	bool        isWireless     (void) const;
	int            getStrength         (void) const;
	bool 		isValid() const;

	void 		 setInterface        (const QString&);
	void         setObjectPath       (const QString&);
	void         setType             (uint);
	void         setUdi              (const QString&);
	void         setActive           (bool);
	void         setActivationStage  (int);
	void         setIPv4Address      (const QString&);
	void         setSubnetmask       (const QString&);
	void         setBroadcast        (const QString&);
	void         setHardwareAddress  (const QString&);
	void         setRoute            (const QString&);
	void         setPrimaryDNS       (const QString&);
	void         setSecondaryDNS     (const QString&);
	void		 setDriver					(const QString &);
	void         setMode             (int);
	void         setStrength         (int);
	void         setLinkActive       (bool);
	void         setSpeed            (int);
	void         setCapabilities     (uint);
	void         setCapabilitiesType (uint);
	void 		 setActiveNetworkPath(const QString &);
	void 		 setupNetworks(const QStringList &);

	bool 		update();
private:
	QDBusObjectPath _path;

	NDBusDevicePrivate * d;

};

typedef QList<NDBusDevice*> NDBusDeviceList;

#endif // _NDBUS_DEVICE_H__
