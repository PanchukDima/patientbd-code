#include "dialog_invalids_patient.h"
#include "ui_dialog_invalids_patient.h"

Dialog_invalids_patient::Dialog_invalids_patient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_invalids_patient)
{
    ui->setupUi(this);
    setting();
    connect(ui->checkBox_alltime,SIGNAL(stateChanged(int)),SLOT(check_state_changes(int)));
    connect(ui->lineEdit_date_view,SIGNAL(textChanged(QString)),SLOT(point_add_date(QString)));
    connect(ui->lineEdit_pereosved,SIGNAL(textChanged(QString)),SLOT(point_add_date_preosved(QString)));
    connect(ui->pushButton_ok,SIGNAL(clicked(bool)),SLOT(send_data()));
    connect(ui->pushButton_cancel,SIGNAL(clicked(bool)),SLOT(close()));
}

Dialog_invalids_patient::~Dialog_invalids_patient()
{
    delete ui;
}
void Dialog_invalids_patient::setting()
{
    ui->comboBox_group_inv->addItem("I","0");
    ui->comboBox_group_inv->addItem("II","1");
    ui->comboBox_group_inv->addItem("III","2");
}
void Dialog_invalids_patient::setParam(int param, QString id, QString staff)
{
    global_id=id;
    global_staff_id=staff;
}
void Dialog_invalids_patient::check_state_changes(int state)
{
    if(state)
    {
        ui->label_3->hide();
        ui->lineEdit_date_view->hide();
    }
    else
    {
        ui->label_3->show();
        ui->lineEdit_date_view->show();
    }
}

void Dialog_invalids_patient::get_data()
{

}
void Dialog_invalids_patient::send_data()
{
    QSqlDatabase db=QSqlDatabase::database();
    QSqlQuery query;
    QString group_invalid_value = ui->comboBox_group_inv->currentData().toString();
    QString from_other_value;
    QString work_yes_value;
    QString date_review_value;
    QString date_review_value_test;
    QString date_pereosved_value;
    QString date_pereosved_value_test = validate_date(ui->lineEdit_pereosved->text());

    if(ui->checkBox_alltime->checkState()==Qt::Unchecked)
    {
        date_review_value_test = validate_date(ui->lineEdit_date_view->text());
    }
    if(date_pereosved_value_test=="exit")
    {
        return;
    }
    else
    {
        date_pereosved_value=date_pereosved_value_test;
    }

    if(date_review_value_test=="exit")
    {
        return;
    }
    else
    {
        date_review_value=date_review_value_test;
    }

    if(ui->checkBox_work_yes->checkState()==Qt::Checked)
    {
        work_yes_value="true";
    }
    else if (ui->checkBox_work_yes->checkState()==Qt::Unchecked)
    {
        work_yes_value="false";
    }

    if(ui->checkBox_from_other->checkState()==Qt::Checked)
    {
        from_other_value="true";
    }
    else if (ui->checkBox_from_other->checkState()==Qt::Unchecked)
    {
        from_other_value="false";
    }


    if(db.open())
    {
        if(ui->checkBox_alltime->checkState()==Qt::Checked)
        {
        query.exec("INSERT INTO test.invalid_patient(medcard_id, staff_add_id, group_inv, priznan_trudosp, from_other, date_peresmotra, srok_ocherednogo_pereosvidet, bs) VALUES ('"+global_id+"', '"+global_staff_id+"', '"+group_invalid_value+"', '"+work_yes_value+"', '"+from_other_value+"', '"+date_review_value+"', NULL, true);");
        }
        else if (ui->checkBox_alltime->checkState()==Qt::Unchecked)
        {
            query.exec("INSERT INTO test.invalid_patient(medcard_id, staff_add_id, group_inv, priznan_trudosp, from_other, date_peresmotra, srok_ocherednogo_pereosvidet, bs) VALUES ('"+global_id+"', '"+global_staff_id+"', '"+group_invalid_value+"', '"+work_yes_value+"', '"+from_other_value+"', '"+date_review_value+"', '"+date_pereosved_value+"', false);");
        }
        Dialog_invalids_patient::accept();
    }

}
QString const Dialog_invalids_patient::validate_date(QString date)
{
    QStringList day_list = date.split(".");
    QString day;
    QString month;
    QString year;
    QDate date_valid;
    QString date_valid_string;
    if(day_list.count()==3)
    {
        day = day_list[0];
        month = day_list[1];
        year = day_list[2];
        if(date_valid.setDate(year.toInt(),month.toInt(),day.toInt()))
        {
            date_valid_string = date_valid.toString("MM.dd.yyyy");
            return date_valid_string;
        }
        else
        {
            QMessageBox::information(this,"Не правильная дата","Не правильная дата");
            return "exit";
        }
    }
    else
    {
        QMessageBox::information(this,"Не правильный формат даты","Не правильный формат даты");
        return "exit";

    }
}
void Dialog_invalids_patient::point_add_date(QString text)
{
    switch (text.count()) {
    case 2:
        if(text.lastIndexOf(".")!=1)
        {
        ui->lineEdit_date_view->setText(text+".");
        }
        break;
    case 5:

        if(text.lastIndexOf(".")!=4)
        {
            ui->lineEdit_date_view->setText(text+".");
        }
            break;
    case 11:
        text.replace(10,1,"");
        ui->lineEdit_date_view->setText(text);
        break;

    }
}
void Dialog_invalids_patient::point_add_date_preosved(QString text)
{
    switch (text.count()) {
    case 2:
        if(text.lastIndexOf(".")!=1)
        {
        ui->lineEdit_pereosved->setText(text+".");
        }
        break;
    case 5:

        if(text.lastIndexOf(".")!=4)
        {
            ui->lineEdit_pereosved->setText(text+".");
        }
            break;
    case 11:
        text.replace(10,1,"");
        ui->lineEdit_pereosved->setText(text);
        break;


    }
}
