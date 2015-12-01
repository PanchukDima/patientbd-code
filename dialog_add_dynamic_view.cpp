#include "dialog_add_dynamic_view.h"
#include "ui_dialog_add_dynamic_view.h"
#include <QDebug>

Dialog_add_dynamic_view::Dialog_add_dynamic_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_add_dynamic_view)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->radioButton_d->setChecked(true);
    connect(ui->radioButton_d,SIGNAL(toggled(bool)),SLOT(active_radio_button(bool)));
    connect(ui->pushButton_OK,SIGNAL(clicked()),SLOT(send_data()));
    connect(ui->pushButton_Cancel,SIGNAL(clicked()),SLOT(close()));
}

Dialog_add_dynamic_view::~Dialog_add_dynamic_view()
{
    delete ui;
}
void Dialog_add_dynamic_view::setParam(int param, QString id,QString staff)
{

    global_param = param;
    global_staff = staff;
    if(param==1)
    {
        global_id_row=id;
        getData();
    }
    else if(param==0)
    {
         global_id = id;
    }

}

void Dialog_add_dynamic_view::active_radio_button(bool q)
{
    if(q)
    {
        ui->groupBox_ambulance->setEnabled(true);

    }
    else
    {
        ui->groupBox_ambulance->setEnabled(false);
    }
}
void Dialog_add_dynamic_view::getData()
{
    QSqlDatabase  db = QSqlDatabase::database();
    QSqlQuery query;
    if(db.open())
    {
        QString sqlquery;
        sqlquery.append("SELECT \
                        dynamic_view.on_date, \
                        dynamic_view.group_disp_view, \
                        dynamic_view.type_of_help\
                        FROM \
                        test.dynamic_view\
                        WHERE \
                        dynamic_view.delete_row = '0' AND\
                dynamic_view.id = ").append(global_id_row);
                query.exec(sqlquery);
                while(query.next())
        {
         QDate date_value = query.value(0).toDate();
         int group_disp_value = query.value(1).toInt();
         int type_to_help = query.value(2).toInt();
         ui->dateEdit->setDate(date_value);
         switch (group_disp_value) {
         case 1:
             ui->radioButton_d->setChecked(true);
             ui->radioButton_lp->setChecked(false);
             ui->radioButton_no->setChecked(false);
             break;
         case 2:
             ui->radioButton_d->setChecked(false);
             ui->radioButton_lp->setChecked(true);
             ui->radioButton_no->setChecked(false);
             break;
         case 3:
             ui->radioButton_d->setChecked(false);
             ui->radioButton_lp->setChecked(false);
             ui->radioButton_no->setChecked(true);
             break;
         }
         switch (type_to_help) {
         case 1:
             ui->radioButton_adn->setChecked(true);
             ui->radioButton_apl->setChecked(false);
             break;
         case 2:
             ui->radioButton_adn->setChecked(false);
             ui->radioButton_apl->setChecked(true);
             break;
         }
        }


    }
}

void Dialog_add_dynamic_view::send_data()
{
    QSqlDatabase  db = QSqlDatabase::database();
    QSqlQuery query;
    QString date = ui->dateEdit->text();



    if(ui->radioButton_d->isChecked())
    {
        dynamic_type="1";
    }
    if(ui->radioButton_lp->isChecked())
    {
        dynamic_type="2";
    }
    if(ui->radioButton_no->isChecked())
    {
        dynamic_type="3";
    }
    if(ui->radioButton_adn->isChecked())
    {
        help_type="1";
    }
    if(ui->radioButton_apl->isChecked())
    {
        help_type="2";
    }
    if(db.open())
    {
        switch (global_param) {
        case 0:
            //insert
            if(dynamic_type=="1")
            {
                query.exec("INSERT INTO test.dynamic_view(medcard_id, type_of_help, group_disp_view, on_date, staff_add_id, delete_row)VALUES ('"+global_id+"', '"+help_type+"', '"+dynamic_type+"', '"+date+"','"+global_staff+"','0');");
                Dialog_add_dynamic_view::accept();
            }
            else
            {
                query.exec("INSERT INTO test.dynamic_view(medcard_id, type_of_help, group_disp_view, on_date,staff_add_id, delete_row)VALUES ('"+global_id+"', '0', '"+dynamic_type+"', '"+date+"', '"+global_staff+"', '0');");
                Dialog_add_dynamic_view::accept();
            }
            break;
        case 1:
            if(dynamic_type=="1")
            {
                query.exec("UPDATE test.dynamic_view SET type_of_help='"+help_type+"', group_disp_view='"+dynamic_type+"', on_date='"+date+"' WHERE dynamic_view.id="+global_id_row);
                Dialog_add_dynamic_view::accept();
            }
            else
            {
                qDebug()<<"UPDATE test.dynamic_view SET type_of_help='0', group_disp_view='"+dynamic_type+"' WHERE  dynamic_view.id="+global_id_row;
                query.exec("UPDATE test.dynamic_view SET type_of_help='0', group_disp_view='"+dynamic_type+"', on_date='"+date+"' WHERE  dynamic_view.id="+global_id_row);
                Dialog_add_dynamic_view::accept();
            }
            break;
        }
    }


}
