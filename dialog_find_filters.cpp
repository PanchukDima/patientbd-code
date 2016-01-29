#include "dialog_find_filters.h"
#include "ui_dialog_find_filters.h"

Dialog_find_filters::Dialog_find_filters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_find_filters)
{
    ui->setupUi(this);
}

Dialog_find_filters::~Dialog_find_filters()
{
    delete ui;
}

void Dialog_find_filters::send_result(QString sql)
{

}
