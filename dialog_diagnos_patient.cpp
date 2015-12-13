#include "dialog_diagnos_patient.h"
#include "ui_dialog_diagnos_patient.h"

Dialog_diagnos_patient::Dialog_diagnos_patient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_diagnos_patient)
{
    ui->setupUi(this);
    load_allow_date();
    connect(ui->pushButton_ok,SIGNAL(clicked(bool)),SLOT(send_data()));
    connect(ui->pushButton_cancel,SIGNAL(clicked(bool)),SLOT(close()));
}

Dialog_diagnos_patient::~Dialog_diagnos_patient()
{
    delete ui;
}

void Dialog_diagnos_patient::load_allow_date()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    if(db.open())
    {
            query.exec("SELECT \
               diagnos.id,\
               diagnos.name,\
               diagnos.code\
             FROM\
               test.diagnos;");
    while (query.next())
    {
        QString id_diagnos = query.value(0).toString();
        QString diagnos = query.value(2).toString();
        diagnos.append(":  :").append(query.value(1).toString());
        ui->comboBox_diagnos->addItem(diagnos, id_diagnos);

    }
    }
}

void Dialog_diagnos_patient::setParam(int param, QString id, QString staff_id)
{
    global_param = param;
    global_id = id;
    global_staff_id = staff_id;
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
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    if(db.open())
    {
        query.exec("0"); //select
    }

}
void Dialog_diagnos_patient::send_data()
{
    QString date_fixing_diagnos = ui->dateEdit_date_fixing_diagnos->date().toString("MM.dd.yyyy");
    QString diagnos_id = ui->comboBox_diagnos->currentData().toString();
    switch (global_param) {
    case 0:
        //insert

        break;
    case 1:
        //update

        break;
    }
}
