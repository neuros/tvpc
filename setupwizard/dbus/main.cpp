#include <QApplication>
#include "NNetworkTools.h"

int main()
{
	NNetworkTools tools;
	NDevice *dev;
	NNetworkList netlist;
	NNetwork *net;
	qDebug() << NNetworkState::getInstance()->isConnected();
	dev = NNetworkManager::getInstance()->getActiveDevice();

	net = dev->getActiveNetwork();
	qDebug() << net->getEssid();
	qDebug() << net->getEncryptionProtocol();
	//NNetworkManager::networkRefresh();
//	for (int i=0; i<netlist.count(); i++) {
	//	netlist.at(i)->updateNetworkInfo();
	//	qDebug() << netlist.at(i)->getHardwareAddress();
	//	qDebug() << netlist.at(i)->getRate();
	//}
	//NDeviceList list = NNetworkManager::getInstance()->getDevices();

	//for (int i=0; i< list.count(); i++) {
		//qDebug() << list.at(i)->getVendor();
		//qDebug() << list.at(i)->setLinkActive(
		//qDebug() << list.at(i)->getLinkActive();
	//}

	//NNetworkManager::getInstance()->setActiveDevice(list.at(0));
	//qDebug() << NNetworkManager::getInstance()->getActiveDevice()->getObjectPath();
	return 1;
}
