#ifndef _NINPUT_SSID_PASSWORD_H__
#define _NINPUT_SSID_PASSWORD_H__
#include "ui_ninputssidpassword.h"
#include <QKeyEvent>
#include "NDBusNetwork.h"


class NInputSSIDPasswordForm : public QWidget, private Ui::NInputSSIDPasswordForm
{
	Q_OBJECT
public:
	NInputSSIDPasswordForm(QWidget *parent = 0);
	~NInputSSIDPasswordForm();
	void setNetwork(NDBusNetwork *);

	const QString password() const;
	void clearPassword();
protected:
	bool eventFilter(QObject *obj, QEvent *event);

public slots:
signals:
	void quit(QWidget *);
	void createConnect2NetworkForm(QWidget *, NDBusNetwork *);

private:
	NDBusNetwork *_net;
};

#endif /* _NINPUT_SSID_PASSWORD_H__ */
