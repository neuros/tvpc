#ifndef _NWIRELESS_CONFIG_QUERY_H__
#define _NWIRELESS_CONFIG_QUERY_H__
#include "ui_nwirelessconfigquery.h"
#include <QKeyEvent>

class NWirelessConfigQueryForm : public QWidget, private Ui::NWirelessConfigQueryForm
{
	Q_OBJECT

public:
	NWirelessConfigQueryForm(QWidget *parent = 0);
	~NWirelessConfigQueryForm();
public slots:

signals:
	void createInserLanForm(QWidget *);
	void createNetworkListForm(QWidget *);

	void quit(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);
};

#endif /* _NWIRELESS_CONFIG_QUERY_H__ */
