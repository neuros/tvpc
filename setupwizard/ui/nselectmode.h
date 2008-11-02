#ifndef _NSELECT_MODE_H__
#define _NSELECT_MODE_H__
#include "ui_nselectmode.h"
#include <QKeyEvent>

class NSelectModeForm : public QWidget, private Ui::NSelectModeForm
{
	Q_OBJECT

public:
	NSelectModeForm(QWidget *parent = 0);
	~NSelectModeForm();
public slots:
signals:
	void createOverViewForm(QWidget *);
	void quit(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);
};
#endif /* _NSELECT_MODE_H__ */
