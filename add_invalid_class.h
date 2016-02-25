#ifndef ADD_INVALID_CLASS_H
#define ADD_INVALID_CLASS_H

#include <QObject>
#include <QtSql>

class add_invalid_class : public QObject
{
    Q_OBJECT
public:
    explicit add_invalid_class(QObject *parent = 0);

signals:
    send_ok();
    error(int);

public slots:
    void send_data(QString global_id,QString global_staff_id, QString group_invalid_value,QString from_other_value,QString work_yes_value, bool bs);


};

#endif // ADD_INVALID_CLASS_H
