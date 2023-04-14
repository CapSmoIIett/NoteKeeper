#ifndef CALENDAR_H
#define CALENDAR_H

#include <QString>


#define JANUARY 	0
#define FEBRUARY	1
#define MARCH		2
#define APRIL		3
#define MAY			4
#define JUNE			5
#define JULY			6
#define AUGUST		7
#define SEPTEMBER	8
#define OCTOBER		9
#define NOVEMBER	10
#define DECEMBER	11

#define MONDAY		0
#define TUESDAY		1
#define WEDNESDAY	2
#define THURSDAY	3
#define FRIDAY		4
#define SATURDAY	5
#define SUNDAY		6

#define TODAY 		10
#define PAST 		11
#define FUTURE 		12

#include <QString>
#include <QVector>
#include <QDateTime>

struct Date
{
    int day;
    int month;
    int year;
};

class CalendarCtrl
{
public:
    CalendarCtrl ();

    static int GetDayNumber (int day, int month, int  year);
    static int GetNumbersOfDays (int monthNumber, int year);
    static QString GetMonthName (int monthNumber);
    static QString GetDayOfWeekName (Date date);
    static QString GetDayOfWeekName (int numberOfDayOfWeek);

    // Work - is functions about month we show
    int GetWorkYear  ();
    int GetWorkMonth ();
    void SetWorkMonth (int month);

    QVector<int> GetWorkMonthDays ();
    QVector<Date> GetWorkMonthDates ();
    QVector<QString> GetWorkMonthDaysStatus ();

    // Current - is functions about current month, day, year in real life
    int GetCurDay ();
    int GetCurMonth ();
    int GetCurYear ();

    bool isMonthNeedAdditionalRow ();

    void GoNextMonth();
    void GoPrevMonth();

    int GetDateInt (int day, int month, int year);
    int GetDateInt (Date);
    int GetCurDateInt();

    const static inline QVector<QString> v_Months =
    {
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };

    const static inline QVector<QString> v_daysOfWeek = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };

private:

    int i_WorkMonth;
    int i_WorkYear;


};

#endif // CALENDAR_H
