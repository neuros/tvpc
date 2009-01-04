#ifndef _NNETWORK_H__
#define _NNETWORK_H__
#include "NDBusConnection.h"
#include "NEncryption.h"
#include <QStringList>
#include <QObject>

class NNetworkTools;
class NDevice;

class NNetwork : public QObject
{
	Q_OBJECT

public:
	  NNetwork (const QString&, NDevice *);
	  ~NNetwork ();

	  void	setDevice(NDevice *);
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

	  const QStringList getEncryptionProtocol(void) const;
	  const QString		getObjectPath(void) const;
	  const QString     getEssid(void) const;
	  const QString     getHardwareAddress(void) const;

	  double      getFrequency(void) const;
	  int		getStrength(void) const;
	  int		getRate(void) const;
	  int		getMode(void) const;
	  int		getCapabilities(void) const;
	  bool	  isActive(void) const;
	  bool	  isEncrypted(void) const;
	  bool	  isHidden(void) const;

	  NEncryption* getEncryption (void) const;
	  void	setEncryption (NEncryption*);

	  NDevice *getDevice(void) const;

      void push(NNetworkTools *ctx);
public slots:
	void emitStrengthChange(NNetwork *net);
signals:
	void strengthChange(NNetwork *net);
private:
	  NEncryption*  _encryption;
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
