#ifndef _NSPlASHFORM_H__
#include "ui_nsplashform.h"
#include <QtGui>

class NSplashForm : public QWidget, private Ui::nsplashForm
{
	Q_OBJECT

public:
	NSplashForm(QWidget *parent = 0);
	~NSplashForm();

public slots:

signals:
	void createSelectModeForm(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);
};

#endif /* _NSPlASHFORM_H__ */
