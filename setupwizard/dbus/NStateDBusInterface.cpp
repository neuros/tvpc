#include "NStateDBusInterface.h"
#include "NNetworkManager.h"

NNetworkManager *NStateDBusInterface::_ctx = NULL;

void NStateDBusInterface::enableWireless (bool set)
{
	DBusConnection* con = _ctx->getDBus ()->getConnection ();
	DBusMessage*    msg = NULL;
	dbus_bool_t     enable = set;

	if (!con) {
		return;
	}

	msg = dbus_message_new_method_call (NM_DBUS_SERVICE, NM_DBUS_PATH, NM_DBUS_INTERFACE, "setWirelessEnabled");
	if (msg) {
		dbus_message_append_args (msg, DBUS_TYPE_BOOLEAN, &enable, DBUS_TYPE_INVALID);
		dbus_connection_send (con, msg, NULL);
		dbus_message_unref (msg);
	}

	return;
}

bool NStateDBusInterface::isNetworkManagerRunning ()
{
	DBusConnection* con        = _ctx->getDBus ()->getConnection ();
	bool            nm_running = false;

	if (!con) {
		return nm_running;
	}
	
	nm_running = dbus_bus_name_has_owner (con, NM_DBUS_SERVICE, NULL);

	return nm_running;
}


void NStateDBusInterface::switchMode (const char* method)
{
	DBusConnection* con = _ctx->getDBus ()->getConnection ();
	DBusMessage*    msg = NULL;

	if (!con) {
		return;
	}

	msg = dbus_message_new_method_call (NM_DBUS_SERVICE, NM_DBUS_PATH, NM_DBUS_INTERFACE, method);
	if (msg) {
		dbus_connection_send (con, msg, NULL);
		dbus_message_unref (msg);
	}

	return;
}

void NStateDBusInterface::setState (NMState nmstate)
{
	NNetworkState* state = _ctx->getState ();

	state->setState (nmstate);

	return;
}

void NStateDBusInterface::setWirelessState (bool wireless_state)
{
	NNetworkState* state = _ctx->getState ();

	state->updateWirelessState (wireless_state);

	return;
}

void NStateDBusInterface::getState (void)
{
	DBusMessage *	message;
	DBusMessage *	reply;
	NMState         nmstate = NM_STATE_UNKNOWN;
	DBusError		error;
	DBusConnection *con = _ctx->getDBus()->getConnection();

	if (!con)
		return;

	if (!(message = dbus_message_new_method_call (NM_DBUS_SERVICE, NM_DBUS_PATH, 
												  NM_DBUS_INTERFACE_DEVICES, "state")))
	{
		printf ("%s(): Couldn't allocate the dbus message", __func__);
		return;
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (con, message, -1, &error);
	dbus_message_unref (message);
	if (dbus_error_is_set (&error)) {
		fprintf (stderr, "%s raised:\n %s\n\n", error.name, error.message);
        dbus_error_free (&error);
	}
	else if (reply)
	{
		if (dbus_message_get_args (reply, NULL, DBUS_TYPE_UINT32, &nmstate, DBUS_TYPE_INVALID))
			setState (nmstate);
		dbus_message_unref (reply);
	}

}

void NStateDBusInterface::getWirelessState (void)
{
	DBusConnection*  con   = _ctx->getDBus ()->getConnection ();
	DBusMessage *	message;
	DBusMessage *	reply;
	DBusError		error;
	dbus_bool_t wireless_enabled;
	dbus_bool_t hwrf_enabled;

	if (!con)
		return ;

	if (!(message = dbus_message_new_method_call (NM_DBUS_SERVICE,NM_DBUS_PATH, 
												  NM_DBUS_INTERFACE, "getWirelessEnabled")))
	{
		printf ("%s(): Couldn't allocate the dbus message", __func__);
		return ;
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (con, message, -1, &error);
	dbus_message_unref (message);
	if (dbus_error_is_set (&error)) {
		 fprintf (stderr, "%s raised:\n %s\n\n", error.name, error.message);
		 dbus_error_free (&error);
		 return ;
	}
	else if (reply)
	{
		if (dbus_message_get_args (reply, NULL, DBUS_TYPE_BOOLEAN, &wireless_enabled, DBUS_TYPE_BOOLEAN,
								   &hwrf_enabled, DBUS_TYPE_INVALID))
		dbus_message_unref (reply);
		setWirelessState (wireless_enabled);
		return ;
	}

	return ;
}

void NStateDBusInterface::push (NNetworkManager* ctx)
{
	NStateDBusInterface::_ctx = ctx;
}

