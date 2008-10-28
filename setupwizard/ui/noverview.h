#ifndef _NOVER_VIEW_H__
#define _NOVER_VIEW_H__
#include "ui_noverview.h"
#include <QKeyEvent>

class NOverView : public QDialog, private Ui::NOverViewDlg
{
	Q_OBJECT

public:
	NOverView(QDialog *parent = 0);
	~NOverView();
public slots:
signals:
	void createWireConfigQueryDlg(QDialog *);
	void createWirelessConfigQueryDlg(QDialog *);

protected:
	void keyPressEvent(QKeyEvent *);
private:
	bool isLanDetected(void) const;

};

#endif /* _NOVER_VIEW_H__ */
