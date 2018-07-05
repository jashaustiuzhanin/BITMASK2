#-------------------------------------------------
#
# Project created by QtCreator 2018-06-07T14:15:28
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bitmask2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=\
    ../../../../SRC/main.cpp \
    ../../../../SRC/mainwindow.cpp \
    ../../../../SRC/bmqspinbox.cpp \
    ../../../../SRC/dlgmaskdatastyle.cpp

HEADERS  += \
    ../../../../SRC/mainwindow.h \
    ../../../../SRC/bmqspinbox.h \
    ../../../../SRC/dlgmaskdatastyle.h \
    ../../../../SRC/maskdata.h

FORMS    += \
    ../../../../SRC/mainwindow.ui \
    ../../../../SRC/dlgmaskdatastyle.ui

INCLUDEPATH += ../../../../SRC/

DEPENDPATH  += ../../../../SRC

RESOURCES += \
    ../../../../SRC/res.qrc
