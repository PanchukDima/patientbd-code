#ifndef NEW_CHANGES_THREAD_H
#define NEW_CHANGES_THREAD_H

#include <QObject>
#include "windows.h" //Unix not Work
#include <QFileInfo>
#include <QtSql>
#include <QDateTime>
#include <QSettings>
#include <QDebug>
#include <QFileSystemWatcher>
#include <QFile>

#include "mainwindow.h"

class new_changes_thread : public QObject
{
    Q_OBJECT
public:
    explicit new_changes_thread(QObject *parent = 0);
    ~new_changes_thread();
    QString global_session_id;

signals:
    void finished();
    void status(QString st);
public slots:
    void check_new_changes_blanks();
    void get_session_id();


};

#endif // NEW_CHANGES_THREAD_H
