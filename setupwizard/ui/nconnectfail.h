#ifndef _NCONNECT_FAIL_H__
#define _NCONNECT_FAIL_H__
#include "ui_nconnectfail.h"
#include "NDBusNetwork.h"
#include <QKeyEvent>

class NConnectFailForm : public QWidget, private Ui::NConnectFailForm
{
	Q_OBJECT
public:
	NConnectFailForm(NDBusNetwork *net, QWidget *parent = 0);
	~NConnectFailForm();

public slots:
signals:
	void quit(QWidget *);
	void tryAgain(QWidget *, NDBusNetwork *);
	void gotoNext(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);
private:
	NDBusNetwork *_net;
};

#endif //_NCONNECT_FAIL_H__
