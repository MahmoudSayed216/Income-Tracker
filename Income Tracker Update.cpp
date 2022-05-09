#define max_rc 500
#define max_is 500

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include<stdlib.h>
#include<fstream> //file stream
#include<iomanip> // will use it later to organize the date format

#include "date.h"
#include "extraFuncs.h"

using namespace std;
struct RecurringCost;

ifstream filein("Data.txt"); //input file-stream for loading
ofstream fileout; //output file-stream for saving

void save(RecurringCost rc);

bool strcomp(string s1, string s2);
void mainMenu();

struct RecurringCost {
    string name;
    float price;
    int rate;

    void print() {
        cout << "Name: " << name << "\nPrice: $" << price << endl; 
        if(rate > 0) cout << "Payed every " << rate << " days";
        else cout << "Payed monthly";
        cout << "\n------------------------------\n";
    }
};
void manageRC();
void listRCs();
void promptAddRC();
void addRC(string name, float price, Date date);
void promptRemoveRC();
int locateCost(string name);
void removeRC(int index);

void promptEditRC();
void editRC(int index, int option);
void editCostName(int index);
void editCostPrice(int index);
void editCostRate(int index);
bool checkIfCostExists(string name);

void listRecurringCosts();
void promptAddRC();
void addRC(string name, float price, int rate);
void promptRemoveRC();
void promptEditRC();
void editRC();
void manageIS();

// Declare Income-focused Functions
struct IncomeSource {
    string name; float size;
    int rate; //Number of days between recieving money

    void print() {
        cout << "Income Source: " + name + "\nProvides $" << size; 
        if (rate > 0) cout << " every " << rate << " days" << endl;
        else cout << " monthly";
        cout << "\n------------------------------\n";
    }
};
void manageIncome();
void listIncomeSources();
void promptAddIncome();
void addIncome(string name, float size, float rate);
void editIncomeName(int index);
void editIncomeSize(int index);
void editIncomeRate(int index);
void promptRemoveIncome();
void removeIncome(int index);
void promptEditIncome();
void editincome(int index, int option);
bool strcomp(string s1, string s2);

bool checkIfIncomeExists(string itemName);
int locateIncome(string name);

// Declare Tracking-focused functions
struct TrackingDetails{
    float wallet_start;
    float wallet_end;
    int cost_reps[max_rc]; float costs_sum;
    int income_reps[max_is]; float income_sum;
    float additional_expenses_sum;
};
void promptTracking();
TrackingDetails track(Date start, Date end);
void print_summary(TrackingDetails details);
void print_detailed(TrackingDetails details);


float Wallet = 0;

RecurringCost recurring_costs[max_rc]; int num_of_costs = 0;
IncomeSource incomes[max_is]; int num_of_incomes = 0;

void addRC(string name, float price, int rate) { //Addsd a recurring cost to the recurring costs array
    recurring_costs[num_of_costs++] = {name, price, rate};
}

void mainMenu() {
    
    system("cls");
    cout << "Welcome to your income tracker" << endl;

    while (true) {
        cout << "Select an option: " << endl <<
            "1. View and manage recurring costs" << endl <<
            "2. View and manage income sources" << endl <<
            "3. Track income between two dates" << endl <<
            "4. Exit" << endl;
    m:
        int choice;
        choice = get_posint();
        switch (choice) {
        case 1:
            manageRC();
            break;
        case 2:
            manageIncome(); 
            break;
        case 3:
            promptTracking();
            break;
        case 4:
            return;
        default:
            cout << "Please enter a valid choice" << endl; goto m;
        }
        system("CLS");
    }
}

void manageRC() {
    bool keepgoing = true;
    do {
        system("CLS");
        listRCs();
        cout << "\nSelect an option: " << endl <<
            "1. Add a recurring cost" << endl <<
            "2. Remove a recurring cost" << endl <<
            "3. Edit a recurring cost" << endl <<
            "4. Go Back" << endl;
        int option;
    m:
        option = get_posint();
        switch (option) {
        case 1:
            promptAddRC(); break;
        case 2: 
            promptRemoveRC(); break;
        case 3:
            promptEditRC(); break;
        case 4:
            keepgoing = false; break;
        default:
            cout << "Please enter a valid choice\n"; goto m;
        }
    } while (keepgoing);
}

void listRCs() {
    int choice;
    if (!num_of_costs)
    { 
        char AE;
        cout << "There are currently no recurring costs, would you like to add a recurring costs ? (y/n)\n";
        cin >> AE;
        if (lettercomp(AE, 'y'))
            promptAddRC();
        else if (lettercomp(AE, 'n'))
        {
            return;
        }
    }

    cout << "Your current recurring costs are:\n------------------------------\n";
    for (int i = 0; i < num_of_costs; i++) {
         recurring_costs[i].print();
    }
}

