#ifndef DIALOG_DIAGNOS_PATIENT_H
#define DIALOG_DIAGNOS_PATIENT_H

#include <QDialog>

namespace Ui {
class Dialog_diagnos_patient;
}

class Dialog_diagnos_patient : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_diagnos_patient(QWidget *parent = 0);
    ~Dialog_diagnos_patient();

private:
    Ui::Dialog_diagnos_patient *ui;
};

#endif // DIALOG_DIAGNOS_PATIENT_H
