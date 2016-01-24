#include "dialog_invalids_patient.h"
#include "ui_dialog_invalids_patient.h"

Dialog_invalids_patient::Dialog_invalids_patient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_invalids_patient)
{
    ui->setupUi(this);
    setting();
}

Dialog_invalids_patient::~Dialog_invalids_patient()
{
    delete ui;
}
void Dialog_invalids_patient::setting()
{
    ui->comboBox_invalids->addItem("I","0");
    ui->comboBox_invalids->addItem("II","1");
    ui->comboBox_invalids->addItem("III","2");
    ui->dateEdit->setDate(QDate::currentDate());
}
void Dialog_invalids_patient::setParam(int, QString, QString)
{

}
void Dialog_invalids_patient::get_data()
{

}
void Dialog_invalids_patient::send_data()
{

}
