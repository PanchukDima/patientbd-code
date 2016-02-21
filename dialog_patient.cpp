#include "dialog_patient.h"
#include "ui_dialog_patient.h"

Dialog_patient::Dialog_patient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_patient)
{
    ui->setupUi(this);
    put_all_settings();
    connect(ui->pushButton_apply,SIGNAL(clicked()),SLOT(apply_send_data_sql()));
    //connect(ui->lineEdit_work_post,SIGNAL(textChanged(QString)),SLOT(get_work_post()));
    connect(ui->pushButton_ok,SIGNAL(clicked()),SLOT(apply_send_data_sql()));
    connect(ui->pushButton_cancel,SIGNAL(clicked()),SLOT(button_cancel()));
    connect(ui->pushButton_add_street,SIGNAL(clicked()),SLOT(add_street()));

    connect(ui->lineEdit_fname,SIGNAL(textEdited(QString)),SLOT(set_default_color_lineedit_fname()));
    connect(ui->lineEdit_name,SIGNAL(textEdited(QString)),SLOT(set_default_color_lineedit_name()));
    //connect(ui->lineEdit_oname,SIGNAL(textEdited(QString)),SLOT(set_default_color_lineedit_mname()));
    connect(ui->lineEdit_serial_passport,SIGNAL(textEdited(QString)),SLOT(set_default_color_lineedit_serial_passport()));
    connect(ui->lineEdit_number_passport,SIGNAL(textEdited(QString)),SLOT(set_default_color_lineedit_number_passport()));
    //connect(ui->lineEdit_house,SIGNAL(textEdited(QString)),SLOT(set_default_color_lineedit_house()));

    connect(ui->tableWidget_text_1,SIGNAL(itemSelectionChanged()),SLOT(load_text_table_1()));
    connect(ui->tableWidget_text_2,SIGNAL(itemSelectionChanged()),SLOT(load_text_table_2()));
    connect(ui->tableWidget_text_3,SIGNAL(itemSelectionChanged()),SLOT(load_text_table_3()));
    connect(ui->tableWidget_text_4,SIGNAL(itemSelectionChanged()),SLOT(load_text_table_4()));
    connect(ui->tableWidget_text_5,SIGNAL(itemSelectionChanged()),SLOT(load_text_table_5()));

    connect(ui->pushButton_save_1,SIGNAL(clicked(bool)),SLOT(save_text_1()));
    connect(ui->pushButton_save_2,SIGNAL(clicked(bool)),SLOT(save_text_2()));
    connect(ui->pushButton_save_3,SIGNAL(clicked(bool)),SLOT(save_text_3()));
    connect(ui->pushButton_save_4,SIGNAL(clicked(bool)),SLOT(save_text_4()));
    connect(ui->pushButton_save_5,SIGNAL(clicked(bool)),SLOT(save_text_5()));
    connect(ui->pushButton_creat_1,SIGNAL(clicked(bool)),SLOT(creat_text_1()));
    connect(ui->pushButton_creat_2,SIGNAL(clicked(bool)),SLOT(creat_text_2()));
    connect(ui->pushButton_creat_3,SIGNAL(clicked(bool)),SLOT(creat_text_3()));
    connect(ui->pushButton_creat_4,SIGNAL(clicked(bool)),SLOT(creat_text_4()));
    connect(ui->pushButton_creat_5,SIGNAL(clicked(bool)),SLOT(creat_text_5()));
    connect(ui->pushButton_del_1,SIGNAL(clicked(bool)),SLOT(del_text_1()));
    connect(ui->pushButton_del_2,SIGNAL(clicked(bool)),SLOT(del_text_2()));
    connect(ui->pushButton_del_3,SIGNAL(clicked(bool)),SLOT(del_text_3()));
    connect(ui->pushButton_del_4,SIGNAL(clicked(bool)),SLOT(del_text_4()));
    connect(ui->pushButton_del_5,SIGNAL(clicked(bool)),SLOT(del_text_5()));
    connect(ui->checkBox_ds_end_state,SIGNAL(toggled(bool)),SLOT(change_state_ds_end(bool)));
    connect(ui->lineEdit_date_start,SIGNAL(textChanged(QString)),SLOT(point_add_ds_start(QString)));
    connect(ui->lineEdit_date_birtday,SIGNAL(textChanged(QString)),SLOT(point_add_birtday(QString)));
    connect(ui->lineEdit_date_end,SIGNAL(textChanged(QString)),SLOT(point_add_ds_stop(QString)));
    connect(ui->pushButton_add_history,SIGNAL(clicked(bool)),SLOT(add_histry()));
    connect(ui->comboBox_area,SIGNAL(currentIndexChanged(int)),SLOT(set_default_color_combox_area()));
    connect(ui->comboBox_area_street,SIGNAL(currentIndexChanged(int)),SLOT(set_default_color_combox_area_street()));
    connect(ui->comboBox_sex,SIGNAL(currentIndexChanged(int)),SLOT(set_default_color_combox_sex()));






    //ui->comboBox_marital_status->setEnabled(true);

}

Dialog_patient::~Dialog_patient()
{
    delete ui;
}


QString const Dialog_patient::validate_date(QString date)
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
void Dialog_patient::keyPressEvent(QKeyEvent *e)
{

    if(e->key()==Qt::Key_Return)
        {

            Dialog_patient DP;
            this->focusNextChild();
        }
    if(e->key()==Qt::Key_Enter)
        {

            Dialog_patient DP;
            this->focusNextChild();
        }
}

