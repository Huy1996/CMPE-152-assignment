#ifndef TEAM5_ASSIGNMENT2_SYMTABENTRY_H
#define TEAM5_ASSIGNMENT2_SYMTABENTRY_H

#include <string>
using namespace std;

class SymtabEntry{
private:
    string variable_name;
    int value;

public:
    SymtabEntry(string variable): variable_name(variable), value(0){}
    string get_variable_name(){ return variable_name; }
    int get_variable(){ return value; }
    void set_value(int value){ this->value = value; }
};


#endif //TEAM5_ASSIGNMENT2_SYMTABENTRY_H