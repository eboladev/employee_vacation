#-------------------------------------------------
#
# Project created by QtCreator 2013-04-17T16:33:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = employee_vacation
TEMPLATE = app

SOURCES += \
    src/gui/widget_calendar/calendar_item.cpp \
    src/gui/widget_calendar/calendar_item_painter.cpp \
    src/gui/widget_calendar/calendar_item_delegate.cpp \
    src/gui/widget_calendar/calendar_data.cpp \
    src/gui/widget_calendar/tableview_month_calendar.cpp \
    src/gui/widget_calendar/data_model_month.cpp \
    src/main.cpp \
    src/gui/widget_calendar/widget_year_calendar.cpp \
    src/gui/listview_employee.cpp \
    src/app/application.cpp \
    src/db_module/data_adapter_employee.cpp \
    src/logic/data_model_employee.cpp \
    src/logic/business_logic.cpp \
    src/qt_sqlite/qt_sqlite_dbvalue.cpp \
    src/qt_sqlite/qt_sqlite_connection.cpp \
    src/qt_sqlite/qt_sqlite_command.cpp \
    src/qt_sqlite/qt_data_row.cpp \
    src/qt_sqlite/qt_data_parameter.cpp \
    src/gui/delegate_line_edit.cpp \
    src/gui/widget_central.cpp \
    src/gui/main_window.cpp \
    src/app/application_params.cpp \
    src/gui/widget_employee.cpp \
    src/gui/dialog_employee.cpp \
    src/db_module/data_adapter_vacation_period.cpp \
    src/gui/widget_employee_vacation.cpp \
    src/logic/thread_object.cpp

HEADERS  += \
    src/gui/widget_calendar/calendar_item.h \
    src/gui/widget_calendar/calendar_item_painter.h \
    src/gui/widget_calendar/calendar_item_delegate.h \
    src/gui/widget_calendar/calendar_data.h \
    src/gui/widget_calendar/tableview_month_calendar.h \
    src/gui/widget_calendar/data_model_month.h \
    src/gui/widget_calendar/widget_year_calendar.h \
    src/gui/listview_employee.h \
    src/app/application.h \
    src/db_module/data_adapter_employee.h \
    src/logic/data_model_employee.h \
    src/logic/business_logic.h \
    src/qt_sqlite/qt_sqlite_dbvalue.h \
    src/qt_sqlite/qt_sqlite_connection.h \
    src/qt_sqlite/qt_sqlite_command.h \
    src/qt_sqlite/qt_data_row.h \
    src/qt_sqlite/qt_data_parameter.h \
    src/gui/delegate_line_edit.h \
    src/gui/widget_central.h \
    src/gui/main_window.h \
    src/app/application_params.h \
    src/gui/widget_employee.h \
    src/gui/dialog_employee.h \
    src/db_module/data_adapter_vacation_period.h \
    src/gui/widget_employee_vacation.h \
    src/utils/date_period.h \
    src/logic/thread_object.h

INCLUDEPATH += src/gui/widget_calendar \
				src/gui \
				src/app \
				src/db_module \
				src/logic \
				src/utils \
				src/qt_sqlite

MOC_DIR = ./xmoc
OBJECTS_DIR = ./xobj
UI_DIR = ./ui
UI_HEADERS_DIR = ./ui_src
UI_SOURCES_DIR = ./ui_src
RCC_DIR = ./xrcc
RESOURCES += \
    res/employee_vacation.qrc
TRANSLATIONS += ts/strings_ru.ts

unix: {
LIBS += /usr/lib64/libsqlite3.so
}

win32: {
INCLUDEPATH += J:/Qt/sqlite
LIBS += J:/Qt/sqlite/sqlite3.dll
RC_FILE += res/winres/app_icon.rc
}

