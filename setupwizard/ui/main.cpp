#include <QApplication>
#include <QtGui>
#include "nsetupwizardmanager.h"
#include "NDBusStateTools.h"
#include "NDBusTools.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	//qDebug() << NDBusStateTools::getInstance()->getWirelessState();
	//qDebug() << NDBusStateTools::getInstance()->isNetworkManagerRunning();
	//NDBusStateTools::getInstance()->updateNMState();
	//qDebug() << NDBusStateTools::getInstance()->stateToString();

	NDBusTools::getInstance()->update();
	NDBusDevice *dev = NDBusTools::getInstance()->getWirelessDevice();
	//NDBusTools::getInstance()->activeDevice(dev);

	if (dev) {
		dev->update();
		NDBusNetwork *net = dev->getNetwork("TP-LINK");

		if (net) {
			net->update();
			NDBusEncryption *enc = new NDBusEncryptionWEP(NDBusEncryptionWEP::WEP_ASCII);
			enc->setSecret("34202");
			net->setEncryption(enc);
			dev->activeNetwork(net);
		}
// 		NDBusTools::getInstance()->activeDevice(dev);
// 		NDBusTools::getInstance()->update();
// 		dev = NDBusTools::getInstance()->getActiveDevice();
// 		qDebug() << dev;
	}
	//NDBusDeviceList list = NDBusTools::getInstance()->getDevices();
	//for (int i=0; i<list.count(); i++) {;
		//qDebug() << list.at(i)->getObjectPath().path();
		//list.at(i)->update();
	//}
	//qDebug() << NDBusStateTools::getInstance()->getWirelessState();

//	qDebug() << "disable";
	//NDBusStateTools::getInstance()-> enableWireless(true);
//	qDebug() << "enable";
	//NDBusStateTools::getInstance()->switchState(NDBusStateTools::Sleep);
	//sleep(10);
	//qDebug() << "disable";
	//NDBusStateTools::getInstance()->switchState(NDBusStateTools::Wake);
	//qDebug() << "enable";
	return app.exec();
}

