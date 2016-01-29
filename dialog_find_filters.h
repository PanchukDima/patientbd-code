#ifndef DIALOG_FIND_FILTERS_H
#define DIALOG_FIND_FILTERS_H

#include <QDialog>

namespace Ui {
class Dialog_find_filters;
}

class Dialog_find_filters : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_find_filters(QWidget *parent = 0);
    ~Dialog_find_filters();

private:
    Ui::Dialog_find_filters *ui;

public slots:
    void send_result(QString);

};

#endif // DIALOG_FIND_FILTERS_H
