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
            + QString("%1%2").arg((date.month + 1) / 10).arg((date.month + 1) % 10) + "/"
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
    int result = 0;

    query.prepare("SELECT text FROM notes WHERE data = TO_DATE(:date, 'DD/MM/YYYY')");

    query.bindValue(":date", QString("%1%2").arg(date.day / 10).arg(date.day % 10) + "/"
            + QString("%1%2").arg((date.month + 1) / 10).arg((date.month + 1) % 10) + "/"
            + QString::number(date.year));

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return "";
    }

    if (!query.next())
    {
        text = query.value(0).toString();
    }

    return text;
}

QVector<QString> Database::GetNotes(QVector<Date> dates)
{
    int days = dates.last().day == 0 ? 35 : 42;

    QVector<QString> notes(days, "");
    QSqlQuery query(db);
    int result = 0;

    Date firstDate = dates.first();
    Date secondDate = dates[days - 1];

    query.prepare("SELECT * FROM notes WHERE date BETWEEN "
                  "TO_DATE(:firstDate, 'DD/MM/YYYY') AND "
                  "TO_DATE(:secondDate, 'DD/MM/YYYY')");

    query.bindValue(":firstDate", QString("%1%2").arg(firstDate.day / 10).arg(firstDate.day % 10) + "/"
            + QString("%1%2").arg((firstDate.month + 1) / 10).arg((firstDate.month + 1) % 10) + "/"
            + QString::number(firstDate.year));

    query.bindValue(":secondDate", QString("%1%2").arg(secondDate.day / 10).arg(secondDate.day % 10) + "/"
            + QString("%1%2").arg((secondDate.month + 1) / 10).arg((secondDate.month + 1) % 10) + "/"
            + QString::number(secondDate.year));

    result = query.exec();

    if (!result)
    {
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
        return notes;
    }

    QSqlRecord rec = query.record();
    const int indexDate = rec.indexOf( "date" );
    const int indexText = rec.indexOf( "text" );

    int i = 0;
    while (query.next())
    {
        for (; i < days; i++)
        {
            if (query.value(indexDate).toDate().day() == dates[i].day &&
                query.value(indexDate).toDate().month() == (dates[i].month + 1) &&
                query.value(indexDate).toDate().year() == dates[i].year)
            {
                notes[i] = query.value(indexText).toString();
                break;
            }
        }
    }

    return notes;
}
