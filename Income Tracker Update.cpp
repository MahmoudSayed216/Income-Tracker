#include <iostream>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<iomanip> // will use it later to organize the date format


using namespace std;
struct Date;
struct Expense;


void save(int index);

bool strcomp(string s1, string s2);
//void prepTracker();
void mainMenu();
void manageExpenses();
void listExpenses();
void promptAddExpense();
void addExpense(string name, float price, Date date);
bool checkDate(int day, int month, int year);
void promptRemoveExpense();
int locateExpense(string name);
void removeExpense(int index);

void promptEditExpense();
void editExpense(int index, int option);
void editName(int index);
void editPrice(int index);
void editDate(int index);
bool checkIfExists(string itemName);
void manageRC(); //Manage repeated costs
void listRecurringCosts();
void promptAddRC();
void addRC(string name, float price, Date date);
void promptRemoveRC();
void promptEditRC();
void editRC();
void manageIS();
// part 2
void manageIncome();
void listIncome();
void promptAddIncome();
void addIncome(string name, float size, float rate);
void editIncomeName(int index);
void editIncomeSize(int index);
void editIncomeRate(int index);
void promptRemoveIncome();
void removeIncome(int index);
void promptEditIncome();
void editincome(int index, int option);
bool strcompIncome(string s1, string s2);

bool checkIfIncomeExists(string itemName);
int locateIncome(string name);


float Wallet = 0;
struct Date
{
    int day;
    int month;
    int year;

    Date(int d = 0, int m = 0, int y = 0)
    {
        day = d;
        month = m;
        year = y;
    }
};
struct Expense {
    string name;
    float price;
    Date date;

    Expense() {
        name = "";
        price = 0;
        date = Date(0, 0, 0);
    }

    Expense(string n, float p, Date d) { //Constructor function
        name = n;
        price = p;
        date = d;
        applyCharges();
    }
    void applyCharges() {
        Wallet -= price;
    }
    void print() {
        cout << "Name: " << name << "\nPrice: " << price << "\nDate: " << date.day << " / " << date.month << " / " << date.year << endl << "------------------------------" << endl;
    }
};

struct IncomeSource {
    string name; float size;
    float rate; //Number of days between recieving money

    IncomeSource(string n = "", float val = 0, float r = 0) {
        name = n;
        size = val;
        rate = r;
    }

    void print() {
        cout << "Income Source: " + name + "\nProvides " << size << " every " << rate << " days" << endl;
    }
};

Expense expenses[5000]; int num_of_expenses = 0;
Expense recurring_costs[100]; int num_of_costs = 0;
IncomeSource incomes[5000]; int num_of_incomes = 0;

/*void prepTracker() {
    addExpense("School", 42069,Date(9,11,2003));
    addExpense("Laptop", 4200, Date(9, 3, 3));
    addRC("car fuel", 420, Date(9, 3, 3));
    addRC("hosue rent", 69420, Date(9, 3, 3));
    addRC("water", 100, Date(9, 3, 3));
    addRC("electricity", 220, Date(9, 3, 3));
    addRC("pet food", 200, Date(9, 3, 3));
}*/

void addExpense(string name, float price, Date date) { //Addsd an expense to the expenses array
    expenses[num_of_expenses++] = Expense(name, price, date);
}

void addRC(string name, float price, Date date) { //Adds a repeating cost to the repeating_costs array
    recurring_costs[num_of_costs++] = Expense(name, price, date);
}

void mainMenu() {
    
    system("cls");
    cout << "Welcome to your income tracker" << endl;

    while (true) {
        cout << "Select an option: " << endl <<
            "1. Manage expenses" << endl <<
            "2. Manage recurring costs" << endl <<
            "3. Manage income sources" << endl <<
            "4. View details" << endl <<
            "5. Exit" << endl;
    m:
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            manageExpenses();
            break;
        case 2:
            //manageRC(); 
            break;
        case 3:
             manageIncome(); 
            break;
        case 4:
            // details(); 
            break;
        case 5:
            return;
        default:
            cout << "Please enter a valid choice" << endl; goto m;
        }
    }
}

void manageExpenses() {

        cout << "Select an option: " << endl <<
            "\t1.View all expenses" << endl <<
            "\t2.Edit An Expense" << endl <<
            "\t3.Go Back" << endl;
        int option;
    m:
        cin >> option;
        switch (option) {
        case 1:
            listExpenses(); break;
        case 2:
            promptEditExpense(); break;
        case 3:
            mainMenu();
        default:
            cout << "Please enter a valid choice\n"; goto m;

        }
  
    system("CLS");
}

