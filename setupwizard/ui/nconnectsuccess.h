#ifndef _NCONNECTION_SUCCESS_H__
#define _NCONNECTION_SUCCESS_H__
#include "ui_nconnectsuccess.h"
#include <QKeyEvent>

class NConnectSuccessForm : public QWidget, private Ui::NConnectSuccessForm
{
	Q_OBJECT
public:
	NConnectSuccessForm(QWidget *parent = 0);
	~NConnectSuccessForm();

public slots:
	void on_continueBtn_clicked();
signals:
	void quit(QWidget *);
	void gotoNextStep(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);
};

#endif // _NCONNECTION_SUCCESS_H__