void Dialog_patient::point_add_birtday(QString text)
{


        if(!global_param)
        {
    //        QFont font_lineedit;
    //        font_lineedit.setPointSize(11);
    //        ui->lineEdit_house->setFont(font_lineedit);
            ui->lineEdit_date_birtday->setStyleSheet("");
    //        ui->label_house_status->setPixmap(ok_icon.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    //        ui->lineEdit_house->setFrame(true);
        }


    switch (text.count()) {
    case 2:
        if(text.lastIndexOf(".")!=1)
        {
        ui->lineEdit_date_birtday->setText(text+".");
        }
        break;
    case 5:

        if(text.lastIndexOf(".")!=4)
        {
            ui->lineEdit_date_birtday->setText(text+".");
        }
            break;
    case 11:
        text.replace(10,1,"");
        qDebug()<<text;
        ui->lineEdit_date_birtday->setText(text);
        break;

    }
}

void Dialog_patient::point_add_ds_start(QString text)
{
    switch (text.count()) {
    case 2:
        if(text.lastIndexOf(".")!=1)
        {
        ui->lineEdit_date_start->setText(text+".");
        }
        break;
    case 5:

        if(text.lastIndexOf(".")!=4)
        {
            ui->lineEdit_date_start->setText(text+".");
        }
            break;
    case 11:
        text.replace(10,1,"");
        qDebug()<<text;
        ui->lineEdit_date_start->setText(text);
        break;

    }
}
void Dialog_patient::point_add_ds_stop(QString text)
{
    switch (text.count()) {
    case 2:
        if(text.lastIndexOf(".")!=1)
        {
        ui->lineEdit_date_end->setText(text+".");
        }
        break;
    case 5:

        if(text.lastIndexOf(".")!=4)
        {
            ui->lineEdit_date_end->setText(text+".");
        }
            break;
    case 11:
        text.replace(10,1,"");
        qDebug()<<text;
        ui->lineEdit_date_end->setText(text);
        break;

    }
}


