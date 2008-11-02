#include "noverview.h"
#include <QDesktopWidget>

NOverViewForm::NOverViewForm(QWidget *parent)
	:QWidget(parent)
{
	setupUi(this);
}

NOverViewForm::~NOverViewForm()
{

}

void NOverViewForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
		break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		emit createNetworkConfigQueryForm(this);
		break;
	default:
		break;
	}

	e->ignore();
}
