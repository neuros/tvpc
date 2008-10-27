#include <QApplication>
#include <QtGui>
#include "nsplashform.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	NSplashForm form;

	form.resize(300, 300);
	form.setGeometry((QApplication::desktop()->size().width() - 300) /2,
					 (QApplication::desktop()->size().height() - 300)/2, 300, 300);

	form.show();

	return app.exec();
}

