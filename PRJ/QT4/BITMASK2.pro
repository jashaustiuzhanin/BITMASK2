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
    ../../SRC/settings.cpp

HEADERS  += \
    ../../SRC/mainwindow.h \
    ../../SRC/bmqspinbox.h \
    ../../SRC/dlgmaskdatastyle.h \
    ../../SRC/maskdata.h \
    ../../SRC/settings.h

FORMS    += \
    ../../SRC/mainwindow.ui \
    ../../SRC/dlgmaskdatastyle.ui

INCLUDEPATH += ../../SRC/

DEPENDPATH  += ../../SRC

RESOURCES += \
    ../../SRC/res.qrc
