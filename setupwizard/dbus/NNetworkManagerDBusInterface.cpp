#include "NNetworkManagerDBusInterface.h"
#include "NNetworkTools.h"

NNetworkTools *NNetworkManagerDBusInterface::_ctx = NULL;

void NNetworkManagerDBusInterface::setupDevices(char **path, int num)
{
	NNetworkManager *manager = _ctx->getManager();
	manager->setupDevices(path, num);
}

void NNetworkManagerDBusInterface::activateDevice (NDevice* dev)
{
	DBusMessage*    msg = NULL;
	DBusConnection* con = _ctx->getDBus ()->getConnection ();

	if (!con) {
		return;
	}

	msg = dbus_message_new_method_call (NM_DBUS_SERVICE, NM_DBUS_PATH, NM_DBUS_INTERFACE, "setActiveDevice");
	if (msg) {
		const char *obj_path = dev->getObjectPath ().toUtf8().data(); 

		dbus_message_append_args (msg, DBUS_TYPE_OBJECT_PATH, &obj_path, DBUS_TYPE_INVALID);
		dbus_connection_send (con, msg, NULL);
		dbus_message_unref (msg);
	}

	return;
}


void NNetworkManagerDBusInterface::getDevices()
{
	DBusConnection*  con    = _ctx->getDBus()->getConnection ();
    DBusMessage *	message = NULL;
	DBusMessage *	reply = NULL;
	DBusError		error;
	char **		paths = NULL;
	int			num = -1;

	if (!(message = dbus_message_new_method_call (
		NM_DBUS_SERVICE, NM_DBUS_PATH,
		NM_DBUS_INTERFACE, "getDevices")))
	{
		fprintf (stderr, "print_devices(): couldn't create new dbus message.\n");
		return;
	}

	dbus_error_init (&error);
	reply = dbus_connection_send_with_reply_and_block (con, message, -1, &error);
	dbus_message_unref (message);
	if (!reply)
	{
		fprintf (stderr, "print_devices(): didn't get a reply from NetworkManager.\n");
		if (dbus_error_is_set (&error))
		{
			if (dbus_error_has_name (&error, NM_DBUS_NO_DEVICES_ERROR))
				fprintf (stderr, "There are no available network devices.\n");
		}
		else
			fprintf (stderr, "print_devices(): NetworkManager returned an error: '%s'\n", error.message);
		return;
	}

	if (!dbus_message_get_args (reply, NULL, DBUS_TYPE_ARRAY, DBUS_TYPE_OBJECT_PATH, &paths, &num, DBUS_TYPE_INVALID))
	{
		fprintf (stderr, "print_devices(): unexpected reply from NetworkManager.\n");
		dbus_message_unref (reply);

		return;
	}

	setupDevices(paths, num);

	return;
}

void NNetworkManagerDBusInterface::push(NNetworkTools *ctx)
{
	NNetworkManagerDBusInterface::_ctx = ctx;
	NNetworkManagerDBusInterface::getDevices();
}
