#include <iostream>
#include<string>
#include<sstream>

#include<stdlib.h>
#include<fstream>
#include<iomanip> // will use it later to organize the date format

#include "date.h"
#include "extraFuncs.h"


using namespace std;
struct Expense;

ifstream filein("Data.txt");
ofstream fileout;

void save(int index);
void load();
bool strcomp(string s1, string s2);

void mainMenu();

void manageExpenses();
void listExpenses();
    void promptAddExpense();
        void addExpense(string name, float price, Date date);
    void promptRemoveExpense();
        void removeExpense(int index);
    void promptEditExpense();
    
    bool checkIfExpenseExists(string itemName);
    int locateExpense(string name);

void manageRC(); //Manage repeated costs
void listRecurringCosts();
    void promptAddRC();
        void addRC(string name, float price, Date date);
    void promptRemoveRC();
    void promptEditRC();
void editRC();
void manageIS();

double Wallet = 0;
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
    }
    void applyExpense() {
        Wallet -= price;
    }

    /**EXPENSE EDITING**/
    void editName(){
        string newname;
        cout << "Please enter the new name: ";
        cin >> newname;
        name = newname;
    }
    void editPrice(){
        float newprice;
        cout << "Please enter the new price: ";
        cin >> newprice;
        price = newprice;
    }
    void editDate(){
        int day, month, year;
        cout << "Please Enter the new date: ";
    d:
        cin >> day >> month >> year;
        if (checkDate(day, month, year))
        {
            date = Date(day, month, year);
        }
        else
        {
            cout << "Please enter a valid date: "; goto d;
        }
    }
    void editExpense(int option)
    {
    m:
        switch (option)
        {
            case 1:
                editName(); break;
            case 2:
                editPrice();  break;
            case 3:
                editDate(); break;
            case 4:
                editName(); editPrice(); editDate(); break;

            default:
                cout << "Please enter a valid option: ";
                cin >> option; goto m;
        }
    }

    /**OUTPUT**/
    void print() {
        cout << "Name: " << name << "\nPrice: " << price << "\nDate: " << date.day << " / " << date.month << " / " << date.year << endl << "------------------------------" << endl;
    }
    void save(){
        fileout << name << " " << price << " " << date.toString() << endl;
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

void addExpense(string name, float price, Date date) { //Addsd an expense to the expenses array
    expenses[num_of_expenses++] = Expense(name, price, date);
}

void addRC(string name, float price, Date date) { //Adds a repeating cost to the repeating_costs array
    recurring_costs[num_of_costs++] = Expense(name, price, date);
}

void mainMenu() {
    system("CLS");
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
            // manageIncome(); 
            break;
        case 4:
            // details(); 
            break;
        case 5:
            return;
        default:
            cout << "Please enter a valid choice" << endl; goto m;
        }
        system("CLS");
    }
}

void manageExpenses() {
    bool keepgoing = true;
    do {
        system("CLS");
        listExpenses();
        cout << "Select an option: " << endl <<
            "\t1. Add an expense" << endl <<
            "\t2. Remove an expense" << endl <<
            "\t3. Edit an expense" << endl <<
            "\t4. Go Back" << endl;
        int option;
    m:
        cin >> option;
        switch (option) {
        case 1:
            promptAddExpense(); break;
        case 2: 
            promptRemoveExpense(); break;
        case 3:
            promptEditExpense(); break;
        case 4:
            keepgoing = false; break;
        default:
            cout << "Please enter a valid choice\n"; goto m;

        }
    } while (keepgoing);
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
            return;
        }
    }

    for (int i = 0; i < num_of_expenses; i++) {
         expenses[i].print();
    }
}

bool checkIfExpenseExists(string name){
    return locateExpense(name) != -1;
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

        if (checkIfExpenseExists(name))
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
        if (strcomp(expenses[i].name, name))
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
    int index = locateExpense(choice);
    if (index != -1)
    {
        cout << "1- Change Name\n"
            << "2- Change Value\n"
            << "3- Change Date\n"
            << "4- Change All\n";
        cin >> option;
        expenses[index].editExpense(option);
    }
    else
    {
        cout << "Please enter a valid name" << endl;    goto m;
    }
}

bool checkIExpensefExists(string expenseName)
{
    return locateExpense(expenseName) != -1;
}

void INITload(){
    string line; getline(filein, line);
    while(getline(filein, line)){
        if(line == "RecurringCosts") break;
        istringstream data(line); string name; float price; int d, m, y;
        data >> name >> price >> d >> m >> y;
        expenses[num_of_expenses++] = Expense(name, price, Date(d,m,y));
    }
    filein.close();
}

void INITsave()
{
    fileout.open("Data.txt");
    fileout << "Expenses\n";
    for (int i = 0; i < num_of_expenses; i++)
        expenses[i].save();

    fileout.close();
}

int main(){
    INITload();

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
   
    mainMenu();
    INITsave();

}