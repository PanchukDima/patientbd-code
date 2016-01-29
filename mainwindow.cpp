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

    thread_new_changes();
    }

    connect(ui->action_report_1,SIGNAL(triggered()),SLOT(gen_report_1()));
    //connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),SLOT(load_all_info()));  //то что снизу работает лучше, но для примера оставлю это здесь
    connect(ui->tableWidget,SIGNAL(itemSelectionChanged()),SLOT(load_all_info()));
    connect(ui->tableWidget_dynamic_view,SIGNAL(customContextMenuRequested(QPoint)),SLOT(context_menu_dynamic_view(QPoint)));
    connect(ui->tableWidget_control_pos,SIGNAL(customContextMenuRequested(QPoint)),SLOT(context_menu_visits_control(QPoint)));
    connect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),SLOT(context_menu_main_table(QPoint)));
    connect(ui->tableWidget_diagnos_patient,SIGNAL(customContextMenuRequested(QPoint)),SLOT(context_menu_diagnos_table(QPoint)));
    connect(ui->tableWidget_sved_gospital,SIGNAL(customContextMenuRequested(QPoint)),SLOT(context_menu_hospitalization_table(QPoint)));
    connect(ui->pushButton_add_history_patient,SIGNAL(clicked(bool)),SLOT(added_files_patient()));


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
        connect(changes_new,SIGNAL(status(QString)),SLOT(changes_new(QString)));

        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        thread->start();
}


