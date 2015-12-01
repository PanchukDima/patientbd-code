#include "new_changes_thread.h"


new_changes_thread::new_changes_thread(QObject *parent) : QObject(parent)
{


}

new_changes_thread::~new_changes_thread()
{

}
void new_changes_thread::check_new_changes_blanks()
{
    while (true) {
        emit status(0);
        Sleep(5000); //Unix not Work
    }
}
