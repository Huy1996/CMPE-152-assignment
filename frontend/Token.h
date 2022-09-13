//
// Created by Huy Duong on 9/1/22.
//

#ifndef TEAM5_ASSIGNMENT2_TOKEN_H
#define TEAM5_ASSIGNMENT2_TOKEN_H

#include <map>
#include <string>
#include <iostream>
#include "../helper.h"

using namespace std;

class Token {
public:
    Token(int line): line_number(line), done(false), state(0), text(""){};
    bool is_done();
    void scan(char ch);
    void end_of_file(){done = true; state = -33;};
    int get_line_number() { return line_number; };
    string get_text();
    string get_token_type();
    int get_state(){return state;};

private:
    bool done;
    int state, line_number;
    int type_of(char ch);
    static const int ERR = -99999;
    string text;
    static const int row = 43;
    static const int col = 25;
    static const int matrix[row][col];
    static const string token_type[34];
    static const map<char, int> char_type;
    static const string reserved_word[57];

};


#endif //TEAM5_ASSIGNMENT2_TOKEN_H
