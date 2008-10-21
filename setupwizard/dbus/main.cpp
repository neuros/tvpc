#include <QApplication>
#include "NNetworkTools.h"

int main()
{
	NNetworkTools tools;
	NDeviceList devlist;
	NDevice *dev;
	NNetworkList netlist;
	NNetwork *net;
	//qDebug() << NNetworkState::getInstance()->isConnected();
	devlist = NNetworkManager::getInstance()->getDevices();
	for (int i=0; i<devlist.count(); i++) {
		if (devlist.at(i)->isWireless())
			dev = devlist.at(i);;
	}

	netlist = dev->getNetworks();
	for (int i=0; i<netlist.count(); i++) {
		if (netlist.at(i)->getEssid() == "TP-LINK") {
			NEncryption *enc =  new NEncryptionWEP(WEP_ASCII);
			enc->setSecret("34202");
			netlist.at(i)->setEncryption(enc);
			dev->activeNetwork(netlist.at(i));
			//qDebug() << enc.isValid(netlist.at(i)->getEssid());
			//dev->activeNetwork(netlist.at(i));
		}
	}
	//net = dev->getActiveNetwork();
	//qDebug() << net->getEssid();
	//qDebug() << net->getEncryptionProtocol();
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