void Dialog_patient::set_default_color_lineedit_fname()
{
    QPixmap ok_icon(":/icon/png/images/ok.png");
    if(!global_param)
    {
        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_fname->setFont(font_lineedit);
        ui->lineEdit_fname->setStyleSheet("border: 2px solid green");
        ui->label_fname_icon->setPixmap(ok_icon.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }

}
void Dialog_patient::set_default_color_lineedit_name()
{
    QPixmap ok_icon(":/icon/png/images/ok.png");
    if(!global_param)
    {
        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_name->setFont(font_lineedit);
        ui->lineEdit_name->setStyleSheet("border: 2px solid green");
        ui->label_name_icon->setPixmap(ok_icon.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
}
void Dialog_patient::set_default_color_lineedit_mname()
{
    QPixmap ok_icon(":/icon/png/images/ok.png");
    if(!global_param)
    {
        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_oname->setFont(font_lineedit);
        ui->lineEdit_oname->setStyleSheet("border: 2px solid green");
        ui->label_mname_icon->setPixmap(ok_icon.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
}
void Dialog_patient::set_default_color_lineedit_serial_passport()
{
    QFont font_lineedit;
    if(!global_param)
    {
    font_lineedit.setPointSize(11);
    ui->lineEdit_serial_passport->setFont(font_lineedit);
    ui->lineEdit_serial_passport->setStyleSheet("border: 2px solid green");
    ui->lineEdit_serial_passport->setFrame(true);
    }
}
void Dialog_patient::set_default_color_lineedit_number_passport()
{
    if(!global_param)
    {
        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_number_passport->setFont(font_lineedit);
        ui->lineEdit_number_passport->setStyleSheet("border: 2px solid green");
        ui->lineEdit_number_passport->setFrame(true);
    }
}
//void Dialog_patient::set_default_color_lineedit_house()
//{
//    QPixmap ok_icon(":/icon/png/images/ok.png");
//    if(!global_param)
//    {

//        QFont font_lineedit;
//        font_lineedit.setPointSize(11);
//        ui->lineEdit_house->setFont(font_lineedit);
//        ui->lineEdit_house->setStyleSheet("border: 2px solid green");
//        ui->label_house_status->setPixmap(ok_icon.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
//        ui->lineEdit_house->setFrame(true);
//    }
//}
void Dialog_patient::set_default_color_combox_area()
{
    if(!global_param)
    {
//        QFont font_lineedit;
//        font_lineedit.setPointSize(11);
//        ui->lineEdit_house->setFont(font_lineedit);
        ui->comboBox_area->setStyleSheet("");
//        ui->label_house_status->setPixmap(ok_icon.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
//        ui->lineEdit_house->setFrame(true);
    }
}
void Dialog_patient::set_default_color_combox_area_street()
{
    if(!global_param)
    {
//        QFont font_lineedit;
//        font_lineedit.setPointSize(11);
//        ui->lineEdit_house->setFont(font_lineedit);
        ui->comboBox_area_street->setStyleSheet("");
//        ui->label_house_status->setPixmap(ok_icon.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
//        ui->lineEdit_house->setFrame(true);
    }
}
void Dialog_patient::set_default_color_combox_sex()
{
    if(!global_param)
    {
//        QFont font_lineedit;
//        font_lineedit.setPointSize(11);
//        ui->lineEdit_house->setFont(font_lineedit);
        ui->comboBox_sex->setStyleSheet("");
//        ui->label_house_status->setPixmap(ok_icon.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
//        ui->lineEdit_house->setFrame(true);
    }
}

void Dialog_patient::put_all_settings()
{
    QSqlDatabase db = QSqlDatabase::database();
    ui->comboBox_sex->clear();
    ui->comboBox_street->clear();
    ui->tableWidget_text_1->setColumnCount(2);
    if(db.open())
    {
        QSqlQuery query;
        query.exec("SELECT \
                   street.id, \
                   street.name\
                   FROM \
                   test.street;");
        while (query.next())
        {
            QString street = query.value(1).toString();
            QString code_street = query.value(0).toString();
            ui->comboBox_street->addItem(street, code_street);
        }
        ui->comboBox_sex->addItem("Ж","false");
        ui->comboBox_sex->addItem("М","true");
        ui->comboBox_area_street->addItem("Выборгский район", "1");
        ui->comboBox_area_street->addItem("Калининский район", "2");
        ui->comboBox_invalid->addItem("",3);
        ui->comboBox_invalid->addItem("I",0);
        ui->comboBox_invalid->addItem("II",1);
        ui->comboBox_invalid->addItem("III",2);
        ui->lineEdit_date_start->setText(QDate::currentDate().toString("dd.MM.yyyy"));
        ui->lineEdit_date_end->setText(QDate::currentDate().toString("dd.MM.yyyy"));
        ui->lineEdit_date_end->hide();
        ui->comboBox_why_close->hide();
        ui->checkBox_ds_end_state->isChecked();

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
            //ui->comboBox_diagnosis->addItem(diagnos, id_diagnos);

        }

        query.exec("SELECT why_removed.id, why_removed.description FROM test.why_removed;");
        while (query.next())
        {
            QString id_status = query.value(0).toString();
            QString description = query.value(1).toString();
            ui->comboBox_why_close->addItem(description,id_status);
        }

        query.exec("SELECT id, name FROM test.area");
        while (query.next()) {
            QString id_status = query.value(0).toString();
            QString description = query.value(1).toString();
            ui->comboBox_area->addItem(description,id_status);
        }
        query.exec("SELECT id, description FROM test.direct");
        while (query.next()) {
            QString id_status = query.value(0).toString();
            QString description = query.value(1).toString();
            ui->comboBox_direction->addItem(description,id_status);
        }
    }

}
void Dialog_patient::check_data()
{

}
void Dialog_patient::change_state_ds_end(bool state) //событие на изменение галкой состояния
{
    if(state)
    {
        ui->lineEdit_date_end->show();
        ui->lineEdit_date_start->hide();
        ui->label_10->hide();
        ui->label_11->show();
        ui->comboBox_direction->hide();
        ui->comboBox_why_close->show();
    }
    else
    {
        ui->lineEdit_date_end->hide();
        ui->lineEdit_date_start->show();
        ui->label_10->show();
        ui->label_11->hide();
        ui->comboBox_direction->show();
        ui->comboBox_why_close->hide();
    }
}

void Dialog_patient::setParam(int param,int id, QString staff_id)
{
    global_param = param;
    global_staff_id = staff_id;
    global_id_str.setNum(id);
    qDebug()<<id;
    switch(param)
    {
    case 0:
        qDebug()<<"added patient";
        ui->tableView->hide();
        ui->pushButton_add_history->hide();
        ui->comboBox_area->setStyleSheet("border: 3px solid orange");
        ui->comboBox_area_street->setStyleSheet("border: 3px solid orange");
        ui->lineEdit_date_birtday->setStyleSheet("border: 3px solid orange");
        ui->lineEdit_name->setStyleSheet("border: 3px solid orange");
        ui->lineEdit_fname->setStyleSheet("border: 3px solid orange");
        ui->lineEdit_number_passport->setStyleSheet("border: 3px solid orange");
        ui->lineEdit_serial_passport->setStyleSheet("border: 3px solid orange");
        ui->comboBox_sex->setStyleSheet("border: 3px solid orange");
        break;
    case 1:
        qDebug()<<"edit patient";
        get_data_sql(id);
        load_text_table();
        break;
    case 2:
        qDebug()<<"del patient"; //я не знаю где это выполнять может на главном экране?
        break;
    }

}

void Dialog_patient::get_data_sql(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    global_id = id;
    if(db.open())
    {
        QSqlQuery query;
        QString id_str;
        id_str.setNum(id);
        qDebug()<<"operation select";
        query.exec("SELECT address_patient.street_id, address_patient.building, address_patient.home, patient.fname, patient.name, patient.mname, medcard.sex, address_patient.flat, patient.serial_passport, patient.number_passport, medcard.birthday, address_patient.telefon, medcard.job_place, medcard.tutor, medcard.pt, medcard.group_lgot_preparat, medcard.area_id, medcard.serial_snils, medcard.district_id, medcard.group_inv_obsh, medcard.polis_serial, medcard.polis_number  FROM test.address_patient, test.patient, test.medcard  WHERE medcard.patient_id = patient.id AND medcard.id = address_patient.medcard_id AND medcard.id ="+id_str);
        while (query.next())
        {
            QString street_value = query.value(0).toString();
            QString building_value = query.value(1).toString();
            QString house_value = query.value(2).toString();
            QString fname_value = query.value(3).toString();
            QString name_value = query.value(4).toString();
            QString mname_value = query.value(5).toString();
            QString sex_value = query.value(6).toString();
            QString flat = query.value(7).toString();
            QString serial_passport = query.value(8).toString();
            QString number_passport = query.value(9).toString();
            QString date_birthday = query.value(10).toDate().toString("dd.MM.yyyy");
            QString telefon_value = query.value(11).toString();
            QString job_place_value = query.value(12).toString();
            bool tutor_value = query.value(13).toBool();
            bool pt_value = query.value(14).toBool();
            QString group_lgot_preparat_value = query.value(15).toString();
            QString area_id_value = query.value(16).toString();
            QString snils_serial_value = query.value(17).toString();
            QString district_value = query.value(18).toString();
            QString invalid = query.value(19).toString();
            QString polis_serial_value = query.value(20).toString();
            QString polis_number_value = query.value(21).toString();

//            if(query.value(13).toString()=="")
//            {
//                ui->checkBox_ds_end_state->setCheckState(Qt::Unchecked);
//            }
//            else
//            {
//                ui->checkBox_ds_end_state->setCheckState(Qt::Checked);
//            }
            qDebug()<<street_value<<"|"<<building_value<<"|"<<house_value<<"|"<<fname_value<<"|"<<name_value<<"|"<<mname_value;
            ui->comboBox_street->setCurrentIndex(ui->comboBox_street->findData(street_value));
            ui->lineEdit_korpuse->setText(building_value);
            ui->lineEdit_house->setText(house_value);
            ui->lineEdit_fname->setText(fname_value);
            ui->lineEdit_name->setText(name_value);
            ui->lineEdit_oname->setText(mname_value);
            ui->comboBox_sex->setCurrentIndex(ui->comboBox_sex->findData(sex_value));
            ui->lineEdit_room->setText(flat);
            ui->lineEdit_serial_passport->setText(serial_passport);
            ui->lineEdit_number_passport->setText(number_passport);
            ui->lineEdit_date_birtday->setText(date_birthday);
            ui->lineEdit_telefon->setText(telefon_value);
            ui->lineEdit_work_or_education->setText(job_place_value);
            ui->checkBox_custody->setChecked(tutor_value);
            ui->checkBox_pt->setChecked(pt_value);
            ui->lineEdit_group_lgot->setText(group_lgot_preparat_value);
            ui->comboBox_area->setCurrentIndex(ui->comboBox_area->findData(area_id_value));
            ui->lineEdit_polis_number->setText(polis_number_value);
            ui->lineEdit_polis_serial->setText(polis_serial_value);
            ui->comboBox_invalid->setCurrentIndex(ui->comboBox_invalid->findData(invalid));
            ui->comboBox_area_street->setCurrentIndex(ui->comboBox_area_street->findData(district_value));
            //ui->comboBox_direction->setCurrentIndex(ui->comboBox_direction->findData(direct_value));
            ui->lineEdit_snils->setText(snils_serial_value);

        }
        query.clear();
        table_uchet_history();
 }


}
void Dialog_patient::table_uchet_history()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlRelationalTableModel * model = new QSqlRelationalTableModel();
    model->setTable("test.uchet");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setRelation(4, QSqlRelation("test.why_removed", "id", "description"));
    model->setRelation(6, QSqlRelation("test.direct", "id", "description"));
    model->setFilter("uchet.medcard_id = "+global_id_str );
    model->sort(0,Qt::SortOrder());
    model->setHeaderData(2, Qt::Horizontal, tr("Дата\nпостановки\nна учет"));
    model->setHeaderData(3, Qt::Horizontal, tr("Дата\nснятия\nс учета"));
    model->setHeaderData(4, Qt::Horizontal, tr("Причина\nснятия"));
    model->setHeaderData(6, Qt::Horizontal, tr("Направлен"));

    model->select();
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(5);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Dialog_patient::clear_table_text_1()
{
    int c;
    ui->tableWidget_text_1->clear();

    for (c = ui->tableWidget_text_1->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_text_1->removeRow(c);
    }
}
void Dialog_patient::clear_table_text_2()
{
    int c;
    ui->tableWidget_text_2->clear();

    for (c = ui->tableWidget_text_2->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_text_2->removeRow(c);
    }
}
void Dialog_patient::clear_table_text_3()
{
    int c;
    ui->tableWidget_text_3->clear();

    for (c = ui->tableWidget_text_3->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_text_3->removeRow(c);
    }
}
void Dialog_patient::clear_table_text_4()
{
    int c;
    ui->tableWidget_text_4->clear();

    for (c = ui->tableWidget_text_4->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_text_4->removeRow(c);
    }
}
void Dialog_patient::clear_table_text_5()
{
    int c;
    ui->tableWidget_text_5->clear();
    ;
    for (c = ui->tableWidget_text_5->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_text_5->removeRow(c);
    }
}
void Dialog_patient::load_text_table()
{


    clear_table_text_1();
    clear_table_text_2();
    clear_table_text_3();
    clear_table_text_4();
    clear_table_text_5();
    // наполняем таблицы записями
    int last_row_table_1 = ui->tableWidget_text_1->rowCount();
    int last_row_table_2 = ui->tableWidget_text_2->rowCount();
    int last_row_table_3 = ui->tableWidget_text_3->rowCount();
    int last_row_table_4 = ui->tableWidget_text_4->rowCount();
    int last_row_table_5 = ui->tableWidget_text_5->rowCount();

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    if(db.open())
    {
    query.exec("SELECT id, type, date_creat FROM test.text_info_patients WHERE medcard_id = "+global_id_str+"AND delete_row='false'");
    while(query.next())
    {
        QString id_value = query.value(0).toString();
        int type_value = query.value(1).toInt();
        QString date_value = query.value(2).toDate().toString("dd.MM.yyyy");

        QTableWidgetItem * id = new QTableWidgetItem();
        QTableWidgetItem * date = new QTableWidgetItem();

        id->setText(id_value);
        date->setText(date_value);

        switch (type_value) {
        case 0:
            ui->tableWidget_text_1->insertRow(last_row_table_1);
            ui->tableWidget_text_1->setItem(last_row_table_1,0,id);
            ui->tableWidget_text_1->setItem(last_row_table_1,1,date);
            break;
        case 1:
            ui->tableWidget_text_2->insertRow(last_row_table_2);
            ui->tableWidget_text_2->setItem(last_row_table_2,0,id);
            ui->tableWidget_text_2->setItem(last_row_table_2,1,date);
            break;
        case 2:
            ui->tableWidget_text_3->insertRow(last_row_table_3);
            ui->tableWidget_text_3->setItem(last_row_table_3,0,id);
            ui->tableWidget_text_3->setItem(last_row_table_3,1,date);
            break;
        case 3:
            ui->tableWidget_text_4->insertRow(last_row_table_4);
            ui->tableWidget_text_4->setItem(last_row_table_4,0,id);
            ui->tableWidget_text_4->setItem(last_row_table_4,1,date);
            break;
        case 4:
            ui->tableWidget_text_5->insertRow(last_row_table_5);
            ui->tableWidget_text_5->setItem(last_row_table_5,0,id);
            ui->tableWidget_text_5->setItem(last_row_table_5,1,date);
            break;
        }
    }
    }
}

void Dialog_patient::load_text_table_1()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    ui->textEdit_1->clear();
    int selected_tables = ui->tableWidget_text_1->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_1->currentRow();
        QString id = ui->tableWidget_text_1->item(cu_row,0)->text();
        if(db.open())
        {
            query.exec("SELECT text FROM test.text_info_patients WHERE id = "+id);
            while(query.next())
            {
                QString text = query.value(0).toString();
                ui->textEdit_1->setText(text);
            }
        }
    }
}
void Dialog_patient::load_text_table_2()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    ui->textEdit_2->clear();
    int selected_tables = ui->tableWidget_text_2->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_2->currentRow();
        QString id = ui->tableWidget_text_2->item(cu_row,0)->text();
        if(db.open())
        {
            query.exec("SELECT text FROM test.text_info_patients WHERE id = "+id);
            while(query.next())
            {
                QString text = query.value(0).toString();
                ui->textEdit_2->setText(text);
            }
        }
    }
}
void Dialog_patient::load_text_table_3()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    ui->textEdit_3->clear();
    int selected_tables = ui->tableWidget_text_3->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_3->currentRow();
        QString id = ui->tableWidget_text_3->item(cu_row,0)->text();
        if(db.open())
        {
            query.exec("SELECT text FROM test.text_info_patients WHERE id = "+id);
            while(query.next())
            {
                QString text = query.value(0).toString();
                ui->textEdit_3->setText(text);
            }
        }
    }
}
void Dialog_patient::load_text_table_4()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    ui->textEdit_4->clear();
    int selected_tables = ui->tableWidget_text_4->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_4->currentRow();
        QString id = ui->tableWidget_text_4->item(cu_row,0)->text();
        if(db.open())
        {
            query.exec("SELECT text FROM test.text_info_patients WHERE id = "+id);
            while(query.next())
            {
                QString text = query.value(0).toString();
                ui->textEdit_4->setText(text);
            }
        }
    }
}
void Dialog_patient::load_text_table_5()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    ui->textEdit_5->clear();
    int selected_tables = ui->tableWidget_text_5->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_5->currentRow();
        QString id = ui->tableWidget_text_5->item(cu_row,0)->text();
        if(db.open())
        {
            query.exec("SELECT text FROM test.text_info_patients WHERE id = "+id);
            while(query.next())
            {
                QString text = query.value(0).toString();
                ui->textEdit_5->setText(text);
            }
        }
    }
}
void Dialog_patient::save_text_1()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_text_1->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_1->currentRow();
        QString id = ui->tableWidget_text_1->item(cu_row,0)->text();
        if(db.open())
        {
            QString text = ui->textEdit_1->toPlainText();
            QString date = QDate::currentDate().toString("MM.dd.yyyy");
            query.exec("UPDATE test.text_info_patients SET staff_add_id='"+global_staff_id+"', text='"+text+"' , date_creat = '"+date+"' WHERE id="+id);
        }
    }
    else
    {
        creat_text_1();
    }
}
void Dialog_patient::save_text_2()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_text_2->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_2->currentRow();
        QString id = ui->tableWidget_text_2->item(cu_row,0)->text();
        if(db.open())
        {
            QString text = ui->textEdit_2->toPlainText();
            QString date = QDate::currentDate().toString("MM.dd.yyyy");
            query.exec("UPDATE test.text_info_patients SET staff_add_id='"+global_staff_id+"', text='"+text+"' , date_creat = '"+date+"' WHERE id="+id);
        }
    }
    else
    {
        creat_text_2();
    }
}
void Dialog_patient::save_text_3()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_text_3->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_3->currentRow();
        QString id = ui->tableWidget_text_3->item(cu_row,0)->text();
        if(db.open())
        {
            QString text = ui->textEdit_3->toPlainText();
            QString date = QDate::currentDate().toString("MM.dd.yyyy");
            query.exec("UPDATE test.text_info_patients SET staff_add_id='"+global_staff_id+"', text='"+text+"' , date_creat = '"+date+"' WHERE id="+id);
        }
    }
    else
    {
        creat_text_3();
    }
}
void Dialog_patient::save_text_4()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_text_4->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_4->currentRow();
        QString id = ui->tableWidget_text_4->item(cu_row,0)->text();
        if(db.open())
        {
            QString text = ui->textEdit_4->toPlainText();
            QString date = QDate::currentDate().toString("MM.dd.yyyy");
            query.exec("UPDATE test.text_info_patients SET staff_add_id='"+global_staff_id+"', text='"+text+"' , date_creat = '"+date+"' WHERE id="+id);
        }
    }
    else
    {
        creat_text_4();
    }
}
void Dialog_patient::save_text_5()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_text_4->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_4->currentRow();
        QString id = ui->tableWidget_text_4->item(cu_row,0)->text();
        if(db.open())
        {
            QString text = ui->textEdit_5->toPlainText();
            QString date = QDate::currentDate().toString("MM.dd.yyyy");
            query.exec("UPDATE test.text_info_patients SET staff_add_id='"+global_staff_id+"', text='"+text+"' , date_creat = '"+date+"' WHERE id="+id);
        }
    }
    else
    {
        creat_text_5();
    }
}
void Dialog_patient::creat_text_1()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

        if(db.open())
        {
            QString text = ui->textEdit_1->toPlainText();
            QString date = QDate::currentDate().toString("MM.dd.yyyy");
            query.exec("INSERT INTO test.text_info_patients(medcard_id, type, date_creat, staff_add_id, text, delete_row) VALUES ('"+global_id_str+"', '0', '"+date+"', '"+global_staff_id+"', '"+text+"', 'false')");
            load_text_table();
        }

}
void Dialog_patient::creat_text_2()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    if(db.open())
    {
        QString text = ui->textEdit_2->toPlainText();
        QString date = QDate::currentDate().toString("MM.dd.yyyy");
        query.exec("INSERT INTO test.text_info_patients(medcard_id, type, date_creat, staff_add_id, text, delete_row) VALUES ('"+global_id_str+"', '1', '"+date+"', '"+global_staff_id+"', '"+text+"', 'false')");
        load_text_table();
    }

}
void Dialog_patient::creat_text_3()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    if(db.open())
    {
        QString text = ui->textEdit_3->toPlainText();
        QString date = QDate::currentDate().toString("MM.dd.yyyy");
        query.exec("INSERT INTO test.text_info_patients(medcard_id, type, date_creat, staff_add_id, text, delete_row) VALUES ('"+global_id_str+"', '2', '"+date+"', '"+global_staff_id+"', '"+text+"', 'false')");
        load_text_table();
    }

}
void Dialog_patient::creat_text_4()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    if(db.open())
    {
        QString text = ui->textEdit_4->toPlainText();
        QString date = QDate::currentDate().toString("MM.dd.yyyy");
        query.exec("INSERT INTO test.text_info_patients(medcard_id, type, date_creat, staff_add_id, text, delete_row) VALUES ('"+global_id_str+"', '3', '"+date+"', '"+global_staff_id+"', '"+text+"', 'false')");
        load_text_table();
    }

}
void Dialog_patient::creat_text_5()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    if(db.open())
    {
        QString text = ui->textEdit_5->toPlainText();
        QString date = QDate::currentDate().toString("MM.dd.yyyy");
        query.exec("INSERT INTO test.text_info_patients(medcard_id, type, date_creat, staff_add_id, text, delete_row) VALUES ('"+global_id_str+"', '4', '"+date+"', '"+global_staff_id+"', '"+text+"', 'false')");
        load_text_table();
    }

}
void Dialog_patient::del_text_1()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_text_1->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_1->currentRow();
        QString id = ui->tableWidget_text_1->item(cu_row,0)->text();
        if(db.open())
        {

            query.exec("UPDATE test.text_info_patients SET staff_add_id='"+global_staff_id+"', delete_row='true' WHERE id="+id);
            load_text_table();
        }
    }
}
void Dialog_patient::del_text_2()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_text_2->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_2->currentRow();
        QString id = ui->tableWidget_text_2->item(cu_row,0)->text();
        if(db.open())
        {

            query.exec("UPDATE test.text_info_patients SET staff_add_id='"+global_staff_id+"', delete_row='true' WHERE id="+id);
            load_text_table();
        }
    }
}
void Dialog_patient::del_text_3()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_text_3->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_3->currentRow();
        QString id = ui->tableWidget_text_3->item(cu_row,0)->text();
        if(db.open())
        {

            query.exec("UPDATE test.text_info_patients SET staff_add_id='"+global_staff_id+"', delete_row='true' WHERE id="+id);
            load_text_table();
        }
    }
}
void Dialog_patient::del_text_4()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_text_4->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_4->currentRow();
        QString id = ui->tableWidget_text_4->item(cu_row,0)->text();
        if(db.open())
        {

            query.exec("UPDATE test.text_info_patients SET staff_add_id='"+global_staff_id+"', delete_row='true' WHERE id="+id);
            load_text_table();
        }
    }
}
void Dialog_patient::del_text_5()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_text_5->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_text_5->currentRow();
        QString id = ui->tableWidget_text_5->item(cu_row,0)->text();
        if(db.open())
        {

            query.exec("UPDATE test.text_info_patients SET staff_add_id='"+global_staff_id+"', delete_row='true' WHERE id="+id);
            load_text_table();
        }
    }
}

