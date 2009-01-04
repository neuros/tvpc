#include "nnetworklist.h"
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

void NNetworkSSIDListForm::updateNetworkList(const NDBusNetworkList &list)
{
	int i;
	networkList->clear();
	for (i=0; i<list.count(); i++) {
        networkList->addItem("            " + list.at(i)->getEssid());
	}
	networkList->addItem("            Other ...");

	if (networkList->count())
		networkList->setCurrentRow(0);

	_list = list;
}

void NNetworkSSIDListForm::updateSignalStrength(NDBusNetwork *net)
{

}

void NNetworkSSIDListForm::updateNetworkList(NDBusDevice *dev)
{
	if (!dev)
		return;

	updateNetworkList(dev->getNetworks());
}

void NNetworkSSIDListForm::keyPressEvent(QKeyEvent *e)
{
	NDBusNetwork *net = NULL;

	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
		break;
	case Qt::Key_A:
		emit createDeviceInfoForm(this);
		break;
	case Qt::Key_H:
		if (networkList->currentRow() < _list.count())
			net = _list.at(networkList->currentRow());

		emit createNetworkInfoForm(this, net);
		break;
	case Qt::Key_Right:
	case Qt::Key_Enter:

		if (networkList->currentRow() < _list.count()) {
			net = _list.at(networkList->currentRow());
			if (net->isEncrypted() == true) {
				emit createInputSSIDPasswordForm(this, net);
			} else {
				emit createSelectIPMethodForm(this, net);
			}
		} else {

		}
		break;
	default:
		break;
	}

	e->ignore();
}
