#ifndef DIALOG_HOSPITALIZATION_H
#define DIALOG_HOSPITALIZATION_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QIcon>

namespace Ui {
class Dialog_hospitalization;
}

class Dialog_hospitalization : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_hospitalization(QWidget *parent = 0);
    ~Dialog_hospitalization();
    QString global_id;
    QString global_staff;
    int global_param;

private:
    Ui::Dialog_hospitalization *ui;
public slots:
    void setParam(int param, QString id, QString staff);
    void get_data();
    void send_data();
    void check_change_check(int);
    void config_ui();
};

#endif // DIALOG_HOSPITALIZATION_H
