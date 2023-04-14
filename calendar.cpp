#include "calendar.h"
#include <map>

CalendarCtrl::CalendarCtrl() :
    i_WorkMonth(GetCurMonth()), // JANUARY
    i_WorkYear(GetCurYear()) // 2000
{

}


int CalendarCtrl::GetDayNumber (int day, int month, int  year)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    year -= month < 3;

    int dayNumber = ( year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;

    // we start from mondey
    if (dayNumber == 0)
        return SUNDAY;

    return dayNumber - 1;
}

int CalendarCtrl::GetNumbersOfDays (int monthNumber, int year)
{
    if (monthNumber == JANUARY)
        return (31);

    if (monthNumber == FEBRUARY)
    {
        // If the year is leap then February has
        // 29 days
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
            return (29);
        else
            return (28);
    }

    if (monthNumber == MARCH)
        return (31);

    if (monthNumber == APRIL)
        return (30);

    if (monthNumber == MAY)
        return (31);

    if (monthNumber == JUNE)
        return (30);

    if (monthNumber == JULY)
        return (31);

    if (monthNumber == AUGUST)
        return (31);

    if (monthNumber == SEPTEMBER)
        return (30);

    if (monthNumber == OCTOBER)
        return (31);

    if (monthNumber == NOVEMBER)
        return (30);

    if (monthNumber == DECEMBER)
        return (31);

    return 0;
}

QString CalendarCtrl::GetMonthName (int monthNumber)
{
    return v_Months[monthNumber];
}

QString CalendarCtrl::GetDayOfWeekName (Date date)
{
   return v_daysOfWeek[GetDayNumber(date.day, date.month + 1, date.year)];
}

QString CalendarCtrl::GetDayOfWeekName (int numberOfDayOfWeek)
{
    return v_daysOfWeek[numberOfDayOfWeek];
}

int CalendarCtrl::GetWorkYear  ()
{
    return i_WorkYear;
}

int CalendarCtrl::GetWorkMonth ()
{
    return i_WorkMonth;
}

void CalendarCtrl::SetWorkMonth (int month)
{
    i_WorkMonth = month;
}


// return array for calendar
// each date in the right cell
QVector<int> CalendarCtrl::GetWorkMonthDays ()
{
    QVector<int> month(42, 0);

    int placeOfFirstDay = GetDayNumber (1, i_WorkMonth + 1, i_WorkYear);

    int workMonthNumberOfDays = GetNumbersOfDays(i_WorkMonth, i_WorkYear);

    for (int numberOfDay = 1; numberOfDay <= workMonthNumberOfDays; numberOfDay++)
        month[numberOfDay + placeOfFirstDay - 1] = numberOfDay;


    int prevMonthNumberOfDays = GetNumbersOfDays(
        i_WorkMonth == JANUARY ? DECEMBER : i_WorkMonth - 1,
        i_WorkMonth == JANUARY ? i_WorkYear - 1 : i_WorkYear);

    for (int i = placeOfFirstDay - 1; i >= 0; i--)
       month[i] = prevMonthNumberOfDays--;


    for (int i = 1; (i + placeOfFirstDay + workMonthNumberOfDays - 1) % 7 != 0; i++)
        month[i + placeOfFirstDay + workMonthNumberOfDays - 1] = i;


    return month;
}

QVector<Date> CalendarCtrl::GetWorkMonthDates ()
{
    QVector<Date> date(42, {0, 0, 0});

    int placeOfFirstDay = GetDayNumber (1, i_WorkMonth + 1, i_WorkYear);

    int workMonthNumberOfDays = GetNumbersOfDays(i_WorkMonth, i_WorkYear);

    for (int numberOfDay = 1; numberOfDay <= workMonthNumberOfDays; numberOfDay++)
        date[numberOfDay + placeOfFirstDay - 1] = {numberOfDay, i_WorkMonth, i_WorkYear};


    int prevMonth = 0;
    int prevYear = 0;
    if (i_WorkMonth == JANUARY)
    {
        prevMonth = DECEMBER;
        prevYear = i_WorkYear - 1;
    }
    else
    {
        prevMonth = i_WorkMonth - 1;
        prevYear = i_WorkYear;
    }

    int prevMonthNumberOfDays = GetNumbersOfDays(prevMonth, prevYear);

    for (int i = placeOfFirstDay - 1; i >= 0; i--)
       date[i] = {prevMonthNumberOfDays--, prevMonth, prevYear};


    int nextMonth = 0;
    int nextYear = 0;
    if (i_WorkMonth == DECEMBER)
    {
        nextMonth = JANUARY;
        nextYear = i_WorkYear + 1;
    }
    else
    {
        nextMonth = i_WorkMonth + 1;
        nextYear = i_WorkYear;
    }

    for (int i = 1; (i + placeOfFirstDay + workMonthNumberOfDays - 1) % 7 != 0; i++)
        date[i + placeOfFirstDay + workMonthNumberOfDays - 1] = {i, nextMonth, nextYear};


    return date;
}

int CalendarCtrl::GetCurDay ()
{
    auto str = QDateTime::currentDateTime().toString("dd");
    return str.toInt();
}

int CalendarCtrl::GetCurMonth ()
{
    auto str = QDateTime::currentDateTime().toString("MM");
    return str.toInt() - 1;
}

int CalendarCtrl::GetCurYear ()
{
    auto str = QDateTime::currentDateTime().toString("yyyy");
    return str.toInt();
}

bool CalendarCtrl::isMonthNeedAdditionalRow ()
{
    return false;
}

void CalendarCtrl::GoNextMonth()
{
    if (i_WorkMonth == DECEMBER) i_WorkYear++;
    i_WorkMonth = i_WorkMonth == DECEMBER ? JANUARY : i_WorkMonth + 1;
}

void CalendarCtrl::GoPrevMonth()
{
    if (i_WorkMonth == JANUARY) i_WorkYear--;
    i_WorkMonth = i_WorkMonth == JANUARY ? DECEMBER : i_WorkMonth - 1;
}

int CalendarCtrl::GetDateInt (int day, int month, int year)
{
    return day + month * 31 + year * 366;
}

int CalendarCtrl::GetDateInt (Date date)
{
    return GetDateInt(date.day, date.month, date.year);
}

int CalendarCtrl::GetCurDateInt()
{
    return GetDateInt(GetCurDay(), GetCurMonth(), GetCurYear());

}


