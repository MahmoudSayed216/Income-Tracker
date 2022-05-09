#include<string.h>
#include<sstream>
#include "date.h"
using namespace std;

#include<iostream>

bool isFloat(string s){
    istringstream iss(s);
    float f;
    iss >> f;
    return iss.eof() && !iss.fail();
}

bool isPosInt(string s){
    for(int i = 0; i < s.length(); i++)
        if(s[i] < '0' || s[i] > '9') return false;
    return true;
}

bool lettercomp(char c1, char c2){
    return (
        c1 == c2 ||
        c1 - c2 == 'a' - 'A' ||
        c2 - c1 == 'a' - 'A'
    );
}

bool strcomp(string s1, string s2)
{
    if (s1.length() != s2.length()) return false;

    bool same = true;

    for (int i = 0; i < s1.length(); i++)
    {
        if (lettercomp(s1[i], s2[i]))
            same = false;
    }

    return same;
}

int get_posint(){
    string s;
    m:
    cin >> s;
    if(!isPosInt(s)){cout << "Please enter a positive integer: "; goto m;}
    int x = stof(s); float f = stof(s);
    if(x < 0 || x != f){cout << "Please enter a positive integer: "; goto m;}
    return x;
}
float get_posf(){
    string s;
    m:
    cin >> s;
    if(!isFloat(s)){cout << "Please enter a positive number: "; goto m;}
    float x = stof(s);
    if(x < 0){cout << "Please enter a positive number: "; goto m;}
    return x;
}
