#ifndef NEW_CHANGES_THREAD_H
#define NEW_CHANGES_THREAD_H

#include <QObject>

class new_changes_thread : public QObject
{
    Q_OBJECT
public:
    explicit new_changes_thread(QObject *parent = 0);

signals:

public slots:
};

#endif // NEW_CHANGES_THREAD_H
