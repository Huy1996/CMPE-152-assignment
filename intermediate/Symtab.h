#ifndef TEAM5_ASSIGNMENT2_SYMTAB_H
#define TEAM5_ASSIGNMENT2_SYMTAB_H

#include <string>
#include <map>
#include "SymtabEntry.h"

class Symtab{
private:
    map<string, SymtabEntry*> symbol_table;

public:
    SymtabEntry *new_variable(string variable_name){
        SymtabEntry *new_variable = new SymtabEntry(variable_name);
        symbol_table[variable_name] = new_variable;
        return new_variable;
    }

    SymtabEntry *find_variable(string variable_name){
        if(symbol_table.find(variable_name) != symbol_table.end()){
            return symbol_table[variable_name];
        }
        return nullptr;
    }

};



#endif //TEAM5_ASSIGNMENT2_SYMTAB_H