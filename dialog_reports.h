#ifndef DIALOG_REPORTS_H
#define DIALOG_REPORTS_H

#include <QDialog>

namespace Ui {
class Dialog_reports;
}

class Dialog_reports : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_reports(QWidget *parent = 0);
    ~Dialog_reports();
    int global_num;

private:
    Ui::Dialog_reports *ui;
public slots:
    void gen_report(int);
    void open_excel();
    void print_doc();
};

#endif // DIALOG_REPORTS_H
