#include "new_changes_thread.h"


new_changes_thread::new_changes_thread(QObject *parent) : QObject(parent)
{


}

new_changes_thread::~new_changes_thread()
{

}
void new_changes_thread::check_new_changes_blanks()
{
    while(true)
    {
        Sleep(5000);
        get_session_id();
    }
}
void new_changes_thread::get_session_id()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    if(db.open())
    {
        query.exec("SELECT  text_task, status, session_id FROM test.tasks WHERE session_id="+global_session_id);
        while(query.next())
        {
            switch (query.value(1).toInt()) {
            case 1:
                exit(0);
                break;
            default:
                break;
            }
        }
    }
}

