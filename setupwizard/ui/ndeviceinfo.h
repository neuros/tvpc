#ifndef _NDEVICE_INFORMATION_H__
#define _NDEVICE_INFORMATION_H__
#include "ui_ndeviceinfo.h"
#include "NDBusTools.h"
#include <QKeyEvent>
class NDeviceInformation : public QWidget, private Ui::NDeviceInfoForm
{
	Q_OBJECT
public:
	NDeviceInformation(QWidget *parent = 0);
	~NDeviceInformation();

public slots:
	void updateDeviceInfo(NDBusDevice *);
signals:
	void quit(QWidget *);
protected:
	void keyPressEvent(QKeyEvent *);
};

#endif /* _NDEVICE_INFORMATION_H__ */
