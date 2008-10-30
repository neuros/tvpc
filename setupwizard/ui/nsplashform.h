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
	void createOverViewDlg(QDialog *);
	void createWireConfigQueryDlg(QDialog *);
	void createWirelessConfigQueryDlg(QDialog *);
	void createInsertLanDlg(QDialog *);
	void createNetworkListForm(QWidget *);

	void onNetworkConfigQuery(QDialog *);
	void onInsertLan(QDialog *);

	void onSelectModeQuit();
	void onOverViewQuit();
	void onWirelessQueryQuit();
	void onInsertLanQuit();
	void onNetworkListQuit();
protected:
	void keyPressEvent(QKeyEvent *);

private:
	bool isLanDetected(void) const;

private:
	QDialog *selectMode;
	QDialog *overView;
	QDialog *wireQuery;
	QDialog *wirelessQuery;
	QDialog *insertLan;

	QWidget *networkList;
};
#endif /* _NSPlASHFORM_H__ */
