#ifndef _SELECT_IP_METHOD_H__
#define _SELECT_IP_METHOD_H__
#include "ui_nselectipmethod.h"
#include <QKeyEvent>

class NSelectIPMethodForm : public QWidget, private Ui::NSelectIPMethodForm
{
	Q_OBJECT
public:
	NSelectIPMethodForm(QWidget *parent = 0);
	~NSelectIPMethodForm();
public slots:
signals:
	void quit(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);
};

#endif /* _SELECT_IP_METHOD_H__ */
