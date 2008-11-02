#include "nsetupwizardmanager.h"

NSetupWizardManager *NSetupWizardManager::_manager = NULL;

NSetupWizardManager::NSetupWizardManager()
	: QObject(), _splashForm(NULL), _selectModeForm(NULL),
	_overViewForm(NULL), _wirelessConfigForm(NULL), _wireConfigForm(NULL),
	_wirelessNetworkListForm(NULL), _insertLanForm(NULL), _deviceInfoForm(NULL),
	_networkInfoForm(NULL)
{

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
		connect(_wirelessNetworkListForm, SIGNAL(createNetworkInfoForm(QWidget *, int)),
				this, SLOT(createNetworkInfoForm(QWidget *, int)));
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
	if (!isLanDetected() == false) {
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

void NSetupWizardManager::createNetworkInfoForm(QWidget *form, int index)
{
	if (_networkInfoForm == NULL) {
		_networkInfoForm = new NNetworkInfoForm();
		_networkInfoForm->resize(QApplication::desktop()->size());

		connect(_networkInfoForm, SIGNAL(quit(QWidget *)),
				this, SLOT(raiseForm(QWidget *)));
	}

	NDevice *dev = NNetworkManager::getInstance()->getActiveDevice();
	if (dev) {
		NNetworkList list = dev->getNetworks();
		if (index < list.count() && index >= 0) {
			static_cast<NNetworkInfoForm *>(_networkInfoForm)->updateNetworkInfo(list.at(index));
		}
	}
	_networkInfoForm->show();

	lowerForm(form);
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
