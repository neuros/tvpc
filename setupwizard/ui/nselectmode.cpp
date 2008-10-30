#include "nselectmode.h"
#include <QDesktopWidget>

NSelectMode::NSelectMode(QDialog *parent)
	: QDialog(parent)
{
	setupUi(this);

}

NSelectMode::~NSelectMode()
{

}

void NSelectMode::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit destroyed();
    break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (selectModeList->currentRow() == 0) {
			emit createOverViewDlg(this);
		}
		break;
	default:
		break;
	}
	e->ignore();
}
