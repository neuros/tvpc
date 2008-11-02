#include "nnetworklist.h"
#include "dbus/NNetworkManager.h"
#include "ndeviceinfo.h"
#include <QDesktopWidget>

NNetworkSSIDListForm::NNetworkSSIDListForm(QWidget *parent)
	:QWidget(parent)
{
	setupUi(this);
}

NNetworkSSIDListForm::~NNetworkSSIDListForm()
{

}

void NNetworkSSIDListForm::updateNetworkList(const NNetworkList &list)
{
	int i;
	networkList->clear();
	for (i=0; i<list.count(); i++) {
        networkList->insertItem(i, "            " + list.at(i)->getEssid());
	}
	networkList->insertItem(i, "            Other ...");

	if (networkList->count())
		networkList->setCurrentRow(0);

	if (list.count() > 0) {
			connect(NNetworkManager::getInstance(), SIGNAL(networkStrengthChange(NNetwork *)),
					this, SLOT(updateSignalStrength(NNetwork *)));
	}
}

void NNetworkSSIDListForm::updateSignalStrength(NNetwork *net)
{
	qDebug() <<"network" << net->getEssid() << "Strength = " << net->getStrength();
}

void NNetworkSSIDListForm::updateNetworkList(NDevice *dev)
{
	if (!dev)
		return;

	updateNetworkList(dev->getNetworks());
}

void NNetworkSSIDListForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
		break;
	case Qt::Key_A:
		emit createDeviceInfoForm(this);
		break;
	case Qt::Key_H:
		emit createNetworkInfoForm(this, networkList->currentRow());
		break;
	default:
		break;
	}

	e->ignore();
}