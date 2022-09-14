#ifndef TEAM5_ASSIGNMENT2_PARSER_H
#define TEAM5_ASSIGNMENT2_PARSER_H

#include "Scanner.h"
#include "Token.h"
#include "../intermediate/Symtab.h"
#include "../intermediate/SymtabEntry.h"
#include "../intermediate/Node.h"
#include <string>
#include <set>
#include <iostream>

using namespace std;

class Parser{
public:
    Parser(Scanner *scanner, Symtab *symtab): scanner(scanner), symtab(symtab),
        current_token(nullptr), line_number(0), error_count(0){}
    int get_error(){ return error_count; }
    Node *parseProgram();

private:
    Scanner *scanner;
    Symtab *symtab;
    Token *current_token;
    int line_number;
    int error_count;

    static const set<string> starting_token;
    static const set<string> follow_token;
    static const set<string> relation_op_token;
    static const set<string> expression_op_token;
    static const set<string> term_op_token;
    
    Node *parseStatement();
    Node *parseAssignmentStatement();
    Node *parseCompoundStatement();
    Node *parseRepeatStatement();
    Node *parseWriteStatement();
    Node *parseWritelnStatement();
    Node *parseExpression();
    Node *parseSimpleExpression();
    Node *parseTerm();
    Node *parseFactor();
    Node *parseVariable();
    Node *parseIntegerConstant();
    Node *parseRealConstant();
    Node *parseStringConstant();
    Node *parseForStatement();
    Node *parseWhileStatement();
    Node *parseIfStatement();
    Node *parseNot();
    Node *parseCaseStatement();


    void parseStatementList(Node *parentNode, string terminalType);
    void parseWriteArguments(Node *node);

    void syntaxError(string message);
    void semanticError(string message);
};



#endif //TEAM5_ASSIGNMENT2_PARSER_H