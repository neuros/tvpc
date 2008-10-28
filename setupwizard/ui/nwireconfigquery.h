#ifndef _NWIRE_CONFIG_QUERY_H__
#define _NWIRE_CONFIG_QUERY_H__
#include "ui_nwireconfigquery.h"
#include <QKeyEvent>

class NWireConfigQuery : public QDialog, private Ui::NWireConfigQueryDlg
{
	Q_OBJECT

public:
	NWireConfigQuery(QDialog *parent = 0);
	~NWireConfigQuery();
protected:
	void keyPressEvent(QKeyEvent *);
};

#endif /* _NWIRE_CONFIG_QUERY_H__ */
