#include "nsplashform.h"

NSplashForm::NSplashForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

NSplashForm::~NSplashForm()
{

}

void NSplashForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Right:
	case Qt::Key_Enter:
		emit createSelectModeForm(this);
		break;
	default:
		break;
	}

	e->ignore();
}
