#include "NDBusConnection.h"
#include "NNetworkTools.h"
#include "NStateDBusInterface.h"
#include "NDeviceDBusInterface.h"
#include "NNetworkDBusInterface.h"
#include "NNetworkManagerDBusInterface.h"

NNetworkTools *NDBusConnection::_ctx = NULL;
DBusConnection * NDBusConnection::_dbus_connection = NULL;
static const char *UPDATE_DEVICE_SIGNALS[] = {
	/*"DeviceStrengthChanged",*/ "DeviceCarrierOn", "DeviceCarrierOff", 
	"DeviceAdded",  "DeviceNoLongerActive", "DeviceNowActive", 
	"DeviceActivating" , "DeviceRemoved"
};
static const int UPDATE_DEVICE_SIGNAL_COUNT = 7;

NDBusConnection::NDBusConnection(void)
{

}

NDBusConnection::~NDBusConnection()
{

}

bool NDBusConnection::handleUpdateDeviceSignal( DBusMessage * msg )
{
	bool matched = false;
	char *obj_path = NULL;

	for (int i = 0; !matched && (i < UPDATE_DEVICE_SIGNAL_COUNT); ++i ) {
		if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, UPDATE_DEVICE_SIGNALS[i])) {

			qDebug() << "\n";
			qDebug() << "======== " + QString(UPDATE_DEVICE_SIGNALS[i]) + " ========";
			qDebug() << "\n";

			matched = true;
			if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path,
									   DBUS_TYPE_INVALID))
					NDeviceDBusInterface::updateDevice (_ctx->getManager()->getDevice(obj_path),
														UPDATE_DEVICE_SIGNALS[i]);
		}
	}

	return matched;
}

int NDBusConnection::triggerReconnect(void */* user data */)
{
	qDebug() <<  "\n======== triggerReconnect ========\n";

	if (_ctx->getDBus()->dbusInit() == true) {
		qDebug() << "Successfully reconnected to the system bus.";
		return TRUE;
	}

	return FALSE;
}

DBusHandlerResult NDBusConnection::nmd_dbus_filter (
	DBusConnection * /* connection */, DBusMessage *msg, void */* user_data */)
{
	bool handled = true;
	NDevice *dev = NULL;

	if (dbus_message_is_signal (msg, DBUS_INTERFACE_LOCAL, "Disconnected")) {

		qDebug() <<  "\n======== Disconnected ========\n";
		triggerReconnect(NULL);

	} else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE,
									   NM_DBUS_SIGNAL_STATE_CHANGE)) {

		qDebug() <<  "\n======== Signal State Change ========\n";

		NMState state = NM_STATE_UNKNOWN;
		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_UINT32, &state, DBUS_TYPE_INVALID))
 			NStateDBusInterface::setState (state);

 	} else if (handleUpdateDeviceSignal(msg)) {
			;
	} else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, "WirelessNetworkAppeared")) {

		qDebug() <<  "\n======== WirelessNetworkAppeared ========\n";

		char *obj_path = NULL;
		char *net_path = NULL;

		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path,
							  DBUS_TYPE_OBJECT_PATH, &net_path, DBUS_TYPE_INVALID)) {

			dev = _ctx->getManager()->getWirelessDevice();
			if (dev)
					NDeviceDBusInterface::updateDevice(dev, "WirelessNetworkAppeared");
		}

	} else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, "WirelessNetworkDisappeared")) {

		qDebug() <<  "\n======== WirelessNetworkDisappeared ========\n";

		char *obj_path = NULL;
		char *net_path = NULL;

		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path,
							  DBUS_TYPE_OBJECT_PATH, &net_path, DBUS_TYPE_INVALID)) {
			dev = _ctx->getManager()->getWirelessDevice();
			if (dev)
					NDeviceDBusInterface::updateDevice(dev, "WirelessNetworkDisappeared");
		}
	} else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE,
									   "WirelessNetworkStrengthChanged")) {

		qDebug() <<  "\n======== WirelessNetworkStrengthChanged ========\n";

		char *obj_path = NULL;
		char *net_path = NULL;
		int strength = -1;

		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path,
							  DBUS_TYPE_OBJECT_PATH, &net_path,
							  DBUS_TYPE_INT32, &strength, DBUS_TYPE_INVALID)) {

			dev = _ctx->getManager()->getDevice(obj_path);
			if (dev)
				NNetworkDBusInterface::updateNetworkStrength (dev->getNetwork(net_path), 
															  strength);
		}
	} else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, "DeviceActivationStage")) {

		qDebug() <<  "\n======== DeviceActivationStage ========\n";

		char *obj_path  = NULL;
		NMActStage act_stage = NM_ACT_STAGE_UNKNOWN;

		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path,
									  DBUS_TYPE_UINT32,      &act_stage, DBUS_TYPE_INVALID)) {
			dev = _ctx->getManager()->getDevice(obj_path);
			if (dev)
				NDeviceDBusInterface::updateActivationStage (dev, act_stage);
		}

	} else if (dbus_message_is_signal (msg, NM_DBUS_INTERFACE, "DeviceActivationFailed")) {

		qDebug() <<  "\n======== DeviceActivationFailed ========\n";

		char *dev_path = NULL;
		char *net_path = NULL;

		/* NM FIXME: NetworkManager does not invalidate the devices by asking us to update the device
		 * and/or network which failed.  Hence, the 'active' flag for devices and networks is out of sync.
		 */

		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_OBJECT_PATH, &dev_path,
									  DBUS_TYPE_OBJECT_PATH, &net_path, DBUS_TYPE_INVALID)) {
			dev = _ctx->getManager()->getDevice(dev_path);
			if (dev)
				NDeviceDBusInterface::updateDevice (dev, "DeviceActivationFailed");
		}

	} else if (dbus_message_is_signal (msg, DBUS_INTERFACE_DBUS, "NameAcquired")) {

		qDebug() <<  "\n======== DeviceActivationFailed ========\n";

		const char *name = NULL;
		if (dbus_message_get_args (msg, NULL, DBUS_TYPE_STRING,
								   &name, DBUS_TYPE_INVALID) && (strcmp (name, NMI_DBUS_SERVICE) != 0))
			NNetworkManagerDBusInterface::requestName (msg);
	}

	return (handled ? DBUS_HANDLER_RESULT_HANDLED :
			DBUS_HANDLER_RESULT_NOT_YET_HANDLED);
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
	if (dbus_error_is_set (&error))
		dbus_error_free (&error);

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
 		qDebug() << "Could not register a handler for NetworkManager.  Not enough memory?";
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
		qDebug() << "Register object path failed. Bailing out.";
		return false;
	}

	if (this->addMatch () == false) {
		qDebug() << "Adding matches failed. Bailing out.";
		return false;
	}

	if (this->addFilter() ==  false) {
		qDebug() << "Adding filter failed. Bailing out.";
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
