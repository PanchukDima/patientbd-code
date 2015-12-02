#include "dialog_preview_print.h"
#include "ui_dialog_preview_print.h"

Dialog_preview_print::Dialog_preview_print(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_preview_print)
{
    ui->setupUi(this);
    connect(ui->pushButton_Print,SIGNAL(clicked(bool)),SLOT(print()));
    connect(ui->pushButton_word_export,SIGNAL(clicked(bool)),SLOT(export_word()));
}

Dialog_preview_print::~Dialog_preview_print()
{
    delete ui;
}
void Dialog_preview_print::setParam(int param, QString id, QString staff_id)
{
    QSettings *settings = new QSettings("settings_user.ini",QSettings::IniFormat);
    global_id = id;
    global_staff_id=staff_id;
    global_param = param;
    QString path_blanks;
    QString control_char = path_blanks.at(0);
    if(control_char=="/")
    {
    path_blanks.append("file://").append(settings->value("path_blanks").toString()).append("/");
    }
    else
    {
      path_blanks.append("file:///").append(settings->value("path_blanks").toString()).append("/");
    }
    QUrl url_blank;
    switch (param) {
    case 0:
        path_blanks.append("medcard.html");
        qDebug()<<path_blanks;
        url_blank.setUrl(path_blanks);
        break;
    case 1:
        //preview alow
        break;
    }
    ui->webView->setUrl(url_blank);
}
void Dialog_preview_print::print()
{
    QPrinter printer(QPrinter::HighResolution);
        QPrintDialog *dlg = new QPrintDialog(&printer, this);
        dlg->setWindowTitle(tr("Print Document"));
        if (dlg->exec() == QDialog::Accepted) {
            ui->webView->render(&printer);
        }
        delete dlg;
}
void Dialog_preview_print::export_word()
{

}
