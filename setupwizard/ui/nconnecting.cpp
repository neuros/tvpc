#include "nconnecting.h"
#include "NDBusStateTools.h"

NConnectingForm::NConnectingForm(QWidget *parent)
	:QWidget(parent)
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
	if (cnt < 6) {
		cnt ++;
		connectLabel->setText(connectLabel->text() + ".");
	} else {
		cnt = 0;
		connectLabel->setText(connectLabel->text().left(connectLabel->text().length() - 6));
	}
	NDBusStateTools::getInstance()->updateNMState();

	if (iAmConnecting && NDBusStateTools::getInstance()->isDisconnected()) {
		stopTimer();
		emit disconnect();
	} else if (iAmConnecting && NDBusStateTools::getInstance()->isConnected()) {
		stopTimer();
		emit connected();
	} else if (NDBusStateTools::getInstance()->isConnecting()) {
		iAmConnecting = true;
	}
        //NDBusStateTools::getInstance()->isConnecting();
//	if (!NDBusStateTools::getInstance()->isConnecting())
		
}
