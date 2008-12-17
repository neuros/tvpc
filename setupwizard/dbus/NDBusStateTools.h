#ifndef _NDBUS_STATE_TOOLS_H__
#define _NDBUS_STATE_TOOLS_H__
#include <QtDBus/QtDBus>
#include <NetworkManager.h>
#include <QObject>

class NDBusStateTools : QObject
{
	Q_OBJECT

public:
	NDBusStateTools();
	~NDBusStateTools();

	enum State {
		Sleep,
		Wake,
	};
	static NDBusStateTools *getInstance();

	bool isSleeping(void);
	bool isConnecting(void);
	bool isConnected(void);
	bool isDisconnected(void);

	bool isNetworkManagerRunning(void);

	const QString stateToString() const;

	bool switchState(NDBusStateTools::State);
	bool enableWireless(bool enable = true);
	bool getWirelessState();

	bool updateNMState();

	bool isSystemBusConnected();

private slots:
	void reply(const QDBusMessage&);
private:
	static NDBusStateTools *_tools_instance;

	NMState _connectionState;
};

#endif // _NDBUS_STATE_TOOLS_H__
