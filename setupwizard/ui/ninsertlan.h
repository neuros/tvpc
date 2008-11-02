#ifndef _NINSERT_LAN_H__
#define _NINSERT_LAN_H__
#include "ui_ninsertlan.h"
#include <QKeyEvent>

class NInsertLANForm : public QWidget, private Ui::NInsertLANForm
{
	Q_OBJECT

public:
	NInsertLANForm(QWidget *parent = 0);
	~NInsertLANForm();
signals:
	void checkLanInserted(QWidget *);
	void createNetworkListForm(QWidget *);
	void quit(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);
};
#endif /* _NINSERT_LAN_H__ */
