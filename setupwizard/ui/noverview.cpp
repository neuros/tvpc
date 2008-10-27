#include "noverview.h"

NOverView::NOverView(QDialog *parent)
	:QDialog(parent)
{
	setupUi(this);
}

void NOverView::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		close();
		emit destroyed(this);
		break;
	default:
		break;
	}

	e->ignore();
}
