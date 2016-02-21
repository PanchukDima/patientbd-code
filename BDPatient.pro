#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T17:57:38
#
#-------------------------------------------------

QT       += core gui sql axcontainer printsupport webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = base
TEMPLATE = app
#CONFIG += CONSOLE


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_patient.cpp \
    dialog_settings_user.cpp \
    dialog_login.cpp \
    dialog_registratura.cpp \
    dialog_reports.cpp \
    dialog_add_dynamic_view.cpp \
    dialog_add_visits.cpp \
    dialog_preview_print.cpp \
    new_changes_thread.cpp \
    dialog_diagnos_patient.cpp \
    dialog_hospitalization.cpp \
    dialog_copy_files_to_server.cpp \
    dialog_invalids_patient.cpp \
    dialog_find_filters.cpp

HEADERS  += mainwindow.h \
    dialog_patient.h \
    dialog_settings_user.h \
    dialog_login.h \
    dialog_registratura.h \
    dialog_reports.h \
    dialog_add_dynamic_view.h \
    dialog_add_visits.h \
    dialog_preview_print.h \
    new_changes_thread.h \
    dialog_diagnos_patient.h \
    dialog_hospitalization.h \
    dialog_copy_files_to_server.h \
    dialog_invalids_patient.h \
    dialog_find_filters.h

FORMS    += mainwindow.ui \
    dialog_patient.ui \
    dialog_settings_user.ui \
    dialog_login.ui \
    dialog_registratura.ui \
    dialog_reports.ui \
    dialog_add_dynamic_view.ui \
    dialog_add_visits.ui \
    dialog_preview_print.ui \
    dialog_diagnos_patient.ui \
    dialog_hospitalization.ui \
    dialog_copy_files_to_server.ui \
    dialog_invalids_patient.ui \
    dialog_find_filters.ui

RESOURCES += \
    images.qrc
LIBS += -L /plugin/sqldrivers
INCLUDEPATH += C:/ProjectPSI/nonstoklibrary/poppler-0.40.0/qt5/src

