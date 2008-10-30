#ifndef _NNETWORK_LIST_H__
#define _NNETWORK_LIST_H__
#include "ui_nnetworklist.h"
#include "dbus/NNetwork.h"
#include "dbus/NDevice.h"
#include <QKeyEvent>

class NNetworkSSIDList : public QWidget , private Ui::NNetworkListWidget
{
	Q_OBJECT

public:
	NNetworkSSIDList(QWidget *parent = 0);
	~NNetworkSSIDList();

public slots:
	void updateNetworkList(const NNetworkList &list);
	void updateNetworkList(NDevice *dev);
	void updateSignalStrength(NNetwork *net);

protected:
	void keyPressEvent(QKeyEvent *);
};

#endif /* _NNETWORK_LIST_H__ */
