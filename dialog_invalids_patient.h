#ifndef DIALOG_INVALIDS_PATIENT_H
#define DIALOG_INVALIDS_PATIENT_H

#include <QDialog>

namespace Ui {
class Dialog_invalids_patient;
}

class Dialog_invalids_patient : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_invalids_patient(QWidget *parent = 0);
    ~Dialog_invalids_patient();

private:
    Ui::Dialog_invalids_patient *ui;
public slots:
    void setParam(int, QString, QString);
    void get_data();
    void send_data();
    void setting();
};

#endif // DIALOG_INVALIDS_PATIENT_H
