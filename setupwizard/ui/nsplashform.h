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
	void onCreateOverViewDlg(QDialog *);
	void onCreateWireConfigQueryDlg(QDialog *);
	void onCreateWirelessConfigQueryDlg(QDialog *);
	void onCreateInsertLanDlg(QDialog *);
protected:
	void keyPressEvent(QKeyEvent *);

private:
	QDialog *selectMode;
	QDialog *overView;
	QDialog *wireQuery;
	QDialog *wirelessQuery;
	QDialog *insertLan;
};
#endif /* _NSPlASHFORM_H__ */
