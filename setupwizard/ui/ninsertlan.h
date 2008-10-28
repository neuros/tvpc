#ifndef _NINSERT_LAN_H__
#define _NINSERT_LAN_H__
#include "ui_ninsertlan.h"
#include <QKeyEvent>

class NInsertLAN : public QDialog, private Ui::NInsertLANDlg
{
	Q_OBJECT

public:
	NInsertLAN(QDialog *parent = 0);
	~NInsertLAN();
signals:

protected:
	void keyPressEvent(QKeyEvent *);
};
#endif /* _NINSERT_LAN_H__ */
