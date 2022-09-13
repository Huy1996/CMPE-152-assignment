//
// Created by Huy Duong on 9/1/22.
//

#include "Token.h"
// #include <algorithm>

// string toUpperCase(string text){
//     string to_return;
//     for (int i = 0; i < text.length(); i++) {
//         to_return += toupper(text[i]);
//     }
//     return to_return;
// }

const int Token::matrix[row][col] = {
        /*        letter digit  +     -    .    E    *    /    :    <    >    =    ^    ;    ,    (    )    [    ]    {    }   \n    '  EOF  other */
        /*  0 */ {   1,	   2,	8,	  9,  40,	1,	10,	 11,  12,  13,  14,	 16,  17,  18,  19,  15, 21,  22,  23,   24,  25, 	0,  35,   0,    31  },
        /*  1 */ {   1,	   1,  -1,	 -1,  -1,	1,	-1,	 -1,  -1,  -1,	-1,  -1,  -1,  -1,	-1,  -1,  -1,  -1,	-1,  -1,  -1,  -1,  -1,  -1,	-1  },
        /*  2 */ {  -2,	   2,  -2,	 -2,   3,	5,	-2,	 -2,  -2,  -2,	-2,  -2,  -2,  -2,	-2,  -2,  -2,  -2,	-2,  -2,  -2,  -2,  -2,  -2,	-2  },
        /*  3 */ { ERR,	   4, ERR,  ERR, ERR, ERR, ERR,	ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR,	ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR,	ERR },
        /*  4 */ {  -3,	   4,  -3,	 -3,  42,	5,	-3,  -3,  -3,  -3,	-3,  -3,  -3,  -3,	-3,  -3,  -3,  -3,	-3,  -3,  -3,  -3,  -3,  -3,	-3  },
        /*  5 */ { ERR,    7,	6,	  6, ERR, ERR, ERR, ERR, ERR, ERR, ERR,	ERR, ERR, ERR, ERR,	ERR, ERR, ERR, ERR,	ERR, ERR, ERR, ERR, ERR,	ERR },
        /*  6 */ { ERR,	   7, ERR,	ERR, ERR, ERR, ERR,	ERR, ERR, ERR, ERR,	ERR, ERR, ERR, ERR,	ERR, ERR, ERR, ERR,	ERR, ERR, ERR, ERR, ERR,	ERR },
        /*  7 */ {  -3,    7,  -3,	 -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,    -3  },
        /*  8 */ {  -4,   -4,  -4,   -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  26,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,    -4  },
        /*  9 */ {  -5,   -5,  -5,   -5,  -5,  -5,  -5,  -5,  -5,  -5,  -5,  27,  -5,  -5,  -5,  -5,  -5,  -5,  -5,  -5,  -5,  -5,  -5,  -5,    -5  },
        /* 10 */ {  -6,   -6,  -6,   -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  32,  -6,  -6,  -6,  -6, -29,  -6,  -6,  -6,  -6,  -6,  -6,  -6,    -6  },
        /* 11 */ {  -7,   -7,  -7,   -7,  -7,  -7,  -7,  -7,  -7,  -7,  -7,  33,  -7,  -7,  -7,  -7,  -7,  -7,  -7,  -7,  -7,  -7,  -7,  -7,    -7  },
        /* 12 */ { -34,  -34, -34,  -34, -34, -34, -34, -34, -34, -34, -34,  34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34,    -34 },
        /* 13 */ { -13,  -13, -13,  -13, -13, -13, -13, -13, -13, -13,  28,  29, -13, -13, -13, -13, -13, -13, -13, -13, -13, -13, -13, -13,    -13 },
        /* 14 */ { -14,  -14, -14,  -14, -14, -14, -14, -14, -14, -14, -14,  30, -14, -14, -14, -14, -14, -14, -14, -14, -14, -14, -14, -14,    -14 },
        /* 15 */ { -22,  -22, -22,  -22, -22, -22,  20, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22,    -22 },
        /* 16 */ {  -9,   -9,  -9,   -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,  -9,    -9  },
        /* 17 */ { -19,  -19, -19,  -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19,    -19 },
        /* 18 */ { -20,  -20, -20,  -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20,    -20 },
        /* 19 */ { -21,  -21, -21,  -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21,    -21 },
        /* 20 */ { -28,  -28, -28,  -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28,    -28 },
        /* 21 */ { -23,  -23, -23,  -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23,    -23 },
        /* 22 */ { -24,  -24, -24,  -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24,    -24 },
        /* 23 */ { -25,  -25, -25,  -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25,    -25 },
        /* 24 */ { -26,  -26, -26,  -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26,    -26 },
        /* 25 */ { -27,  -27, -27,  -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27,    -27 },
        /* 26 */ { -15,  -15, -15,  -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15,    -15 },
        /* 27 */ { -16,  -16, -16,  -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16,    -16 },
        /* 28 */ { -10,  -10, -10,  -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10,    -10 },
        /* 29 */ { -11,  -11, -11,  -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11,    -11 },
        /* 30 */ { -12,  -12, -12,  -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,    -12 },
        /* 31 */ { ERR,  ERR, ERR,  ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR,    ERR },
        /* 32 */ { -17,  -17, -17,  -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17,    -17 },
        /* 33 */ { -18,  -18, -18,  -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18, -18,    -18 },
        /* 34 */ {  -8,   -8,  -8,   -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,     -8 },
        /* 35 */ {  36,   36,  36,   36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36, ERR,  39, ERR,     36 },
        /* 36 */ {  38,   38,  38,   38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38, ERR,  37, ERR,     38 },
        /* 37 */ { -30,  -30, -30,  -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,    -30 },
        /* 38 */ {  38,   38,  38,   38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38, ERR,  39, ERR,     38 },
        /* 39 */ { -31,  -31, -31,  -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31,    -31 },
        /* 40 */ {  31,   31,  31,   31,  41,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,     31 },
        /* 41 */ { -32,  -32, -32,  -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32,    -32 },
        /* 42 */ { ERR,   42, ERR,  ERR,  42, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR,    ERR }

};

