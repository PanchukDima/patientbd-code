#include "dialog_add_dynamic_view.h"
#include "ui_dialog_add_dynamic_view.h"
#include <QDebug>

Dialog_add_dynamic_view::Dialog_add_dynamic_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_add_dynamic_view)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_adn->setDate(QDate::currentDate());
    ui->dateEdit_apl->setDate(QDate::currentDate());
    ui->radioButton_d->setChecked(true);
    ui->dateEdit_adn->setEnabled(false);
    ui->dateEdit_apl->setEnabled(false);
    block_state = false;

    connect(ui->radioButton_d,SIGNAL(toggled(bool)),SLOT(active_radio_button(bool)));
    connect(ui->radioButton_k,SIGNAL(toggled(bool)),SLOT(active_radio_button_k(bool)));
    connect(ui->radioButton_lp,SIGNAL(toggled(bool)),SLOT(active_radio_button_lp(bool)));
    connect(ui->checkBox_adn,SIGNAL(toggled(bool)),SLOT(active_adn_check(bool)));
    connect(ui->checkBox_apl,SIGNAL(toggled(bool)),SLOT(active_apl_check(bool)));
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
        ui->radioButton_k->setEnabled(false);
        ui->radioButton_lp->setEnabled(false);
        ui->radioButton_d->setEnabled(false);
        ui->frame->setEnabled(false);
        getData();
    }
    else if(param==0)
    {
         global_id = id;
    }

}

void Dialog_add_dynamic_view::active_adn_check(bool state)
{
    if(state)
    {
        ui->dateEdit_adn->setEnabled(true);
    }
    else
    {
        ui->dateEdit_adn->setEnabled(false);
    }
}
void Dialog_add_dynamic_view::active_apl_check(bool state)
{
    if(state)
    {
        ui->dateEdit_apl->setEnabled(true);
    }
    else
    {
        ui->dateEdit_apl->setEnabled(false);
    }
}
void Dialog_add_dynamic_view::active_radio_button_k(bool q)
{
    if(q)
    {
        ui->radioButton_d->setChecked(false);
        ui->radioButton_lp->setChecked(false);
        ui->checkBox_adn->setCheckState(Qt::Unchecked);
        ui->checkBox_apl->setCheckState(Qt::Unchecked);
    }

}
void Dialog_add_dynamic_view::active_radio_button(bool q)
{
    if(q)
    {
        ui->groupBox_ambulance->setEnabled(true);
        ui->radioButton_k->setChecked(false);
        ui->radioButton_lp->setChecked(false);
        ui->frame->setEnabled(true);
    }
    else
    {
        ui->groupBox_ambulance->setEnabled(false);
        ui->frame->setEnabled(false);
    }
}
void Dialog_add_dynamic_view::active_radio_button_lp(bool q)
{
    if(q)
    {
        ui->radioButton_d->setChecked(false);
        ui->radioButton_k->setChecked(false);
        ui->checkBox_adn->setCheckState(Qt::Unchecked);
        ui->checkBox_apl->setCheckState(Qt::Unchecked);
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
                        dynamic_view.group_disp_view \
                        FROM \
                        test.dynamic_view\
                        WHERE \
                        dynamic_view.delete_row = '0' AND\
                dynamic_view.medcard_id = ").append(global_id_row);
                query.exec(sqlquery);
                while(query.next())
                {
                qDebug()<<query.value(1).toInt()<<query.value(0).toString();
                int type_help = query.value(1).toInt();
                switch (type_help) {
                case 1:
                    ui->radioButton_d->setChecked(true);
                    ui->radioButton_1->setChecked(true);
                    ui->dateEdit->setDate(query.value(0).toDate());
                    break;
                case 2:
                    ui->radioButton_d->setChecked(true);
                    ui->radioButton_2->setChecked(true);
                    ui->dateEdit->setDate(query.value(0).toDate());
                    break;
                case 3:
                    ui->radioButton_d->setChecked(true);
                    ui->radioButton_3->setChecked(true);
                    ui->dateEdit->setDate(query.value(0).toDate());
                    break;
                case 4:
                    ui->radioButton_d->setChecked(true);
                    ui->radioButton_4->setChecked(true);
                    ui->dateEdit->setDate(query.value(0).toDate());
                    break;
                case 5:
                    ui->radioButton_d->setChecked(true);
                    ui->radioButton_5->setChecked(true);
                    ui->dateEdit->setDate(query.value(0).toDate());
                    break;
                case 6:
                    ui->radioButton_d->setChecked(true);
                    ui->radioButton_6->setChecked(true);
                    ui->dateEdit->setDate(query.value(0).toDate());
                    break;
                case 7:
                    ui->radioButton_d->setChecked(true);
                    ui->radioButton_7->setChecked(true);
                    ui->dateEdit->setDate(query.value(0).toDate());
                    break;
                case 8:
                    ui->checkBox_adn->setEnabled(false);
                    ui->dateEdit_adn->setDate(query.value(0).toDate());
                    block_message = "Добавлен АДН";
                    block_state = true;
                    break;
                case 9:
                    ui->checkBox_apl->setCheckState(Qt::Checked);
                    ui->checkBox_apl->setEnabled(false);
                    ui->dateEdit_apl->setDate(query.value(0).toDate());
                    block_message = "Добавлен АПЛ";
                    block_state = true;
                    break;
                case 10:
                    ui->radioButton_lp->setChecked(true);
                    ui->dateEdit->setDate(query.value(0).toDate());
                    ui->radioButton_d->setEnabled(false);
                    ui->frame->setEnabled(false);
                    break;
                case 11:
                    ui->radioButton_k->setChecked(true);
                    ui->dateEdit->setDate(query.value(0).toDate());
                    ui->radioButton_d->setEnabled(false);
                    ui->frame->setEnabled(false);
                    break;
                }
        }
    }
}

