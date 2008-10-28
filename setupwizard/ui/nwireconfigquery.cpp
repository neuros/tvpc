#include "nwireconfigquery.h"

NWireConfigQuery::NWireConfigQuery(QDialog *parent)
	:QDialog(parent)
{
	setupUi(this);
}

NWireConfigQuery::~NWireConfigQuery()
{

}

void NWireConfigQuery::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Left:
		close();
		break;
	default:
		break;
	}

	e->ignore();
}
