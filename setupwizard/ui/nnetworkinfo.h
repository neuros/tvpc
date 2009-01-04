#ifndef _NNETWORK_INFO_H__
#define _NNETWORK_INFO_H__
#include "ui_nnetworkinfo.h"
#include "NDBusNetwork.h"
#include <QKeyEvent>
class NNetworkInfoForm : public QWidget, private Ui::NNetworkInfoForm
{
	Q_OBJECT
public:
	NNetworkInfoForm(QWidget *parent = 0);
	~NNetworkInfoForm();
public slots:
	void updateNetworkInfo(NDBusNetwork *net);
signals:
	void quit(QWidget *);

protected:
	void keyPressEvent(QKeyEvent *);
};
#endif /* _NNETWORK_INFO_H__ */
