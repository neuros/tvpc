#ifndef _NNETWORK_LIST_H__
#define _NNETWORK_LIST_H__
#include "ui_nnetworklist.h"
#include "dbus/NNetwork.h"
#include "dbus/NDevice.h"
#include <QKeyEvent>

class NNetworkSSIDListForm : public QWidget , private Ui::NNetworkListForm
{
	Q_OBJECT

public:
	NNetworkSSIDListForm(QWidget *parent = 0);
	~NNetworkSSIDListForm();

public slots:
	void updateNetworkList(const NNetworkList &list);
	void updateNetworkList(NDevice *dev);
	void updateSignalStrength(NNetwork *net);
signals:
	void quit(QWidget *);
	void createDeviceInfoForm(QWidget *);
	void createNetworkInfoForm(QWidget *, int);
protected:
	void keyPressEvent(QKeyEvent *);
};

#endif /* _NNETWORK_LIST_H__ */