const string Token::token_type[34] = {
        "IDENTIFIER", "INTEGER", "REAL", "PLUSOP", "MINUSOP", "MULTOP", "DIVOP", "ASSIGN", "EQUAL",
        "NE", "LTEQ", "GTEQ", "LT", "GT", "PLUSEQUAL", "MINUSEQUAL", "MULTEQUAL", "DIVEQUAL", "CARAT",
        "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "LCOMMENT",
        "RCOMMENT", "CHARACTER", "STRING", "DOTDOT", "END_OF_FILE", "COLON"
};

const string Token::reserved_word[57] = {
        "PROGRAM", "BEGIN", "END", "REPEAT", "UNTIL",
        "DIV", "MOD", "AND", "OR", "NOT", "ARRAY",
        "CONST", "TYPE", "VAR", "PROCEDURE", "FUNCTION",
        "WHILE", "DO", "FOR", "TO", "DOWNTO", "IF", "THEN",
        "ELSE", "CASE", "OF", "DESTRUCTOR", "CONSTRUCTOR",
        "ASM", "BREAK", "CONTINUE", "IMPLEMENTATION",
        "FALSE", "FILE", "IDENTIFIER", "STRING", "GOTO",
        "IN", "INLINE", "INTERFACE", "LABEL", "NIL", "OBJECT", "ON",
        "OPERATOR", "PACKED", "RECORD", "SET", "SHL", "SHR",
        "TRUE", "UNIT", "USES", "WITH", "XOR", "WRITE", "WRITELN"
};

const map<char, int> Token::char_type = {
        {'+', 2},
        {'-', 3},
        {'.', 4},
        {'E', 5},
        {'*', 6},
        {'/', 7},
        {':', 8},
        {'<', 9},
        {'>', 10},
        {'=', 11},
        {'^', 12},
        {';', 13},
        {',', 14},
        {'(', 15},
        {')', 16},
        {'[', 17},
        {']', 18},
        {'{', 19},
        {'}', 20},
        {'\n', 21},
        {'\'', 22},
};


bool Token::is_done() {
    return done;
}

void Token::scan(char ch) {
    state = matrix[state][type_of(ch)];
    if(state < 0) {
        done = true;
        return;
    }
    text += ch;
}

int Token::type_of(char ch) {
    
    if (ch == char(13)) return 21;
    if (ch == EOF) return 23;
    try{
        return char_type.at(ch);
    }
    catch (out_of_range){
        return isalpha(ch) ? 0 : isdigit(ch) ? 1 : (col - 1);
    }
}

string Token::get_text() {
    return text;
}

string Token::get_token_type() {
    if (state == ERR) return "**ERROR**";
    if (state == -1){
        string upper = toUpperCase(text);
        bool found = false;
        for (int i=0; i<57; i++){
            if(upper.compare(reserved_word[i]) == 0) { found = true; break;}
        }
        if (found)
            return upper;
        else return token_type[abs(state) - 1];
    }
    return token_type[abs(state) - 1];
}
