#ifndef NEW_CHANGES_THREAD_H
#define NEW_CHANGES_THREAD_H

#include <QObject>
#include "windows.h" //Unix not Work
#include <QFileInfo>
#include <QDateTime>
#include <QSettings>
#include <QDebug>
#include <QFileSystemWatcher>
#include <QFile>


class new_changes_thread : public QObject
{
    Q_OBJECT
public:
    explicit new_changes_thread(QObject *parent = 0);
    ~new_changes_thread();

signals:
    void finished();
    void status(QString st);
public slots:
    void check_new_changes_blanks();


};

#endif // NEW_CHANGES_THREAD_H
