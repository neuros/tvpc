#include <QApplication>
#include <QtGui>
#include "nsetupwizardmanager.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	NSetupWizardManager::getInstance()->start();

	return app.exec();
}

