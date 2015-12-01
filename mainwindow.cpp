#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Dialog_login login_win;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    if(login_win.exec())
    {
        staff_id = login_win.staff_id;
        if(db.open())
        {
            query.exec("SELECT \
                       rights.select_patients, \
                       rights.insert_patients,\
                       rights.delete_patients, \
                       rights.update_patients, \
                       rights.add_dynamic_view,\
                       rights.edit_dynamic_view,\
                       rights.del_dynamic_view, \
                       rights.add_visits, \
                       rights.edit_visits, \
                       rights.del_visits, \
                       rights.add_today_visits\
                       FROM \
                       test.rights, \
                       test.staff, \
                       test.users\
                       WHERE \
                       staff.id = users.staff_id AND\
                    users.id = rights.user_id AND\
                    staff.id = "+staff_id);
                    while(query.next())
            {
                    rights_user.append(query.value(0).toBool());
                    rights_user.append(query.value(1).toBool());
                    rights_user.append(query.value(2).toBool());
                    rights_user.append(query.value(3).toBool());
                    rights_user.append(query.value(4).toBool());
                    rights_user.append(query.value(5).toBool());
                    rights_user.append(query.value(6).toBool());
                    rights_user.append(query.value(7).toBool());
                    rights_user.append(query.value(8).toBool());
                    rights_user.append(query.value(9).toBool());
                    rights_user.append(query.value(10).toBool());

        }
        }
        settings_user();
        settings_ui();

        connect(ui->action_settings_program,SIGNAL(triggered()),SLOT(open_win_settings()));


    }
    else
    {
        exit(0);
    }
    if(first_start!=1)
    {
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(find_patients()));
    timer->start(500);
    thread_new_changes();
    }
    connect(ui->action_report_1,SIGNAL(triggered()),SLOT(gen_report_1()));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),SLOT(load_all_info()));
    connect(ui->tableWidget_dynamic_view,SIGNAL(customContextMenuRequested(QPoint)),SLOT(context_menu_dynamic_view(QPoint)));
    connect(ui->tableWidget_control_pos,SIGNAL(customContextMenuRequested(QPoint)),SLOT(context_menu_visits_control(QPoint)));
    connect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),SLOT(context_menu_main_table(QPoint)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::thread_new_changes()
{
    qDebug()<<"thread start";
        QThread* thread = new QThread;
        new_changes_thread * changes_new = new new_changes_thread;
        changes_new->moveToThread(thread);
        connect(thread,SIGNAL(started()),changes_new,SLOT(check_new_changes_blanks()));

        connect(changes_new, SIGNAL(finished()), thread, SLOT(quit()));
        connect(changes_new, SIGNAL(finished()), changes_new, SLOT(deleteLater()));
        connect(changes_new,SIGNAL(status(int)),SLOT(changes_new(int)));

        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        thread->start();
}

void MainWindow::changes_new(int status)
{
    qDebug()<<status;
}

void MainWindow::load_main_table()
{
    clear_main_table();
    settings_ui();
}
void MainWindow::settings_ui()
{
    //Создаем объекты
    QSqlDatabase db = QSqlDatabase::database();
    str_find_patient=new QLineEdit();
    valid_info = new QLabel();

    QPushButton * add_patient = new QPushButton();
    QPushButton * edit_patient = new QPushButton();
    QPushButton * del_patient = new QPushButton();

    str_find_patient->setEnabled(rights_user[0]);
    add_patient->setEnabled(rights_user[1]);
    edit_patient->setEnabled(rights_user[2]);
    del_patient->setEnabled(rights_user[3]);

    QIcon icon_add(":/icon/png/images/add_icon.png");
    QIcon icon_edit(":/icon/png/images/edit_icon.png");
    QTableWidget * patientTable = ui->tableWidget; //Основная таблица
    QTableWidget * dynamicView = ui->tableWidget_dynamic_view;// Динамика наблюдения
    QTableWidget * controlpos = ui->tableWidget_control_pos; //Контроль посещений

    //    QTableWidgetItem * name_1_collumn_main = new QTableWidgetItem();
    //    QTableWidgetItem * name_2_collumn_main = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_main = new QTableWidgetItem();
    QTableWidgetItem * name_4_collumn_main = new QTableWidgetItem();
    QTableWidgetItem * name_5_collumn_main = new QTableWidgetItem();

    QTableWidgetItem * name_1_collumn_dynamic_view = new QTableWidgetItem();
    QTableWidgetItem * name_2_collumn_dynamic_view = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_dynamic_view = new QTableWidgetItem();

    QTableWidgetItem * name_1_collumn_control_pos = new QTableWidgetItem();
    QTableWidgetItem * name_2_collumn_control_pos = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_control_pos = new QTableWidgetItem();

    
    //Настраиваем объекты
    
    str_find_patient->setMaximumWidth(100);
    str_find_patient->setToolTip("Для поиска по карте \nвведите только номер,\n фамилия и имя должны быть разделены\n одним пробелом");
    valid_info->setText("<-Введите номер карты или Фамилию");

    add_patient->setText("Добавить");
    add_patient->setIcon(icon_add);
    edit_patient->setText("Редактировать");
    edit_patient->setIcon(icon_edit);
    del_patient->setText("Удалить");
    //patientTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //Рястягивает все по ширине таблицы
    dynamicView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    controlpos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    patientTable->setColumnCount(5);
    dynamicView->setColumnCount(4);
    controlpos->setColumnCount(4);

    patientTable->hideColumn(0);
    patientTable->hideColumn(1);
    dynamicView->hideColumn(0);
    controlpos->hideColumn(0);
    //    patientTable->setColumnWidth(0,50);
    //    patientTable->setColumnWidth(3,30);
    //    patientTable->setColumnWidth(4,50);
    //    patientTable->setColumnWidth(5,50);
    //    patientTable->setColumnWidth(8,70);
    //    patientTable->setColumnWidth(9,70);
    //name_2_collumn_main->setText("");
    QFont font_table_header;
    font_table_header.setPointSize(11);
    name_3_collumn_main->setText("ФИО");
    name_4_collumn_main->setText("Серия\n паспорта");
    name_5_collumn_main->setText("Номер\n паспорта");
    name_1_collumn_dynamic_view->setText("Помощь\n оказывается с:");
    name_2_collumn_dynamic_view->setText("Группа диспансерного\n наблюдения:");
    name_3_collumn_dynamic_view->setText("Вид \nамбулаторной\n помощи:");

    name_1_collumn_control_pos->setText("Назначено:");
    name_2_collumn_control_pos->setText("Назначил:");
    name_3_collumn_control_pos->setText("Дата явки:");

    name_3_collumn_main->setFont(font_table_header);
    name_4_collumn_main->setFont(font_table_header);
    name_5_collumn_main->setFont(font_table_header);
    name_1_collumn_dynamic_view->setFont(font_table_header);
    name_2_collumn_dynamic_view->setFont(font_table_header);
    name_3_collumn_dynamic_view->setFont(font_table_header);
    name_1_collumn_control_pos->setFont(font_table_header);
    name_2_collumn_control_pos->setFont(font_table_header);
    name_3_collumn_control_pos->setFont(font_table_header);
    //patientTable->setHorizontalHeaderItem(0,name_1_collumn_main);
    //patientTable->setHorizontalHeaderItem(1,name_2_collumn_main);
    //patientTable->setHorizontalHeaderItem(2,name_2_collumn_main);
    patientTable->setHorizontalHeaderItem(2,name_3_collumn_main);
    patientTable->setHorizontalHeaderItem(3,name_4_collumn_main);
    patientTable->setHorizontalHeaderItem(4,name_5_collumn_main);

    dynamicView->setHorizontalHeaderItem(1,name_1_collumn_dynamic_view);
    dynamicView->setHorizontalHeaderItem(2,name_2_collumn_dynamic_view);
    dynamicView->setHorizontalHeaderItem(3,name_3_collumn_dynamic_view);


    controlpos->setHorizontalHeaderItem(1,name_1_collumn_control_pos);
    controlpos->setHorizontalHeaderItem(2,name_2_collumn_control_pos);
    controlpos->setHorizontalHeaderItem(3,name_3_collumn_control_pos);
    
    
    //отрисовываем объекты
    ui->mainToolBar->addWidget(add_patient);
    ui->mainToolBar->addWidget(edit_patient);
    ui->mainToolBar->addWidget(del_patient);
    ui->mainToolBar->addWidget(str_find_patient);
    
    //обрабатываем сигналы
    connect(add_patient,SIGNAL(clicked()),SLOT(added_info_patient()));
    connect(edit_patient,SIGNAL(clicked()),SLOT(edit_info_patient()));
    connect(del_patient,SIGNAL(clicked()),SLOT(del_info_patient()));
    connect(str_find_patient,SIGNAL(returnPressed()),SLOT(find_patients()));
    //меняем title
    if(db.open())
    {
        QSqlQuery query;
        query.exec("SELECT staff.fname, staff.name, staff.mname FROM test.staff WHERE staff.id = "+staff_id);
        while(query.next())
        {
            QString name_login;
            name_login.append(query.value(0).toString()).append(" ").append(query.value(1).toString()).append(" ").append(query.value(2).toString());
            this->setWindowTitle("Вы вошли как: "+name_login);
        }
    }
    
}
void MainWindow::open_win_settings()
{
    Dialog_settings_user settings_dialog;
    settings_dialog.exec();
    settings_user();
    if(str_find_patient->text()!="")
    {
        find_patients();
    }
}
void MainWindow::settings_user()
{
    font_size = 8;
    QSettings *settings = new QSettings("settings_user.ini",QSettings::IniFormat);
    ipdatabase = settings->value("ipdatabase").toString();
    font_size = settings->value("sizefonttexttable").toInt();
    
}
void MainWindow::added_info_patient()
{
    Dialog_patient dialog;
    dialog.setParam(0,0,staff_id);

    if(dialog.exec())
    {
        find_patients();
    }
}
void MainWindow::edit_info_patient()
{
    Dialog_patient dialog;
    
    int selected_tables = ui->tableWidget->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget->currentRow();
        int id = ui->tableWidget->item(cu_row,0)->text().toInt();
        dialog.setParam(1,id,staff_id);
        if(dialog.exec())
        {
            find_patients();
        }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка", "Выберете одного пациента");

    }


}
void MainWindow::del_info_patient()
{

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget->currentRow();
        QString id = ui->tableWidget->item(cu_row,1)->text();
        int ret = QMessageBox::warning(this, tr("Удаление динамики наблюдения"),
                                       tr("Вы точно хотите удалить?"),
                                       QMessageBox::Yes|QMessageBox::No);

        if(ret==16384)
        {
            query.exec("UPDATE test.patient  SET status='1' WHERE id= "+id);
            ui->tableWidget->removeRow(cu_row);
            query.clear();
        }

    }
    else
    {
        QMessageBox::warning(this,"Ошибка", "Выберете одного пациента");

    }
}
void MainWindow::clear_main_table()
{
    int c =0;
    ui->tableWidget->clear();
    ui->mainToolBar->clear();
    for (c = ui->tableWidget->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget->removeRow(c);
    }

}
void MainWindow::clear_dynamic_view_table()
{
    int c;
    ui->tableWidget_dynamic_view->clear();
    ui->mainToolBar->clear();
    for (c = ui->tableWidget_dynamic_view->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_dynamic_view->removeRow(c);
    }

}
void MainWindow::clear_visiting_control_table()
{
    int c;
    ui->tableWidget_control_pos->clear();
    ui->mainToolBar->clear();
    for (c = ui->tableWidget_control_pos->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_control_pos->removeRow(c);
    }
}
void MainWindow::find_patients()
{
    first_start=1;
    if(first_start)
    {
    timer->stop();
    }
    QSqlDatabase db = QSqlDatabase::database();
    QSettings *settings = new QSettings("settings_user.ini",QSettings::IniFormat);
    int vari=0;
    bool use_filter = settings->value("use_filter").toBool();
    if(use_filter)
    {
        ui->statusBar->showMessage("Используеться фильтр поиска");
        QString fname = settings->value("fname_filter").toString();
        QString name = settings->value("name_filter").toString();
        QString mname = settings->value("mname_filter").toString();

    }
    else
    {
        QString save_find_string = str_find_patient->text();
        QStringList find_string = str_find_patient->text().split(" ");
        clear_main_table();
        clear_dynamic_view_table();
        clear_visiting_control_table();
        settings_ui();
        str_find_patient->setText(save_find_string);

        if(find_string[0].toInt()>0)
        {
            vari=1;
        }
        else if (find_string[0]==0 && find_string[0]=="")
        {
            vari=2;
        }
        else if(find_string.count()==1)
        {
            vari=3;
        }
        else if (find_string.count()>1)
        {
            vari=4;
        }
        if(db.open())
        {

            QSqlQuery query;
            QString sqlquery;
            QString sqlquery_count;
            switch (vari) {
            case 1:

                sqlquery="SELECT medcard.id, patient.id, patient.fname, patient.name, patient.mname, patient.serial_passport, patient.number_passport FROM test.medcard, test.patient WHERE medcard.patient_id = patient.id AND patient.status = '0' AND patient.id = ";
                sqlquery.append(find_string[0]).append(";");
                sqlquery_count="SELECT count(patient.id) FROM test.medcard, test.patient WHERE medcard.patient_id = patient.id AND patient.status = '0' AND patient.id = ";
                sqlquery_count.append(find_string[0]).append(";");
                break;
            case 2:
                sqlquery="SELECT medcard.id, patient.id, patient.fname, patient.name, patient.mname, patient.serial_passport, patient.number_passport FROM test.medcard, test.patient WHERE medcard.patient_id = patient.id AND patient.status = '0';";
                sqlquery_count="SELECT count(patient.id) FROM test.medcard, test.patient WHERE medcard.patient_id = patient.id AND patient.status = '0';";

                break;
            case 3:
                sqlquery="SELECT medcard.id, patient.id, patient.fname, patient.name, patient.mname, patient.serial_passport, patient.number_passport FROM test.medcard, test.patient WHERE medcard.patient_id = patient.id AND patient.status = '0' AND patient.fname LIKE ";
                sqlquery.append("'%").append(find_string[0]).append("%'").append(";");
                sqlquery_count="SELECT count(patient.id) FROM test.medcard, test.patient WHERE medcard.patient_id = patient.id AND patient.status = '0' AND patient.fname LIKE ";
                sqlquery_count.append("'%").append(find_string[0]).append("%'").append(";");

                break;
            case 4:

                sqlquery="SELECT medcard.id, patient.id, patient.fname, patient.name, patient.mname, patient.serial_passport, patient.number_passport FROM test.medcard, test.patient WHERE medcard.patient_id = patient.id AND patient.status = '0' AND patient.fname LIKE ";
                sqlquery.append("'%").append(find_string[0]).append("%'").append(" AND patient.name LIKE ").append("'").append(find_string[1]).append("%'").append(";");
                sqlquery_count="SELECT count(patient.id) FROM test.medcard, test.patient WHERE medcard.patient_id = patient.id AND patient.status = '0' AND patient.fname LIKE";
                sqlquery_count.append("'%").append(find_string[0]).append("%'").append(" AND patient.name LIKE ").append("'").append(find_string[1]).append("%'").append(";");
                break;
            }
            query.exec(sqlquery_count);
            while(query.next())
            {
                ui->progressBar->setMaximum(query.value(0).toInt());
            }
            query.exec(sqlquery);
            int last_row = ui->tableWidget->rowCount();
            int progress_status=0;
            while (query.next()) {
                progress_status++;
                ui->progressBar->setValue(progress_status);
                QString id_medcard = query.value(0).toString();
                QString id_patient = query.value(1).toString();
                QString name;
                name.append(query.value(2).toString())
                        .append(" ")
                        .append(query.value(3).toString())
                        .append(" ")
                        .append(query.value(4).toString());
                QString serial_passport_value = query.value(5).toString();
                QString number_passport_value = query.value(6).toString();

                QTableWidgetItem * medcard_id = new QTableWidgetItem();
                QTableWidgetItem * patient_id = new QTableWidgetItem();
                QTableWidgetItem * name_t = new QTableWidgetItem();
                QTableWidgetItem * serial_passport = new QTableWidgetItem();
                QTableWidgetItem * number_passport = new QTableWidgetItem();

                QFont font_text;
                font_text.setPointSize(font_size);

                medcard_id->setText(id_medcard);
                patient_id->setText(id_patient);
                name_t->setText(name);
                serial_passport->setText(serial_passport_value);
                number_passport->setText(number_passport_value);

                medcard_id->setFont(font_text);
                patient_id->setFont(font_text);
                name_t->setFont(font_text);
                serial_passport->setFont(font_text);
                number_passport->setFont(font_text);


                ui->tableWidget->insertRow(last_row);
                //            if (query.value(0)==2)
                //            {
                //                patient_id->setBackground(Qt::red);
                //                medcard_id->setBackground(Qt::red);
                //                name_t->setBackground(Qt::red);
                //                serial_passport->setBackground(Qt::red);
                //                number_passport->setBackground(Qt::red);

                //            }
                ui->tableWidget->setItem(last_row,0,medcard_id);
                ui->tableWidget->setItem(last_row,1,patient_id);
                ui->tableWidget->setItem(last_row,2,name_t);
                ui->tableWidget->setItem(last_row,3,serial_passport);
                ui->tableWidget->setItem(last_row,4,number_passport);

            }
            query.finish();
            query.clear();

        }
    }
}
void MainWindow::gen_report_1()
{
    Dialog_reports dialog;
    dialog.gen_report(1);
    dialog.exec();
}
void MainWindow::load_all_info()
{
    clear_dynamic_view_table();
    clear_visiting_control_table();
    settings_ui();
    QSqlDatabase db = QSqlDatabase::database();
    int selected_tables = ui->tableWidget->selectionModel()->selectedRows().count();
    qDebug()<<"selected"<<selected_tables;
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget->currentRow();
        QString id = ui->tableWidget->item(cu_row,0)->text();
        qDebug()<<db.open();
        if(db.open())
        {
            QSqlQuery query;
            QString sqlquery;
            sqlquery.append("SELECT \
                            dynamic_view.id, \
                            dynamic_view.on_date, \
                            dynamic_view.group_disp_view, \
                            dynamic_view.type_of_help\
                            FROM \
                            test.dynamic_view\
                            WHERE \
                            dynamic_view.delete_row = '0' AND\
                    dynamic_view.medcard_id = ").append(id);
                    query.exec(sqlquery);
                    int last_row = ui->tableWidget_dynamic_view->rowCount();
            while (query.next()) {
                QString id_value = query.value(0).toString();
                QString date_value = query.value(1).toString();
                QString group_value = query.value(2).toString();
                QString vid_value = query.value(3).toString();
                QTableWidgetItem * id =new QTableWidgetItem();
                QTableWidgetItem * date = new QTableWidgetItem();
                QTableWidgetItem * group = new QTableWidgetItem();
                QTableWidgetItem * vid = new QTableWidgetItem();
                QFont font_text;
                font_text.setPointSize(font_size);
                if(group_value=="1")
                {
                    group_value="Д";
                }
                if(group_value=="2")
                {
                    group_value="ЛП";
                }
                if(group_value=="3")
                {
                    group_value="Нет согласия";
                }
                if(vid_value=="0")
                {
                    vid_value="";
                }
                if(vid_value=="1")
                {
                    vid_value="АДН";
                }
                if(vid_value=="2")
                {
                    vid_value="АПЛ";
                }
                id->setText(id_value);
                date->setText(date_value);
                group->setText(group_value);
                vid->setText(vid_value);

                date->setFont(font_text);
                group->setFont(font_text);
                vid->setFont(font_text);
                ui->tableWidget_dynamic_view->insertRow(last_row);
                ui->tableWidget_dynamic_view->setItem(last_row,0,id);
                ui->tableWidget_dynamic_view->setItem(last_row,1,date);
                ui->tableWidget_dynamic_view->setItem(last_row,2,group);
                ui->tableWidget_dynamic_view->setItem(last_row,3,vid);

            }
            sqlquery.clear();
            sqlquery.append("SELECT \
                            visits_control.id, \
                            visits_control.date_assigned, \
                            visits_control.date_presence, \
                            staff.fname, \
                            staff.name, \
                            staff.mname\
                            FROM \
                            test.visits_control, \
                            test.staff\
                            WHERE \
                            visits_control.delete_row = '0' AND\
                    visits_control.staff_add_id = staff.id AND\
                    visits_control.medcard_id = ").append(id);
                    query.exec(sqlquery);
                    int last_row_control = ui->tableWidget_control_pos->rowCount();
            QString current_date = QDate::currentDate().toString("MM.dd.yyyy");
            while (query.next()) {
                QString id_value = query.value(0).toString();
                QString assign_value = query.value(1).toDate().toString("dd.MM.yyyy");
                QString who_value;
                who_value.append(query.value(3).toString()).append(" ").append(query.value(4).toString()).append(" ").append(query.value(5).toString());
                QString presence_value = query.value(2).toDate().toString("dd.MM.yyyy");

                QTableWidgetItem * id = new QTableWidgetItem();
                QTableWidgetItem * assign = new QTableWidgetItem();
                QTableWidgetItem * who = new QTableWidgetItem();
                QTableWidgetItem * presence = new QTableWidgetItem();

                assign->setText(assign_value);
                who->setText(who_value);
                presence->setText(presence_value);
                id->setText(id_value);

                QFont font_text;
                font_text.setPointSize(font_size);

                assign->setFont(font_text);
                who->setFont(font_text);
                presence->setFont(font_text);
                id->setFont(font_text);
                if(query.value(2).toString()=="")
                {

                    if (QDate::fromString(current_date, "MM.dd.yyyy")>query.value(1).toDate())
                    {
                        assign->setBackground(Qt::red);
                        who->setBackground(Qt::red);
                        presence->setBackground(Qt::red);
                    }
                    if (QDate::fromString(current_date, "MM.dd.yyyy")==query.value(1).toDate())
                    {
                        assign->setBackground(Qt::cyan);
                        who->setBackground(Qt::cyan);
                        presence->setBackground(Qt::cyan);
                    }
                }
                ui->tableWidget_control_pos->insertRow(last_row_control);

                ui->tableWidget_control_pos->setItem(last_row_control,0,id);
                ui->tableWidget_control_pos->setItem(last_row_control,1,assign);
                ui->tableWidget_control_pos->setItem(last_row_control,2,who);
                ui->tableWidget_control_pos->setItem(last_row_control,3,presence);

            }
        }

    }

}
void MainWindow::context_menu_dynamic_view(QPoint pos) // Контекстное меню для Таблицы Динамика наблюдения
{
    QMenu *menu = new QMenu;
    menu->addAction("Добавить", this, SLOT(add_dynamic_view()))->setEnabled(rights_user[4]);
    menu->addAction("Изменить", this, SLOT(edit_dynamic_view()))->setEnabled(rights_user[5]); // это можно использовать для прав->setEnabled(false);
    menu->addAction("Удалить", this, SLOT(del_dynamic_view()))->setEnabled(rights_user[6]);
    menu->exec(ui->tableWidget_dynamic_view->mapToGlobal(pos));
}
void MainWindow::context_menu_visits_control(QPoint pos) //Контекстное меню для Таблицы Контроль посещений
{
    QMenu *menu = new QMenu;
    QString date;
    bool set1=rights_user[7];
    bool set2=rights_user[10];
    bool set3=rights_user[8];
    bool set4=rights_user[9];
    int selected_tables = ui->tableWidget_control_pos->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_control_pos->currentRow();
        date = ui->tableWidget_control_pos->item(cu_row,3)->text();
    }
    if(date=="")
    {
        set2=true;
    }
    else
    {
        set2=false;
    }
    menu->addAction("Добавить", this, SLOT(add_visit()))->setEnabled(set1);
    menu->addAction("Пришел (сегодня)", this, SLOT(add_today_visit()))->setEnabled(set2);
    menu->addAction("Изменить", this, SLOT(edit_visit()))->setEnabled(set3); // это можно использовать для прав->setEnabled(false);
    menu->addAction("Удалить", this, SLOT(del_visit()))->setEnabled(set4);
    menu->exec(ui->tableWidget_control_pos->mapToGlobal(pos));
}
void MainWindow::context_menu_main_table(QPoint pos)
{
    int selected_tables = ui->tableWidget->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        QMenu *menu = new QMenu;
        QMenu *submenu_status = new QMenu("Статус", menu);
        menu->addAction("Добавить", this, SLOT(added_info_patient()));
        menu->addAction("Изменить", this, SLOT(edit_info_patient()));
        menu->addAction("Удалить", this, SLOT(del_info_patient()));
        menu->addMenu(submenu_status);
        submenu_status->addAction("В Архив", this, SLOT(set_status_arhive()));
        menu->addSeparator();
        menu->addAction("Печать медкарты", this ,SLOT(print_medcard()));
        menu->exec(ui->tableWidget->mapToGlobal(pos));
    }
}
void MainWindow::add_visit()
{
    Dialog_add_visits dialog;
    int selected_tables = ui->tableWidget->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget->currentRow();
        QString id = ui->tableWidget->item(cu_row,0)->text();
        dialog.setParam(0,id,staff_id);
        if(dialog.exec())
        {
            load_all_info();
        }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Чтобы добавить посещение нужно сначала выбрать пациента");
    }

}
void MainWindow::edit_visit()
{
    Dialog_add_visits dialog;
    int selected_tables = ui->tableWidget_control_pos->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_control_pos->currentRow();
        QString id = ui->tableWidget_control_pos->item(cu_row,0)->text();
        dialog.setParam(1,id,staff_id);
        if(dialog.exec())
            {
                load_all_info();
            }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Нельзя изменить того чего нет)");
    }
}
void MainWindow::del_visit()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_control_pos->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_control_pos->currentRow();
        QString id = ui->tableWidget_control_pos->item(cu_row,0)->text();
        int ret = QMessageBox::warning(this, tr("Удаление посещения!"),
                                       tr("Вы точно хотите удалить?"),
                                       QMessageBox::Yes|QMessageBox::No);

        if(ret==16384)
        {
            qDebug()<<"UPDATE test.visits_control  SET delete_row='1' WHERE id= "+id;
            query.exec("UPDATE test.visits_control  SET delete_row='1' WHERE id= "+id);
            load_all_info();
        }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Нельзя удалить того чего нет)");
    }
}
void MainWindow::add_today_visit()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QDate *date_presence;
    QString date_string = date_presence->currentDate().toString("dd.MM.yyyy");
    int selected_tables = ui->tableWidget_control_pos->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_control_pos->currentRow();
        QString id = ui->tableWidget_control_pos->item(cu_row,0)->text();
        query.exec("UPDATE test.visits_control  SET date_presence='"+date_string+"' WHERE id= "+id);
        load_all_info();
    }
}
void MainWindow::add_dynamic_view()
{
    Dialog_add_dynamic_view dialog;
    int selected_tables = ui->tableWidget->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget->currentRow();
        QString id = ui->tableWidget->item(cu_row,0)->text();
        dialog.setParam(0,id,staff_id);
        if(dialog.exec())
            {
                load_all_info();
            }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Чтобы добавить динамику наблюдения нужно сначала выбрать пациента");
    }
}
void MainWindow::del_dynamic_view()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_dynamic_view->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_dynamic_view->currentRow();
        QString id = ui->tableWidget_dynamic_view->item(cu_row,0)->text();
        int ret = QMessageBox::warning(this, tr("Удаление динамики наблюдения"),
                                       tr("Вы точно хотите удалить?"),
                                       QMessageBox::Yes|QMessageBox::No);

        if(ret==16384)
        {
            query.exec("UPDATE test.dynamic_view  SET delete_row='1' WHERE id= "+id);
            load_all_info();
        }


    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Нельзя удалить того чего нет)");
    }

}
void MainWindow::edit_dynamic_view()
{
    Dialog_add_dynamic_view dialog;
    int selected_tables = ui->tableWidget_dynamic_view->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_dynamic_view->currentRow();
        QString id = ui->tableWidget_dynamic_view->item(cu_row,0)->text();
        dialog.setParam(1,id,staff_id);
        if(dialog.exec())
            {
                load_all_info();
            }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Нельзя изменить того чего нет)");
    }

}
void MainWindow::print_medcard()
{
    Dialog_preview_print dialog;
    int selected_tables = ui->tableWidget->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget->currentRow();
        QString id = ui->tableWidget->item(cu_row,0)->text();
        dialog.setParam(0,id,staff_id);
        if(dialog.exec())
        {
            find_patients();
        }
    }
}
void MainWindow::set_status_arhive()
{

}
