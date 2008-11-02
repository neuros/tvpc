#ifndef _NOVER_VIEW_H__
#define _NOVER_VIEW_H__
#include "ui_noverview.h"
#include <QKeyEvent>

class NOverViewForm : public QWidget, private Ui::NOverViewForm
{
	Q_OBJECT

public:
	NOverViewForm(QWidget *parent = 0);
	~NOverViewForm();
public slots:
signals:
	void createNetworkConfigQueryForm(QWidget *);
	void quit(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);

};

#endif /* _NOVER_VIEW_H__ */
