#include "ninsertlan.h"

NInsertLANForm::NInsertLANForm(QWidget *parent)
	:QWidget(parent)
{
	setupUi(this);
}

NInsertLANForm::~NInsertLANForm()
{

}

void NInsertLANForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
		break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (selectlist->currentRow() == 0) {
			emit checkLanInserted(this);
		} else if (selectlist->currentRow() == 1) {
			emit createNetworkListForm(this);
		}
		break;
	default:
		break;
	}

	e->ignore();
}