void listExpenses() {
    int choice;
    if (!num_of_expenses)
    {
        char AE;
        cout << "There are currently no expenses, would you like to add an expense ? (y/n)\n";
        cin >> AE;
        if (AE == 'y' || AE == 'Y')
            promptAddExpense();
        else if (AE == 'N' || AE == 'n')
        {
            manageExpenses();
        }
    }

    for (int i = 0; i < num_of_expenses; i++) {
        expenses[i].print();
    }
    cout << "Select an option: "
        << "\n1- Add Expenses\n"
        << "2- Remove Expenses\n"
        << "3- Go back" << endl;

m:
    cin >> choice;

    switch (choice)
    {
    case 1:
        promptAddExpense(); break;
    case 2:
        promptRemoveExpense(); break;
    case 3:
        manageExpenses(); break;
    default:
        cout << "Please enter a valid choice:"; goto m;

    }
    system("pause");
}

void promptAddExpense() {
    string name; float price; char yn;
    do {
        int day;
        int month;
        int year;

        cout << "Enter expense name: ";
    m:
        cin >> name;

        if (checkIfExists(name))
        {
            cout << "An expense with the same name alraedy exists, please enter another name " << endl; goto m;
        }
        cout << "Enter expense value: ";
        cin >> price;
        cout << "Enter the Date: ";
    n:
        cin >> day >> month >> year;
        if ((checkDate(day, month, year)))
        {
            addExpense(name, price, Date(day, month, year));
        }
        else
        {
            cout << "Please Enter a valid date: "; goto n;
        }

        cout << endl << "Expense added successfully" << endl <<
            "do you want to add another expense? ";
        cin >> yn;
    } while (yn == 'y' || yn == 'Y');
    system("CLS");
}

int locateExpense(string name)
{
    int index = -1;
    for (int i = 0; i < num_of_expenses; i++)
    {
        if (expenses[i].name == name)
            index = i;
    }
    return index;
}



void removeExpense(int index)
{
    for (int i = index; i < num_of_expenses; i++)
    {
        expenses[i] = expenses[i + 1];
    }
    expenses[--num_of_expenses] = Expense();
}

void promptRemoveExpense()
{
    string expenseName;
    cout << "Enter the name of the expense you want to remove: ";
    cin >> expenseName;
    int index = locateExpense(expenseName);
    if (index > -1)
    {
        removeExpense(index);
    }
    else
    {
        cout << "Expense not found\n";
    }
}

void promptEditExpense()
{
    string choice;
    int option;
    cout << "Enter the name of the expense that you want to change: ";
m:
    cin >> choice;
    if (checkIfExists(choice))
    {
        int index = locateExpense(choice);
        cout << "1- Change Name\n"
            << "2- Change Value\n"
            << "3- Change Date\n"
            << "4- Change All\n";
        cin >> option;
        editExpense(index, option);
    }
    else
    {
        cout << "Please enter a valid name" << endl;    goto m;
    }
}

void editExpense(int index, int option)
{

m:
    switch (option)
    {
    case 1:
        editName(index); break;
    case 2:
        editPrice(index);  break;
    case 3:
        editDate(index); break;
    case 4:
        editName(index); editPrice(index); editDate(index); break;

    default:
        cout << "Please enter a valid option: ";
        cin >> option; goto m;


    }

}
bool strcomp(string s1, string s2)
{
    bool same = true;

    if (s1.length() == s2.length())
    {
        for (int i = 0; i < s1.length(); i++)
        {
            if (s1[i] != s2[i])
                same = false;
        }
    }

    else if (s1.length() != s2.length())
        same = false;

    return same;
}
bool checkIfExists(string expenseName)
{
    bool exists = true;
    for (int i = 0; i < num_of_expenses + 1; i++)
    {

        if (strcomp(expenseName, expenses[i].name))
        {
            exists = true;
            break;
        }

        else
        {
            exists = false;
        }
    }
    return exists;

}
bool checkDate(int day, int month, int year)
{
    bool correct_date = true;

    if (day < 1 || day > 31)
        correct_date = false;
    if (month < 1 || month > 12)
        correct_date = false;
    if (year < 1950 || year > 2022)
        correct_date = false;

    return correct_date;
}
void editName(int index)
{
    string name;
    cout << "Please enter the new name: ";
    cin >> name;
    expenses[index].name = name;
}
void editPrice(int index)
{
    float price;
    cout << "Please enter the new price: ";
    cin >> price;
    expenses[index].price = price;
}
void editDate(int index)
{
    int day, month, year;
    cout << "Please Enter the new date: ";
d:
    cin >> day >> month >> year;
    if (checkDate(day, month, year))
    {
        expenses[index].date = Date(day, month, year);
    }
    else
    {
        cout << "Please enter a valid date: "; goto d;
    }

}
void INITsave(Expense expense)
{
    ofstream file("Data.txt", ios::out);

    file << expense.name << " " << expense.price << " " << expense.date.day << " " << expense.date.month
        << " " << expense.date.year << endl;

    file.close();
}
void save()
{
    for (int i = 0; i < num_of_expenses; i++)
        INITsave(expenses[i]);
}
// part 2 definition
void addIncome(string name, float size, float rate)
{
    incomes[num_of_incomes++] = IncomeSource(name, size, rate);
}

