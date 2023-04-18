#include "database.h"

Database::Database()
{
    //
    // QSQLITE
    db = QSqlDatabase::addDatabase("QPSQL");


    db.setDatabaseName("NoteKeeper");
    db.setUserName("postgres");
    db.setPassword("1111");
    db.setHostName("localhost");
    //db.setPort(5434);

    db.open();

    if (db.isOpen())
    {
        qDebug("DB open");
    }
    else
    {
        qDebug("DB not open");
    }

    CreateTables();
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
               "	text TEXT NOT NULL"
               ")"
               );

}

void Database::InsertNote(Date date, QString str)
{
    QSqlQuery query(db);

    query.prepare("INSERT INTO notes (date, text) "
          "VALUES (TO_DATE(:date, 'DD/MM/YYYY'), :text)");


    QString s = QString("%1%2").arg(date.day / 10).arg(date.day % 10) + "/"
            + QString("%1%2").arg(date.month / 10).arg(date.month % 10) + "/"
                + QString::number(date.year);

    query.bindValue(":date", QString("%1%2").arg(date.day / 10).arg(date.day % 10) + "/"
            + QString("%1%2").arg(date.month / 10).arg(date.month % 10) + "/"
            + QString::number(date.year));
    query.bindValue(":text", str);

    query.exec();


    qDebug() << query.lastQuery() << "\n";
    qDebug() << db.lastError().text() << "\n";

}

QString Database::GetNote(Date date)
{
    QSqlQuery query(db);
    QString text;

    query.exec("CREATE TABLE IF NOT EXISTS note"
               "("
               "	date DATE NOT NULL,"
               "	text TEXT NOT NULL"
               ")"
               );

    return text;
}

QVector<QString> Database::GetNotes(Date firstDate, Date secondDate)
{
    QVector<QString> result;

    return result;
}
