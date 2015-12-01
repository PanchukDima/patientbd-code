#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T17:57:38
#
#-------------------------------------------------

QT       += core gui sql axcontainer printsupport webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = base
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_patient.cpp \
    dialog_settings_user.cpp \
    dialog_login.cpp \
    dialog_registratura.cpp \
    dialog_reports.cpp \
    dialog_add_dynamic_view.cpp \
    dialog_add_visits.cpp \
    dialog_preview_print.cpp

HEADERS  += mainwindow.h \
    dialog_patient.h \
    dialog_settings_user.h \
    dialog_login.h \
    dialog_registratura.h \
    dialog_reports.h \
    dialog_add_dynamic_view.h \
    dialog_add_visits.h \
    dialog_preview_print.h

FORMS    += mainwindow.ui \
    dialog_patient.ui \
    dialog_settings_user.ui \
    dialog_login.ui \
    dialog_registratura.ui \
    dialog_reports.ui \
    dialog_add_dynamic_view.ui \
    dialog_add_visits.ui \
    dialog_preview_print.ui

RESOURCES += \
    images.qrc
LIBS += -L /plugin/sqldrivers

