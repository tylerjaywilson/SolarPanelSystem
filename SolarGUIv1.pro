#-------------------------------------------------
#
# Project created by QtCreator 2016-02-20T14:08:43
#
#-------------------------------------------------

QT       += core gui
#Enable c++11
QMAKE_CXXFLAGS += -std=c++0x

TARGET = SolarGUIv1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    solarpanel_configpage.cpp \
    mytimer.cpp \
    voltagesoc.cpp \
    uart.cpp \
    psoccomm.cpp \
    i2c.cpp \
    cccomm.cpp

HEADERS  += mainwindow.h \
    mySolarProject.h \
    solarpanel_configpage.h \
    mytimer.h \
    voltagesoc.h \
    uart.hpp \
    psoccomm.hpp \
    i2cdefines.hpp \
    i2c.hpp \
    cccomm.hpp

FORMS    += mainwindow.ui \
    solarpanel_configpage.ui

RESOURCES += \
    myResources.qrc
