#include "nsplashform.h"
#include "nselectmode.h"
#include "noverview.h"
#include "nwireconfigquery.h"
#include "nwirelessconfigquery.h"
#include "ninsertlan.h"

NSplashForm::NSplashForm(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	selectMode = NULL;
	overView = NULL;
	wireQuery = NULL;
	wirelessQuery = NULL;
	insertLan = NULL;
}

NSplashForm::~NSplashForm()
{
 	if (selectMode)
 		delete selectMode;
 	if (overView)
 		delete overView;
 	if (wireQuery)
 		delete wireQuery;
 	if (wirelessQuery)
 		delete wirelessQuery;
 	if (insertLan)
 		delete insertLan;
}

void NSplashForm::onCreateWireConfigQueryDlg(QDialog *dlg)
{
	if (wireQuery == NULL) {
		wireQuery = new NWireConfigQuery(dlg);
	}

	if (wireQuery) {
		wireQuery->resize(QApplication::desktop()->size());
		wireQuery->exec();
	}
}

void NSplashForm::onCreateWirelessConfigQueryDlg(QDialog *dlg)
{
	if (wirelessQuery == NULL) {
		wirelessQuery = new NWirelessConfigQuery(dlg);
		connect(wirelessQuery, SIGNAL(createInserLanDlg(QDialog *)),
				this, SLOT(onCreateInsertLanDlg(QDialog *)));
	}

	if (wirelessQuery) {
		wirelessQuery->resize(QApplication::desktop()->size());
		wirelessQuery->exec();
	}
}

void NSplashForm::onCreateOverViewDlg(QDialog *dlg)
{
	if (overView == NULL) {
		overView = new NOverView(dlg);

		connect(overView, SIGNAL(createWireConfigQueryDlg(QDialog *)),
				this, SLOT(onCreateWireConfigQueryDlg(QDialog *)));
		connect(overView, SIGNAL(createWirelessConfigQueryDlg(QDialog *)),
				this, SLOT(onCreateWirelessConfigQueryDlg(QDialog *)));
	}

	if (overView) {
		overView->resize(QApplication::desktop()->size());
		overView->exec();
	}
}

void NSplashForm::onCreateInsertLanDlg(QDialog *dlg)
{
	if (insertLan == NULL) {
		insertLan = new NInsertLAN(dlg);
	}
	if (insertLan) {
		insertLan->resize(QApplication::desktop()->size());
		insertLan->exec();
	}

}

void NSplashForm::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Right:
	case Qt::Key_Enter:
		if (selectMode == NULL) {
			selectMode = new NSelectMode();
			connect(selectMode, SIGNAL(createOverViewDlg(QDialog *)),
					this, SLOT(onCreateOverViewDlg(QDialog *)));
		}
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
