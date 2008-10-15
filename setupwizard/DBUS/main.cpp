#include <QApplication>
#include <QDebug>
#include "NDBusConnection.h"
#include "NDBusDeviceInterface.h"

static void showNetworkInfo(const NDBusDeviceInterface &iface)
{
	NNetworkProperty property;
	NWirelessDetailInfo info;

	const char *state_string = NULL;
	const char *enc_string = NULL;
	QStringList devicesList = iface.getDevices();

	qDebug() << "\nNetworkManager Tool\n";

	switch (iface.getNetworkManagerState())
	{
		case NM_STATE_ASLEEP:
			state_string = "asleep";
			break;

		case NM_STATE_CONNECTING:
			state_string = "connecting";
			break;

		case NM_STATE_CONNECTED:
			state_string = "connected";
			break;

		case NM_STATE_DISCONNECTED:
			state_string = "disconnected";
			break;

		case NM_STATE_UNKNOWN:
		default:
			state_string = "unknown";
			break;
	}

	qDebug() << "State: "<< state_string << "\n";

	for (int i=0; i<devicesList.count(); i++) {
		property = iface.getDeviceDetail(devicesList.at(i));

		qDebug() << "- Device:"<< property.deviceName().toAscii().data() << "----------------------------------------------------------------";
		qDebug() << "  NM Path:          " << property.networkPath().toAscii().data();
		
		if (property.deviceType() == DEVICE_TYPE_802_11_WIRELESS)
			qDebug() << "  Type:              802.11 Wireless";
		else if (property.deviceType() == DEVICE_TYPE_802_3_ETHERNET)
			qDebug() << "  Type:              Wired";

		qDebug() << "  Driver:           " << iface.getDriverName(devicesList.at(i)).toAscii().data();

		if (property.deviceActive() == true)
			qDebug() << "  Active:            yes";
		else
			qDebug() << "  Active:            no";

		qDebug() << "  HW Address:       "<< property.hardwareAddress().toAscii().data();
		qDebug() << "\n  Capabilities:";

		if (property.deviceCapability()& NM_DEVICE_CAP_NM_SUPPORTED)
			qDebug() << "    Supported:       yes";
		else
			qDebug() << "    Supported:        no";

		if (property.deviceCapability() & NM_DEVICE_CAP_CARRIER_DETECT)
			qDebug() << "    Carrier Detect:  yes";

		if (property.networkSpeed())
			qDebug() << "    Speed:          " << property.networkSpeed() <<"Mb/s";

		if (property.deviceType() == DEVICE_TYPE_802_11_WIRELESS) {
			qDebug() <<"\n  Wireless Settings";

			if (property.wirelessCapability() & NM_DEVICE_CAP_WIRELESS_SCAN)
				qDebug() << "    Scanning:        yes";

			if (property.wirelessCapability() & NM_802_11_CAP_PROTO_WEP)
				qDebug() << "    WEP Encryption:  yes";
			if (property.wirelessCapability() & NM_802_11_CAP_PROTO_WPA)
				qDebug() << "    WPA Encryption:  yes";
			if (property.wirelessCapability() & NM_802_11_CAP_PROTO_WPA2)
				qDebug() << "    WPA2 Encryption: yes";

			qDebug() << "\n  Wireless Networks (* = Current Network)";
			for (int i =0; i<property.wirelessNetworks().count(); i++) {
				info = iface.getWirelessNetworkInfo(property.wirelessNetworks().at(i));

                 if (info.capability() & NM_802_11_CAP_PROTO_WEP)
                     enc_string = "WEP";
                 if (info.capability()  & NM_802_11_CAP_PROTO_WPA)
                     enc_string = "WPA";
                 if (info.capability()  & NM_802_11_CAP_PROTO_WPA2)
                    enc_string = "WPA2";
                 if (info.capability()  & NM_802_11_CAP_KEY_MGMT_802_1X)
                     enc_string ="Enterprise";

				qDebug() <<((property.wirelessNetworks().at(i) == property.activeNetworkPath() ? "    *":"     ") +
					info.ESSID() +":       ").toAscii().data() << (((info.operationMode() == IW_MODE_INFRA) ? "Infrastructure" : "Ad-Hoc") + 
					QString(" Mode, Freq")).toAscii().data() <<info.frequency() <<"MHz, Rate" << info.bitRate() << "Mb/s, Strength"<<
					info.signalStrength() <<"%," << ((enc_string == NULL ? "" : "Encrypted (") + QString(enc_string) + ")").toAscii().data();

			}
		}
		else if (property.deviceType() == DEVICE_TYPE_802_3_ETHERNET)
		{
			qDebug() <<"\n  Wired Settings";
			if (property.linkActive())
				qDebug() << "    Hardware Link:  yes";
			else
				qDebug() << "    Hardware Link:   no";
		}

		if (property.deviceActive())
		{
			qDebug() << "\n  IP Settings:";
			qDebug() << "    IP Address:     " << property.ip4Address().toAscii().data();
			qDebug() << "    Subnet Mask:    " << property.subNetmask().toAscii().data();
			qDebug() << "    Broadcast:      " << property.broadcastAddress().toAscii().data();
			qDebug() << "    Gateway:        " << property.routeAddress().toAscii().data();
			qDebug() << "    Primary DNS:    " << property.primaryDNS().toAscii().data();
			qDebug() << "    Secondary DNS:  " << property.secondaryDNS().toAscii().data();
		}
		qDebug() <<"\n";
	}
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	if (NDBusConnection::systemBus().isConnected() ==  false) {
			qDebug() << "Cannot connect to systemBus\n";
			return 0;
	}

	NDBusDeviceInterface iface(NDBusConnection::systemBus());
	if (iface.isValid()) {
		showNetworkInfo(iface);
	}
	return 0;
}
