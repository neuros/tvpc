#include "ninputssidpassword.h"
#include <QDebug>

NInputSSIDPasswordForm::NInputSSIDPasswordForm(QWidget *parent)
	: QWidget(parent), _net(NULL)
{
	setupUi(this);
	passwordEdit->installEventFilter(this);
}

NInputSSIDPasswordForm::~NInputSSIDPasswordForm()
{

}

void NInputSSIDPasswordForm::setNetwork(NDBusNetwork *net)
{
	_net = net;
}

bool NInputSSIDPasswordForm::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) {

		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		switch (keyEvent->key()) {
		case Qt::Key_Left:
			if (passwordEdit->cursorPosition() ==0)
                emit quit(this);
			break;
		case Qt::Key_Right:
		case Qt::Key_Enter:
			if (passwordEdit->cursorPosition() >= passwordEdit->text().length()) {
				emit createConnect2NetworkForm(this, _net);
			}
			break;
		default:
			break;
		}
	}

	return QObject::eventFilter(obj, event);
}

const QString NInputSSIDPasswordForm::password() const
{
	return passwordEdit->text();
}

void NInputSSIDPasswordForm::clearPassword()
{
	passwordEdit->clear();
}
