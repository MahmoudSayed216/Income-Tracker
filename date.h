#pragma once
using namespace std;
#include "extraFuncs.h"

int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool dateIsValid(int day, int month, int year)
{
    return(
        !(month < 1 || month > 12) && //Checks if month entered is between 1 - 12
        !(day < 1 || day > (months[month - 1] + (month==2 && !(year%4)))) && //Checks if day exists in that month (Accounts for leap years)
        !(year < 1950 || year > 2080) //Checks if the year is between 1950 and 2080
    );
}

struct Date
{
    int day;
    int month;
    int year;

    Date(int d=0, int m=0, int y=0)
    {
        day = d;
        month = m;
        year = y;
    }

    string toString(){
        return to_string(day) + " " + to_string(month) + " " + to_string(year);
    }

    void next(){
        if(day < months[month-1] || (day == 28 && month == 2)) { day++; return; }
        day = 1; if (month < 12) { month ++; return; }
        month = 1; year++;
    }

    // bool isBefore(Date date){
    //     return(
    //         year < date.year ||
    //         (year == date.year && month < date.month) ||
    //         (year == date.year && month == date.month && day < date.day)
    //     );
    // }
    // bool isbetween(Date start, Date end){
    //     return !(isBefore(start) || end.isBefore(*this));
    // }

    // bool equals(Date date){
    //      return(
    //         day == date.day && month == date.month && year == date.year
    //     );
    // }
    // bool equals(int d, int m, int y){
    //     return(
    //         day == d && month == m && year == y
    //     );
    // }

    int days_from(Date date){
        int c_day = date.day;
        int c_month = date.month;
        int c_year = date.year;
        
        int year_dif = year - date.year;
        int month_dif = month - date.month;
        int day_dif = day - date.day;

        int res = 0;
       
        res += day_dif; c_day += day_dif; day_dif = 0;
        while(month_dif < 0){
            res += -(c_month==2 && c_year%4 == 0) - months[--c_month - 1]; month_dif++;
        }
        while(month_dif > 0){
            res += (c_month==2 && c_year%4 == 0) + months[c_month++ - 1]; month_dif--;
        }

        // cout << "current res: " << res << endl;
        
        while(year_dif > 0){
            // cout << "year dif: " << year_dif << endl;
            res += 365 + (++c_year % 4 == 0); year_dif--;
            // cout << "current res: " << res << endl;
        }
        return res + 1;
    }
    int day_ones_from(Date date){
        return month - date.month + (date.day == 1) + (year - date.year) * 12;
    }

    void get_date(){
        m:
        int d, m, y;
        cin >> d >> m >> y;
        if(!dateIsValid(d,m,y)){
            cout << "Please enter a valid date: "; goto m;
        }
        day = d; month = m; year = y;
    }
};

