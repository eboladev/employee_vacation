#-------------------------------------------------
#
# Project created by QtCreator 2013-03-15T17:11:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += \
    main.cpp \
    calendar_item_delegate.cpp \
    data_model_month.cpp \
    tableview_month_calendar.cpp \
    calendar_data.cpp \
    calendar_item_painter.cpp \
    calendar_item.cpp

HEADERS  += \
    tableview_month_calendar.h \
    data_model_month.h \
    calendar_item_delegate.h \
    calendar_item.h \
    calendar_data.h \
    calendar_item_painter.h
