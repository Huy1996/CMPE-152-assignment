#include "TreeWalker.h"

const string TreeWalker::INDENT_SIZE = "    ";

void TreeWalker::print(Node *node)
{
    // Opening tag.
    line += indentation;
    line += "<" + NODE_TYPE_STRINGS[(int) node->type];

    // Attributes.
    if      (node->type == NodeType::PROGRAM)          line += " " + node->text;
    else if (node->type == NodeType::VARIABLE)         line += " " + node->text;
    else if (node->type == NodeType::INTEGER_CONSTANT) line += " " + to_string(node->value);
    else if (node->type == NodeType::REAL_CONSTANT)    line += " " + to_string(node->value);
    else if (node->type == NodeType::STRING_CONSTANT)  line += " '" + node->string_value + "'";
    if (node->lineNumber > 0)                line += " line " + to_string(node->lineNumber);

    // Print the node's children followed by the closing tag.
    vector<Node *> children = node->node_container;
    if (children.size() > 0)
    {
        line += ">";
        printLine();

        printChildren(children);
        line += indentation;
        line += "</" + NODE_TYPE_STRINGS[(int) node->type] + ">";
    }

    // No children: Close off the tag.
    else line += " />";

    printLine();
}

void TreeWalker::printChildren(vector<Node *> children)
{
    string saveIndentation = indentation;
    indentation += INDENT_SIZE;
    for (Node *child : children) print(child);
    indentation = saveIndentation;
}

void TreeWalker::printLine()
{
    cout << line << endl;
    line = "";
}