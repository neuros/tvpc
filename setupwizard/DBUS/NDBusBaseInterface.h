#ifndef _NDBUS_BASE_INTERFACE_H__
#define _NDBUS_BASE_INTERFACE_H__
#include <NetworkManager.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <iwlib.h>
#include <QStringList>
#include <QString>
#include "NDBusConnection.h"
#define INVALID  ~0

class NDBusBaseInterface
{
public:
	NDBusBaseInterface(const NDBusConnection &con);
	bool isValid() const;
protected:
	const QStringList StringListCall(const QString &server, const QString &device,
							const QString &interface, const QString &method) const;
	const QString StringCall(const QString &server, const QString &device,
							const QString &interface, const QString &method) const;
	dbus_int32_t IntCall(const QString &server, const QString &device,
							const QString &interface, const QString &method) const;
	dbus_uint32_t UintCall(const QString &server, const QString &device,
						    const QString &interface, const QString &method) const;
	dbus_bool_t BoolCall(const QString &server, const QString &device,
							const QString &interface, const QString &method) const;
	double DoubleCall(const QString &server, const QString &device,
	  						const QString &interface, const QString &method) const;
	NDBusConnection connection;
private:
	int err;

};

#endif