void Dialog_patient::apply_send_data_sql()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString id_str;
    id_str.setNum(global_id);
    QString fname_value = ui->lineEdit_fname->text();
    QString name_value = ui->lineEdit_name->text();
    QString oname_value = ui->lineEdit_oname->text();
    QString serial_passport = ui->lineEdit_serial_passport->text();
    QString number_passport = ui->lineEdit_number_passport->text();
    QString sex_value = ui->comboBox_sex->currentData().toString();
    QString home = ui->lineEdit_house->text();
    QString building = ui->lineEdit_korpuse->text();
    QString flat = ui->lineEdit_room->text();
    QString street_id = ui->comboBox_street->currentData().toString();

    QString date_birthday;

    QString date_birthday_test = validate_date(ui->lineEdit_date_birtday->text());
    if(date_birthday_test=="exit")
    {
        return;
    }
    else
    {
        date_birthday=date_birthday_test;
    }



    QString telefon_value = ui->lineEdit_telefon->text();
    QString id_patient;
    QString id_medcard;
    QString job_place_value = ui->lineEdit_work_or_education->text();
    QString area_value = ui->comboBox_area->currentData().toString();
    QString tutor_value;
    QString pt_value;
    QString group_lgot_value = ui->lineEdit_group_lgot->text();
    QString polis_serial_value = ui->lineEdit_polis_serial->text();
    QString polis_number_value = ui->lineEdit_polis_number->text();
    QString snils_serial_value = ui->lineEdit_snils->text();
    QString district_value = ui->comboBox_area_street->currentData().toString();
    QString direct_value = ui->comboBox_direction->currentData().toString();
    QString group_inv_value = ui->comboBox_invalid->currentData().toString();

    QString ds_end;
    QString ds_start;
    QString ds_start_test = validate_date(ui->lineEdit_date_start->text());
    QString why_remove;

    if(ui->checkBox_ds_end_state->checkState()==Qt::Checked)
    {
        QString ds_end_test = validate_date(ui->lineEdit_date_end->text());
        if(ds_end_test=="exit")
        {
            return;
        }
        else
        {
            ds_end=ds_end_test;
        }
        why_remove = ui->comboBox_why_close->currentData().toString();

    }
    else if(ui->checkBox_ds_end_state->checkState()==Qt::Unchecked)
    {
        ds_end = "";
        why_remove="-1";
    }


    if(ds_start_test=="exit")
    {
        return;
    }
    else
    {
        ds_start=ds_start_test;
    }

    if(ui->checkBox_custody->checkState()==Qt::Checked)
    {
        tutor_value = "1";

    }
    else if(ui->checkBox_custody->checkState()==Qt::Unchecked)
    {
        tutor_value = "0";
    }
    if(ui->checkBox_pt->checkState()==Qt::Checked)
    {
        pt_value = "1";

    }
    else if(ui->checkBox_pt->checkState()==Qt::Unchecked)
    {
        pt_value = "0";
    }

    int control_lineedit=0;
    QPixmap error_pix(":/icon/png/images/Warning.png");