void Dialog_add_dynamic_view::send_data()
{
    QSqlDatabase  db = QSqlDatabase::database();
    QSqlQuery query;
    QString date = ui->dateEdit->date().toString("MM.dd.yyyy");
    QString type_disp_view;
    switch (global_param) {
    case 1:
        if(ui->checkBox_adn->isEnabled())
        {
            if(ui->checkBox_adn->isChecked())
            {
                type_disp_view = "8";
                QString date_adn = ui->dateEdit_adn->date().toString("MM.dd.yyyy");
                if(db.open())
                {
                    query.exec("INSERT INTO test.dynamic_view(medcard_id, on_date, staff_add_id, group_disp_view, status , delete_row) VALUES ("+global_id+", '"+date_adn+"',"+global_staff+", "+type_disp_view+", 'false', '0')");
                }

            }
        }
        if(ui->checkBox_apl->isEnabled())
        {
            if(ui->checkBox_apl->isChecked())
            {
                type_disp_view = "9";
                QString date_apl = ui->dateEdit_apl->date().toString("MM.dd.yyyy");
                //insert apl
                if(db.open())
                {
                    query.exec("INSERT INTO test.dynamic_view(medcard_id, on_date, staff_add_id, group_disp_view, status, delete_row) VALUES ("+global_id+", '"+date_apl+"',"+global_staff+", "+type_disp_view+", 'false', '0')");
                }
            }
        }
        break;
    case 0:

    if(ui->radioButton_1->isChecked())
    {
        type_disp_view="1";
    }
    if(ui->radioButton_2->isChecked())
    {
        type_disp_view="2";
    }
    if(ui->radioButton_3->isChecked())
    {
        type_disp_view="3";
    }
    if(ui->radioButton_4->isChecked())
    {
        type_disp_view="4";
    }
    if(ui->radioButton_5->isChecked())
    {
        type_disp_view="5";
    }
    if(ui->radioButton_6->isChecked())
    {
        type_disp_view="6";
    }
    if(ui->radioButton_7->isChecked())
    {
        type_disp_view="7";
    }
    if(!block_state)
    {
        if(ui->radioButton_lp->isChecked())
        {
            type_disp_view = "10";
        }
    }
    else
    {
        global_block();
    }
    if(db.open())
    {
        QDate date_d = ui->dateEdit->date();
        switch (type_disp_view.toInt()) {
        case 1:
            //insert control pos 1 week
            date_d = date_d.addDays(7);
            qDebug()<<date_d;
            break;
        case 2:
            //insert control pos 2 week
            date_d = date_d.addDays(14);
            qDebug()<<date_d;
            break;
        case 3:
            //insert control pos 1 mounth
            date_d = date_d.addMonths(1);
            qDebug()<<date_d;
            break;
        case 4:
            //insert control pos 3 mounth
            date_d = date_d.addMonths(3);
            qDebug()<<date_d;
            break;
        case 5:
            //insert control pos 1/2 year
            date_d = date_d.addMonths(6);
            qDebug()<<date_d;
            break;
        case 6:
            //insert control pos 1 year
            date_d = date_d.addYears(1);
            qDebug()<<date_d;
            break;
        case 7:
            //insert control pos stationar
            break;
        }
        QString date = date_d.toString("MM.dd.yyyy");
        query.exec("INSERT INTO test.visits_control(date_assigned, medcard_id, staff_add_id, delete_row) VALUES ('"+date+"', "+global_id+", "+global_staff+", '0');");
    }

    if(db.open())
    {
    query.exec("INSERT INTO test.dynamic_view(medcard_id, on_date, staff_add_id, group_disp_view, status, delete_row) VALUES ("+global_id+", '"+date+"',"+global_staff+", "+type_disp_view+", 'false', '0')");
    }
    if(ui->radioButton_d->isChecked())
    {
        if(ui->checkBox_adn->isChecked())
        {
            type_disp_view = "8";
            QString date_adn = ui->dateEdit_adn->date().toString("MM.dd.yyyy");
            if(db.open())
            {
            query.exec("INSERT INTO test.dynamic_view(medcard_id, on_date, staff_add_id, group_disp_view, status , delete_row) VALUES ("+global_id+", '"+date_adn+"',"+global_staff+", "+type_disp_view+", 'false', '0')");
            }

        }
        if(ui->checkBox_apl->isChecked())
        {
            type_disp_view = "9";
            QString date_apl = ui->dateEdit_apl->date().toString("MM.dd.yyyy");
            //insert apl
            if(db.open())
            {
            query.exec("INSERT INTO test.dynamic_view(medcard_id, on_date, staff_add_id, group_disp_view, status, delete_row) VALUES ("+global_id+", '"+date_apl+"',"+global_staff+", "+type_disp_view+", 'false', '0')");
            }
       }
    }
        break;
    }
    Dialog_add_dynamic_view::accept();

}
void Dialog_add_dynamic_view::global_block()
{
    QMessageBox::warning(this, tr("Ошибка"), block_message, QMessageBox::Ok);
    Dialog_add_dynamic_view::close();
}
