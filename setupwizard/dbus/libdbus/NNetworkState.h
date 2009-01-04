#ifndef _NNETWORK_STATE_H__
#define _NNETWORK_STATE_H__
#include "NDBusConnection.h"
#include <QObject>

class NNetworkTools;

class NNetworkState : public QObject
{
	Q_OBJECT
public:
	NNetworkState  ();
	~NNetworkState ();

	static NNetworkState* getInstance(void);

	bool isNetworkManagerRunning(void);
	bool isSleeping(void);
	bool isConnecting(void);
	bool isConnected(void);
	bool isDisconnected(void);
	bool isWirelessEnabled(void);
	bool isDialupActive(void);
	bool isWaitingForKey(void);

	void setOfflineMode (bool);

	void updateWirelessState(bool);
	void setWirelessState(bool);

	void setDialupState(bool);
	void setState(NMState);
	void setWaitingForKey(bool);

	void updateNetworkState(void);
	NMState  getConnectionState(void);

	void push(NNetworkTools*);

	const QString stateToString() const;
 	signals:
	void wirelessStateChanged(void);
	void connectionStateChanged (void);

 	void connecting();
 	void connected();
 	void disconnected();
 	void sleeping();

private:
	NNetworkTools* _ctx;
	static NNetworkState* _instance;
	/* connection state */
	NMState _connectionState;
	bool    _wirelessEnabled;
	bool    _dialupActive;
	bool    _waitingForKey;

};

#endif
