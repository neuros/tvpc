#ifndef _NSELECT_MODE_H__
#define _NSELECT_MODE_H__
#include "ui_nselectmode.h"
#include <QKeyEvent>

class NSelectMode : public QDialog, private Ui::NSelectModeDlg
{
	Q_OBJECT

public:
	NSelectMode(QDialog *parent = 0);
	~NSelectMode();
public slots:
signals:
	void createOverViewDlg(QDialog *);

protected:
	void keyPressEvent(QKeyEvent *);
};
#endif /* _NSELECT_MODE_H__ */
