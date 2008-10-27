#include "nselectmode.h"
#include "noverview.h"
#include <QDesktopWidget>

NSelectMode::NSelectMode(QDialog *parent)
	: QDialog(parent)
{
	setupUi(this);

	overViewDlg = NULL;
}

NSelectMode::~NSelectMode()
{
	if (overViewDlg)
		delete overViewDlg;
}

void NSelectMode::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		close();
		emit destroyed(this);
    break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (selectModeList->currentRow() == 0) {
			if (overViewDlg == NULL)
				overViewDlg = new NOverView();
			if (overViewDlg) {
				overViewDlg->resize(QApplication::desktop()->size());
				overViewDlg->exec();
			}
		}
		break;
	default:
		break;
	}
	e->ignore();
}
