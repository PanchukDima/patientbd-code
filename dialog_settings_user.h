#ifndef DIALOG_SETTINGS_USER_H
#define DIALOG_SETTINGS_USER_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class Dialog_settings_user;
}

class Dialog_settings_user : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_settings_user(QWidget *parent = 0);
    ~Dialog_settings_user();

private:
    Ui::Dialog_settings_user *ui;
public slots:
    void apply_settings();
    void load_settings();
    void default_settings();
    void push_ok();
};

#endif // DIALOG_SETTINGS_USER_H
