#-------------------------------------------------
#
# Project created by QtCreator 2018-06-07T14:15:28
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    DEFINES += HAVE_QT5
}

CONFIG -= debug_and_release debug_and_release_target

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

CONFIG(debug, debug|release){
    BUILD_SUB_PATH = QT5_DEBUG
}else{
    BUILD_SUB_PATH = QT5_RELEASE
}

BUILD_PATH = $${_PRO_FILE_PWD_}/../../BLD
RCC_DIR = $${BUILD_PATH}/RCC/$${BUILD_SUB_PATH}
UI_DIR  = $${BUILD_PATH}/UI/$${BUILD_SUB_PATH}
MOC_DIR = $${BUILD_PATH}/MOC/$${BUILD_SUB_PATH}
OBJECTS_DIR = $${BUILD_PATH}/OBJ/$${BUILD_SUB_PATH}


SOURCES +=\
    ../../SRC/main.cpp \
    ../../SRC/mainwindow.cpp \
    ../../SRC/bmqspinbox.cpp \
    ../../SRC/dlgmaskdatastyle.cpp \
    ../../SRC/settings.cpp \
    ../../SRC/colorschemas_init.cpp \
    ../../SRC/qtablewidgetwithcopypaste.cpp \
    ../../SRC/thexspinbox.cpp \
    ../../SRC/tspinbox64.cpp \
    ../../SRC/dialogcolorst0.cpp \
    ../../SRC/dialogcolorallst.cpp \
    ../../SRC/dialogcolorst1.cpp \
    ../../LIB/libmodbus/src/modbus.c \
    ../../LIB/libmodbus/src/modbus-data.c \
    ../../LIB/libmodbus/src/modbus-rtu.c \
    ../../LIB/libmodbus/src/modbus-tcp.c \
    ../../SRC/tmodbusparams.cpp \
    ../../SRC/dialogmodbusparams.cpp

HEADERS  += \
    ../../SRC/mainwindow.h \
    ../../SRC/bmqspinbox.h \
    ../../SRC/dlgmaskdatastyle.h \
    ../../SRC/maskdata.h \
    ../../SRC/settings.h \
    ../../SRC/colorschema.h \
    ../../SRC/qtablewidgetwithcopypaste.h \
    ../../SRC/thexspinbox.h \
    ../../SRC/tspinbox64.h \
    ../../SRC/version.h \
    ../../SRC/dialogcolorst0.h \
    ../../SRC/dialogcolorallst.h \
    ../../SRC/dialogcolorst1.h \
    ../../LIB/libmodbus/config.h \
    ../../SRC/tmodbusparams.h \
    ../../SRC/dialogmodbusparams.h

FORMS    += \
    ../../SRC/mainwindow.ui \
    ../../SRC/dlgmaskdatastyle.ui \
    ../../SRC/dialogcolorst0.ui \
    ../../SRC/dialogcolorallst.ui \
    ../../SRC/dialogcolorst1.ui \
    ../../SRC/dialogmodbusparams.ui

INCLUDEPATH += ../../SRC/ \
               ../../LIB/libmodbus/src/ \
               ../../LIB/libmodbus/

DEPENDPATH  += ../../SRC \
               ../../LIB/libmodbus/src/ \
               ../../LIB/libmodbus/


RESOURCES += \
    ../../SRC/res.qrc

#RC_FILE += ../../SRC/mainico.rc
win32 {
RC_FILE += ../../SRC/appinfo.rc
LIBS += -lsetupapi -lwsock32 -lws2_32
}
