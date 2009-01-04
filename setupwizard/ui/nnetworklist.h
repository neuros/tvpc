#ifndef _NNETWORK_LIST_H__
#define _NNETWORK_LIST_H__
#include "ui_nnetworklist.h"
#include "NDBusNetwork.h"
#include "NDBusDevice.h"

#include <QKeyEvent>

class NNetworkSSIDListForm : public QWidget , private Ui::NNetworkListForm
{
	Q_OBJECT

public:
	NNetworkSSIDListForm(QWidget *parent = 0);
	~NNetworkSSIDListForm();

public slots:
	void updateNetworkList(const NDBusNetworkList &list);
	void updateNetworkList(NDBusDevice *dev);
	void updateSignalStrength(NDBusNetwork *net);
signals:
	void quit(QWidget *);
	void createDeviceInfoForm(QWidget *);
	void createNetworkInfoForm(QWidget *, NDBusNetwork *);
	void createSelectIPMethodForm(QWidget *, NDBusNetwork *);
	void createInputSSIDPasswordForm(QWidget *, NDBusNetwork *);
protected:
	void keyPressEvent(QKeyEvent *);

private:
	NDBusNetworkList _list;
};

#endif /* _NNETWORK_LIST_H__ */
