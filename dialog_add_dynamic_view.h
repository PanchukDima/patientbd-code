#ifndef DIALOG_ADD_DYNAMIC_VIEW_H
#define DIALOG_ADD_DYNAMIC_VIEW_H

#include <QDialog>
#include <QSql>
#include<QSqlQuery>

namespace Ui {
class Dialog_add_dynamic_view;
}

class Dialog_add_dynamic_view : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_add_dynamic_view(QWidget *parent = 0);
    ~Dialog_add_dynamic_view();
    QString global_id;
    QString global_id_row;
    int global_param;
    QString global_staff;
    QString dynamic_type;
    QString help_type;


private:
    Ui::Dialog_add_dynamic_view *ui;
public slots:
    void active_radio_button(bool);
    void send_data();
    void setParam(int,QString,QString);
    void getData();

};

#endif // DIALOG_ADD_DYNAMIC_VIEW_H
