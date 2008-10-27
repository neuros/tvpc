######################################################################
# Automatically generated by qmake (2.01a) Mon Oct 27 21:42:18 2008
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . dbus form ui
INCLUDEPATH += . dbus \
	        /usr/include/dbus-1.0 \
                /usr/lib/dbus-1.0/include \
                /usr/include/glib-2.0 \
                /usr/lib/glib-2.0/include \
                /usr/local/include/NetworkManager

LIBS += -ldbus-glib-1 -ldbus-1 -lrt -lhal -lnm-util -lnl
	
# Input
HEADERS += dbus/NDBusConnection.h \
           dbus/NDevice.h \
           dbus/NDeviceDBusInterface.h \
           dbus/NEncryption.h \
           dbus/NNetwork.h \
           dbus/NNetworkDBusInterface.h \
           dbus/NNetworkManager.h \
           dbus/NNetworkManagerDBusInterface.h \
           dbus/NNetworkManagerInfo.h \
           dbus/NNetworkState.h \
           dbus/NNetworkTools.h \
           dbus/NStateDBusInterface.h \
           ui/nsplashform.h \
	   ui/nselectmode.h \
	   ui/noverview.h 
FORMS += form/nsplashform.ui \
	 form/nselectmode.ui \
	 form/noverview.ui 
SOURCES += dbus/NDBusConnection.cpp \
           dbus/NDevice.cpp \
           dbus/NDeviceDBusInterface.cpp \
           dbus/NEncryption.cpp \
           dbus/NNetwork.cpp \
           dbus/NNetworkDBusInterface.cpp \
           dbus/NNetworkManager.cpp \
           dbus/NNetworkManagerDBusInterface.cpp \
           dbus/NNetworkManagerInfo.cpp \
           dbus/NNetworkState.cpp \
           dbus/NNetworkTools.cpp \
           dbus/NStateDBusInterface.cpp \
	   nsplashform.cpp \
	   nselectmode.cpp \
	   noverview.cpp \
	   main.cpp \