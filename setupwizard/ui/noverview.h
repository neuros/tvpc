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
	void networkConfigQuery(QDialog *);
protected:
	void keyPressEvent(QKeyEvent *);

};

#endif /* _NOVER_VIEW_H__ */
