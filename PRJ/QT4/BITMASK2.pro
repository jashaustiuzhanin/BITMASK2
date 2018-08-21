#-------------------------------------------------
#
# Project created by QtCreator 2018-04-03T15:27:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BITMASK2
TEMPLATE = app

CONFIG -= debug_and_release debug_and_release_target

CONFIG(debug, debug|release){
    BUILD_SUB_PATH = QT4_DEBUG
}else{
    BUILD_SUB_PATH = QT4_RELEASE
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
    ../../SRC/dialogcolorst0.cpp \
    ../../SRC/dialogcolorst1.cpp \
    ../../SRC/dialogcolorallst.cpp \
    ../../LIB/libmodbus/src/modbus-tcp.c \
    ../../LIB/libmodbus/src/modbus-rtu.c \
    ../../LIB/libmodbus/src/modbus-data.c \
    ../../LIB/libmodbus/src/modbus.c \
    ../../SRC/tmodbusparams.cpp \
    ../../SRC/dialogmodbusparams.cpp

HEADERS  += \
    ../../SRC/mainwindow.h \
    ../../SRC/bmqspinbox.h \
    ../../SRC/dlgmaskdatastyle.h \
    ../../SRC/maskdata.h \
    ../../SRC/settings.h \
    ../../SRC/colorschema.h \
    ../../SRC/dialogcolorst0.h \
    ../../SRC/dialogcolorst1.h \
    ../../SRC/dialogcolorallst.h \
    ../../LIB/libmodbus/config.h \
    ../../SRC/tmodbusparams.h \
    ../../SRC/dialogmodbusparams.h

FORMS    += \
    ../../SRC/mainwindow.ui \
    ../../SRC/dlgmaskdatastyle.ui \
    ../../SRC/dialogcolorst0.ui \
    ../../SRC/dialogcolorst1.ui \
    ../../SRC/dialogcolorallst.ui \
    ../../SRC/dialogmodbusparams.ui

INCLUDEPATH += ../../SRC/ \
               ../../LIB/libmodbus/ \
               ../../LIB/libmodbus/src/

DEPENDPATH  += ../../SRC \
               ../../LIB/libmodbus/ \
               ../../LIB/libmodbus/src/

RESOURCES += \
    ../../SRC/res.qrc

#RC_FILE += ../../SRC/mainico.rc
win32 {
RC_FILE += ../../SRC/appinfo.rc
LIBS += -lsetupapi -lwsock32 -lws2_32
DEFINES +=  EINPROGRESS=WSAEINPROGRESS
}
