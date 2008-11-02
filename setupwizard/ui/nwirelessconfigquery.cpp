#include "nwirelessconfigquery.h"
#include "ninsertlan.h"
#include <QDesktopWidget>

NWirelessConfigQueryForm::NWirelessConfigQueryForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

NWirelessConfigQueryForm::~NWirelessConfigQueryForm()
{

}

void NWirelessConfigQueryForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
		break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (selectList->currentRow() == 0) {
			emit createNetworkListForm(this);
		} else if (selectList->currentRow() == 1) {
			emit createInserLanForm(this);
		}
		break;
	default:
		break;
	}

	e->ignore();
}