void promptAddRC() {
    string name; char yn;
    do {
        system("CLS");
        cout << "Enter recurring cost's name: ";
    m:
        cin >> name;

        if (checkIfCostExists(name))
        {
            cout << "A recurring cost with the same name alraedy exists, please enter another name " << endl; goto m;
        }
        cout << "Enter the recurring cost's value: ";
        float price = get_posf();

        cout << "Please enter the number of days between payements: (enter 0 for monthly payment)\n";
        int rate = get_posint();

        addRC(name, price, rate);

        cout << endl << "Recurring cost added successfully" << endl <<
            "do you want to add another recurring cost? (y/n)\n";
        cin >> yn;
    } while (lettercomp(yn, 'y'));
    system("CLS");
}

int locateCost(string name)
{
    int index = -1;
    for (int i = 0; i < num_of_costs; i++)
    {
        if (recurring_costs[i].name == name)
            index = i;
    }
    return index;
}



void removeRC(int index)
{
    for (int i = index; i < num_of_costs; i++)
    {
        recurring_costs[i] = recurring_costs[i + 1];
    }
    recurring_costs[--num_of_costs] = {};
}

void promptRemoveRC()
{
    string name;
    cout << "Enter the name of the recurring cost you want to remove: ";
    cin >> name;
    int index = locateCost(name);
    if (index > -1){
        removeRC(index);
    }
    else{
        cout << "recurring cost not found\n";
    }
}

void promptEditRC()
{
    string choice;
    int option;
    cout << "Enter the name of the recurring cost that you want to change: ";
m:
    cin >> choice;
    if (checkIfCostExists(choice))
    {
        int index = locateCost(choice);
        cout << "1- Change Name\n"
            << "2- Change Value\n"
            << "3- Change Rate\n"
            << "4- Change All\n";
        option = get_posint();
        editRC(index, option);
    }
    else{
        cout << "Please enter a valid name" << endl;    goto m;
    }
}

void editRC(int index, int option){
m:
    switch (option)
    {
    case 1:
        editCostName(index); break;
    case 2:
        editCostPrice(index);  break;
    case 3:
        editCostRate(index); break;
    case 4:
        editCostName(index); editCostPrice(index); editCostRate(index); break;

    default:
        cout << "Please enter a valid option: ";
        cin >> option; goto m;
    }

}

bool checkIfCostExists(string name){
    return locateCost(name) > -1;
}


void editCostName(int index){
    string name;
    cout << "Please enter the new name: ";
    cin >> name;
    recurring_costs[index].name = name;
}
void editCostPrice(int index){
    cout << "Please enter the new price: ";
    float price = get_posf();
    recurring_costs[index].price = price;
}
void editCostRate(int index){
    cout << "Please Enter the new rate: ";
    int rate = get_posint();
    recurring_costs[index].rate = rate; 
}


//INCOME
void addIncome(string name, float size, int rate){
    incomes[num_of_incomes++] = {name, size, rate};
}

void manageIncome(){
        system("CLS");
        listIncomeSources();
        cout << "Select an option: " << endl <<
            "1. Add an income source" << endl <<
            "2. Remove an income source" << endl <<
            "3. Edit an income source" << endl << endl;
        cout << "4. Go back" << endl << endl;

        int option;
    m:
        option = get_posint();
        switch (option)
        {
        case 1:
            promptAddIncome();
            break;
        case 2:
            //promptRemoveIncome();
            break;
        case 3:
            promptEditIncome();
            break;
        case 4:
            mainMenu();
            break;
        default:
            cout << "Please enter a valid choice\n";
            goto m;
        }
  
}

void listIncomeSources()
{
    system("CLS");
    int choice;
    if (!num_of_incomes)
    {
        char YN;
        cout << "There are currently no income sources, would you like to add an income source ? (y/n)\n";
        cin >> YN;
        if (YN == 'y' || YN == 'Y')
            promptAddIncome();
        else if (YN == 'n' || YN == 'N')
        {
            system("CLC"); return;
        }
    }
    cout << "Your current sources of income:\n------------------------------\n";
    for (int i = 0; i < num_of_incomes; i++)
        incomes[i].print();
    cout << endl;
}


bool checkIfIncomeExists(string name){
    return locateIncome(name) > -1;
}

int locateIncome(string name){
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
{
    string income_name;
    float  income_value;
    int  income_rate;
    char   adding_choice;

    do {
        system("cls");
        cout << "Enter income name:\n";
    m:
        getline(cin, income_name); cin;
        if (checkIfIncomeExists(income_name))
        {
            cout << "An income source with the same name alraedy exists, please enter another name " << endl; goto m;
        }
        cout << "Enter paycheck value: ";
        income_value = get_posf();

        cout << "Enter the number of days between recieving paychecks (enter 0 for every month): ";
        income_rate = get_posint();
        addIncome(income_name, income_value, income_rate);

        cout << "Do you want to add any other income sources? (y/n)";
        cin >> adding_choice;

    } while (adding_choice == 'y' || adding_choice == 'Y');
    system("CLS");
}

void promptRemoveIncome(){
    string name;

}

//EDITING INCOME
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
            << "2- Change Payment Value\n"
            << "3- Change Date\n"
            << "4- Change All\n";
        option = get_posint();
        editincome(index, option);
    }
    else
    {
        cout << "Please enter a valid name" << endl;    goto m;
    }
}

