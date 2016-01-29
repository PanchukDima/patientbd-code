#ifndef DIALOG_PATIENT_H
#define DIALOG_PATIENT_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QIcon>
#include <QInputDialog>
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
    QString global_id_str;
    QString global_staff_id;
    QString why_remove_str;



private:
    Ui::Dialog_patient *ui;
public slots:
    void setParam(int ,int, QString);
    void get_data_sql(int);
    void apply_send_data_sql();
    void put_all_settings();
    void load_text_table();
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
    void load_text_table_1();
    void load_text_table_2();
    void load_text_table_3();
    void load_text_table_4();
    void load_text_table_5();
    void save_text_1();
    void save_text_2();
    void save_text_3();
    void save_text_4();
    void save_text_5();
    void creat_text_1();
    void creat_text_2();
    void creat_text_3();
    void creat_text_4();
    void creat_text_5();
    void del_text_1();
    void del_text_2();
    void del_text_3();
    void del_text_4();
    void del_text_5();
    void clear_table_text_1();
    void clear_table_text_2();
    void clear_table_text_3();
    void clear_table_text_4();
    void clear_table_text_5();
    void change_state_ds_end(bool);


};

#endif // DIALOG_PATIENT_H
