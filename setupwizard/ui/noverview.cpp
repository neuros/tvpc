#include "noverview.h"
#include <QDesktopWidget>

NOverView::NOverView(QDialog *parent)
	:QDialog(parent)
{
	setupUi(this);
}

NOverView::~NOverView()
{

}

void NOverView::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit destroyed();
		break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		emit networkConfigQuery(this);
		break;
	default:
		break;
	}

	e->ignore();
}
