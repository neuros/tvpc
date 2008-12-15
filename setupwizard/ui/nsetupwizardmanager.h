#ifndef _NSETUP_WIZARD_MANAGER_H__
#define _NSETUP_WIZARD_MANAGER_H__
#include <QWidget>
#include <QStack>
#include "dbus/NNetworkTools.h"

class NSetupWizardManager : public QWidget
{
	Q_OBJECT
public:
	NSetupWizardManager();
	~NSetupWizardManager();

	static NSetupWizardManager *getInstance();
	void start();
	enum encryptType {
		WepASCII,
		WepHex,
		Wep,
		Invalid,
	};
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

	void connecting();
	void connected();
	void disconnected();

	void stopConnecting(QWidget *widget);

	void lowerForm(QWidget *);
	void raiseForm(QWidget *);
private:
	void startConnecting();
	bool isLanDetected() const;
	bool isHex(const QString &num) const;
	NSetupWizardManager::encryptType safeCheckPassword(
		const QString &passwd, encryptType type) const;
	void setupConnections();

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
	QWidget *_connectingForm;

	bool _iAmConnecting;
};

#endif /* _NSETUP_WIZARD_MANAGER_H__ */
