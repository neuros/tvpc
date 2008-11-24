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

public slots:
	void timeOut();

private:
	void setupConnections();
private:
	QTimer *timer;
	int cnt;
};

#endif /* _NCONNECTING_H__ */
