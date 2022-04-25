#include<string.h>
using namespace std;

#ifndef xtra
#define xtra

#include<iostream>

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

#endif