void MainWindow::changes_new(QString status)
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
    QPushButton * filter_find = new QPushButton();

    str_find_patient->setEnabled(rights_user[0]);
    add_patient->setEnabled(rights_user[1]);
    edit_patient->setEnabled(rights_user[2]);
    del_patient->setEnabled(rights_user[3]);

    QIcon icon_add(":/icon/png/images/add_icon.png");
    QIcon icon_edit(":/icon/png/images/edit_icon.png");
    QTableWidget * patientTable = ui->tableWidget; //Основная таблица
    QTableWidget * dynamicView = ui->tableWidget_dynamic_view;// Динамика наблюдения
    QTableWidget * controlpos = ui->tableWidget_control_pos; //Контроль посещений
    QTableWidget * diagnos_table = ui->tableWidget_diagnos_patient; //Диагнозы пациентов
    QTableWidget * gospit_table = ui->tableWidget_sved_gospital;
    QTableWidget * list_not_work_table = ui->tableWidget_point_time_notwork;
    QTableWidget * invalid_table = ui->tableWidget_invalid_psi;
    QTableWidget * suicid_table = ui->tableWidget_suicid;


    //Итемы главной таблицы
    //    QTableWidgetItem * name_1_collumn_main = new QTableWidgetItem();
    //    QTableWidgetItem * name_2_collumn_main = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_main = new QTableWidgetItem();
    QTableWidgetItem * name_4_collumn_main = new QTableWidgetItem();
    QTableWidgetItem * name_5_collumn_main = new QTableWidgetItem();
    //Итемы таблицы динамики наблюдения
    QTableWidgetItem * name_1_collumn_dynamic_view = new QTableWidgetItem();
    QTableWidgetItem * name_2_collumn_dynamic_view = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_dynamic_view = new QTableWidgetItem();
    QTableWidgetItem * name_4_collumn_dynamic_view = new QTableWidgetItem();
    //Итемы таблицы контроль посешщений
    QTableWidgetItem * name_1_collumn_control_pos = new QTableWidgetItem();
    QTableWidgetItem * name_2_collumn_control_pos = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_control_pos = new QTableWidgetItem();
    //Итемы таблицы диагнозов
    QTableWidgetItem * name_1_collumn_diagnos_table = new QTableWidgetItem();
    QTableWidgetItem * name_2_collumn_diagnos_table = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_diagnos_table = new QTableWidgetItem();
    QTableWidgetItem * name_4_collumn_diagnos_table = new QTableWidgetItem();
    QTableWidgetItem * name_5_collumn_diagnos_table = new QTableWidgetItem();
    //Итемы таблицы госпитализация
    QTableWidgetItem * name_1_collumn_gospit = new QTableWidgetItem();
    QTableWidgetItem * name_2_collumn_gospit = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_gospit = new QTableWidgetItem();
    QTableWidgetItem * name_4_collumn_gospit = new QTableWidgetItem();

    //Итемы таблицы нетрудоспособности
    QTableWidgetItem * name_1_collumn_list_not_work = new QTableWidgetItem();
    QTableWidgetItem * name_2_collumn_list_not_work = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_list_not_work = new QTableWidgetItem();
    //Итемы таблицы нетрудоспособности
    QTableWidgetItem * name_1_collumn_invalid = new QTableWidgetItem();
    QTableWidgetItem * name_2_collumn_invalid = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_invalid = new QTableWidgetItem();
    QTableWidgetItem * name_4_collumn_invalid = new QTableWidgetItem();
    //Итемы таблицы суицид
    QTableWidgetItem * name_1_collumn_suicid = new QTableWidgetItem();

    //Настраиваем объекты
    str_find_patient->setMaximumWidth(100);
    str_find_patient->setToolTip("Для поиска по карте \nвведите только номер,\n фамилия и имя должны быть разделены\n одним пробелом");
    valid_info->setText("<-Введите номер карты или Фамилию");

    add_patient->setText("Добавить");
    add_patient->setIcon(icon_add);
    edit_patient->setText("Редактировать");
    edit_patient->setIcon(icon_edit);
    del_patient->setText("Удалить");
    filter_find->setText("Фильтр поиска");

    //Настройка таблиц Рястягивание заголовка
    //patientTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //Рястягивает все по ширине таблицы
    dynamicView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    controlpos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    diagnos_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    diagnos_table->verticalHeader()->setDefaultSectionSize(70);

    gospit_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    list_not_work_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    invalid_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    suicid_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //Количество столбцов
    patientTable->setColumnCount(5);
    dynamicView->setColumnCount(5);
    controlpos->setColumnCount(4);
    diagnos_table->setColumnCount(6);
    gospit_table->setColumnCount(5);
    list_not_work_table->setColumnCount(4);
    invalid_table->setColumnCount(5);
    suicid_table->setColumnCount(2);
    //Скрытие столбцов
    patientTable->hideColumn(0);
    patientTable->hideColumn(1);
    dynamicView->hideColumn(0);
    controlpos->hideColumn(0);
    diagnos_table->hideColumn(0);
    gospit_table->hideColumn(0);
    list_not_work_table->hideColumn(0);
    invalid_table->hideColumn(0);
    suicid_table->hideColumn(0);


    //    patientTable->setColumnWidth(0,50);
    //    patientTable->setColumnWidth(3,30);
    //    patientTable->setColumnWidth(4,50);
    //    patientTable->setColumnWidth(5,50);
    //    patientTable->setColumnWidth(8,70);
    //    patientTable->setColumnWidth(9,70);
    //    name_2_collumn_main->setText("");


    QFont font_table_header;
    // Выставляем размер шрифта заголовков
    font_table_header.setPointSize(11);
    //текст заголовка таблицы вывода пациентов
    name_3_collumn_main->setText("ФИО");
    name_4_collumn_main->setText("Серия\n паспорта");
    name_5_collumn_main->setText("Номер\n паспорта");
    //текст заголовка таблицы динамика наблюдения
    name_1_collumn_dynamic_view->setText("Помощь\n оказывается с:");
    name_2_collumn_dynamic_view->setText("Группа\nдиспансерного\nнаблюдения:");
    name_3_collumn_dynamic_view->setText("Статус");
    name_4_collumn_dynamic_view->setText("Врач");
    //текст заголовка таблицы контроль посещений
    name_1_collumn_control_pos->setText("Назначено:\n");
    name_2_collumn_control_pos->setText("Назначил:\n");
    name_3_collumn_control_pos->setText("Дата явки:\n");
    //текст заголовка таблицы диагнозы
    name_1_collumn_diagnos_table->setText("Код по МКБ-10");
    name_2_collumn_diagnos_table->setText("Наименование\nпо МКБ-10");
    name_3_collumn_diagnos_table->setText("Дата\nпостановки\nдиагноза");
    name_4_collumn_diagnos_table->setText("Код врача");
    name_5_collumn_diagnos_table->setText("ФИО врача");
    //текст заголовка таблицы госпитализация
    name_1_collumn_gospit->setText("Инициатор\nгоспитализации");
    name_2_collumn_gospit->setText("Дата\nПоступления");
    name_3_collumn_gospit->setText("Дата выбытия");
    name_4_collumn_gospit->setText("Добавил\nИзменил");
    //текст заголовка таблицы лист нетрудоспособности
    name_1_collumn_list_not_work->setText("Дата открытия\nбольничного листа");
    name_2_collumn_list_not_work->setText("Дата закрытия\nбольничного листа");
    name_3_collumn_list_not_work->setText("Число дней ВН");
    //текст заголовка таблицы инвалидность по псих. заболеваниям
    name_1_collumn_invalid->setText("Дата\nустановления\nили\nпересмотра");
    name_2_collumn_invalid->setText("Группа\nинвалидности");
    name_3_collumn_invalid->setText("Срок очередного\nпереосвидетельствования");
    name_4_collumn_invalid->setText("Для работающих\n- место работы");
    //текст заголовка таблицы суицид
    name_1_collumn_suicid->setText("Дата совершения");

    // Выставляем размер шрифта заголовков "Главной таблицы"
    name_3_collumn_main->setFont(font_table_header);
    name_4_collumn_main->setFont(font_table_header);
    name_5_collumn_main->setFont(font_table_header);
    // Выставляем размер шрифта заголовков таблицы "Динамика наблюдения"
    name_1_collumn_dynamic_view->setFont(font_table_header);
    name_2_collumn_dynamic_view->setFont(font_table_header);
    name_3_collumn_dynamic_view->setFont(font_table_header);
    name_4_collumn_dynamic_view->setFont(font_table_header);
    // Выставляем размер шрифта заголовков таблицы "Контроль посещений"
    name_1_collumn_control_pos->setFont(font_table_header);
    name_2_collumn_control_pos->setFont(font_table_header);
    name_3_collumn_control_pos->setFont(font_table_header);
    // Выставляем размер шрифта заголовков таблицы "Диагноз"
    name_1_collumn_diagnos_table->setFont(font_table_header);
    name_2_collumn_diagnos_table->setFont(font_table_header);
    name_3_collumn_diagnos_table->setFont(font_table_header);
    name_4_collumn_diagnos_table->setFont(font_table_header);
    name_5_collumn_diagnos_table->setFont(font_table_header);
    // Выставляем размер шрифта заголовков таблицы "Госпитализация"
    name_1_collumn_gospit->setFont(font_table_header);
    name_2_collumn_gospit->setFont(font_table_header);
    name_3_collumn_gospit->setFont(font_table_header);
    name_4_collumn_gospit->setFont(font_table_header);
    // Выставляем размер шрифта заголовков таблицы "Лист нетрудоспособности"
    name_1_collumn_list_not_work->setFont(font_table_header);
    name_2_collumn_list_not_work->setFont(font_table_header);
    name_3_collumn_list_not_work->setFont(font_table_header);
    // Выставляем размер шрифта заголовков таблицы "инвалидность по псих. заболеваниям"
    name_1_collumn_invalid->setFont(font_table_header);
    name_2_collumn_invalid->setFont(font_table_header);
    name_3_collumn_invalid->setFont(font_table_header);
    name_4_collumn_invalid->setFont(font_table_header);
    // Выставляем размер шрифта заголовков таблицы "суицид"
    name_1_collumn_suicid->setFont(font_table_header);

    //Добавляем итемы на "Главную таблицу"
    //patientTable->setHorizontalHeaderItem(0,name_1_collumn_main);
    //patientTable->setHorizontalHeaderItem(1,name_2_collumn_main);
    //patientTable->setHorizontalHeaderItem(2,name_2_collumn_main);
    patientTable->setHorizontalHeaderItem(2,name_3_collumn_main);
    patientTable->setHorizontalHeaderItem(3,name_4_collumn_main);
    patientTable->setHorizontalHeaderItem(4,name_5_collumn_main);
    //Добавляем итемы на таблицу "Динамика наблюдения"
    dynamicView->setHorizontalHeaderItem(1,name_1_collumn_dynamic_view);
    dynamicView->setHorizontalHeaderItem(2,name_2_collumn_dynamic_view);
    dynamicView->setHorizontalHeaderItem(3,name_3_collumn_dynamic_view);
    dynamicView->setHorizontalHeaderItem(4,name_4_collumn_dynamic_view);
    //Добавляем итемы на таблицу "Контроль посещений"
    controlpos->setHorizontalHeaderItem(1,name_1_collumn_control_pos);
    controlpos->setHorizontalHeaderItem(2,name_2_collumn_control_pos);
    controlpos->setHorizontalHeaderItem(3,name_3_collumn_control_pos);
    //Добавляем итемы на таблицу "Диагноз"
    diagnos_table->setHorizontalHeaderItem(1,name_1_collumn_diagnos_table);
    diagnos_table->setHorizontalHeaderItem(2,name_2_collumn_diagnos_table);
    diagnos_table->setHorizontalHeaderItem(3,name_3_collumn_diagnos_table);
    diagnos_table->setHorizontalHeaderItem(4,name_4_collumn_diagnos_table);
    diagnos_table->setHorizontalHeaderItem(5,name_5_collumn_diagnos_table);
    //Добавляем итемы на таблицу "Динамика наблюдения"
    gospit_table->setHorizontalHeaderItem(1,name_1_collumn_gospit);
    gospit_table->setHorizontalHeaderItem(2,name_2_collumn_gospit);
    gospit_table->setHorizontalHeaderItem(3,name_3_collumn_gospit);
    gospit_table->setHorizontalHeaderItem(4,name_4_collumn_gospit);
    //Добавляем итемы на таблицу "Лист нетрудоспособности"
    list_not_work_table->setHorizontalHeaderItem(1,name_1_collumn_list_not_work);
    list_not_work_table->setHorizontalHeaderItem(2,name_2_collumn_list_not_work);
    list_not_work_table->setHorizontalHeaderItem(3,name_3_collumn_list_not_work);
    //Добавляем итемы на таблицу "инвалидность по псих. заболеваниям"
    invalid_table->setHorizontalHeaderItem(1,name_1_collumn_invalid);
    invalid_table->setHorizontalHeaderItem(2,name_2_collumn_invalid);
    invalid_table->setHorizontalHeaderItem(3,name_3_collumn_invalid);
    invalid_table->setHorizontalHeaderItem(4,name_4_collumn_invalid);
    //Добавляем итемы на таблицу "суицид"
    suicid_table->setHorizontalHeaderItem(1,name_1_collumn_suicid);

    //отрисовываем объекты
    ui->mainToolBar->addWidget(add_patient);
    ui->mainToolBar->addWidget(edit_patient);
    ui->mainToolBar->addWidget(del_patient);
    ui->mainToolBar->addWidget(str_find_patient);
    ui->mainToolBar->addWidget(filter_find);

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
void MainWindow::clear_diagnos_table()
{
    int c;
    ui->tableWidget_diagnos_patient->clear();
    ui->mainToolBar->clear();
    for (c = ui->tableWidget_diagnos_patient->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_diagnos_patient->removeRow(c);
    }
}
void MainWindow::clear_hospitalization_table()
{
    int c;
    ui->tableWidget_sved_gospital->clear();
    ui->mainToolBar->clear();
    for (c = ui->tableWidget_sved_gospital->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_sved_gospital->removeRow(c);
    }
}

