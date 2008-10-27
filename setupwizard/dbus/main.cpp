#include <QApplication>
#include "NNetworkTools.h"
#include <netlink/route/addr.h>
#define NM_RTNL_ADDR_NONE		0x0000
#define NM_RTNL_ADDR_ADDR		0x0001
#define NM_RTNL_ADDR_PTP_ADDR		0x0002
#define NM_RTNL_ADDR_NETMASK		0x0004
#define NM_RTNL_ADDR_BROADCAST	0x0008

#define NM_RTNL_ADDR_DEFAULT		(NM_RTNL_ADDR_ADDR | NM_RTNL_ADDR_NETMASK | NM_RTNL_ADDR_BROADCAST)
#define NM_RTNL_ADDR_PTP_DEFAULT	(NM_RTNL_ADDR_ADDR | NM_RTNL_ADDR_NETMASK | NM_RTNL_ADDR_PTP_ADDR)

struct nl_addr * nm_utils_ip4_addr_to_nl_addr (guint32 ip4_addr)
{
	struct nl_addr * nla = NULL;

	if (!(nla = nl_addr_alloc (sizeof (in_addr_t))))
		return NULL;
	nl_addr_set_family (nla, AF_INET);
	nl_addr_set_binary_addr (nla, &ip4_addr, sizeof (guint32));

	return nla;
}

static int ip4_addr_to_rtnl_local (guint32 ip4_address, struct rtnl_addr *addr)
{
	struct nl_addr * local = NULL;
	int err = 0;

	g_return_val_if_fail (addr != NULL, -1);

	local = nm_utils_ip4_addr_to_nl_addr (ip4_address);
	err = rtnl_addr_set_local (addr, local);
	nl_addr_put (local);

	return err;
}
static int ip4_addr_to_rtnl_peer (guint32 ip4_address, struct rtnl_addr *addr)
{
	struct nl_addr * peer = NULL;
	int err = 0;

	g_return_val_if_fail (addr != NULL, -1);

	peer = nm_utils_ip4_addr_to_nl_addr (ip4_address);
	err = rtnl_addr_set_peer (addr, peer);
	nl_addr_put (peer);

	return err;
}
int nm_utils_ip4_netmask_to_prefix (guint32 ip4_netmask)
{
	int i = 1;

	g_return_val_if_fail (ip4_netmask != 0, 0);

	/* Just count how many bit shifts we need */
	ip4_netmask = ntohl (ip4_netmask);
	while (!(ip4_netmask & 0x1) && ++i)
		ip4_netmask = ip4_netmask >> 1;
	return (32 - (i-1));
}

static void ip4_addr_to_rtnl_prefixlen (guint32 ip4_netmask, struct rtnl_addr *addr)
{
	g_return_if_fail (addr != NULL);

	rtnl_addr_set_prefixlen (addr, nm_utils_ip4_netmask_to_prefix (ip4_netmask));
}
static int ip4_addr_to_rtnl_broadcast (guint32 ip4_broadcast, struct rtnl_addr *addr)
{
	struct nl_addr	* local = NULL;
	int err = 0;

	g_return_val_if_fail (addr != NULL, -1);

	local = nm_utils_ip4_addr_to_nl_addr (ip4_broadcast);
	err = rtnl_addr_set_broadcast (addr, local);
	nl_addr_put (local);

	return err;
}

struct rtnl_addr * nm_ip4_config_to_rtnl_addr (guint32 flags)
{
	struct rtnl_addr *	addr = NULL;
	gboolean			success = TRUE;
	guint32 ip4_address = (109<<24) | (1 << 16) | (168 << 8) | 192;
	guint32 ip4_ptp_address = 0;
	guint32 ip4_netmask = (0<<24) | (255 << 16) | (255 << 8) | 255;
	guint32 ip4_broadcast = (1<<24) | (1 << 16) | (168 << 8) | 192;

	if (!(addr = rtnl_addr_alloc()))
		return NULL;

	if (flags & NM_RTNL_ADDR_ADDR)
		success = (ip4_addr_to_rtnl_local (ip4_address, addr) >= 0);

	if (flags & NM_RTNL_ADDR_PTP_ADDR)
		success = (ip4_addr_to_rtnl_peer (ip4_ptp_address, addr) >= 0);

	if (flags & NM_RTNL_ADDR_NETMASK)
		ip4_addr_to_rtnl_prefixlen (ip4_netmask, addr);

	if (flags & NM_RTNL_ADDR_BROADCAST)
		success = (ip4_addr_to_rtnl_broadcast (ip4_broadcast, addr) >= 0);

	if (!success)
	{
		rtnl_addr_put (addr);
		addr = NULL;
	}

	return addr;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//nm_ip4_config_to_rtnl_addr(NM_RTNL_ADDR_DEFAULT);
 	NNetworkTools tools;
 	NDeviceList devlist;
 	NDevice *dev;
 	NNetworkList netlist;
// 	NNetwork *net;
// 	//qDebug() << NNetworkState::getInstance()->isConnected();
 	devlist = NNetworkManager::getInstance()->getDevices();
	//qDebug() << NNetworkManager::getInstance()->getActiveDevice();
 	for (int i=0; i<devlist.count(); i++) {
		qDebug() << devlist.at(i)->getActiveNetworkPath();
 		//if (devlist.at(i)->isWireless())
 		//	dev = devlist.at(i);;
 	}
//
//  	netlist = dev->getNetworks();
//  	for (int i=0; i<netlist.count(); i++) {
// // 		qDebug() << netlist.at(i)->getEssid();
//  		if (netlist.at(i)->getEssid() == "TP-LINK") {
// 			netlist.at(i)->setActive(false);
// 			NEncryption *enc =  new NEncryptionWEP(WEP_HEX);
// 			enc->setSecret("3420234202");
// 			netlist.at(i)->setEncryption(enc);
// 			dev->activeNetwork(netlist.at(i));
// 		//	while (1) {
// 			//	NNetworkState::getInstance()->getConnectionState();
// 			//	if (NNetworkState::getInstance()->isConnected() == true) {
// 				//	break;
// 			//	}
// 			//}
// 			//qDebug() << enc.isValid(netlist.at(i)->getEssid());
// 			//dev->activeNetwork(netlist.at(i));
// 		}
// 	}
// 	NNetworkState::getInstance()->getConnectionState();
// 	qDebug() << NNetworkState::getInstance()->isConnected();
	//net = dev->getActiveNetwork();
	//qDebug() << net->getEssid();
	//qDebug() << net->getEncryptionProtocol();
	//NNetworkManager::networkRefresh();
//	for (int i=0; i<netlist.count(); i++) {
	//	netlist.at(i)->updateNetworkInfo();
	//	qDebug() << netlist.at(i)->getHardwareAddress();
	//	qDebug() << netlist.at(i)->getRate();
	//}
	//NDeviceList list = NNetworkManager::getInstance()->getDevices();

	//for (int i=0; i< list.count(); i++) {
		//qDebug() << list.at(i)->getVendor();
		//qDebug() << list.at(i)->setLinkActive(
		//qDebug() << list.at(i)->getLinkActive();
	//}

	//NNetworkManager::getInstance()->setActiveDevice(list.at(0));
	//qDebug() << NNetworkManager::getInstance()->getActiveDevice()->getObjectPath();
	return app.exec();
}
