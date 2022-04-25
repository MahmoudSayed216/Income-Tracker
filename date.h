#ifndef DATE
#define DATE

int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


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
};

bool checkDate(int day, int month, int year)
{
    return(
        !(month < 1 || month > 12) && //Checks if month entered is between 1 - 12
        !(day < 1 || day > (months[month - 1] + (month==2 && !(year%4)))) && //Checks if day exists in that month (Accounts for leap years)
        !(year < 1950 || year > 2080) //Checks if the year is between 1950 and 2080
    );
}

#endif