void editincome(int index, int option){
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
    size = get_posf();
    incomes[index].size = size;
}
void editIncomeRate(int index)
{
    int rate;
    cout << "Please Enter the new rate: ";
    rate = get_posint();
    incomes[index].rate = rate;
}




// TRACKING
void promptTracking(){
    Date start, end;
    cout<<"Please enter the start date for tracking (format dd mm yyyy): " << endl;
    start.get_date();

    cout<<"Please enter the end date for tracking (format dd mm yyyy): " << endl;
    start.get_date();

    TrackingDetails details = track(start, end);

    cout<<"\nWould you like an abreviated view of the tracking, or a detailed view? (enter 'a' for abreviated, or 'd' for detialed)\n"; char type;
    cin >> type;
    if(lettercomp(type, 'a')){ print_summary(details); }
    else if(lettercomp(type, 'd')){ print_summary(details);}
}

TrackingDetails track(Date start, Date end){
    TrackingDetails result = {0, 0, {}, 0, {}, 0, 0};

    cout << "Please enter the initial amount of money in the wallet: "; cin >> result.wallet_start; result.wallet_end = result.wallet_start;

    int days = end.days_from(start);
    int months = end.day_ones_from(start);

    for(int i = 0; i < num_of_incomes; i++){
        result.income_reps[i] = incomes[i].rate > 0 ? days/incomes[i].rate : months;
        result.income_sum += result.income_reps[i] * incomes[i].size;
    }

    for(int i = 0; i < num_of_costs; i++){
        result.cost_reps[i] = recurring_costs[i].rate > 0 ? days/recurring_costs[i].rate : months;
        result.costs_sum += result.income_reps[i] * incomes[i].size;
    }

    char addExpense;

    cout << "Are there any additional expenses? (y/n)"<< endl;
    cin >> addExpense;
    while(lettercomp(addExpense, 'y')){
        cout << "Please enter the value of the expenses: ";
        int x = get_posint();
        result.additional_expenses_sum += x;
        cout << "Are there any additional expenses? (y/n)"<< endl;
        cin >> addExpense;
    }

    result.wallet_end += result.income_sum;
    result.wallet_end -= result.costs_sum;
    result.wallet_end -= result.additional_expenses_sum;

    return result;
}

void print_summary(TrackingDetails details){
    cout << "The initial balance: " << details.wallet_start << endl << "The final balance in your wallet is: " << details.wallet_end << "\n\n$" << details.income_sum << "came in through your sources of income\n$" << details.costs_sum << "went out to your recurring costs\nAnd $" << details.additional_expenses_sum << "went out to additional expenses\nMaking the NET change in your balance " << (details.wallet_end - details.wallet_start > 0 ? "$" : "-$") << details.wallet_end - details.wallet_start;
}

void print_detailed(TrackingDetails details){
    cout << "Costs:\n------------------------------\n";
    for(int i = 0; i < num_of_costs; i++){
        cout << i+1 << ". " << recurring_costs[i].name << "\nnumber of payments: " << details.cost_reps[i] << "\tsum cost: " << details.cost_reps[i] * recurring_costs[i].price << "\n------------------------------\n";
    }
    cout << "\nIncome:\n------------------------------\n";
    for(int i = 0; i < num_of_incomes; i++){
        cout << i+1 << ". " << recurring_costs[i].name << "\nnumber of payments: " << details.cost_reps[i] << "\tsum cost: " << details.cost_reps[i] * incomes[i].size << "\n------------------------------\n";
    }
    print_summary(details);
}




// FILE MANAGEMENT
void INITsave(){
    fileout.open("Data.txt");
    fileout << "RecurringCosts\n";
    for (int i = 0; i < num_of_costs; i++)
        save(recurring_costs[i]);

    fileout << "IncomeSources\n";

    fileout.close();
}

void save(RecurringCost rc){
    fileout << rc.name << endl << " " << rc.price << " " << rc.rate << endl; 
}

void INITload(){
    string line1, line2; getline(filein, line1);

    while(getline(filein, line1)){
        if(line1 == "IncomeSources") break;
        string name = line1; 

        getline(filein, line2);
        istringstream data(line2); 
        float price; int rate;
        data >> price >> rate;
        recurring_costs[num_of_costs++] = {name, price, rate};
    }

    filein.close();
}



int main()
{
    INITload();

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    mainMenu();
    INITsave();
}
