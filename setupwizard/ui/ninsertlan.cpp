#include "ninsertlan.h"

NInsertLAN::NInsertLAN(QDialog *parent)
	:QDialog(parent)
{
	setupUi(this);
}

NInsertLAN::~NInsertLAN()
{

}

void NInsertLAN::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit destroyed();
		break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (selectList->currentRow() == 0) {
			emit checkLanInserted(this);
		}
		break;
	default:
		break;
	}

	e->ignore();
}
