#include "nsplashform.h"
#include "nselectmode.h"
NSplashForm::NSplashForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	selectMode = NULL;
}

NSplashForm::~NSplashForm()
{
	if (selectMode)
		delete selectMode;
}

void NSplashForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (selectMode == NULL)
			selectMode = new NSelectMode();
		if (selectMode) {
			selectMode->resize(QApplication::desktop()->size());
			selectMode->exec();
		}

		break;
	default:
		break;
	}

	e->ignore();
}
