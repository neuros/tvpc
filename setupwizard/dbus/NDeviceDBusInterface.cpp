#include "NDeviceDBusInterface.h"
#include "NNetworkTools.h"

NNetworkTools *NDeviceDBusInterface::_ctx = NULL;

void NDeviceDBusInterface::getHalProperty (
	const QString &udi, const QString &property, QString &result)
{
	DBusConnection* con      = _ctx->getDBus ()->getConnection ();
	LibHalContext*  hal_ctx  = NULL;
	char*           prop_val = NULL;

	if (!con || property.isNull()) {
		goto out;
	}

	if (!dbus_bus_name_has_owner (con, "org.freedesktop.Hal", NULL)) {
		printf ("Error: HAL seems not to be running.\n");
		goto out;
	}
	
	hal_ctx = libhal_ctx_new ();

	if (!libhal_ctx_set_dbus_connection (hal_ctx, con)) {
		goto out;
	}

	if (!libhal_ctx_init (hal_ctx, NULL)) {
		goto out;
	}

	prop_val = libhal_device_get_property_string (hal_ctx, udi.toUtf8().data(), property.toUtf8().data(), NULL);
	result = prop_val;

	libhal_free_string (prop_val);
out:
	if (hal_ctx) {
		libhal_ctx_shutdown (hal_ctx, NULL);
		libhal_ctx_free (hal_ctx);
	}

	return;
}


void NDeviceDBusInterface::setHalDeviceInfo (NDevice* dev)
{
	QString device_udi = "";
	QString parent_udi = "";
	QString subsystem  = "";
	QString vendor     = "";
	QString product    = "";
	bustype  type       = BUS_UNKNOWN;

 	device_udi = dev->getUdi ();
	getHalProperty (device_udi, "info.parent", parent_udi);
 	getHalProperty (parent_udi, "linux.subsystem", subsystem);
 	dev->setBustype(subsystem);

	type = dev->getBustype ();
	if (type == BUS_PCI || type == BUS_PCMCIA) {
		getHalProperty (parent_udi, "info.vendor", vendor);
		getHalProperty (parent_udi, "info.product", product);
	} else if (type == BUS_USB) {
		getHalProperty (parent_udi, "usb.vendor", vendor);
		getHalProperty (parent_udi, "usb.product", product);
	} else {
		getHalProperty (parent_udi, "info.vendor", vendor);
		getHalProperty (parent_udi, "info.product", product);
	}

	dev->setVendor (vendor.isNull () ?"Unknown" : vendor);
	dev->setProduct (product.isNull() ? "Unknown" : product);

	return;
}

void NDeviceDBusInterface::getProperties(const QString &path,
										 NDevice *dev)
{
	DBusMessage*     msg   = NULL;
	DBusConnection*  con   = _ctx->getDBus()->getConnection ();
	DBusMessage *		reply = NULL;

	const char*   obj_path          = NULL;
	const char*   interface         = NULL;
	NMDeviceType  type              = DEVICE_TYPE_UNKNOWN;
	const char*   udi               = NULL;
	dbus_bool_t   active            = false;
	NMActStage    act_stage         = NM_ACT_STAGE_UNKNOWN;
	const char*   ipv4_address      = NULL;
	const char*   subnetmask        = NULL;
	const char*   broadcast         = NULL;
	const char*   hw_address        = NULL;
	const char*   route             = NULL;
	const char*   pri_dns           = NULL;
	const char*   sec_dns           = NULL;
	dbus_int32_t  mode              = 0;
	dbus_int32_t  strength          = -1;
	dbus_bool_t   link_active       = false;
	dbus_int32_t  speed             = 0;
	dbus_uint32_t capabilities      = NM_DEVICE_CAP_NONE;
	dbus_uint32_t capabilities_type = NM_DEVICE_CAP_NONE;
	char**        networks          = NULL;
	int           num_networks      = 0;
	const char*   active_net_path   = NULL;

	if (!con|| path.isNull() || !dev) {
		return;
	}

	if (!(msg = dbus_message_new_method_call (NM_DBUS_SERVICE, path.toUtf8().data(), 
												  NM_DBUS_INTERFACE_DEVICES, "getProperties")))
	{
		qDebug() << "getProperties(): couldn't create new dbus message.\n";
		return;
	}

	reply = dbus_connection_send_with_reply_and_block (con, msg, -1, NULL);
	dbus_message_unref (msg);
	if (!reply)
	{
		qDebug() << "getProperties(): didn't get a reply from NetworkManager for device" << path;
		return;
	}

	if (!dbus_message_get_args (reply, NULL,	DBUS_TYPE_OBJECT_PATH, &obj_path,
									DBUS_TYPE_STRING, &interface,
									DBUS_TYPE_UINT32, &type,
									DBUS_TYPE_STRING, &udi,
									DBUS_TYPE_BOOLEAN,&active,
									DBUS_TYPE_UINT32, &act_stage,
									DBUS_TYPE_STRING, &ipv4_address,
									DBUS_TYPE_STRING, &subnetmask,
									DBUS_TYPE_STRING, &broadcast,
									DBUS_TYPE_STRING, &hw_address,
									DBUS_TYPE_STRING, &route,
									DBUS_TYPE_STRING, &pri_dns,
									DBUS_TYPE_STRING, &sec_dns,
									DBUS_TYPE_INT32,  &mode,
									DBUS_TYPE_INT32,  &strength,
									DBUS_TYPE_BOOLEAN,&link_active,
									DBUS_TYPE_INT32,  &speed,
									DBUS_TYPE_UINT32, &capabilities,
									DBUS_TYPE_UINT32, &capabilities_type,
									DBUS_TYPE_STRING, &active_net_path,
									DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &networks, &num_networks,
									DBUS_TYPE_INVALID))
	{
 		qDebug() <<  "getProperties(): unexpected reply from NetworkManager for device." << path;
		dbus_message_unref (reply);
		return;
 	}

	dev->setInterface (interface);
	dev->setObjectPath (obj_path);
	dev->setType (type);
	dev->setUdi (udi);
	dev->setActive (active);
	dev->setActivationStage (act_stage);
	dev->setIPv4Address (ipv4_address);
	dev->setSubnetmask (subnetmask);
	dev->setBroadcast (broadcast);
	dev->setHardwareAddress (hw_address);
	dev->setRoute (route);
	dev->setPrimaryDNS (pri_dns);
	dev->setSecondaryDNS (sec_dns);
	dev->setMode (mode);
	dev->setStrength (strength);
	dev->setLinkActive (link_active);
	dev->setSpeed (speed);
	dev->setCapabilities (capabilities);
	dev->setCapabilitiesType (capabilities_type);
	dev->setActiveNetworkPath(active_net_path);

	setHalDeviceInfo (dev);

	if ((dev->isWireless()) && (num_networks > 0))
		dev->setupNetworks(networks, num_networks);

	dbus_free_string_array (networks);


	dbus_message_unref (reply);
	return;
}

void NDeviceDBusInterface::push(NNetworkTools *ctx)
{
	NDeviceDBusInterface::_ctx = ctx;
}
