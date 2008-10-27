#include "NDBusConnection.h"
#include "NNetworkTools.h"
#include "NStateDBusInterface.h"
#include "NDeviceDBusInterface.h"
#include "NNetworkDBusInterface.h"
#include "NNetworkManagerDBusInterface.h"

NNetworkTools* NDBusConnection::_ctx = NULL;
DBusConnection*  NDBusConnection::_dbus_connection = NULL;
static const char * UPDATE_DEVICE_SIGNALS[] = {
	"DeviceStrengthChanged", "DeviceCarrierOn", "DeviceCarrierOff", 
	"DeviceAdded",  "DeviceNoLongerActive", "DeviceNowActive", 
	"DeviceActivating" , "DeviceRemoved"
};
static const int UPDATE_DEVICE_SIGNAL_COUNT = 8;

NDBusConnection::NDBusConnection(void)
{

}

NDBusConnection::~NDBusConnection()
{

}

bool NDBusConnection::handleUpdateDeviceSignal( DBusMessage * msg )
{
	bool matched = false;
	char * obj_path = 0;
	for ( int i = 0; !matched && (i < UPDATE_DEVICE_SIGNAL_COUNT ); ++i )
	{
		if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, UPDATE_DEVICE_SIGNALS[i] ) ) {
			fprintf(stderr, "%s handle\n", UPDATE_DEVICE_SIGNALS[i]);
			matched = true;
			if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path, DBUS_TYPE_INVALID)) {
					NDeviceDBusInterface::updateDevice (_ctx->getManager()->getDevice(obj_path),
														UPDATE_DEVICE_SIGNALS[i]);
			}
		}
	}
	return matched;
}


gboolean NDBusConnection::triggerReconnect(gpointer user_data)
{
	fprintf(stderr, "triggerReconnect\n");
	if (_ctx->getDBus()->dbusInit() == true) {
		printf("Successfully reconnected to the system bus.\n");
		return TRUE;
	}

	return FALSE;
}

DBusHandlerResult NDBusConnection::nmd_dbus_filter (
	DBusConnection *connection, DBusMessage *msg, void *user_data)
{
	const char* member      = dbus_message_get_member    (msg);
	bool        handled     = true;
	NDevice *dev = NULL;
	fprintf(stderr, "filter\n");
	if (dbus_message_is_signal (msg, DBUS_INTERFACE_LOCAL, "Disconnected")) {
		fprintf(stderr, "Disconnected\n");
		g_timeout_add (3000, triggerReconnect, NULL);
	}
	/* Signal indicating that NetworkManager's D-Bus interface owner has changed 
	 *
	 * D-Bus signal: NameOwnerChanged
	 */
//
// 	/* Signal indicating that the state of NetworkManager has changed.
// 	 *
// 	 * D-Bus signal: NM_DBUS_SIGNAL_STATE_CHANGE
// 	 */
//
 	else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, NM_DBUS_SIGNAL_STATE_CHANGE)) {
 		NMState state = NM_STATE_UNKNOWN;
 		fprintf(stderr, "NM_DBUS_SIGNAL_STATE_CHANGE\n");
//
 		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_UINT32, &state, DBUS_TYPE_INVALID)) {
 			NStateDBusInterface::setState (state);
 		}
 	}
//
// 	/* Signals regarding device changes.
// 	 *
// 	 * D-Bus signals: DeviceActivating,
// 	 *		  DeviceAdded,
// 	 *		  DeviceCarrierOff,
// 	 *		  DeviceCarrierOn,
// 	 *		  DeviceNoLongerActive,
// 	 *		  DeviceNowActive,
// 	 *		  DeviceStrengthChanged
// 	 */
 	else if ( handleUpdateDeviceSignal( msg ) ) {
 		;
 	}
//
// 	/* Signal regarding removal of devices.
// 	 *
// 	 * D-Bus signal: DeviceRemoved
// 	 *
// 	 */
//
// 	else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, "DeviceRemoved")) {
// 		char* obj_path = NULL;
// 		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path, DBUS_TYPE_INVALID)) {
// 			DeviceStoreDBus::removeDevice (obj_path);
// 		}
// 	}
//
// 	/* Signals regarding wireless devices.
// 	 *
// 	 * D-Bus signals: WirelessNetworkAppeared
// 	 */
 	else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, "WirelessNetworkAppeared")) {
 		char* obj_path = NULL;
 		char* net_path = NULL;
//
 		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path,
 						      DBUS_TYPE_OBJECT_PATH, &net_path, DBUS_TYPE_INVALID)) {
			dev = _ctx->getManager()->getDevice(obj_path);
			if (dev)
					NNetworkDBusInterface::updateNetwork (
						dev->getNetwork(net_path), "WirelessNetworkAppeared");
			}
 		}
