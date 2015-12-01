#include "dialog_reports.h"
#include "ui_dialog_reports.h"


#include <QAxObject>
#include <QAxWidget>

Dialog_reports::Dialog_reports(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_reports)
{
    ui->setupUi(this);
    connect(ui->pushButton_excel,SIGNAL(clicked()),SLOT(open_excel()));
    connect(ui->pushButton_print,SIGNAL(clicked()),SLOT(print_doc()));

}

Dialog_reports::~Dialog_reports()
{
    delete ui;
}
void Dialog_reports::gen_report(int num)
{
    global_num = num;
    switch (num) {
    case 1:
        QString report1;
        report1.append("<table border=1>"
                       "<tr>"
                       "<td>№ Строки</td><td>Код по МКБ X</td><td>1</td><td>2</td><td>3</td><td>4</td><td>5</td><td>6</td><td>7</td><td>8</td><td>9</td><td>10</td><td>11</td><td>12</td><td>13</td><td>14</td><td>15</td><td>16</td><td>17</td><td>18</td><td>19</td><td>20</td><td>21</td><td>22</td><td>23</td><td>22-п.т</td>"
                       "</tr>"
                       "<tr>"
                       "<td>1</td><td>F00-F09,F20-F99</td>"
                       "</tr>"
                       "<tr>"
                       "<td>2</td><td>F00-F05, F06(часть),<br> F09,F20-F25,F28,<br> F29,F84 0-4, F30-F39 <br> (часть)</td>"
                       "</tr>"
                       "<tr>"
                       "<td>3</td><td>F20, F21, F25, F3x x4</td>"
                       "</tr>"
                       "<tr>"
                       "<td>4</td><td>F06(часть),F07, <br> F30-39(часть),<br> F40-F69, F80-F83, <br> F84.5, F90-F98</td>"
                       "</tr>"
                       "<tr>"
                       "<td>5</td><td>F70-F79</td>"
                       "</tr>"
                       "<tr>"
                       "<td>6</td><td>A52.1,A81.0,B22.0,G10-G40 и др.</td>"
                       "</tr>");
        ui->textBrowser->append(report1);
        break;
    }
}
void Dialog_reports::open_excel()
{
    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject * workbooks = excel.querySubObject("WorkBooks");
    switch (global_num) {
    case 1:
        workbooks->dynamicCall("Open (const QString&)", QString("C:/tmp/test3.xlsx"));
        QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
        QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
        QAxObject * range = worksheet->querySubObject("Cells(1,1)");
        range->setProperty("Value", QVariant("Helloo Excel"));
        break;

    }


}
void Dialog_reports::print_doc()
{

}
