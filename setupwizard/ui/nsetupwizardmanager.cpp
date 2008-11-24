#include "nsetupwizardmanager.h"
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
#include "nconnecting.h"

NSetupWizardManager *NSetupWizardManager::_manager = NULL;

NSetupWizardManager::NSetupWizardManager()
	: QWidget(), _splashForm(NULL), _selectModeForm(NULL),
	_overViewForm(NULL), _wirelessConfigForm(NULL), _wireConfigForm(NULL),
	_wirelessNetworkListForm(NULL), _insertLanForm(NULL), _deviceInfoForm(NULL),
	_networkInfoForm(NULL), _selectipmethodForm(NULL), _inputssidpasswordForm(NULL),
	_connectingForm(NULL)
{

	setupConnections();
}

NSetupWizardManager::~NSetupWizardManager()
{
	if (_splashForm)
		delete _splashForm;
	if (_selectModeForm)
		delete _selectModeForm;
	if (_overViewForm)
		delete _overViewForm;
	if (_wirelessConfigForm)
		delete _wirelessConfigForm;
	if (_wirelessNetworkListForm)
		delete _wirelessNetworkListForm;
	if (_wireConfigForm)
		delete _wireConfigForm;
	if (_insertLanForm)
		delete _insertLanForm;
	if (_deviceInfoForm)
		delete _deviceInfoForm;
	if (_networkInfoForm)
		delete _networkInfoForm;
	if (_selectipmethodForm)
		delete _selectipmethodForm;
	if (_inputssidpasswordForm)
		delete _inputssidpasswordForm;
	if (_connectingForm)
		delete _connectingForm;
}

NSetupWizardManager *NSetupWizardManager::getInstance()
{
	if (_manager == NULL)
		_manager = new NSetupWizardManager();

	return _manager;
}

void NSetupWizardManager::start()
{
	if (_splashForm == NULL) {
		_splashForm = new NSplashForm();
		connect(_splashForm, SIGNAL(createSelectModeForm(QWidget *)),
				this, SLOT(createSelectModeForm(QWidget *)));
	}

	_splashForm->resize(300, 300);
	_splashForm->setGeometry((QApplication::desktop()->size().width() - 300) /2,
						 (QApplication::desktop()->size().height() - 300)/2, 300, 300);
	_splashForm->show();
}

void NSetupWizardManager::setupConnections()
{
	connect(_tools.getState(), SIGNAL(connecting()), this, SLOT(connecting()));
	connect(_tools.getState(), SIGNAL(connected()), this, SLOT(connected()));
	connect(_tools.getState(), SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void NSetupWizardManager::lowerForm(QWidget *form)
{
	if (form) {
		form->hide();
        _stackWidget.push(form);
	}
}

void NSetupWizardManager::raiseForm(QWidget *form)
{
	QWidget *active = _stackWidget.pop();
	if (active)
		active->show();

	if (form) 
		form->hide();
}

void NSetupWizardManager::createSelectModeForm(QWidget *form)
{
	if (_selectModeForm == NULL) {
		_selectModeForm = new NSelectModeForm();
		_selectModeForm->resize(QApplication::desktop()->size());
		connect(_selectModeForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));
		connect(_selectModeForm, SIGNAL(createOverViewForm(QWidget *)),
				this, SLOT(createOverViewForm(QWidget *)));
	}

	_selectModeForm->show();

	lowerForm(form);
}

void NSetupWizardManager::createOverViewForm(QWidget *form)
{
	if (_overViewForm == NULL) {
		_overViewForm = new NOverViewForm();
		_overViewForm->resize(QApplication::desktop()->size());

		connect(_overViewForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));
		connect(_overViewForm, SIGNAL(createNetworkConfigQueryForm(QWidget *)),
				this, SLOT(createNetworkConfigQueryForm(QWidget *)));
	}

	_overViewForm->show();

	lowerForm(form);
}

void NSetupWizardManager::createWirelessConfigQueryForm(QWidget *form)
{
	qDebug() << "createWirelessConfigQueryForm()";

	if (_wirelessConfigForm == NULL) {
		_wirelessConfigForm = new NWirelessConfigQueryForm();
		_wirelessConfigForm->resize(QApplication::desktop()->size());

		connect(_wirelessConfigForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));
		connect(_wirelessConfigForm, SIGNAL(createNetworkListForm(QWidget *)),
				this, SLOT(createNetworkListForm(QWidget *)));
		connect(_wirelessConfigForm, SIGNAL(createInserLanForm(QWidget *)),
				this, SLOT(createInserLanForm(QWidget *)));
	}

	_wirelessConfigForm->show();

	lowerForm(form);
}

