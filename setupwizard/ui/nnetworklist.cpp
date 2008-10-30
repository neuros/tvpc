#include "nnetworklist.h"
#include "dbus/NNetworkManager.h"
#include "ndeviceinfo.h"
#include <QDesktopWidget>

NNetworkSSIDList::NNetworkSSIDList(QWidget *parent)
	:QWidget(parent)
{
	setupUi(this);
}

NNetworkSSIDList::~NNetworkSSIDList()
{

}

void NNetworkSSIDList::updateNetworkList(const NNetworkList &list)
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

void NNetworkSSIDList::updateSignalStrength(NNetwork *net)
{
	qDebug() <<"network" << net->getEssid() << "Strength = " << net->getStrength();
}

void NNetworkSSIDList::updateNetworkList(NDevice *dev)
{
	if (!dev)
		return;

	updateNetworkList(dev->getNetworks());
}

void NNetworkSSIDList::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit destroyed();
		break;
	case Qt::Key_A:
	{
		NDeviceInformation *info = new NDeviceInformation();
		if (info) {
			info->setAttribute(Qt::WA_DeleteOnClose, true);
			info->resize(QApplication::desktop()->size());
			info->show();
		}
	}
		break;
	default:
		break;
	}

	e->ignore();
}
