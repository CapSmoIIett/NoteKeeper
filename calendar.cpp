#include "calendar.h"
#include <map>

CalendarCtrl::CalendarCtrl() :
    i_WorkMonth(JANUARY),
    i_WorkYear(2000)
{

}


int CalendarCtrl::GetDayNumber (int day, int month, int  year)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    year -= month < 3;

    int dayNumber = ( year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;

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
}

QString CalendarCtrl::GetMonthName (int monthNumber)
{
    return months[monthNumber];
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

void CalendarCtrl::GetCurDate ()
{

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