void NSetupWizardManager::createWireConfigQueryForm(QWidget *form)
{
	qDebug() << "createWireConfigQueryForm()";
	if (_wireConfigForm == NULL) {
		_wireConfigForm = new NWireConfigQueryForm();
		_wireConfigForm->resize(QApplication::desktop()->size());

		connect(_wireConfigForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));
		connect(_wireConfigForm, SIGNAL(createNetworkListForm(QWidget *)),
				this, SLOT(createNetworkListForm(QWidget *)));
	}

	_wireConfigForm->show();
	lowerForm(form);
}

void NSetupWizardManager::createNetworkListForm(QWidget *form)
{
	if (_wirelessNetworkListForm == NULL) {
		_wirelessNetworkListForm = new NNetworkSSIDListForm();
		_wirelessNetworkListForm->resize(QApplication::desktop()->size());
		connect(_wirelessNetworkListForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));
		connect(_wirelessNetworkListForm, SIGNAL(createDeviceInfoForm(QWidget *)),
				this, SLOT(createDeviceInfoForm(QWidget *)));
		connect(_wirelessNetworkListForm, SIGNAL(createNetworkInfoForm(QWidget *, NNetwork *)),
				this, SLOT(createNetworkInfoForm(QWidget *, NNetwork *)));
		connect(_wirelessNetworkListForm, SIGNAL(createSelectIPMethodForm(QWidget *, NNetwork *)),
				this, SLOT(createSelectIPMethodForm(QWidget *, NNetwork *)));
		connect(_wirelessNetworkListForm, SIGNAL(createInputSSIDPasswordForm(QWidget *, NNetwork *)),
				this, SLOT(createInputSSIDPasswordForm(QWidget *, NNetwork *)));
	}

	NDevice *dev = NNetworkManager::getInstance()->getWirelessDevice();
	if (dev) {
		static_cast<NNetworkSSIDListForm *>(_wirelessNetworkListForm)->updateNetworkList(
			dev->getNetworks());
	}

	_wirelessNetworkListForm->show();

	lowerForm(form);
}

void NSetupWizardManager::createInserLanForm(QWidget *form)
{
    if (_insertLanForm == NULL) {
		_insertLanForm = new NInsertLANForm();
		_insertLanForm->resize(QApplication::desktop()->size());

		connect(_insertLanForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));
		connect(_insertLanForm, SIGNAL(checkLanInserted(QWidget *)),
				this, SLOT(createNetworkConfigQueryForm(QWidget *)));
		connect(_insertLanForm, SIGNAL(createNetworkListForm(QWidget *)),
				this, SLOT(createNetworkListForm(QWidget *)));
	}

	_insertLanForm->show();

	lowerForm(form);
}

void NSetupWizardManager::createNetworkConfigQueryForm(QWidget *form)
{
	if (isLanDetected() == false) {
		createWirelessConfigQueryForm(form);
	} else {
		createWireConfigQueryForm(form);
	}
}

void NSetupWizardManager::createDeviceInfoForm(QWidget *form)
{
	if (_deviceInfoForm == NULL) {
		_deviceInfoForm = new NDeviceInformation();
		_deviceInfoForm->resize(QApplication::desktop()->size());
		connect(_deviceInfoForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));
	}

	static_cast<NDeviceInformation *>(_deviceInfoForm)->updateDeviceInfo(
		NNetworkManager::getInstance()->getActiveDevice());

	_deviceInfoForm->show();

	lowerForm(form);
}

void NSetupWizardManager::createNetworkInfoForm(QWidget *form, NNetwork *net)
{
	if (!net)
		return;

	if (_networkInfoForm == NULL) {
		_networkInfoForm = new NNetworkInfoForm();
		_networkInfoForm->resize(QApplication::desktop()->size());

		connect(_networkInfoForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));
	}

	static_cast<NNetworkInfoForm *>(_networkInfoForm)->updateNetworkInfo(net);

	_networkInfoForm->show();

	lowerForm(form);
}

