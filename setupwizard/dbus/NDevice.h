#ifndef _NDEVICE_H__
#define _NDEVICE_H__
#include "NDBusConnection.h"
#include "NNetwork.h"
#include <QObject>

class DevicePrivate;
class NNetworkTools;

enum bustype {
	BUS_PCI		= 0,
	BUS_USB		= 1,
	BUS_PCMCIA	= 2,
	BUS_UNKNOWN	= 15 
};

class NDevice : public QObject
{
	Q_OBJECT
public:
		friend class NDeviceDBusInterface;

	  NDevice (const QString & );
	  NDevice ();
	  ~NDevice ();

	const QString      getInterface        (void) const;
	bustype                 getBustype          (void) const;
	const QString      getProduct          (void) const;
	const QString      getVendor           (void) const;
	const QString      getObjectPath(void) const;
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

	NNetworkList getNetworks(void) const;
	NNetwork *getActiveNetwork(void) const;
	NNetwork *getNetwork(const QString & obj_path) const;
	void activeNetwork(NNetwork *net);

	void 		 setInterface        (const QString&);
	void         setBustype          (const QString&);
	void         setProduct          (const QString&);
	void         setVendor           (const QString&);
	void         setObjectPath       (const QString&);
	void         setType             (const NMDeviceType &);
	void         setUdi              (const QString&);
	void         setActive           (bool);
	void         setActivationStage  (const NMActStage&);
	void         setIPv4Address      (const QString&);
	void         setSubnetmask       (const QString&);
	void         setBroadcast        (const QString&);
	void         setHardwareAddress  (const QString&);
	void         setRoute            (const QString&);
	void         setPrimaryDNS       (const QString&);
	void         setSecondaryDNS     (const QString&);
	void		 setDriver					(const QString &);
	void         setMode             (unsigned int);
	void         setStrength         (int);
	void         setLinkActive       (bool);
	void         setSpeed            (int);
	void         setCapabilities     (unsigned int);
	void         setCapabilitiesType (unsigned int);
	void 		 setActiveNetworkPath(const QString &);

	void updateDeviceInfo(void);
	void push(NNetworkTools *ctx);

public:
	signals:
	void strengthChange     (NDevice *);
	void carrierOn          (NDevice*);
	void carrierOff         (NDevice*);
	void added              (NDevice*);
	void removed            (NDevice*);
	void noLongerActive     (NDevice*);
	void active             (NDevice*);
	void activating         (NDevice*);
	void networkFound       (NDevice*);
	void networkDisappeared (NDevice*);
	void statusChanged(NDevice *);

	void networkStrengthChange(NNetwork *);
public slots:
	void emitStrengthChange (NDevice*);
	void emitCarrierOn      (NDevice*);
	void emitCarrierOff     (NDevice*);
	void emitAdded          (NDevice*);
	void emitRemoved        (NDevice*);
	void emitNoLongerActive (NDevice*);
	void emitActive         (NDevice*);
	void emitActivating     (NDevice*);
	void emitNetworkFound   (NDevice*);
	void emitNetworkDisappeared(NDevice*);
	void emitStatusChanged(NDevice *);
	void emitNetworkStrengthChange(NNetwork *);
private:
	void setupNetworks(char **networks, int num_networks);
private:
	DevicePrivate * d;
	NNetworkTools  *_ctx;
};

typedef QList<NDevice*> NDeviceList;

#endif /* _NDEVICE_H__ */
