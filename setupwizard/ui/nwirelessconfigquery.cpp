#include "nwirelessconfigquery.h"
#include "ninsertlan.h"
#include <QDesktopWidget>

NWirelessConfigQuery::NWirelessConfigQuery(QDialog *parent)
	: QDialog(parent)
{
	setupUi(this);
}

NWirelessConfigQuery::~NWirelessConfigQuery()
{

}

void NWirelessConfigQuery::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit destroyed();
		break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (selectList->currentRow() == 0) {
			emit createNetworkListForm(this);
		} else if (selectList->currentRow() == 1) {
			emit createInserLanDlg(this);
		}
		break;
	default:
		break;
	}

	e->ignore();
}
