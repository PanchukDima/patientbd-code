#include "dialog_diagnos_patient.h"
#include "ui_dialog_diagnos_patient.h"

Dialog_diagnos_patient::Dialog_diagnos_patient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_diagnos_patient)
{
    ui->setupUi(this);
}

Dialog_diagnos_patient::~Dialog_diagnos_patient()
{
    delete ui;
}

void Dialog_diagnos_patient::setParam(int param, QString id, QString staff_id)
{
    global_param =param;
    global_id = id;
    global_staff_id =staff_id;
    switch (param) {
    case 0:
        //add diagnos
        break;
    case 1:
        //edit duiagnos
        break;
    }
}
void Dialog_diagnos_patient::get_data()
{

}
void Dialog_diagnos_patient::send_data()
{

}
