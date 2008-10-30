#include "nsplashform.h"
#include "nselectmode.h"
#include "noverview.h"
#include "nwireconfigquery.h"
#include "nwirelessconfigquery.h"
#include "nnetworklist.h"
#include "dbus/NNetworkTools.h"
#include "ninsertlan.h"

NSplashForm::NSplashForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	selectMode = NULL;
	overView = NULL;
	wireQuery = NULL;
	wirelessQuery = NULL;
	insertLan = NULL;
	networkList = NULL;
}

NSplashForm::~NSplashForm()
{
 	if (selectMode)
 		delete selectMode;
 	if (overView)
 		delete overView;
 	if (wireQuery)
 		delete wireQuery;
 	if (wirelessQuery)
 		delete wirelessQuery;
 	if (insertLan)
 		delete insertLan;
	if (networkList)
		delete networkList;
}

void NSplashForm::createWireConfigQueryDlg(QDialog *dlg)
{
	if (wireQuery == NULL) {
		wireQuery = new NWireConfigQuery(dlg);
	}

	if (wireQuery) {
		wireQuery->resize(QApplication::desktop()->size());
		wireQuery->show();
	}
}

bool NSplashForm::isLanDetected() const
{
	NDeviceList list = NNetworkManager::getInstance()->getDevices();
	for (int i=0; i<list.count(); i++) {
		if (list.at(i)->isWired() && list.at(i)->getLinkActive() == true) {
			return true;
		}
	}

	return false;
}

void NSplashForm::createWirelessConfigQueryDlg(QDialog *dlg)
{
	if (wirelessQuery == NULL) {
		wirelessQuery = new NWirelessConfigQuery(dlg);
		connect(wirelessQuery, SIGNAL(createInserLanDlg(QDialog *)),
				this, SLOT(createInsertLanDlg(QDialog *)));
		connect(wirelessQuery, SIGNAL(createNetworkListForm(QWidget *)),
				this, SLOT(createNetworkListForm(QWidget *)));
		connect(wirelessQuery, SIGNAL(destroyed()),
				this, SLOT(onWirelessQueryQuit()));
	}

	if (wirelessQuery) {
		wirelessQuery->resize(QApplication::desktop()->size());
		wirelessQuery->show();
	}

}

void NSplashForm::createNetworkListForm(QWidget *widget)
{
	if (networkList == NULL) {
		networkList = new NNetworkSSIDList();
		if (networkList) {
			networkList->resize(QApplication::desktop()->size());

			connect(NNetworkManager::getInstance(), SIGNAL(networkInfoRefresh(NDevice *)),
					static_cast<NNetworkSSIDList *>(networkList),
					 SLOT(updateNetworkList(NDevice *)));
			connect(networkList, SIGNAL(destroyed()),
					this, SLOT(onNetworkListQuit()));
		}
	}

	if (networkList) {
		networkList->show();
	
		NDeviceList list = NNetworkManager::getInstance()->getDevices();
		for (int i=0; i<list.count(); i++) {
			if (list.at(i)->isWireless()) {
				(static_cast<NNetworkSSIDList *>(networkList))->updateNetworkList(
					list.at(i)->getNetworks());
			}
		}
    }

	if (wirelessQuery)
		wirelessQuery->hide();

}

void NSplashForm::createOverViewDlg(QDialog *dlg)
{
	if (overView == NULL) {
		overView = new NOverView(dlg);

		connect(overView, SIGNAL(networkConfigQuery(QDialog *)),
				this, SLOT(onNetworkConfigQuery(QDialog *)));
		connect(overView, SIGNAL(destroyed()),
				this, SLOT(onOverViewQuit()));
	}

	if (overView) {
		overView->resize(QApplication::desktop()->size());
		overView->show();
	}

	if (selectMode)
		selectMode->hide();
}

void NSplashForm::onNetworkConfigQuery(QDialog *dlg)
{
	if (isLanDetected())
		createWireConfigQueryDlg(dlg);
	else
		createWirelessConfigQueryDlg(dlg);

	if (overView)
		overView->hide();
}

void NSplashForm::createInsertLanDlg(QDialog *dlg)
{
	if (insertLan == NULL) {
		insertLan = new NInsertLAN(dlg);
		connect(insertLan, SIGNAL(checkLanInserted(QDialog *)),
				this, SLOT(onInsertLan(QDialog *)));
		connect(insertLan, SIGNAL(destroyed()),
				this, SLOT(onInsertLanQuit()));
	}
	if (insertLan) {
		insertLan->resize(QApplication::desktop()->size());
		insertLan->show();
	}

	if (wirelessQuery)
		wirelessQuery->hide();

}

void NSplashForm::onInsertLan(QDialog *dlg)
{
	if (isLanDetected())
		createWireConfigQueryDlg(dlg);
	else
		createWirelessConfigQueryDlg(dlg);

	if (insertLan)
		insertLan->hide();
}

void NSplashForm::onSelectModeQuit()
{
	this->show();
	this->setGeometry((QApplication::desktop()->size().width() - width()) /2,
					 (QApplication::desktop()->size().height() - height())/2, width(), height());
	selectMode->hide();
}

void NSplashForm::onOverViewQuit()
{
	if (selectMode)
		selectMode->show();
	if (overView)
        overView->hide();
}

void NSplashForm::onWirelessQueryQuit()
{
	if (overView)
		overView->show();
	if (wirelessQuery)
		wirelessQuery->hide();
}

void NSplashForm::onInsertLanQuit()
{
	if (wirelessQuery)
		wirelessQuery->show();
	if (insertLan)
		insertLan->hide();
}

void NSplashForm::onNetworkListQuit()
{
	if (wirelessQuery)
		wirelessQuery->show();
	if (networkList)
		networkList->hide();
}

void NSplashForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (selectMode == NULL) {
			selectMode = new NSelectMode();
			connect(selectMode, SIGNAL(createOverViewDlg(QDialog *)),
					this, SLOT(createOverViewDlg(QDialog *)));
			connect(selectMode, SIGNAL(destroyed()),
					this, SLOT(onSelectModeQuit()));
		}
		if (selectMode) {
			selectMode->resize(QApplication::desktop()->size());
			selectMode->show();
		}

		this->hide();
		break;
	default:
		break;
	}

	e->ignore();
}
