#include "nselectmode.h"
#include <QDesktopWidget>

NSelectModeForm::NSelectModeForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

}

NSelectModeForm::~NSelectModeForm()
{

}

void NSelectModeForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
    break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (selectModeList->currentRow() == 0) {
			emit createOverViewForm(this);
		}
		break;
	default:
		break;
	}
	e->ignore();
}
