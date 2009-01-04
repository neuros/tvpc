#ifndef _NCONNECTING_H__
#define _NCONNECTING_H__
#include "ui_nconnecting.h"
#include "NDBusNetwork.h"
#include <QTimer>

class NConnectingForm : public QWidget, private Ui::NConnectingForm
{
	Q_OBJECT
public:
	NConnectingForm(NDBusNetwork *net, QWidget *parent = 0);
	~NConnectingForm();

	void setNetwork(NDBusNetwork *net);

	void stopTimer();
	void startTimer();
public slots:
	void timeOut();
	void on_stopBtn_clicked();
signals:
	void stopConnecting(QWidget *);

	void connected(NDBusNetwork *);
	void disconnected(NDBusNetwork *);
private:
	void setupConnections();
private:
	QTimer *timer;
	int cnt;

	bool iAmConnecting;
	NDBusNetwork *_net;
};

#endif /* _NCONNECTING_H__ */
