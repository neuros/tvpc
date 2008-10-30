#ifndef _NWIRELESS_CONFIG_QUERY_H__
#define _NWIRELESS_CONFIG_QUERY_H__
#include "ui_nwirelessconfigquery.h"
#include <QKeyEvent>

class NWirelessConfigQuery : public QDialog, private Ui::NWirelessConfigQueryDlg
{
	Q_OBJECT

public:
	NWirelessConfigQuery(QDialog *parent = 0);
	~NWirelessConfigQuery();
public slots:

signals:
	void createInserLanDlg(QDialog *);
	void createNetworkListForm(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);
};

#endif /* _NWIRELESS_CONFIG_QUERY_H__ */