void NSetupWizardManager::createSelectIPMethodForm(QWidget *form, NNetwork *net)
{
	qDebug() << "createSelectIPMethodForm()";

	if (_selectipmethodForm == NULL) {
		_selectipmethodForm = new NSelectIPMethodForm();
		_selectipmethodForm->resize(QApplication::desktop()->size());

		connect(_selectipmethodForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));

	}

	_selectipmethodForm->show();

	lowerForm(form);

	Q_UNUSED(net);
}

void NSetupWizardManager::createInputSSIDPasswordForm(QWidget *form, NNetwork *net)
{
	if (!net)
		return;

	qDebug() << "createInputSSIDPasswordForm()" << net->getEssid();

	if (_inputssidpasswordForm == NULL) {
		_inputssidpasswordForm = new NInputSSIDPasswordForm();
		_inputssidpasswordForm->resize(QApplication::desktop()->size());
		connect(_inputssidpasswordForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));
		connect(_inputssidpasswordForm, SIGNAL(createConnect2NetworkForm(QWidget *, NNetwork *)),
				this, SLOT(createConnect2NetworkForm(QWidget *, NNetwork *)));
	}

	static_cast<NInputSSIDPasswordForm *>(_inputssidpasswordForm)->setNetwork(net);
	_inputssidpasswordForm->show();

	lowerForm(form);
}

void NSetupWizardManager::createConnect2NetworkForm(QWidget *form, NNetwork *net)
{
	NInputSSIDPasswordForm *passwordForm = static_cast<NInputSSIDPasswordForm *>(form);

	if (!net || !passwordForm)
		return;
	qDebug() << "createConnect2NetworkForm() " << net->getEssid();

	if (net->getCapabilities() & NM_802_11_CAP_PROTO_WEP) {
		encryptType type;
		type = safeCheckPassword(passwordForm->password(), Wep);
		if (type == Invalid) {
			QMessageBox::critical(this, tr("Invalid password"), tr("The current encryption mode is WEP, please"
																   " input 5 or 13 or 16 chararcters for ASCII, and 10 or 26 or 32 characters"
																   " for Hex."));

			passwordForm->clearPassword();
			return;
		} else if (type == WepASCII) {

			NEncryption *enc = new NEncryptionWEP(NEncryptionWEP::WEP_ASCII);
			enc->setSecret(passwordForm->password());
			net->setEncryption(enc);

			if(net->getDevice())
				net->getDevice()->activeNetwork(net);
		}

	}
}

bool NSetupWizardManager::isLanDetected() const
{
	NDeviceList list = NNetworkManager::getInstance()->getDevices();
	for (int i=0; i<list.count(); i++) {
		if (list.at(i)->isWired() && list.at(i)->getLinkActive() == true) {
			return true;
		}
	}

	return false;
}

NSetupWizardManager::encryptType NSetupWizardManager::safeCheckPassword(const QString &passwd,
																		encryptType type) const
{
	if (type == Wep) {
		if (passwd.length() == 5 || passwd.length() == 13 || passwd.length() == 16)
			return WepASCII;
		else if (passwd.length() == 10 || passwd.length() == 26 || passwd.length() == 32) {
			if (isHex(passwd))
				return WepHex;
			else
				return Invalid;
		} else
			return Invalid;
	}

	return Invalid;
}

bool NSetupWizardManager::isHex(const QString &num) const
{
	for (int i=0; i<num.length(); i++) {
		if (!(num.at(i).isNumber() || (num.at(i).toLower() >= 'a' && 
									 num.at(i).toLower() <= 'f')))
			return false;
	}

	return true;
}

void NSetupWizardManager::connecting()
{
	if (_connectingForm == NULL) {
		_connectingForm = new NConnectingForm();
		_connectingForm->resize(QApplication::desktop()->size());
	}

	_connectingForm->show();
}

void NSetupWizardManager::connected()
{
	if (_connectingForm) {
		static_cast<NConnectingForm *>(_connectingForm)->stopTimer();

		QMessageBox::information(_connectingForm, tr("Congratulations"), tr("Congratulations! Your TVPC succeeds to connect to network."));

		_connectingForm->hide();
	}
}

void NSetupWizardManager::disconnected()
{
	if (_connectingForm) {
		static_cast<NConnectingForm *>(_connectingForm)->stopTimer();

		QMessageBox::information(_connectingForm, tr("Sorry"), tr("Unable to connect to network."));

		_connectingForm->hide();
	}
}


