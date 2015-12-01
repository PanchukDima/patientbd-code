#include "dialog_login.h"
#include "ui_dialog_login.h"

Dialog_login::Dialog_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_login)
{
    ui->setupUi(this);
    QSettings *settings = new QSettings("settings_user.ini",QSettings::IniFormat);
    QString ipdatabase = settings->value("ipdatabase").toString();
    int portdatabase = settings->value("portdatabase").toInt();
    QString databasename = settings->value("databasename").toString();
    QString username = settings->value("username").toString();
    QString password = settings->value("password").toString();
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setUserName(username);
    db.setPassword(password);
    db.setHostName(ipdatabase);
    db.setDatabaseName(databasename);
    db.setPort(portdatabase);
    if(!db.open())
    {
        ui->label_3->setText(tr("Не могу подключиться к серверу"));
    }


    connect(ui->pushButton_ok,SIGNAL(clicked()),SLOT(login_db()));
    connect(ui->pushButton_cancel,SIGNAL(clicked()),SLOT(quit_app()));
    connect(ui->lineEdit_login,SIGNAL(selectionChanged()),SLOT(clear_label_status()));
    connect(ui->lineEdit_password,SIGNAL(selectionChanged()),SLOT(clear_label_status()));
//
}

Dialog_login::~Dialog_login()
{
    delete ui;
}
void Dialog_login::login_db()
{
    QSqlDatabase db = QSqlDatabase::database();
    if(db.open())
    {

        QCryptographicHash hash(QCryptographicHash::Md5);
        QByteArray array(ui->lineEdit_password->text().toStdString().c_str());
        hash.addData(array);
        QString md5_password = hash.result().toHex().data();
        QSqlQuery query;
        query.exec("SELECT users.staff_id FROM test.users WHERE users.user_login = '"+ui->lineEdit_login->text()+"' AND users.password_login_md5 = '"+md5_password+"';");
        qDebug()<<query.result();
        if(query.size()<1)
        {
            ui->label_3->setText(tr("Не правильный логин или пароль!"));
        }
        else
        {
        while (query.next())
        {

            QString result_sql = query.value(0).toString();
                staff_id=result_sql;
                Dialog_login::accept();

        }
    }
    }

}
void Dialog_login::quit_app()
{
    exit(0);
}
void Dialog_login::clear_label_status()
{
    ui->label_3->setText("");
}
