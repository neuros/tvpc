#ifndef _NSETUP_WIZARD_MANAGER_H__
#define _NSETUP_WIZARD_MANAGER_H__
#include <QObject>
#include "dbus/NNetworkTools.h"
#include "nsplashform.h"
#include "nselectmode.h"
#include "noverview.h"
#include "nwirelessconfigquery.h"
#include "nwireconfigquery.h"
#include "nnetworklist.h"
#include "ninsertlan.h"
#include "ndeviceinfo.h"
#include "nnetworkinfo.h"
#include "nselectipmethod.h"
#include "ninputssidpassword.h"

class NSetupWizardManager : public QObject
{
	Q_OBJECT
public:
	NSetupWizardManager();
	~NSetupWizardManager();

	static NSetupWizardManager *getInstance();
	void start();

public slots:
	void createSelectModeForm(QWidget *);
	void createOverViewForm(QWidget *);
	void createNetworkConfigQueryForm(QWidget *widget);
	void createWirelessConfigQueryForm(QWidget *widget);
	void createWireConfigQueryForm(QWidget *widget);
	void createNetworkListForm(QWidget *widget);
	void createInserLanForm(QWidget *widget);
	void createDeviceInfoForm(QWidget *widget);
	void createNetworkInfoForm(QWidget *widget, NNetwork *net);
	void createSelectIPMethodForm(QWidget *widget, NNetwork *net);
	void createInputSSIDPasswordForm(QWidget *widget, NNetwork *net);
	void createConnect2NetworkForm(QWidget *widget, NNetwork *net);

	void lowerForm(QWidget *);
	void raiseForm(QWidget *);
private:
	bool isLanDetected() const;
private:
	static NSetupWizardManager *_manager;

	NNetworkTools _tools;

	QStack<QWidget *> _stackWidget;

	QWidget *_splashForm;
	QWidget *_selectModeForm;
	QWidget *_overViewForm;
	QWidget *_wirelessConfigForm;
	QWidget *_wireConfigForm;
	QWidget *_wirelessNetworkListForm;
	QWidget *_insertLanForm;
	QWidget *_deviceInfoForm;
	QWidget *_networkInfoForm;
	QWidget *_selectipmethodForm;
	QWidget *_inputssidpasswordForm;
};

#endif /* _NSETUP_WIZARD_MANAGER_H__ */
