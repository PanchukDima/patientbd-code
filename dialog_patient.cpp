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

    // ui->dateEdit_date_birthday->setEnabled(false);
    ui->dateEdit_date_end->setEnabled(false);
    ui->dateEdit_date_install_dianosis->setEnabled(false);
    ui->dateEdit_date_start->setEnabled(false);
    ui->comboBox_area->setEnabled(false);
    ui->comboBox_area_street->setEnabled(false);
    ui->checkBox_custody->setEnabled(false);
    ui->comboBox_accommodations->setEnabled(false);
    //ui->comboBox_diagnosis->setEnabled(false);
    ui->comboBox_direction->setEnabled(false);
    ui->lineEdit_work_or_education->setEnabled(false);
    ui->comboBox_work_post->setEnabled(false);
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

void Dialog_patient::setParam(int param,int id, QString staff_id)
{
    global_param = param;
    global_staff_id = staff_id;
    qDebug()<<id;
    switch(param)
    {
    case 0:
        qDebug()<<"added patient";
        break;
    case 1:
        qDebug()<<"edit patient";
        get_data_sql(id);
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
//        query.exec("SELECT address_patient.street_id FROM test.address_patient WHERE  address_patient.medcard_id = "+id_str);
//        while (query.next())
//        {
//            QString street_value = query.value(0).toString();
//            ui->comboBox_street->setCurrentIndex(ui->comboBox_street->findData(street_value));
//        }
        query.exec("SELECT address_patient.street_id, address_patient.building, address_patient.home, patient.fname, patient.name, patient.mname, medcard.sex,address_patient.flat, patient.serial_passport,patient.number_passport,medcard.birthday, address_patient.telefon,diagnos_patient.diagnos_id  FROM test.address_patient, test.patient, test.medcard, test.diagnos_patient WHERE medcard.patient_id = patient.id AND medcard.id = address_patient.medcard_id AND medcard.id = diagnos_patient.medcard_id AND medcard.id = "+id_str);
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
            QString diagnos_id_value = query.value(12).toString();


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
            //ui->comboBox_diagnosis->setCurrentIndex(ui->comboBox_diagnosis->findData(diagnos_id_value));
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
                qDebug()<<"INSERT INTO test.medcard(patient_id,sex,staff_add_id, birthday) VALUES ('"+id_patient+"','"+sex_value+"', '"+global_staff_id+"', '"+date_birthday+"') RETURNING id;";
                query.exec("INSERT INTO test.medcard(patient_id,sex,staff_add_id, birthday) VALUES ('"+id_patient+"','"+sex_value+"', '"+global_staff_id+"', '"+date_birthday+"') RETURNING id;");
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
                query.exec("UPDATE test.medcard SET sex = "+sex_value+", birthday='"+date_birthday+"' WHERE id ="+id_str);
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
