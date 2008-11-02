#include "nwireconfigquery.h"

NWireConfigQueryForm::NWireConfigQueryForm(QWidget *parent)
	:QWidget(parent)
{
	setupUi(this);
}

NWireConfigQueryForm::~NWireConfigQueryForm()
{

}

void NWireConfigQueryForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
		break;
	case Qt::Key_Enter:
	case Qt::Key_Right:
		if (configqurylist->currentRow() == 0) {
		} else if (configqurylist->currentRow() == 1) {
			emit createNetworkListForm(this);
		}
		break;
	default:
		break;
	}

	e->ignore();
}
