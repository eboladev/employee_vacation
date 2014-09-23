TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../src/datetime.cpp

HEADERS += \
    ../../include/datetime.h

INCLUDEPATH += ../../include
