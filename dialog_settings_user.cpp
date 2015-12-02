#include "dialog_settings_user.h"
#include "ui_dialog_settings_user.h"

Dialog_settings_user::Dialog_settings_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_settings_user)
{
    ui->setupUi(this);
    load_settings();
    connect(ui->pushButton_apply,SIGNAL(clicked()),SLOT(apply_settings()));
    connect(ui->pushButton_default_settings_font,SIGNAL(clicked()),SLOT(default_settings()));
    connect(ui->pushButton_cancel,SIGNAL(clicked()),SLOT(close()));
    connect(ui->pushButton_ok,SIGNAL(clicked()),SLOT(push_ok()));
    connect(ui->pushButton_set_path_blanks,SIGNAL(clicked(bool)),SLOT(set_updServ_path_blanks_func()));
    connect(ui->pushButton_set_path_local_blanks,SIGNAL(clicked(bool)),SLOT(set_path_blanks_func()));
}

Dialog_settings_user::~Dialog_settings_user()
{
    delete ui;
}
void Dialog_settings_user::load_settings()
{
    QSettings *settings = new QSettings("settings_user.ini",QSettings::IniFormat);
    QString ip_addr = settings->value("ipdatabase").toString();
    QString port = settings->value("portdatabase").toString();
    QString sizefonttable = settings->value("sizefonttexttable").toString();
    QString version = settings->value("CurrentVersion").toString();
    QString path_UpdServ_blanks = settings->value("path_UpdServ_blanks").toString();
    QString path_blanks = settings->value("path_blanks").toString();
    ui->lineEdit_ip_addr->setText(ip_addr);
    ui->lineEdit_port->setText(port);
    ui->lineEdit_size_font_text_setting->setText(sizefonttable);
    ui->label_CurrentVersion->setText(version);
    ui->lineEdit_path_blanks->setText(path_UpdServ_blanks);
    ui->lineEdit_path_local_blanks->setText(path_blanks);

}

void Dialog_settings_user::apply_settings()
{
    QSettings *settings = new QSettings("settings_user.ini",QSettings::IniFormat);
    settings->setValue("ipdatabase", ui->lineEdit_ip_addr->text());
    settings->setValue("portdatabase", ui->lineEdit_port->text());
    settings->setValue("sizefonttexttable", ui->lineEdit_size_font_text_setting->text());
    settings->setValue("path_UpdServ_blanks" ,ui->lineEdit_path_blanks->text());
    settings->setValue("path_blanks" ,ui->lineEdit_path_local_blanks->text());
}
void Dialog_settings_user::default_settings()
{
    ui->lineEdit_size_font_text_setting->setText("8");
}
void Dialog_settings_user::push_ok()
{
    apply_settings();
    Dialog_settings_user::accept();
}
void Dialog_settings_user::set_path_blanks_func()
{
    QString file_name=ui->lineEdit_path_local_blanks->text();
    file_name = QFileDialog::getExistingDirectory(this, tr("Путь к бланкам"), file_name, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_path_local_blanks->setText(file_name);
}
void Dialog_settings_user::set_updServ_path_blanks_func()
{
    QString file_name=ui->lineEdit_path_blanks->text();
    file_name = QFileDialog::getExistingDirectory(this, tr("Путь к сетевым бланкам"), file_name, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_path_blanks->setText(file_name);
}
