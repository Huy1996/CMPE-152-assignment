//
// Created by Huy Duong on 9/1/22.
//

#ifndef TEAM5_ASSIGNMENT2_SCANNER_H
#define TEAM5_ASSIGNMENT2_SCANNER_H

#include "Source.h"
#include "Token.h"
#include <string>
#include <cctype>
using namespace std;

class Scanner {
private:
    Source *source;
    // char ch;
    char next_available_char();

public:
    Scanner(Source *source) : source(source) {}
    void scan() throw(string);
    Token *next_token();

};


#endif //TEAM5_ASSIGNMENT2_SCANNER_H
