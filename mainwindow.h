#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QtSql>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QContextMenuEvent>
//
#include "dialog_patient.h"
#include "dialog_settings_user.h"
#include "dialog_login.h"
#include "dialog_registratura.h"
#include "dialog_reports.h"
#include "dialog_add_dynamic_view.h"
#include "dialog_add_visits.h"
#include "dialog_preview_print.h"
//

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString ipdatabase;
    QList <bool> rights_user;
    int font_size;
    int port;
    QLineEdit * str_find_patient;
    QLabel * valid_info;
    QString staff_id;
    int first_start;
    QTimer *timer;

private:
    Ui::MainWindow *ui;
public slots:
    void settings_ui();
    void settings_user();
    void added_info_patient();
    void edit_info_patient();
    void del_info_patient();
    void open_win_settings();
    void load_main_table();
    void clear_main_table();
    void clear_dynamic_view_table();
    void clear_visiting_control_table();
    void find_patients();
    void load_all_info();
    void context_menu_dynamic_view(QPoint);
    void context_menu_visits_control(QPoint);
    void context_menu_main_table(QPoint);
    void add_dynamic_view();
    void del_dynamic_view();
    void edit_dynamic_view();
    void add_visit();
    void add_today_visit();
    void edit_visit();
    void del_visit();
    void gen_report_1();
    void print_medcard();
    void set_status_arhive();

};

#endif // MAINWINDOW_H
