#include "nselectipmethod.h"

NSelectIPMethodForm::NSelectIPMethodForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

NSelectIPMethodForm::~NSelectIPMethodForm()
{

}

void NSelectIPMethodForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
		break;
	default:
		break;
	}

	e->ignore();
}