//    if(ui->lineEdit_house->text()=="")
//    {
//        QFont font_lineedit;
//        font_lineedit.setPointSize(11);
//        ui->lineEdit_house->setFont(font_lineedit);
//        ui->lineEdit_house->setStyleSheet("border: 2px solid red");
//        control_lineedit=1;
//    }
//    else
//    {
//        QPalette p = ui->lineEdit_house->palette();
//        p.setColor(QPalette::Base, Qt::white);
//        ui->lineEdit_house->setPalette(p);
//        ui->lineEdit_house->setFrame(true);
//    }
    if(ui->lineEdit_fname->text()=="")
    {
        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_fname->setFont(font_lineedit);
        ui->lineEdit_fname->setStyleSheet("border: 2px solid red");
        ui->label_fname_icon->setPixmap(error_pix.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        control_lineedit=1;
    }
    else
    {
        QPalette p = ui->lineEdit_fname->palette();
        p.setColor(QPalette::Base, Qt::white);
        ui->lineEdit_fname->setPalette(p);
        ui->lineEdit_fname->setFrame(true);
    }
    if(ui->lineEdit_name->text()=="")
    {
        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_name->setFont(font_lineedit);
        ui->lineEdit_name->setStyleSheet("border: 2px solid red");
        ui->label_name_icon->setPixmap(error_pix.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        control_lineedit=1;
    }
    else
    {
        QPalette p = ui->lineEdit_name->palette();
        p.setColor(QPalette::Base, Qt::white);
        ui->lineEdit_name->setPalette(p);
        ui->lineEdit_name->setFrame(true);
    }
//    if(ui->lineEdit_oname->text()=="")
//    {
//        QFont font_lineedit;
//        font_lineedit.setPointSize(11);
//        ui->lineEdit_oname->setFont(font_lineedit);
//        ui->lineEdit_oname->setStyleSheet("border: 2px solid red");
//        ui->label_mname_icon->setPixmap(error_pix.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
//        control_lineedit=1;
//    }
//    else
//    {
//        QPalette p = ui->lineEdit_oname->palette();
//        p.setColor(QPalette::Base, Qt::white);
//        ui->lineEdit_oname->setPalette(p);
//        ui->lineEdit_oname->setFrame(true);
//    }
    if(ui->lineEdit_serial_passport->text()=="")
    {
        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_serial_passport->setFont(font_lineedit);
        ui->lineEdit_serial_passport->setStyleSheet("border: 2px solid red");
        control_lineedit=1;
    }
    else
    {
        QPalette p = ui->lineEdit_serial_passport->palette();
        p.setColor(QPalette::Base, Qt::white);
        ui->lineEdit_serial_passport->setPalette(p);
        ui->lineEdit_serial_passport->setFrame(true);
    }
    if(ui->lineEdit_number_passport->text()=="")
    {
        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_number_passport->setFont(font_lineedit);
        ui->lineEdit_number_passport->setStyleSheet("border: 2px solid red");
        control_lineedit=1;
    }
    else
    {
        QPalette p = ui->lineEdit_number_passport->palette();
        p.setColor(QPalette::Base, Qt::white);
        ui->lineEdit_number_passport->setPalette(p);
        ui->lineEdit_number_passport->setFrame(true);
    }
    if(control_lineedit==0)
    {
        if(db.open())
        {
            switch (global_param) {
            case 0: //insert

                query.exec("INSERT INTO test.patient(fname, name, mname, serial_passport, number_passport, status, staff_add_id) VALUES ('"+fname_value+"', '"+name_value+"', '"+oname_value+"', '"+serial_passport+"', '"+number_passport+"',0, '"+global_staff_id+"') RETURNING id;");
                while (query.next())
                {
                    id_patient = query.value(0).toString();
                }
                qDebug()<<"INSERT INTO test.medcard(patient_id, sex, staff_add_id, birthday, job_place, tutor, pt, group_lgot_preparat, area_id,  district_id , group_inv_obsh, polis_serial, polis_number, serial_snils ) VALUES ('"+id_patient+"','"+sex_value+"', '"+global_staff_id+"', '"+date_birthday+"', '"+job_place_value+"','"+tutor_value+"', '"+pt_value+"', '"+group_lgot_value+"', '"+area_value+"', "+district_value+" , '"+group_inv_value+"', '"+polis_serial_value+"', '"+polis_number_value+"', '"+snils_serial_value+"'  ) RETURNING id;";
                query.exec("INSERT INTO test.medcard(patient_id, sex, staff_add_id, birthday, job_place, tutor, pt, group_lgot_preparat, area_id,  district_id , group_inv_obsh, polis_serial, polis_number, serial_snils ) VALUES ('"+id_patient+"','"+sex_value+"', '"+global_staff_id+"', '"+date_birthday+"', '"+job_place_value+"','"+tutor_value+"', '"+pt_value+"', '"+group_lgot_value+"', '"+area_value+"', "+district_value+" , '"+group_inv_value+"', '"+polis_serial_value+"', '"+polis_number_value+"', '"+snils_serial_value+"'  ) RETURNING id;");
                while (query.next())
                {
                    id_medcard = query.value(0).toString();
                }

                if(ui->checkBox_ds_end_state->checkState()==Qt::Unchecked)
                {

                    query.exec("INSERT INTO test.uchet(staff_add_id, on_uchet, off_uchet, why_removed_id, medcard_id, direct) VALUES ('"+global_staff_id+"', '"+ds_start+"', NULL, '"+why_remove+"', '"+id_medcard+"','"+direct_value+"');");
                }
                else if(ui->checkBox_ds_end_state->checkState()==Qt::Checked)
                {

                    query.exec("INSERT INTO test.uchet(staff_add_id, on_uchet, off_uchet, why_removed_id, medcard_id,direct) VALUES ('"+global_staff_id+"', NULL, '"+ds_end+"', '"+why_remove+"', '"+id_medcard+"',NULL);");
                }

                query.exec("INSERT INTO test.address_patient(medcard_id, street_id, home, building, flat, staff_add_id, telefon) VALUES ('"+id_medcard+"', '"+street_id+"', '"+home+"', '"+building+"', '"+flat+"', '"+global_staff_id+"', '"+telefon_value+"');");
                query.exec("INSERT INTO test.logs(staff_add_id, date_add, text) VALUES ('"+global_staff_id+"', '"+QDate::currentDate().toString("MM.dd.yyyy")+"', 'Добавлена медкарта №"+id_medcard+"')");
                ui->lineEdit_fname->setText("");
                ui->lineEdit_name->setText("");
                ui->lineEdit_oname->setText("");
                ui->lineEdit_serial_passport->setText("");
                ui->lineEdit_number_passport->setText("");
                ui->lineEdit_house->setText("");
                ui->lineEdit_korpuse->setText("");
                ui->lineEdit_room->setText("");
                Dialog_patient::accept();
                break;
            case 1: //update

                // что за херня снизу?

                query.exec("UPDATE test.medcard SET area_id = '"+area_value+"', sex = "+sex_value+", birthday='"+date_birthday+"', job_place='"+job_place_value+"', tutor='"+tutor_value+"', pt='"+pt_value+"', group_lgot_preparat='"+group_lgot_value+"', serial_snils='"+snils_serial_value+"', polis_number='"+polis_number_value+"', polis_serial = '"+polis_serial_value+"', district_id="+district_value+", group_inv_obsh='"+group_inv_value+"' WHERE id ="+id_str);
//                if(ui->checkBox_ds_end_state->checkState()==Qt::Unchecked)
//                {

//                }
//                else if(ui->checkBox_ds_end_state->checkState()==Qt::Checked)
//                {

//                }


                while (query.next())
                {
                    id_patient = query.value(0).toString();
                }
                if(id_patient=="")
                {
                    query.exec("SELECT medcard.patient_id FROM test.medcard WHERE medcard.id="+id_str);
                    while (query.next())
                    {
                        id_patient = query.value(0).toString();
                    }
                }
                query.exec("UPDATE test.patient SET fname ='"+fname_value+"', name ='"+name_value+"', mname = '"+oname_value+"',serial_passport = "+serial_passport+", number_passport = "+number_passport+" WHERE id = "+id_patient);
                query.exec("UPDATE test.address_patient SET street_id ='"+street_id+"', home = '"+home+"', building = '"+building+"', flat = '"+flat+"', telefon='"+telefon_value+"' WHERE medcard_id = "+id_str);
                query.exec("INSERT INTO test.logs(staff_add_id, date_add, text) VALUES ('"+global_staff_id+"', '"+QDate::currentDate().toString("MM.dd.yyyy")+"', 'Обновлена медкарта"+id_str+"')");
                Dialog_patient::accept();
                break;
            }
        }
    }

}
void Dialog_patient::ok_send_data_sql()
{
    apply_send_data_sql();

    Dialog_patient::accept();

}
void Dialog_patient::button_cancel()
{
    Dialog_patient::close();
}
void Dialog_patient::add_street()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString add_street_text = ui->comboBox_street->currentText();
    if(db.open())
    {
        query.exec("INSERT INTO test.logs(staff_add_id, date_add, text) VALUES ('"+global_staff_id+"', '"+QDate::currentDate().toString("MM.dd.yyyy")+"', 'Добавлена улица"+add_street_text+"')");
        query.exec("INSERT INTO test.street(name, staff_add_id) VALUES ('"+add_street_text+"', '"+global_staff_id+"')");
        QMessageBox::information(this,"Добавление улицы","Добавлена улица :'"+add_street_text+"'");
    }
    put_all_settings();
}
void Dialog_patient::add_histry() // кнопка добавить историю
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString ds_end;
    QString ds_start;
    QString ds_start_test = validate_date(ui->lineEdit_date_start->text());
    QString why_remove;
    QString direct_value = ui->comboBox_direction->currentData().toString();
    if(ds_start_test=="exit")
    {
        return;
    }
    else
    {
        ds_start=ds_start_test;
    }

    if(ui->checkBox_ds_end_state->checkState()==Qt::Checked)
    {
        QString ds_end_test = validate_date(ui->lineEdit_date_end->text());
        if(ds_end_test=="exit")
        {
            return;
        }
        else
        {
            ds_end=ds_end_test;
            why_remove = ui->comboBox_why_close->currentData().toString();
            query.exec("INSERT INTO test.uchet(staff_add_id, on_uchet, off_uchet, why_removed_id, medcard_id, direct) VALUES ('"+global_staff_id+"', NULL, '"+ds_end+"', '"+why_remove+"', '"+global_id_str+"', '-1');");

        }


    }
    else if(ui->checkBox_ds_end_state->checkState()==Qt::Unchecked)
    {
        ds_end = "";
        why_remove="-1";
        query.exec("INSERT INTO test.uchet(staff_add_id, on_uchet, off_uchet, why_removed_id, medcard_id, direct) VALUES ('"+global_staff_id+"', '"+ds_start+"', NULL, '-1', '"+global_id_str+"', '"+direct_value+"');");

    }
    table_uchet_history();
}
