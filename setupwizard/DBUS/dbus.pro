######################################################################
# Automatically generated by qmake (2.01a) Tue Oct 14 00:22:45 2008
######################################################################

TEMPLATE = app
TARGET = NDBus-test 
DEPENDPATH += .
INCLUDEPATH += . \
		/usr/include/dbus-1.0 \
		/usr/lib/dbus-1.0/include \
		/usr/include/glib-2.0 \
		/usr/lib/glib-2.0/include \
		/usr/local/include/NetworkManager
LIBS += -ldbus-glib-1 -ldbus-1 -lrt

# Input
HEADERS += NDBusConnection.h NDBusCommon.h NDBusDeviceInterface.h
SOURCES += main.cpp NDBusConnection.cpp NDBusDeviceInterface.cpp
