#include "NNetworkManager.h"
#include "NNetworkState.h"
#include <QApplication>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	NNetworkManager m;


/*
     NNetworkState::getInstance()->setOfflineMode(false);
     NNetworkState::getInstance()->setWirelessState(false);
     qDebug() << NNetworkState::getInstance()->isNetworkManagerRunning();
     qDebug() << NNetworkState::getInstance()->isConnected();
     qDebug() << NNetworkState::getInstance()->isConnecting();
     qDebug() << NNetworkState::getInstance()->isSleeping();
     qDebug() << NNetworkState::getInstance()->isDisconnected();
     qDebug() << NNetworkState::getInstance()->isWirelessEnabled();
     qDebug() << NNetworkState::getInstance()->isWirelessEnabled();
     NNetworkState::getInstance()->setWirelessState(true);
     qDebug() <<NNetworkState::getInstance()->stateToString();
     qDebug() << NNetworkState::getInstance()->isWirelessEnabled();
     NNetworkState::getInstance()->setOfflineMode(false);
     qDebug() << NNetworkState::getInstance()->isSleeping();
*/
	return 1;
}
