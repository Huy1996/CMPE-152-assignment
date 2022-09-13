#ifndef TEAM5_ASSIGNMENT2_TREEWALKER_H
#define TEAM5_ASSIGNMENT2_TREEWALKER_H

#include <string>
#include <vector>
#include <iostream>

#include "Node.h"
using namespace std;

class TreeWalker{


public:
    TreeWalker() : indentation(""), line("") {}

    /**
     * Print a parse tree.
     * @param node the parse tree's root node.
     */
    void print(Node *node);

private:
    static const string INDENT_SIZE;

    string indentation;  // indentation of a line
    string line;         // output line
    void printChildren(vector<Node *> children);
    void printLine();
};




#endif //TEAM5_ASSIGNMENT2_TREEWALKER_H