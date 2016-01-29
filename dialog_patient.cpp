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
    connect(ui->lineEdit_oname,SIGNAL(textEdited(QString)),SLOT(set_default_color_lineedit_mname()));
    connect(ui->lineEdit_serial_passport,SIGNAL(textEdited(QString)),SLOT(set_default_color_lineedit_serial_passport()));
    connect(ui->lineEdit_number_passport,SIGNAL(textEdited(QString)),SLOT(set_default_color_lineedit_number_passport()));
    connect(ui->lineEdit_house,SIGNAL(textEdited(QString)),SLOT(set_default_color_lineedit_house()));
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



    // ui->dateEdit_date_birthday->setEnabled(false);
    //ui->dateEdit_date_end->setEnabled(false);
    ui->dateEdit_date_install_dianosis->setEnabled(false);
    //ui->dateEdit_date_start->setEnabled(false);
    ui->comboBox_area->setEnabled(false);
    ui->comboBox_area_street->setEnabled(false);
    ui->checkBox_custody->setEnabled(false);
    ui->comboBox_accommodations->setEnabled(false);
    //ui->comboBox_diagnosis->setEnabled(false);
    ui->comboBox_direction->setEnabled(false);
    //ui->lineEdit_work_or_education->setEnabled(false);
    //ui->lineEdit_work_post->setEnabled(false);
    ui->comboBox_marital_status->setEnabled(false);
    ui->comboBox_source_funds->setEnabled(false);
    ui->comboBox_benefit->setEnabled(false);
    ui->comboBox_reason_dont_see->setEnabled(false);
    //ui->pushButton_add_street->setEnabled(true);
    //ui->lineEdit_telefon->setEnabled(false);
}

