#include "database.h"

Database::Database()
{
    //
    // QSQLITE
    db = QSqlDatabase::addDatabase("QPSQL");


    db.setDatabaseName("./NoteKeeper");
    db.setUserName("postgres");
    db.setPassword("passw0rd");
    //db.setHostName("127.0.0.1");
    //db.setPort(5434);

    if (db.isOpen())
        qDebug("DB open");
    else
    {
        qDebug("DB not open");
    }
}

Database::~Database()
{
    db.close();
}


void Database::CreateTables()
{
    QSqlQuery query(db);

    query.exec("CREATE TABLE IF NOT EXISTS notes"
               "("
               "	date DATE NOT NULL,"
               "	text TAXT NOT NULL"
               ")"
               );

}

void Database::InsertNote(Date date, QString str)
{
    QSqlQuery query(db);

    query.prepare("INSERT INTO notes (TO_DATE(date, 'DD/MM/YYYY'), text) "
          "VALUES (:date, :text)");

    query.bindValue(":date", QString("%1%2").arg(date.day / 10).arg(date.day % 10) + "/"
            + CalendarCtrl::GetMonthName(date.month) + "/"
            + QString::number(date.year));
    query.bindValue(":text", str);

    query.exec();

}

QString Database::GetNote(Date date)
{
    QSqlQuery query(db);
    QString text;

    query.exec("CREATE TABLE IF NOT EXISTS note"
               "("
               "	date DATE NOT NULL,"
               "	text TAXT NOT NULL"
               ")"
               );

    return text;
}

QVector<QString> Database::GetNotes(Date date)
{
    QVector<QString> result;

    return result;
}
