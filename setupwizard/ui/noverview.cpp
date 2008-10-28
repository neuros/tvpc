#include "noverview.h"
#include "nwireconfigquery.h"
#include "nwirelessconfigquery.h"
#include "dbus/NNetworkTools.h"
#include <QDesktopWidget>

NOverView::NOverView(QDialog *parent)
	:QDialog(parent)
{
	setupUi(this);
}

NOverView::~NOverView()
{

}

bool NOverView::isLanDetected() const
{
	NDeviceList list = NNetworkManager::getInstance()->getDevices();
	for (int i=0; i<list.count(); i++) {
		if (list.at(i)->isWired() && list.at(i)->getLinkActive() == true) {
			return true;
		}
	}

	return false;
}

void NOverView::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		close();
		break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (isLanDetected()) {
			emit createWireConfigQueryDlg(this);
		} else {
			emit createWirelessConfigQueryDlg(this);
		}
		break;
	default:
		break;
	}

	e->ignore();
}
