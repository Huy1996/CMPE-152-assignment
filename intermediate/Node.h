#ifndef TEAM5_ASSIGNMENT2_NODE_H
#define TEAM5_ASSIGNMENT2_NODE_H

#include <string>
#include <vector>
#include "Symtab.h"
#include "SymtabEntry.h"
using namespace std;

enum class NodeType{
    PROGRAM, COMPOUND, ASSIGN, LOOP, TEST, WRITE, WRITELN,
    ADD, SUBTRACT, MULTIPLY, DIVIDE, EQ, LT,
    VARIABLE, INTEGER_CONSTANT, REAL_CONSTANT, STRING_CONSTANT,
    GT, GE, LE, NE, NOT_NODE, CONDITION,
    TRUE_STATEMENT, FALSE_STATEMENT,
    AND_NODE, OR_NODE, DIV_NODE, UP, DOWN, FOR_LOOP, NEGATIVE,
    CASE_STATEMENT, LIST
};

static const string NODE_TYPE_STRINGS[] =
{
    "PROGRAM", "COMPOUND", "ASSIGN", "LOOP", "TEST", "WRITE", "WRITELN",
    "ADD", "SUBTRACT", "MULTIPLY", "DIVIDE", "EQ", "LT",
    "VARIABLE", "INTEGER_CONSTANT", "REAL_CONSTANT", "STRING_CONSTANT",
    "GT", "GE", "LE", "NE", "NOT_NODE", "CONDITION",
    "TRUE_STATEMENT", "FALSE_STATEMENT",
    "AND_NODE", "OR_NODE", "DIV_NODE", "UP", "DOWN", "FOR_LOOP", "NEGATIVE",
    "CASE_STATEMENT", "LIST"
};

class Node
{
public:
    NodeType type;
    int lineNumber;
    string text;
    SymtabEntry *entry;
    int value;
    vector<Node *> node_container;

    Node(NodeType type)
            : type(type), lineNumber(0), entry(nullptr) {}

    void adopt(Node *node) { node_container.push_back(node); }
};

#endif //TEAM5_ASSIGNMENT2_NODE_H