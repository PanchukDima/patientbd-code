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
    global_id = id;
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

        ui->checkBox_adn->setCheckState(Qt::Unchecked);
        ui->checkBox_apl->setCheckState(Qt::Unchecked);
    }

}
void Dialog_add_dynamic_view::getData()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    if(db.open())
    {
        query.exec("SELECT on_date, group_disp_view FROM test.dynamic_view WHERE status = 'false' AND delete_row='false' AND medcard_id = "+global_id);

        while(query.next())
        {
            QDate date_dinamic = query.value(0).toDate();
            int type_disp = query.value(1).toInt();
        }
    }
}

void Dialog_add_dynamic_view::send_data()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString date_d = ui->dateEdit->date().toString("MM.dd.yyyy");
    QString date_apl = ui->dateEdit_apl->date().toString("MM.dd.yyyy");
    QString date_adn = ui->dateEdit_adn->date().toString("MM.dd.yyyy");
    QString date_visits;
    if(ui->radioButton_d->isChecked())
    {
        if(check_data(0))
        {
            QMessageBox::warning(this, tr("Ошибка"), "Уже открыта динамика наблюдения", QMessageBox::Ok);
            Dialog_add_dynamic_view::close();
        }
        else
        {

            if(ui->radioButton_1->isChecked())
            {
                if(check_data(4))
                {
                    QMessageBox::warning(this, tr("Ошибка"), "У пациента открыта АДН или АПЛ", QMessageBox::Ok);
                    Dialog_add_dynamic_view::close();
                }
                else
                {
                query.exec("INSERT INTO test.dynamic_view( medcard_id, on_date, delete_row, staff_add_id, group_disp_view, status) VALUES ( '"+global_id+"', '"+date_d+"', 'false', '"+global_staff+"', '1', 'false');");
                 date_visits = ui->dateEdit->date().addDays(7).toString("MM.dd.yyyy");
                 query.exec("INSERT INTO test.visits_control(date_assigned, medcard_id, staff_add_id, delete_row) VALUES ( '"+date_visits+"', '"+global_id+"', '"+global_staff+"', 'false');");
                }
            }
            if(ui->radioButton_2->isChecked())
            {
                if(check_data(4))
                {
                    QMessageBox::warning(this, tr("Ошибка"), "У пациента открыта АДН или АПЛ", QMessageBox::Ok);
                    Dialog_add_dynamic_view::close();
                }
                else
                {
                query.exec("INSERT INTO test.dynamic_view( medcard_id, on_date, delete_row, staff_add_id, group_disp_view, status) VALUES ( '"+global_id+"', '"+date_d+"', 'false', '"+global_staff+"', '2', 'false');");
                date_visits = ui->dateEdit->date().addDays(14).toString("MM.dd.yyyy");
                query.exec("INSERT INTO test.visits_control(date_assigned, medcard_id, staff_add_id, delete_row) VALUES ( '"+date_visits+"', '"+global_id+"', '"+global_staff+"', 'false');");

                }
            }
            if(ui->radioButton_3->isChecked())
            {
                if(check_data(4))
                {
                    QMessageBox::warning(this, tr("Ошибка"), "У пациента открыта АДН или АПЛ", QMessageBox::Ok);
                    Dialog_add_dynamic_view::close();
                }
                else
                {
                query.exec("INSERT INTO test.dynamic_view( medcard_id, on_date, delete_row, staff_add_id, group_disp_view, status) VALUES ( '"+global_id+"', '"+date_d+"', 'false', '"+global_staff+"', '3', 'false');");
                date_visits = ui->dateEdit->date().addMonths(1).toString("MM.dd.yyyy");
                query.exec("INSERT INTO test.visits_control(date_assigned, medcard_id, staff_add_id, delete_row) VALUES ( '"+date_visits+"', '"+global_id+"', '"+global_staff+"', 'false');");
                }
            }
            if(ui->radioButton_4->isChecked())
            {
                if(check_data(4))
                {
                    QMessageBox::warning(this, tr("Ошибка"), "У пациента открыта АДН или АПЛ", QMessageBox::Ok);
                    Dialog_add_dynamic_view::close();
                }
                else
                {
                query.exec("INSERT INTO test.dynamic_view( medcard_id, on_date, delete_row, staff_add_id, group_disp_view, status) VALUES ( '"+global_id+"', '"+date_d+"', 'false', '"+global_staff+"', '4', 'false');");
                date_visits = ui->dateEdit->date().addMonths(3).toString("MM.dd.yyyy");
                query.exec("INSERT INTO test.visits_control(date_assigned, medcard_id, staff_add_id, delete_row) VALUES ( '"+date_visits+"', '"+global_id+"', '"+global_staff+"', 'false');");
                }
            }
            if(ui->radioButton_5->isChecked())
            {
                if(check_data(4))
                {
                    QMessageBox::warning(this, tr("Ошибка"), "У пациента открыта АДН или АПЛ", QMessageBox::Ok);
                    Dialog_add_dynamic_view::close();
                }
                else
                {
                query.exec("INSERT INTO test.dynamic_view( medcard_id, on_date, delete_row, staff_add_id, group_disp_view, status) VALUES ( '"+global_id+"', '"+date_d+"', 'false', '"+global_staff+"', '5', 'false');");
                date_visits = ui->dateEdit->date().addMonths(6).toString("MM.dd.yyyy");
                query.exec("INSERT INTO test.visits_control(date_assigned, medcard_id, staff_add_id, delete_row) VALUES ( '"+date_visits+"', '"+global_id+"', '"+global_staff+"', 'false');");

                }
            }
            if(ui->radioButton_6->isChecked())
            {
                if(check_data(4))
                {
                    QMessageBox::warning(this, tr("Ошибка"), "У пациента открыта АДН или АПЛ", QMessageBox::Ok);
                    Dialog_add_dynamic_view::close();
                }
                else
                {
                query.exec("INSERT INTO test.dynamic_view( medcard_id, on_date, delete_row, staff_add_id, group_disp_view, status) VALUES ( '"+global_id+"', '"+date_d+"', 'false', '"+global_staff+"', '6', 'false');");
                date_visits = ui->dateEdit->date().addYears(1).toString("MM.dd.yyyy");
                query.exec("INSERT INTO test.visits_control(date_assigned, medcard_id, staff_add_id, delete_row) VALUES ( '"+date_visits+"', '"+global_id+"', '"+global_staff+"', 'false');");
            }
            }

            if(ui->radioButton_7->isChecked())
            {
                 query.exec("INSERT INTO test.dynamic_view( medcard_id, on_date, delete_row, staff_add_id, group_disp_view, status) VALUES ( '"+global_id+"', '"+date_d+"', 'false', '"+global_staff+"', '7', 'false');");

            }
        }

    }
    if(ui->checkBox_adn->checkState()==Qt::Checked)
    {
        if(check_data(0))
        {

            if(check_data(1))
            {
                query.exec("INSERT INTO test.dynamic_view( medcard_id, on_date, delete_row, staff_add_id, group_disp_view, status) VALUES ( '"+global_id+"', '"+date_adn+"', 'false', '"+global_staff+"', '8', 'false');");
            }
            else
            {
                QMessageBox::warning(this, tr("Ошибка"), "Уже открыто АДН", QMessageBox::Ok);
                Dialog_add_dynamic_view::close();
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Ошибка"), "Чтобы добавить АДН должно быть открыто диспансерное наблюдение", QMessageBox::Ok);
            Dialog_add_dynamic_view::close();

        }
    }
    if(ui->checkBox_apl->checkState()==Qt::Checked)
    {
        if(check_data(0))
        {

            if(check_data(2))
            {
                query.exec("INSERT INTO test.dynamic_view( medcard_id, on_date, delete_row, staff_add_id, group_disp_view, status) VALUES ( '"+global_id+"', '"+date_apl+"', 'false', '"+global_staff+"', '9', 'false');");

            }
            else
            {
                QMessageBox::warning(this, tr("Ошибка"), "Уже открыто АПЛ", QMessageBox::Ok);
                Dialog_add_dynamic_view::close();
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Ошибка"), "Чтобы добавить АПЛ должно быть открыто диспансерное наблюдение", QMessageBox::Ok);
            Dialog_add_dynamic_view::close();
        }
    }

Dialog_add_dynamic_view::accept();

}
void Dialog_add_dynamic_view::global_block()
{
    QMessageBox::warning(this, tr("Ошибка"), block_message, QMessageBox::Ok);
    Dialog_add_dynamic_view::close();
}

bool Dialog_add_dynamic_view::check_data(int param)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    switch (param) {
    case 0:
        query.exec("SELECT count(*) FROM test.dynamic_view WHERE status='false' AND group_disp_view IN('0','1','2','3','4','5','6','7') AND medcard_id="+global_id);
        query.next();
        if(query.value(0).toInt()>0)
        {
            return true;
        }
        else if(query.value(0).toInt()==0)
        {
            return false;
        }
        break;
    case 1:
        query.exec("SELECT count(*) FROM test.dynamic_view WHERE status='false' AND group_disp_view IN('8') AND medcard_id="+global_id);
        query.next();
        if(query.value(0).toInt()>0)
        {
            return false;
        }
        else if(query.value(0).toInt()==0)
        {
            return true;
        }
        break;
    case 2:
        query.exec("SELECT count(*) FROM test.dynamic_view WHERE status='false' AND group_disp_view IN('9') AND medcard_id="+global_id);
        query.next();
        if(query.value(0).toInt()>0)
        {
            return false;
        }
        else if(query.value(0).toInt()==0)
        {
            return true;
        }
        break;
    case 3:
        query.exec("SELECT count(*) FROM test.dynamic_view WHERE status='false' AND group_disp_view IN('10') AND medcard_id="+global_id);
        query.next();
        if(query.value(0).toInt()>0)
        {
            return true;
        }
        else if(query.value(0).toInt()==0)
        {
            return false;
        }
        break;
    case 4:
        query.exec("SELECT count(*) FROM test.dynamic_view WHERE status='false' AND group_disp_view IN('8','9') AND medcard_id="+global_id);
        query.next();
        if(query.value(0).toInt()>0)
        {
            return true;
        }
        else if(query.value(0).toInt()==0)
        {
            return false;
        }
        break;
    }
}
