#ifndef DIALOG_PATIENT_H
#define DIALOG_PATIENT_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QIcon>
namespace Ui {
class Dialog_patient;
}

class Dialog_patient : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_patient(QWidget *parent = 0);
    ~Dialog_patient();
    QSqlDatabase dbsql;
    int global_param;
    int global_id;
    QString global_staff_id;



private:
    Ui::Dialog_patient *ui;
public slots:
    void setParam(int ,int, QString);
    void get_data_sql(int);
    void apply_send_data_sql();
    void put_all_settings();
    void ok_send_data_sql();
    void button_cancel();
    void add_street();
    void set_default_color_lineedit_fname();
    void set_default_color_lineedit_name();
    void set_default_color_lineedit_mname();
    void set_default_color_lineedit_serial_passport();
    void set_default_color_lineedit_number_passport();
    void set_default_color_lineedit_house();
    void check_data();


};

#endif // DIALOG_PATIENT_H
