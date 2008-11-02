#include "ndeviceinfo.h"

NDeviceInformation::NDeviceInformation(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

NDeviceInformation::~NDeviceInformation()
{

}

void NDeviceInformation::updateDeviceInfo(NDevice *dev)
{
	if (!dev)
		return;

	winterface->setText(dev->getInterface());
	wtype->setText(dev->getType() == DEVICE_TYPE_802_11_WIRELESS ? "802.11 Wireless" :
				   dev->getType() == DEVICE_TYPE_802_3_ETHERNET ? "Wired" : "Unknown");
    wactive->setText(dev->isActive() ? "yes" : "no");
    whwaddr->setText(dev->getHardwareAddress());
    wspeed->setText(QString::number(dev->getSpeed()) + "Mb/s");
    wipaddr->setText(dev->getIPv4Address());
    wsubnet->setText(dev->getSubnetmask());
    wbroadcast->setText(dev->getBroadcast());
    wgateway->setText(dev->getRoute());
	wpridns->setText(dev->getPrimaryDNS());
	wseddns->setText(dev->getSecondaryDNS());
	wdriver->setText(dev->getDriver());
	wvendor->setText(dev->getVendor());
	wproduct->setText(dev->getProduct());
}

void NDeviceInformation::keyPressEvent(QKeyEvent *e)
{
	emit quit(this);

	e->ignore();
}
