#include "nconnectfail.h"

NConnectFailForm::NConnectFailForm(NDBusNetwork *net, QWidget *parent)
	: QWidget(parent), _net(net)
{
	setupUi(this);
}

NConnectFailForm::~NConnectFailForm()
{

}

void NConnectFailForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		emit quit(this);
		break;
	case Qt::Key_Right:
	case Qt::Key_Enter:
		switch (listWidget->currentRow()) {
		case 0:
			emit tryAgain(this, _net);
			break;
		case 1:
			emit gotoNext(this);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	e->ignore();
}