void manageIncome()
{

        system("cls");

        cout << "Select an option: " << endl <<
            "\t1. Add an income" << endl <<
            "\t2. Remove an income" << endl <<
            "\t3. Edit an income" << endl <<
            "\t4.show all current incomes" << endl << endl;
        cout << "\t5. Go back" << endl << endl;

        int option;
    m:
        cin >> option;
        switch (option)
        {
        case 1:
            //promptAddIncome();
            break;
        case 2:
            //promptRemoveIncome();
            break;
        case 3:
            promptEditIncome();
            break;
        case 4:
            listIncome();
        case 5:
            mainMenu();
            break;
        default:
            cout << "Please enter a valid choice\n";
            goto m;
        }
  
}

void listIncome()
{
    //int choice; i have to release it later
    if (!num_of_incomes)
    {
        char YN;
        cout << "There are currently no income sources, would you like to add an income source ? (y/n)\n";
        cin >> YN;
        if (YN == 'y' || YN == 'Y')
            promptAddIncome();
        else if (YN == 'n' || YN == 'N')
        {
            return;
        }
    }
    for (int i = 0; i < num_of_incomes; i++)
        incomes[i].print();
}


bool checkIfIncomeExists(string itemName)
{
    bool income_exists = true;
    if (locateIncome(itemName) == -1) {


        income_exists = false;
    }

    return income_exists;
}

int locateIncome(string name)
{
    int index = -1;

    for (int i = 0; i < num_of_incomes; i++)
    {
        if (strcomp(incomes[i].name, name))
        {
            for (int i = 0; i < num_of_incomes; i++)
            {
                if (incomes[i].name == name)
                    index = i; break;
            }

            break;
        }


    }
    return index;

}
void promptAddIncome()
{}
void promptEditIncome() {

    string incomename;
    int option;
    if (!num_of_incomes)
    {
        char YN;
        cout << "There are currently no income sources, would you like to add an income source ? (y/n)\n";
        cin >> YN;
        if (YN == 'y' || YN == 'Y')
            promptAddIncome();
    }
    else
        cout << "enter the income source name you would like to edit :";
    //check the edit income functions
m:
    cin >> incomename;
    if (checkIfIncomeExists(incomename))
    {
        int index = locateIncome(incomename);
        cout << "1- Change Name\n"
            << "2- Change  Interest Value\n"
            << "3- Change Date\n"
            << "4- Change All\n";
        cin >> option;
        editincome(index, option);
    }
    else
    {
        cout << "Please enter a valid name" << endl;    goto m;
    }
}
int locateincome(string name)
{
    int index = -1;
    for (int i = 0; i < num_of_incomes; i++)
    {
        if (incomes[i].name == name)
            index = i;
    }
    return index;
}
void editincome(int index, int option)
{

m:
    switch (option)
    {
    case 1:
        editIncomeName(index); break;
    case 2:
        editIncomeSize(index);  break;
    case 3:
        editIncomeRate(index); break;
    case 4:
        editIncomeName(index); editIncomeSize(index); editIncomeRate(index); break;

    default:
        cout << "Please enter a valid option: ";
        cin >> option; goto m;


    }

}
bool strcompIncome(string s1, string s2) //maybe we will use it later
{
    bool same = true;

    if (s1.length() == s2.length())
    {
        for (int i = 0; i < s1.length(); i++)
        {
            if (s1[i] != s2[i])
                same = false;
        }
    }

    else if (s1.length() != s2.length())
        same = false;

    return same;
}


void editIncomeName(int index)
{
    string name;
    cout << "Please enter the new name: ";
    cin >> name;
    incomes[index].name = name;
}
void editIncomeSize(int index)
{
    float size;
    cout << "Please enter the new interest: ";
    cin >> size;
    incomes[index].size = size;
}
void editIncomeRate(int index)
{
    float rate;
    cout << "Please Enter the new rate: ";
    cin >> rate;
    incomes[index].rate = rate;

}



int main()
{

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    //fadi has worked on this project 3alashan ma7adesh y2ool 7aga 8eor kda
    // 7sl w ana 4ahd
    //prepTracker();
    mainMenu();
    save();

    // expenses[0] = Expense("gas", 420);
    // cout << Wallet << endl;
    // expenses[0].applyCharges();
    // cout << Wallet;


}