void MainWindow::find_patients()
{

    QString save_find_string = str_find_patient->text();
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
        //QString save_find_string = str_find_patient->text();
        qDebug()<<save_find_string;
        clear_main_table();
        clear_dynamic_view_table();
        clear_visiting_control_table();
        settings_ui();
        qDebug()<<save_find_string;
        str_find_patient->setText(save_find_string);
        QStringList find_string = save_find_string.split(" ");
        qDebug()<<save_find_string;

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
    //очистка таблиц от старых данных
    QString save_find_string = str_find_patient->text();
    clear_dynamic_view_table();
    clear_visiting_control_table();
    clear_diagnos_table();
    clear_hospitalization_table();

    settings_ui();
    str_find_patient->setText(save_find_string);
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
                            dynamic_view.group_disp_view,\
                            dynamic_view.status,\
                            staff.fname,\
                            staff.name,\
                            staff.mname\
                            FROM\
                            test.dynamic_view,\
                            test.staff\
                            WHERE\
                            staff.id = dynamic_view.staff_add_id AND\
                            dynamic_view.delete_row = '0' AND\
                            dynamic_view.medcard_id = ").append(id);
                    query.exec(sqlquery);

            int last_row = ui->tableWidget_dynamic_view->rowCount();

            while (query.next()) {

                QString id_value = query.value(0).toString();
                QString date_value = query.value(1).toDate().toString("dd.MM.yyyy");
                QString group_value = query.value(2).toString();
                bool status_value = query.value(3).toBool();
                QString status_text;
                QString staff_fio_value;
                staff_fio_value.append(query.value(4).toString()).append("\n").append(query.value(5).toString()).append("\n").append(query.value(6).toString());

                QTableWidgetItem * id =new QTableWidgetItem();
                QTableWidgetItem * date = new QTableWidgetItem();
                QTableWidgetItem * group = new QTableWidgetItem();
                QTableWidgetItem * status = new QTableWidgetItem();
                QTableWidgetItem * fio_doctor = new QTableWidgetItem();

                QFont font_text;
                font_text.setPointSize(font_size);
                if(group_value=="0")
                {
                    group_value="Д";
                }
                if(group_value=="1")
                {
                    group_value="Д-1";
                }
                if(group_value=="2")
                {
                    group_value="Д-2";
                }
                if(group_value=="3")
                {
                    group_value="Д-3";
                }
                if(group_value=="4")
                {
                    group_value="Д-4";
                }
                if(group_value=="5")
                {
                    group_value="Д-5";
                }
                if(group_value=="6")
                {
                    group_value="Д-6";
                }
                if(group_value=="7")
                {
                    group_value="Д-7";
                }
                if(group_value=="10")
                {
                    group_value="ЛП";
                }
                if(group_value=="11")
                {
                    group_value="Нет согласия";
                }
                if(group_value=="8")
                {
                    group_value="АДН";
                }
                if(group_value=="9")
                {
                    group_value="АПЛ";
                }
                if(group_value=="12")
                {
                    group_value="K";
                }

                if(status_value)
                {
                    status_text = "Закрыт";
                    status->setBackgroundColor(Qt::green);

                }
                else
                {
                    status_text = "Открыт";
                }

                id->setText(id_value);
                date->setText(date_value);
                group->setText(group_value);
                status->setText(status_text);
                fio_doctor->setText(staff_fio_value);

                date->setFont(font_text);
                group->setFont(font_text);
                status->setFont(font_text);
                fio_doctor->setFont(font_text);

                ui->tableWidget_dynamic_view->insertRow(last_row);
                ui->tableWidget_dynamic_view->setItem(last_row,0,id);
                ui->tableWidget_dynamic_view->setItem(last_row,1,date);
                ui->tableWidget_dynamic_view->setItem(last_row,2,group);
                ui->tableWidget_dynamic_view->setItem(last_row,3,status);
                ui->tableWidget_dynamic_view->setItem(last_row,4,fio_doctor);

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

            query.exec("SELECT diagnos_patient.id, diagnos.name, diagnos.code, diagnos_patient.fixing_diagnos_date, staff.fname, staff.name, staff.mname, staff.code FROM test.diagnos_patient, test.diagnos, test.staff WHERE diagnos_patient.diagnos_id = diagnos.id AND diagnos_patient.staff_add_id = staff.id AND diagnos_patient.medcard_id = "+id);
            int last_row_diagnos = ui->tableWidget_diagnos_patient->rowCount();

            while (query.next()) {
                QString id_value = query.value(0).toString();
                QString diagnos_name_value = query.value(1).toString();
                QString diagnos_code_value = query.value(2).toString();
                QString fixing_diagnos_date_value = query.value(3).toDate().toString("dd.MM.yyyy");
                QString doctor_fio_value;
                doctor_fio_value.append(query.value(4).toString()).append("\n").append(query.value(5).toString()).append("\n").append(query.value(6).toString());
                QString doctor_code_value = query.value(7).toString();
                qDebug()<<fixing_diagnos_date_value<<doctor_fio_value;

                QTableWidgetItem * id = new QTableWidgetItem();
                QTableWidgetItem * diagnos_name = new QTableWidgetItem();
                QTableWidgetItem * diagnos_code = new QTableWidgetItem();
                QTableWidgetItem * fixing_diagnos_date = new QTableWidgetItem();
                QTableWidgetItem * doctor_fio = new QTableWidgetItem();
                QTableWidgetItem * doctor_code = new QTableWidgetItem();

                id->setText(id_value);
                diagnos_name->setText(diagnos_name_value);
                diagnos_code->setText(diagnos_code_value);
                fixing_diagnos_date->setText(fixing_diagnos_date_value);
                doctor_fio->setText(doctor_fio_value);
                doctor_code->setText(doctor_code_value);

                QFont font_text;
                font_text.setPointSize(font_size);

                diagnos_name->setFont(font_text);
                diagnos_code->setFont(font_text);
                fixing_diagnos_date->setFont(font_text);
                doctor_fio->setFont(font_text);
                doctor_code->setFont(font_text);

                ui->tableWidget_diagnos_patient->insertRow(last_row_diagnos);

                ui->tableWidget_diagnos_patient->setItem(last_row_diagnos,0,id);
                ui->tableWidget_diagnos_patient->setItem(last_row_diagnos,1,diagnos_code);
                ui->tableWidget_diagnos_patient->setItem(last_row_diagnos,2,diagnos_name);
                ui->tableWidget_diagnos_patient->setItem(last_row_diagnos,3,fixing_diagnos_date);
                ui->tableWidget_diagnos_patient->setItem(last_row_diagnos,4,doctor_code);
                ui->tableWidget_diagnos_patient->setItem(last_row_diagnos,5,doctor_fio);

                }
            query.exec("SELECT\
                       hospitalization.id,\
                       hospitalization.who_wrote,\
                       hospitalization.date_up,\
                       hospitalization.date_down,\
                       staff.fname,\
                       staff.name,\
                       staff.mname\
                     FROM \
                       test.hospitalization,\
                       test.staff\
                     WHERE\
                       hospitalization.staff_add_id = staff.id AND delete_row = '0' AND medcard_id="+id);
            int last_row_hospitalization = ui->tableWidget_sved_gospital->rowCount();

            while (query.next())
            {
                QString id_value = query.value(0).toString();
                int who_value = query.value(1).toInt();
                QString who_table_value;
                QString date_up_value = query.value(2).toDate().toString("dd.MM.yyyy");
                QString date_down_value = query.value(3).toDate().toString("dd.MM.yyyy");
                QString staff_fio_value;
                staff_fio_value.append(query.value(4).toString()).append("\n").append(query.value(5).toString()).append("\n").append(query.value(6).toString());

                switch (who_value) {
                case 0:
                    who_table_value = "СП";
                    break;
                case 1:
                    who_table_value = "ПНД";
                    break;
                case 2:
                    who_table_value = "Другое";
                    break;
                }
                QTableWidgetItem * id = new QTableWidgetItem();
                QTableWidgetItem * who = new QTableWidgetItem();
                QTableWidgetItem * date_up = new QTableWidgetItem();
                QTableWidgetItem * date_down = new QTableWidgetItem();
                QTableWidgetItem * staff_fio = new QTableWidgetItem();

                id->setText(id_value);
                who->setText(who_table_value);
                date_up->setText(date_up_value);
                date_down->setText(date_down_value);
                staff_fio->setText(staff_fio_value);

                QFont font_text;
                font_text.setPointSize(font_size);

                id->setFont(font_text);
                who->setFont(font_text);
                date_up->setFont(font_text);
                date_down->setFont(font_text);
                staff_fio->setFont(font_text);

                ui->tableWidget_sved_gospital->insertRow(last_row_hospitalization);

                ui->tableWidget_sved_gospital->setItem(last_row_hospitalization,0,id);
                ui->tableWidget_sved_gospital->setItem(last_row_hospitalization,1,who);
                ui->tableWidget_sved_gospital->setItem(last_row_hospitalization,2,date_up);
                ui->tableWidget_sved_gospital->setItem(last_row_hospitalization,3,date_down);
                ui->tableWidget_sved_gospital->setItem(last_row_hospitalization,4,staff_fio);
             }
        }
        else
        {
            QMessageBox::warning(this,"Ошибка","Потеряно соединение с базой данных");
        }

    }

}
void MainWindow::context_menu_dynamic_view(QPoint pos) // Контекстное меню для Таблицы Динамика наблюдения
{

    QMenu *menu = new QMenu;
        menu->addAction("Добавить", this, SLOT(add_dynamic_view()))->setEnabled(rights_user[4]);
        menu->addAction("Закрыть", this, SLOT(del_dynamic_view()))->setEnabled(rights_user[6]);
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
void MainWindow::context_menu_main_table(QPoint pos) //Контекстное меню главной таблицы
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
void MainWindow::context_menu_diagnos_table(QPoint pos)
{
    QMenu *menu = new QMenu;
    menu->addAction("Добавить", this, SLOT(add_diagnos_patient()));
    menu->addAction("Изменить", this, SLOT(edit_diagnos_patient())); // это можно использовать для прав->setEnabled(false);
    menu->addAction("Удалить", this, SLOT(del_diagnos_patient()));
    menu->exec(ui->tableWidget_diagnos_patient->mapToGlobal(pos));
}
void MainWindow::context_menu_hospitalization_table(QPoint pos)
{
    QMenu *menu = new QMenu;
    menu->addAction("Добавить", this, SLOT(add_hospitalization()));
    menu->addAction("Изменить", this, SLOT(edit_hospitalization())); // это можно использовать для прав->setEnabled(false);
    menu->addAction("Удалить", this, SLOT(del_hospitalization()));
    menu->exec(ui->tableWidget_sved_gospital->mapToGlobal(pos));
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
        int ret = QMessageBox::warning(this, tr("Закрытие динамики наблюдения"),
                                       tr("Вы точно хотите закрыть?"),
                                       QMessageBox::Yes|QMessageBox::No);

        if(ret==16384)
        {
            bool bOk;
            QString str = QInputDialog::getText( 0, "Причина закрытия", "Причина закрытия:", QLineEdit::Normal, "", &bOk );
            if(str=="")
            {
                QMessageBox::warning(this, tr("Пустая строка"),tr("Пустая строка"),QMessageBox::Ok);
                del_dynamic_view();
            }
            else
            {
                if (!bOk)
                {
                    // Была нажата кнопка Cancel
                }
                else
                {
                    query.exec("UPDATE test.dynamic_view  SET status='1', cause='"+str+"', staff_add_id = '"+staff_id+"'  WHERE id= "+id);
                    load_all_info();
                }
            }
        }
        else
        {
            return ;
        }


    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Нельзя закрыть того чего нет)");
    }

}
void MainWindow::edit_dynamic_view()
{
    Dialog_add_dynamic_view dialog;
    int selected_tables = ui->tableWidget->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget->currentRow();
        QString id = ui->tableWidget->item(cu_row,0)->text();
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
void MainWindow::add_diagnos_patient()
{
    Dialog_diagnos_patient dialog;
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
        QMessageBox::warning(this,"Ошибка","Чтобы добавить диагноз нужно сначала выбрать пациента");
    }
}
void MainWindow::edit_diagnos_patient()
{
    Dialog_diagnos_patient dialog;
    int selected_tables = ui->tableWidget_diagnos_patient->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_diagnos_patient->currentRow();
        QString id = ui->tableWidget_diagnos_patient->item(cu_row,0)->text();
        dialog.setParam(1,id,staff_id);
        if(dialog.exec())
        {
            load_all_info();
        }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Чтобы изменить диагноз нужно сначала выбрать диагноз для изменения");
    }
}
void MainWindow::del_diagnos_patient()
{

}
void MainWindow::add_hospitalization()
{
    Dialog_hospitalization dialog;
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
void MainWindow::edit_hospitalization()
{
    Dialog_hospitalization dialog;
    int selected_tables = ui->tableWidget_sved_gospital->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_sved_gospital->currentRow();
        QString id = ui->tableWidget_sved_gospital->item(cu_row,0)->text();
        dialog.setParam(1,id,staff_id);
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
void MainWindow::del_hospitalization()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_sved_gospital->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_sved_gospital->currentRow();
        QString id = ui->tableWidget_sved_gospital->item(cu_row,0)->text();
        int ret = QMessageBox::warning(this, tr("Удаление госпитализации!"),
                                       tr("Вы точно хотите удалить?"),
                                       QMessageBox::Yes|QMessageBox::No);

        if(ret==16384)
        {

            query.exec("UPDATE test.hospitalization SET delete_row='true' WHERE id= "+id);
            load_all_info();
        }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Нельзя удалить того чего нет)");
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

void MainWindow::added_files_patient()
{
    Dialog_copy_files_to_server dialog;
    int selected_tables = ui->tableWidget->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget->currentRow();
        QString id = ui->tableWidget->item(cu_row,0)->text();
        dialog.setParam(id,staff_id);
        if(dialog.exec())
        {
            find_patients();
        }
    }

}
