#ifndef _NDBUSCOMMON_H__
#define _NDBUSCOMMON_H__
#include <NetworkManager.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <QStringList>
#include <QString>

class NNetworkProperty
{
	friend class NDBusDeviceInterface;
public:
	NNetworkProperty() {
		op = NULL;
		iface = NULL;
		type = DEVICE_TYPE_UNKNOWN;
		udi = NULL;
		active = FALSE;
		ip4_address = NULL;
		broadcast = NULL;
		subnetmask = NULL;
		hw_addr = NULL;
		route = NULL;
		primary_dns = NULL;
		secondary_dns = NULL;
		mode = 0;
		strength = -1;
		active_network_path = NULL;
		link_active = FALSE;
		speed = 0;
		caps = NM_DEVICE_CAP_NONE;
		type_caps = NM_DEVICE_CAP_NONE;
		networks = NULL;
		num_networks = 0;
		act_stage = NM_ACT_STAGE_UNKNOWN;
	}

	const QString networkPath() const {
		return op;
	}
	const QString deviceName() const {
		return iface;
	}
	const QString ip4Address() const {
		return ip4_address;
	}
	const QString subNetmask() const {
		return subnetmask;
	}
	const QString broadcastAddress() const {
		return broadcast;
	}
	const QString hardwareAddress() const {
		return hw_addr;
	}
	const QString routeAddress() const {
		return route;
	}
	const QString primaryDNS() const {
		return primary_dns;
	}
	const QString secondaryDNS() const {
		return secondary_dns;
	}
	const QString activeNetworkPath() const {
		return active_network_path;
	}
	NMDeviceType deviceType() const {
		return type;
	}
	bool linkActive() const {
		return link_active;
	}
	bool deviceActive() const {
		return active;
	}
	NMActStage deviceActStage() const {
		return act_stage;
	}
	long wirelessOperationMode() const {
		return mode;
	}
	long wirelessSignalStrength() const {
		return strength;
	}
	long networkSpeed() const {
		return speed;
	}
	long deviceCapability() const {
		return caps;
	}
	long wirelessCapability() const {
		return type_caps;
	}

	const QStringList wirelessNetworks() const {
		QStringList list;
		for (int i=0; i< num_networks; i++)
			list << networks[i];
		return list;
	}

private:
	const char *op;
	const char *iface;
	const char *udi;
	const char *ip4_address;
	const char *subnetmask;
	const char *broadcast;
	const char *hw_addr;
	const char *route;
	const char *primary_dns;
	const char *secondary_dns;
	const char *active_network_path;
	NMDeviceType 	type;
	dbus_bool_t	 	link_active;
	dbus_bool_t 	active;
	NMActStage 		act_stage;
	dbus_uint32_t 	mode;
	dbus_int32_t 	strength;
	dbus_int32_t 	speed;
	dbus_uint32_t 	caps;
	dbus_uint32_t	 type_caps;
	char **	networks;
	int	num_networks;
};

class NWirelessDetailInfo
{
public:
	friend class NDBusNetworkInterface;

	NWirelessDetailInfo() {
		op = NULL;
		essid = NULL;
		hw_addr = NULL;
		strength = -1;
		freq = 0;
		rate = 0;
		capabilities = NM_802_11_CAP_NONE;
		mode = 0;
		broadcast = TRUE;
	}
	const QString networkPath() const {
		return op;
	}
	const QString ESSID() const {
		return essid;
	}
	const QString hardwareAddress() const {
		return hw_addr;
	}
	int signalStrength() const {
		return strength;
	}
	double frequency() const {
		return freq;
	}
	int bitRate() const {
		return rate;
	}
	long capability() const {
		return capabilities;
	}
	long operationMode() const {
		return mode;
	}
	bool isBroadcast() const {
		return !(broadcast == FALSE);
	}

private:
	const char *		op;
	const char *		essid;
	const char *		hw_addr;
	dbus_int32_t		strength;
	double 			freq;
	dbus_int32_t		rate;
	dbus_int32_t		capabilities;
	dbus_uint32_t		mode;
	gboolean			broadcast;
};


#endif /* _NDBUSCOMMON_H__ */
