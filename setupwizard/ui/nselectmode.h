#ifndef _NSELECT_MODE_H__
#define _NSELECT_MODE_H__
#include "ui_nselectmode.h"
#include <QKeyEvent>

class NSelectMode : public QDialog, private Ui::NSelectModeDlg
{
public:
	NSelectMode(QDialog *parent = 0);
	~NSelectMode();
protected:
	void keyPressEvent(QKeyEvent *);
private:
	QDialog *overViewDlg;
};
#endif /* _NSELECT_MODE_H__ */
