#include "nconnectsuccess.h"

NConnectSuccessForm::NConnectSuccessForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

NConnectSuccessForm::~NConnectSuccessForm()
{

}

void NConnectSuccessForm::on_continueBtn_clicked()
{
	emit gotoNextStep(this);
	close();
}

void NConnectSuccessForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
		break;
	case Qt::Key_Right:
		on_continueBtn_clicked();
		break;
	default:
		break;
	}

	e->ignore();
}
