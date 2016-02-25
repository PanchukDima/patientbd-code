#include "add_invalid_class.h"

add_invalid_class::add_invalid_class(QObject *parent) : QObject(parent)
{
    send_data();
}

void add_invalid_class::send_data(QString global_id,QString global_staff_id, QString group_invalid_value,QString from_other_value,QString work_yes_value, bool bs)
{
    QSqlDatabase db=QSqlDatabase::database();
    QSqlQuery query;

    if(db.open())
    {
        if(bs)
        {
            query.exec("INSERT INTO test.invalid_patient(medcard_id, staff_add_id, group_inv, priznan_trudosp, from_other, date_peresmotra, srok_ocherednogo_pereosvidet, bs, delete_row) VALUES ('"+global_id+"', '"+global_staff_id+"', '"+group_invalid_value+"', '"+work_yes_value+"', '"+from_other_value+"', '"+date_review_value+"', NULL, true, false);");
        }
        else
        {
            query.exec("INSERT INTO test.invalid_patient(medcard_id, staff_add_id, group_inv, priznan_trudosp, from_other, date_peresmotra, srok_ocherednogo_pereosvidet, bs, delete_row) VALUES ('"+global_id+"', '"+global_staff_id+"', '"+group_invalid_value+"', '"+work_yes_value+"', '"+from_other_value+"', '"+date_review_value+"', '"+date_pereosved_value+"', false, false);");
        }
        emit send_ok();
    }
    else
    {
        emit error(1);
    }
}

