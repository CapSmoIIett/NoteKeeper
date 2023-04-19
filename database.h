#ifndef DATABASE_H
#define DATABASE_H


#include <QSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "calendar.h"


class Database
{
public:
    Database();
    ~Database();

    void CreateTables();

    void InsertNote(Date date, QString str);

    QString GetNote(Date date);
    QVector<QString> GetNotes(QVector<Date> dates);


private:
    QSqlDatabase db;

};

#endif // DATABASE_H
