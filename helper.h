#ifndef TEAM5_ASSIGNMENT2_HELPER_H
#define TEAM5_ASSIGNMENT2_HELPER_H

#include <string>
#include <algorithm>

using namespace std;

inline string toUpperCase(string str)
{
    string upper_case(str);
    transform(upper_case.begin(), upper_case.end(),
              upper_case.begin(), ::toupper);
    return upper_case;
}


inline string toLowerCase(string str)
{
    string lower_case(str);
    transform(lower_case.begin(), lower_case.end(),
              lower_case.begin(), ::tolower);
    return lower_case;
}

#endif //TEAM5_ASSIGNMENT2_HELPER_H