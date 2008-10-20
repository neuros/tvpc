#include "NNetworkDBusInterface.h"
#include "NNetworkTools.h"

NNetworkTools *NNetworkDBusInterface::_ctx = NULL;

void NNetworkDBusInterface::getProperties(const QString &path, NNetwork *net)
{
	DBusMessage*        msg    = NULL;
	DBusMessage*		reply = NULL;
	DBusConnection*     con    = _ctx->getDBus ()->getConnection ();

	const char*  obj_path     = NULL;
	const char*  essid        = NULL;
	const char*  hw_address   = NULL;
	dbus_int32_t strength     = -1;
	double       freq         = 0;
	dbus_int32_t rate         = 0;
	dbus_int32_t mode         = 0;
	dbus_int32_t capabilities = NM_802_11_CAP_NONE;
	dbus_bool_t  broadcast    = true;

	if (path.isNull() || !net || !con)
		return;

	if (!(msg = dbus_message_new_method_call (NM_DBUS_SERVICE, net->getObjectPath().toUtf8().data(),
										NM_DBUS_INTERFACE_DEVICES, "getProperties"))) {
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

	if (dbus_message_is_error (reply, NM_DBUS_NO_NETWORKS_ERROR)) {
		dbus_message_unref (reply);
		return;
	}

	if (dbus_message_get_args (reply, NULL, DBUS_TYPE_OBJECT_PATH, &obj_path,
						DBUS_TYPE_STRING,      &essid,
						DBUS_TYPE_STRING,      &hw_address,
						DBUS_TYPE_INT32,       &strength,
						DBUS_TYPE_DOUBLE,      &freq,
						DBUS_TYPE_INT32,       &rate,
						DBUS_TYPE_INT32,       &mode,
						DBUS_TYPE_INT32,       &capabilities,
						DBUS_TYPE_BOOLEAN,     &broadcast, DBUS_TYPE_INVALID)) {
		if (net->getDevice()) {
			if (strcmp (obj_path, net->getDevice()->getActiveNetworkPath().toUtf8().data()) == 0)
				net->setActive (true);
			else
				net->setActive (false);
		}

		net->setEssid (essid);
		net->setHardwareAddress (hw_address);
		net->setStrength (strength);
		net->setFrequency (freq);
		net->setRate (rate);
		net->setMode (mode);
		net->setCapabilities (capabilities);
		net->setHidden (!broadcast);
	}

	dbus_message_unref (reply);

	return;

}
void NNetworkDBusInterface::push(NNetworkTools *ctx)
{
	_ctx = ctx;
}
