#-------------------------------------------------
#
# Project created by QtCreator 2017-06-07T09:28:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pelcod
TEMPLATE = app

#RC_ICONS = "$$PWD/serial.ico"
RC_FILE = client.rc

DEFINES = WIN32

SOURCES += main.cpp\
        dialog.cpp \
    pelco_d.cpp \
    serial_comm.cpp

HEADERS  += dialog.h \
    pelco_d.h \
    serial_comm.h

FORMS    += dialog.ui
