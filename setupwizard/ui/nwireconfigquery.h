#ifndef _NWIRE_CONFIG_QUERY_H__
#define _NWIRE_CONFIG_QUERY_H__
#include "ui_nwireconfigquery.h"
#include <QKeyEvent>

class NWireConfigQueryForm : public QWidget, private Ui::NWireConfigQueryForm
{
	Q_OBJECT

public:
	NWireConfigQueryForm(QWidget *parent = 0);
	~NWireConfigQueryForm();
public slots:
signals:
	void quit(QWidget *);
	void createNetworkListForm(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);
};

#endif /* _NWIRE_CONFIG_QUERY_H__ */
