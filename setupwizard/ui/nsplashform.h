#ifndef _NSPlASHFORM_H__
#include "ui_nsplashform.h"
#include <QtGui>

class NSplashForm : public QWidget, private Ui::nsplashForm
{
	Q_OBJECT

public:
	NSplashForm(QWidget *parent = 0);
	~NSplashForm();
protected:
	void keyPressEvent(QKeyEvent *);

private:
	QDialog *selectMode;
};
#endif /* _NSPlASHFORM_H__ */