Dialog_patient::~Dialog_patient()
{
    delete ui;
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

void Dialog_patient::set_default_color_lineedit_house()
{
    QPixmap ok_icon(":/icon/png/images/ok.png");
    if(!global_param)
    {

        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_house->setFont(font_lineedit);
        ui->lineEdit_house->setStyleSheet("border: 2px solid green");
        ui->label_house_status->setPixmap(ok_icon.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        ui->lineEdit_house->setFrame(true);
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
        ui->dateEdit_date_start->setDate(QDate::currentDate());
        ui->dateEdit_date_end->setDate(QDate::currentDate());
        ui->dateEdit_date_end->hide();
        ui->checkBox_ds_end_state->isChecked();
        Dialog_patient::setStyleSheet("font-size: 8 pt;");
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
    }

}
void Dialog_patient::check_data()
{

}
void Dialog_patient::change_state_ds_end(bool state)
{
    if(state)
    {
        ui->dateEdit_date_end->show();
    }
    else
    {
        ui->dateEdit_date_end->hide();
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

        query.exec("SELECT address_patient.street_id, address_patient.building, address_patient.home, patient.fname, patient.name, patient.mname, medcard.sex,address_patient.flat, patient.serial_passport,patient.number_passport,medcard.birthday, address_patient.telefon,diagnos_patient.diagnos_id, medcard.ds_start, medcard.ds_end, medcard.job_place, post  FROM test.address_patient, test.patient, test.medcard, test.diagnos_patient WHERE medcard.patient_id = patient.id AND medcard.id = address_patient.medcard_id AND medcard.id = diagnos_patient.medcard_id AND medcard.id = "+id_str);
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
            QDate date_birthday = query.value(10).toDate();
            QString telefon_value = query.value(11).toString();
            //QString diagnos_id_value = query.value(12).toString();
            QDate ds_start_value = query.value(13).toDate();
            QDate ds_end_value = query.value(14).toDate();
            QString job_place_value = query.value(15).toString();
            QString post_value = query.value(16).toString();

            if(query.value(14).toString()=="")
            {
                ui->checkBox_ds_end_state->setCheckState(Qt::Unchecked);
            }
            else
            {
                ui->checkBox_ds_end_state->setCheckState(Qt::Checked);
            }

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
            ui->dateEdit_date_birthday->setDate(date_birthday);
            ui->lineEdit_telefon->setText(telefon_value);
            ui->dateEdit_date_start->setDate(ds_start_value);
            ui->dateEdit_date_end->setDate(ds_end_value);
            ui->lineEdit_work_or_education->setText(job_place_value);
            ui->lineEdit_work_post->setText(post_value);
            //ui->comboBox_diagnosis->setCurrentIndex(ui->comboBox_diagnosis->findData(diagnos_id_value));
        }





    }


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
    QString date_birthday = ui->dateEdit_date_birthday->date().toString("MM.dd.yyyy");
    QString telefon_value = ui->lineEdit_telefon->text();
    QString id_patient;
    QString id_medcard;
    QString ds_start = ui->dateEdit_date_start->date().toString("MM.dd.yyyy");
    QString ds_end;
    QString why_remove;
    QString job_place_value = ui->lineEdit_work_or_education->text();
    QString job_post_value = ui->lineEdit_work_post->text();
    if(ui->checkBox_ds_end_state->checkState()==Qt::Checked)
    {
    ds_end = ui->dateEdit_date_end->date().toString("MM.dd.yyyy");
    bool bOk;
    QString str = QInputDialog::getText( 0, "Причина снятия с учета", "Причина снятия с учета:", QLineEdit::Normal, "", &bOk );
    if(str=="")
    {
        QMessageBox::warning(this, tr("Пустая строка"),tr("Пустая строка"),QMessageBox::Ok);
        change_state_ds_end(true);
    }
    else
    {
        if (!bOk)
        {
            // Была нажата кнопка Cancel
        }
        else
        {
             why_remove  = str;
        }
    }

    }
    else if(ui->checkBox_ds_end_state->checkState()==Qt::Unchecked)
    {
         ds_end = "";
    }

    //QString diagnos_id = ui->comboBox_diagnosis->currentData().toString();
    int control_lineedit=0;
    QPixmap error_pix(":/icon/png/images/Warning.png");
    if(ui->lineEdit_house->text()=="")
    {
        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_house->setFont(font_lineedit);
        ui->lineEdit_house->setStyleSheet("border: 2px solid red");
        control_lineedit=1;
    }
    else
    {
        QPalette p = ui->lineEdit_house->palette();
        p.setColor(QPalette::Base, Qt::white);
        ui->lineEdit_house->setPalette(p);
        ui->lineEdit_house->setFrame(true);
    }
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
    if(ui->lineEdit_oname->text()=="")
    {
        QFont font_lineedit;
        font_lineedit.setPointSize(11);
        ui->lineEdit_oname->setFont(font_lineedit);
        ui->lineEdit_oname->setStyleSheet("border: 2px solid red");
        ui->label_mname_icon->setPixmap(error_pix.scaled(24,24,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        control_lineedit=1;
    }
    else
    {
        QPalette p = ui->lineEdit_oname->palette();
        p.setColor(QPalette::Base, Qt::white);
        ui->lineEdit_oname->setPalette(p);
        ui->lineEdit_oname->setFrame(true);
    }
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
                query.exec("INSERT INTO test.medcard(patient_id,sex,staff_add_id, birthday, ds_start, ds_end, job_place,why_removed, post) VALUES ('"+id_patient+"','"+sex_value+"', '"+global_staff_id+"', '"+date_birthday+"','"+ds_start+"','"+ds_end+"', '"+job_place_value+"', '"+why_remove+"', '"+job_post_value+"') RETURNING id;");
                while (query.next())
                {
                    id_medcard = query.value(0).toString();

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
                query.exec("UPDATE test.medcard SET sex = "+sex_value+", birthday='"+date_birthday+"',ds_start='"+ds_start+"',ds_end='"+ds_end+"', job_place='"+job_place_value+"', why_removed='"+why_remove+"', post='"+job_post_value+"' WHERE id ="+id_str);
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
                query.exec("UPDATE test.address_patient SET street_id ='"+street_id+"', home = '"+home+"', building = '"+building+"', flat = '"+flat+"' WHERE medcard_id = "+id_str);
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
