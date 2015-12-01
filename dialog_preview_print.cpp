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
    global_id = id;
    global_staff_id=staff_id;
    global_param = param;
    QUrl url_blank;
    switch (param) {
    case 0:
        url_blank.setUrl("file:///blanks/medcard.html");
        break;
    case 1:
        //preview alow
        break;
    }

    ui->webView->setHtml("hello, Medcard! html");
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