// 	}
//
// 	/* Signals regarding wireless devices.
// 	 *
// 	 * D-Bus signals: WirelessNetworkDisappeared
// 	 */
 	else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, "WirelessNetworkDisappeared")) {
 		char* obj_path = NULL;
 		char* net_path = NULL;

 		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path,
 						      DBUS_TYPE_OBJECT_PATH, &net_path, DBUS_TYPE_INVALID)) {
			dev = _ctx->getManager()->getDevice(obj_path);
			if (dev)
					NNetworkDBusInterface::updateNetwork (
						dev->getNetwork(net_path), "WirelessNetworkDisappeared");
			}

			// 			DeviceStoreDBus::removeNetwork (obj_path, net_path);
 	}

//
// 	/* Signal for signal strength change of wireless devices.
// 	 *
// 	 * D-Bus signal: WirelessNetworkStrengthChanged
// 	 */
 	else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, "WirelessNetworkStrengthChanged")) {
 		char* obj_path = NULL;
 		char* net_path = NULL;
 		int   strength = -1;

 		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path,
 						      DBUS_TYPE_OBJECT_PATH, &net_path,
 						      DBUS_TYPE_INT32,       &strength, DBUS_TYPE_INVALID)) {
			dev = _ctx->getManager()->getDevice(obj_path);
			if (dev)
				NNetworkDBusInterface::updateNetworkStrength (dev->getNetwork(net_path), 
															  strength);
			}
		}

// 	/* Signal for activation stage of a connection attempt.
// 	 *
// 	 * D-Bus signal: DeviceActivationStage
// 	 */
 	else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, "DeviceActivationStage")) {
 		char*      obj_path  = NULL;
 		NMActStage act_stage = NM_ACT_STAGE_UNKNOWN;
//
 		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path,
 				                      DBUS_TYPE_UINT32,      &act_stage, DBUS_TYPE_INVALID)) {
			dev = _ctx->getManager()->getDevice(obj_path);
			if (dev)
				NDeviceDBusInterface::updateActivationStage (dev, act_stage);
 		}

 	}
//
// 	/* Signal emitted if the activation of a device failed.
// 	 *
// 	 * D-Bus signal: DeviceActivationFailed
// 	 */
 	else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, "DeviceActivationFailed")) {
 		char* dev_path = NULL;
 		char* net_path = NULL;

 		/* NM FIXME: NetworkManager does not invalidate the devices by asking us to update the device
 		 * and/or network which failed.  Hence, the 'active' flag for devices and networks is out of sync.
 		 */

 		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &dev_path,
 				                      DBUS_TYPE_OBJECT_PATH, &net_path, DBUS_TYPE_INVALID)) {
			dev = _ctx->getManager()->getDevice(dev_path);
			if (dev){
	
				NNetworkDBusInterface::updateNetwork (dev->getNetwork(net_path), ""); //TODO Do we need this? It will be called from updateDevice
				NDeviceDBusInterface::updateDevice (dev, "");
			}
		}
	}
// 		} else if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &dev_path, DBUS_TYPE_INVALID)) {
// 			DeviceStoreDBus::updateDevice (dev_path);
// 		}
// 	}
//
// 	else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE_VPN, "VPNConnectionAdded") ||
// 	         dbus_message_is_signal (msg, NM_DBUS_INTERFACE_VPN, "VPNConnectionUpdate")) {
// 			const char* name = NULL;
// 			if (dbus_message_get_args (msg, NULL, DBUS_TYPE_STRING, &name, DBUS_TYPE_INVALID)) {
// 				VPNDBus::updateVPNConnection (name);
// 			}
// 	}
//
// 	else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE_VPN, "VPNConnectionStateChange")) {
// 			const char*   name = NULL;
// 			NMVPNActStage act_stage;
// 			if (dbus_message_get_args (msg, NULL, DBUS_TYPE_STRING, &name,
// 							      DBUS_TYPE_UINT32, &act_stage, DBUS_TYPE_INVALID)) {
// 				VPNDBus::updateVPNActivationStage (name, act_stage);
// 			}
// 	}
//
// 	else if (  dbus_message_is_signal (msg, NM_DBUS_INTERFACE_VPN, NM_DBUS_VPN_SIGNAL_LOGIN_FAILED)
// 					|| dbus_message_is_signal (msg, NM_DBUS_INTERFACE_VPN, NM_DBUS_VPN_SIGNAL_LAUNCH_FAILED)
// 					|| dbus_message_is_signal (msg, NM_DBUS_INTERFACE_VPN, NM_DBUS_VPN_SIGNAL_CONNECT_FAILED)
// 					|| dbus_message_is_signal (msg, NM_DBUS_INTERFACE_VPN, NM_DBUS_VPN_SIGNAL_VPN_CONFIG_BAD)
// 					|| dbus_message_is_signal (msg, NM_DBUS_INTERFACE_VPN, NM_DBUS_VPN_SIGNAL_IP_CONFIG_BAD)
// 					) {
// 			const char*   name = NULL;
// 			const char* 	err_msg = NULL;
// 			if (dbus_message_get_args (msg, NULL, DBUS_TYPE_STRING, &name,
// 							      DBUS_TYPE_STRING, &err_msg, DBUS_TYPE_INVALID)) {
// 				VPNDBus::showVPNConnectionFailure(member, name, err_msg);
// 			}
// 	}
//
// 	/* FIXME dbus_request_name does not work during the initialization, workaround */
 	else if (dbus_message_is_signal (msg, DBUS_INTERFACE_DBUS, "NameAcquired")) {
 		const char* name = NULL;
 		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_STRING, &name, DBUS_TYPE_INVALID) && (strcmp (name, NMI_DBUS_SERVICE) != 0)) {
 			NNetworkManagerDBusInterface::requestName (msg);
 		}
 	}
