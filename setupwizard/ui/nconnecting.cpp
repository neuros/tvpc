#include "nconnecting.h"
NConnectingForm::NConnectingForm(QWidget *parent)
	:QWidget(parent)
{
	timer = new QTimer(this);
	timer->setInterval(1000);
	timer->start();
	cnt = 0;
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
	if (cnt < 3) {
		cnt ++;
		connectLabel->setText(connectLabel->text() + ".");
	} else {
		cnt = 0;
		connectLabel->setText(connectLabel->text().left(connectLabel->text().length() - 3));
	}
}
