#include "nconnecting.h"
#include "NDBusStateTools.h"
#define MAX_WAIT_TIME 30  // 30s

NConnectingForm::NConnectingForm(NDBusNetwork *net, QWidget *parent)
	:QWidget(parent), _net(net)
{
	timer = new QTimer(this);
	timer->setInterval(1000);
	timer->start();
	cnt = 0;
	iAmConnecting = false;
	setupUi(this);
	setupConnections();
}

NConnectingForm::~NConnectingForm()
{
	delete timer;
}

void NConnectingForm::setupConnections()
{
	connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
}

void NConnectingForm::setNetwork(NDBusNetwork *net)
{
	_net = net;
}

void NConnectingForm::stopTimer()
{
	timer->stop();
}

void NConnectingForm::startTimer()
{
	timer->start();
}

void NConnectingForm::on_stopBtn_clicked()
{
	stopTimer();

	emit stopConnecting(this);
}

void NConnectingForm::timeOut()
{
	cnt ++;

	if (cnt > MAX_WAIT_TIME) {
		cnt = 0;
		stopTimer();

		NDBusStateTools::getInstance()->switchState(NDBusStateTools::Sleep);

		emit disconnected(_net);
		return;
	}

	if (cnt % 7)
		connectLabel->setText(connectLabel->text() + ".");
	else {
        connectLabel->setText(connectLabel->text().left(connectLabel->text().length() - 6));
	}
	NDBusStateTools::getInstance()->updateNMState();

	qDebug() << NDBusStateTools::getInstance()->stateToString();

	if (iAmConnecting && NDBusStateTools::getInstance()->isDisconnected()) {
		stopTimer();
		emit disconnected(_net);
	} else if (iAmConnecting && NDBusStateTools::getInstance()->isConnected()) {
		stopTimer();
		emit connected(_net);
	} else if (NDBusStateTools::getInstance()->isConnecting()) {
		iAmConnecting = true;
	}
}
