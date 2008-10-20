#ifndef _NNETWORK_H__
#define _NNETWORK_H__
#include "NDBusConnection.h"
#include <QStringList>

class NNetworkTools;
class NDevice;

class NNetwork
{

public:
	  NNetwork (const QString&, NDevice *);
	  ~NNetwork ();

	  void 		setDevice(NDevice *dev);
	  void      setObjectPath         (const QString&);
	  void        setEssid              (const QString&);
	  void        setHardwareAddress (const QString&);
	  void        setStrength           (int);
	  void        setFrequency          (double);
	  void        setRate               (int);
	  void        setMode               (int);
	  void        setCapabilities       (int);
	  void        setActive             (bool);
	  const QStringList getEncryptionProtocol (void) const;
	  bool        isEncrypted           (void) const;
	  bool        isHidden              (void) const;
	  void        setHidden             (bool);
	  NDevice *getDevice(void) const;
	  const QString     getObjectPath         (void) const;
	  const QString     getEssid              (void) const;
	  const QString     getHardwareAddress (void) const;
	  int         getStrength           (void) const;
	  double      getFrequency          (void) const;
	  int         getRate               (void) const;
	  int         getMode               (void) const;
	  int         getCapabilities       (void) const;
	  bool        isActive              (void) const;

	  //Encryption* getEncryption (void) const;
	  //void        setEncryption (Encryption*);

	  /**
	   * restores the network's contents from the supplied KConfig or KConfigGroup
	   */
	  //void restore( KConfigBase*, const char*, bool withKey = false);
	  /**
	   * write the network's properties to the supplied KConfig or KConfigGroup 
	   */
	  //void persist( KConfigBase *, bool updateTimestamp = false, bool withKey = true ) const;
	  /**
	   * update timestamp only, do not touch network properties
	   */
	  //void persistTimestamp( KConfigBase * ) const; 
	  void updateNetworkInfo(void);
      void push(NNetworkTools *ctx);
private:
	  //Encryption*  _encryption;
	  QString      _obj_path;
	  QString      _essid;
	  QString	  _hw_address;
	  int          _strength;
	  double       _frequency;
	  int          _rate;
	  bool         _active;
	  int          _mode;
	  int          _capabilities;
	  bool         _hidden;

	  NDevice *_dev;

	  NNetworkTools *_ctx;
};

typedef QList<NNetwork *> NNetworkList;

#endif /* _NNETWORK_H__ */
