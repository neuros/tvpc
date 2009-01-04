#ifndef _NCONNECTING_H__
#define _NCONNECTING_H__
#include "ui_nconnecting.h"
#include <QTimer>

class NConnectingForm : public QWidget, private Ui::NConnectingForm
{
	Q_OBJECT
public:
	NConnectingForm(QWidget *parent = 0);
	~NConnectingForm();

	void stopTimer();
	void startTimer();
public slots:
	void timeOut();
	void on_stopBtn_clicked();
signals:
	void stopConnecting(QWidget *);

	void connected();
	void disconnected();
private:
	void setupConnections();
private:
	QTimer *timer;
	int cnt;

	bool iAmConnecting;
};

#endif /* _NCONNECTING_H__ */