//
// 	else {

 //		printf ("Unhandled message: objectpath='%s' member='%s' interface='%s'\n", objectpath, member, interface);
// 		handled = false;
// 	}

	return (handled ? DBUS_HANDLER_RESULT_HANDLED : DBUS_HANDLER_RESULT_NOT_YET_HANDLED);
}
bool NDBusConnection::open ()
{
	bool status;
	DBusError error;
	
	dbus_error_init (&error);

	_dbus_connection = NULL;
	_dbus_connection = dbus_bus_get (DBUS_BUS_SYSTEM, &error);
	if ((_dbus_connection == NULL) || (dbus_error_is_set (&error))) {
		qDebug() << "Connection to D-Bus system message bus failed:\n" << error.message;
		status = false;
		goto out;
	} else {
		dbus_connection_set_exit_on_disconnect (_dbus_connection, false);
		dbus_connection_setup_with_g_main (_dbus_connection, NULL);

		status = true;
		goto out;
	}

out:
	if (dbus_error_is_set (&error)) {
		dbus_error_free (&error);
	}

	return status;
}

void NDBusConnection::close (void)
{
	/* DBusConnection::open () calls dbus_bus_get (), we need to unref the connection */
	dbus_connection_unref (_dbus_connection);
}

void NDBusConnection::pop(void)
{
	this->_initialized = false;
	this->close();
}

bool NDBusConnection::registerObjectPath () const
{
	DBusError				 error;
	dbus_bool_t			 success = FALSE;
    DBusObjectPathVTable	 vtable = { NULL, NULL, NULL, NULL, NULL, NULL };

	dbus_error_init (&error);
	dbus_bus_request_name (_dbus_connection, NM_DBUS_SERVICE, 0, &error);
	if (dbus_error_is_set (&error)) {
		qDebug() << "Could not acquire its service.  dbus_bus_request_name() says:"  << error.message;
		return false;
	}

	success = dbus_connection_register_object_path (_dbus_connection, NM_DBUS_PATH, &vtable, NULL);
 	if (!success) {
 		printf("Could not register a handler for NetworkManager.  Not enough memory?\n");
		return false;
 	}

	return true;
}

bool NDBusConnection::addFilter(void)
{
	if (!dbus_connection_add_filter (_dbus_connection, nmd_dbus_filter, NULL, NULL))
		return false;
	return true;
}

bool NDBusConnection::addMatch (void)
{
	DBusError error;

	dbus_error_init(&error);
	dbus_bus_add_match (_dbus_connection,
				"type='signal',"
				"interface='" NM_DBUS_INTERFACE "',"
				"sender='" NM_DBUS_SERVICE "',"
				"path='" NM_DBUS_PATH "'", &error);
	if (dbus_error_is_set (&error))
		return false;

	return true;
}

bool NDBusConnection::dbusInit(void)
{
	if (this->open () == false)
		return false;

	if (this->registerObjectPath () == false) {
		printf ("Register object path failed. Bailing out.\n");
		return false;
	}

	if (this->addMatch () == false) {
		printf ("Adding matches failed. Bailing out.\n");
		return false;
	}

	if (this->addFilter() ==  false) {
		printf("Adding filter failed. Bailing out.\n");
		return false;
	}

	return true;
}

bool NDBusConnection::push(NNetworkTools *ctx)
{
	NDBusConnection::_ctx = ctx;

	if (dbusInit() == true)
		_initialized = true;

	return status ();

}
