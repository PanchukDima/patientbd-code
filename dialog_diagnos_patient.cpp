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
