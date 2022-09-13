#include "Parser.h"

const set<string> Parser::starting_token = {
    "BEGIN", "IDENTIFIER", "REPEAT", "WRITE", "WRITELN", "FOR", "WHILE", "IF", "CASE"
};

const set<string> Parser::follow_token = {
    "SEMICOLON", "END", "UNTIL", "END_OF_FILE", "DO", "TO", "DOWNTO", "THEN", "ELSE", "OF"
};

const set<string> Parser::relation_op_token = {
    "EQUAL", "LT", "GT", "LTEQ", "GTEQ", "NE"
};

const set<string> Parser::expression_op_token = {
    "PLUSOP", "MINUSOP", "MINUSEQUAL", "PLUSEQUAL", "OR"
};

const set<string> Parser::term_op_token = {
    "MULTOP", "DIVOP", "MULTEQUAL", "DIVEQUAL", "AND"
};


Node *Parser::parseProgram()
{
    Node *programNode = new Node(NodeType::PROGRAM);

    current_token = scanner->next_token();  // first token!

    if (current_token->get_token_type().compare("PROGRAM") == 0)
    {
        current_token = scanner->next_token();  // consume PROGRAM
    }
    else syntaxError("Expecting PROGRAM");

    if (current_token->get_token_type().compare("IDENTIFIER") == 0)
    {
        string programName = current_token->get_text();
        symtab->new_variable(programName);
        programNode->text = programName;

        current_token = scanner->next_token();  // consume program name
    }
    else syntaxError("Expecting program name");

    if (current_token->get_token_type().compare("SEMICOLON") == 0)
    {
        current_token = scanner->next_token();  // consume ;
    }
    else syntaxError("Missing ;");

    if (current_token->get_token_type().compare("BEGIN") != 0) syntaxError("Expecting BEGIN");

    // The PROGRAM node adopts the COMPOUND tree.
    programNode->adopt(parseCompoundStatement());

    if (current_token->get_token_type().compare("SEMICOLON") == 0) syntaxError("Expecting .");
    return programNode;
}

Node *Parser::parseStatement()
{

    // cout << "Call statement" << endl;
    Node *statement_node = nullptr;
    int savedLineNumber = current_token->get_line_number();
    line_number = savedLineNumber;

    if(current_token->get_token_type().compare("IDENTIFIER") == 0)
        statement_node = parseAssignmentStatement();
    else if(current_token->get_token_type().compare("BEGIN") == 0)
        statement_node = parseCompoundStatement();
    else if(current_token->get_token_type().compare("REPEAT") == 0)
        statement_node = parseRepeatStatement();
    else if(current_token->get_token_type().compare("WRITE") == 0)
        statement_node = parseWriteStatement();
    else if(current_token->get_token_type().compare("WRITELN") == 0)
        statement_node = parseWritelnStatement();
    else if(current_token->get_token_type().compare("WHILE") == 0)
        statement_node = parseWhileStatement();
    else if(current_token->get_token_type().compare("IF") == 0)
        statement_node = parseIfStatement();
    else if(current_token->get_token_type().compare("FOR") == 0)
        statement_node = parseForStatement();
    else if(current_token->get_token_type().compare("CASE") == 0)
        statement_node = parseCaseStatement();
    else if(current_token->get_token_type().compare("SEMICOLON") == 0)
        statement_node = nullptr;
    else
        syntaxError("Unexpected token");


    if (statement_node != nullptr) statement_node->lineNumber = savedLineNumber;
    return statement_node;
}

Node *Parser::parseAssignmentStatement()
{
    // cout << "call := " << endl;
    // The current token should now be the left-hand-side variable name.

    Node *assignmentNode = new Node(NodeType::ASSIGN);

    // Enter the variable name into the symbol table
    // if it isn't already in there.
    string variableName = current_token->get_text();
    SymtabEntry *variableId = symtab->find_variable(toLowerCase(variableName));
    if (variableId == nullptr) variableId = symtab->new_variable(variableName);

    // The assignment node adopts the variable node as its first child.
    Node *left_node  = new Node(NodeType::VARIABLE);
    left_node->text  = variableName;
    left_node->entry = variableId;
    assignmentNode->adopt(left_node);

    current_token = scanner->next_token();  // consume the LHS variable;

    if (current_token->get_token_type().compare("ASSIGN") == 0)
    {
        current_token = scanner->next_token();  // consume :=
    }
    else syntaxError("Missing := ok");

    // The assignment node adopts the expression node as its second child.
    Node *right_node = parseExpression();
    assignmentNode->adopt(right_node);

    return assignmentNode;
}

Node *Parser::parseCompoundStatement()
{
    // cout << "Call compound" << endl;
    Node *compoundNode = new Node(NodeType::COMPOUND);
    compoundNode->lineNumber = current_token->get_line_number();

    current_token = scanner->next_token();  // consume BEGIN
    parseStatementList(compoundNode, "END");

    if (current_token->get_token_type().compare("END") == 0)
    {
        current_token = scanner->next_token();  // consume END
    }
    else syntaxError("Expecting END");

    return compoundNode;
}

void Parser::parseStatementList(Node *parentNode, string terminalType)
{

    // cout << "Call statementlist" << endl;
    while (   (current_token->get_token_type().compare(terminalType) != 0)
           && (current_token->get_token_type().compare("END_OF_FILE") != 0))
    {
        Node *stmtNode = parseStatement();
        if (stmtNode != nullptr) parentNode->adopt(stmtNode);

        // A semicolon separates statements.
        if (current_token->get_token_type().compare("SEMICOLON") == 0)
        {
            while (current_token->get_token_type().compare("SEMICOLON") == 0)
            {
                current_token = scanner->next_token();  // consume ;
            }
        }
        else if (starting_token.find(current_token->get_token_type()) !=
                                                        starting_token.end())
        {
            syntaxError("Missing ;");
        }
    }
}



Node *Parser::parseRepeatStatement()
{
    // cout << "Call repeat" << endl;
    // The current token should now be REPEAT.

    // Create a LOOP node.
    Node *loopNode = new Node(NodeType::LOOP);
    current_token = scanner->next_token();  // consume REPEAT

    parseStatementList(loopNode, "UNTIL");

    if (current_token->get_token_type().compare("UNTIL") == 0)
    {
        // Create a TEST node. It adopts the test expression node.
        Node *testNode = new Node(NodeType::TEST);
        line_number = current_token->get_line_number();
        testNode->lineNumber = line_number;
        current_token = scanner->next_token();  // consume UNTIL

        testNode->adopt(parseExpression());

        // The LOOP node adopts the TEST node as its final child.
        loopNode->adopt(testNode);
    }
    else syntaxError("Expecting UNTIL");

    return loopNode;
}

Node *Parser::parseWriteStatement()
{
    // The current token should now be WRITE.
    // cout << "Call write" << endl;

    // Create a WRITE node-> It adopts the variable or string node.
    Node *writeNode = new Node(NodeType::WRITE);
    current_token = scanner->next_token();  // consume WRITE

    parseWriteArguments(writeNode);
    if (writeNode->node_container.size() == 0)
    {
        syntaxError("Invalid WRITE statement");
    }

    return writeNode;
}

Node *Parser::parseWritelnStatement()
{
    // The current token should now be WRITELN.
    // cout << "Call writeln" << endl;
    // Create a WRITELN node. It adopts the variable or string node.
    Node *writelnNode = new Node(NodeType::WRITELN);
    current_token = scanner->next_token();  // consume WRITELN

    if (current_token->get_token_type().compare("LPAREN") == 0) parseWriteArguments(writelnNode);
    return writelnNode;
}

void Parser::parseWriteArguments(Node *node)
{
    // The current token should now be (
    // cout << "Call write arg" << endl;

    bool hasArgument = false;

    if (current_token->get_token_type().compare("LPAREN") == 0)
    {
        current_token = scanner->next_token();  // consume (
    }
    else syntaxError("Missing left parenthesis");

    if (current_token->get_token_type().compare("IDENTIFIER") == 0)
    {
        node->adopt(parseVariable());
        hasArgument = true;
    }
    else if (   (current_token->get_token_type().compare("CHARACTER") == 0)
             || (current_token->get_token_type().compare("STRING") == 0))
    {
        node->adopt(parseStringConstant());
        hasArgument = true;
    }
    else syntaxError("Invalid WRITE or WRITELN statement");

    // Look for a field width and a count of decimal places.
    if (hasArgument)
    {
        if (current_token->get_token_type().compare("COLON") == 0)
        {
            current_token = scanner->next_token();  // consume ,

            if (current_token->get_token_type().compare("INTEGER") == 0)
            {
                // Field width
                node->adopt(parseIntegerConstant());

                if (current_token->get_token_type().compare("COLON") == 0)
                {
                    current_token = scanner->next_token();  // consume ,

                    if (current_token->get_token_type().compare("INTEGER") == 0)
                    {
                        // Count of decimal places
                        node->adopt(parseIntegerConstant());
                    }
                    else syntaxError("Invalid count of decimal places");
                }
            }
            else syntaxError("Invalid field width");
        }
    }

    if (current_token->get_token_type().compare("RPAREN") == 0)
    {
        current_token = scanner->next_token();  // consume )
    }
    else syntaxError("Missing right parenthesis");
}

Node *Parser::parseExpression()
{
    // The current token should now be an identifier or a number.

    // cout << "Call expression" << endl;

    // The expression's root node->
    Node *exprNode = parseSimpleExpression();

    // The current token might now be a relational operator.
    if (relation_op_token.find(current_token->get_token_type()) != relation_op_token.end())
    {
        string tokenType = current_token->get_token_type();
        Node *opNode = tokenType == "EQUAL"    ?     new Node(NodeType::EQ)
                    : tokenType == "LT" ?      new Node(NodeType::LT)
                    : tokenType == "GT" ?   new Node(NodeType::GT)            //add more node for relationalOperatior
                    : tokenType == "GTEQ" ? new Node(NodeType::GE)
                    : tokenType == "LTEQ" ?    new Node(NodeType::LE)
                    : tokenType == "NE" ?     new Node(NodeType::NE)
                    :                               nullptr;

        current_token = scanner->next_token();  // consume relational operator

        // The relational operator node adopts the first simple expression
        // node as its first child and the second simple expression node
        // as its second child. Then it becomes the expression's root node.
        if (opNode != nullptr)
        {
            opNode->adopt(exprNode);
            opNode->adopt(parseSimpleExpression());
            exprNode = opNode;
        }
    }

    return exprNode;
}

Node *Parser::parseSimpleExpression()
{
    // The current token should now be an identifier or a number.

    // cout << "Call simple expression" << endl;
    // The simple expression's root node->
    Node *simpExprNode = parseTerm();

    // Keep parsing more terms as long as the current token
    // is a + or - operator.
    while (expression_op_token.find(current_token->get_token_type()) != expression_op_token.end())
    {
        Node *opNode = current_token->get_token_type().compare("PLUSOP") == 0 ?     new Node(NodeType::ADD)
                     : current_token->get_token_type().compare("MINUSOP") == 0 ?    new Node(NodeType::SUBTRACT)
                     : current_token->get_token_type().compare("OR") == 0 ?      new Node(NodeType::OR_NODE)            //add or
                     : nullptr;


        current_token = scanner->next_token();  // consume the operator

        // The add or subtract node adopts the first term node as its
        // first child and the next term node as its second child.
        // Then it becomes the simple expression's root node.
        opNode->adopt(simpExprNode);
        opNode->adopt(parseTerm());
        simpExprNode = opNode;
    }

    return simpExprNode;
}

Node *Parser::parseTerm()
{
    // The current token should now be an identifier or a number.

    // cout << "Call Term" << endl;
    // The term's root node->
    Node *termNode = parseFactor();

    // Keep parsing more factors as long as the current token
    // is a * or / operator.
    while (term_op_token.find(current_token->get_token_type()) != term_op_token.end())
    {
        Node *opNode = current_token->get_token_type().compare("MULTOP") == 0 ? new Node(NodeType::MULTIPLY)
                    : current_token->get_token_type().compare("DIVOP") == 0 ? new Node(NodeType::DIVIDE)               //add DIV and AND
                    : current_token->get_token_type().compare("AND") == 0   ? new Node(NodeType::AND_NODE)
                    : nullptr;

        current_token = scanner->next_token();  // consume the operator
        // The multiply or divide node adopts the first factor node as its
        // as its first child and the next factor node as its second child.
        // Then it becomes the term's root node.


        opNode->adopt(termNode);
        opNode->adopt(parseFactor());
        termNode = opNode;
    }

    return termNode;
}

Node *Parser::parseFactor()
{
    // The current token should now be an identifier or a number or (

    // cout << "Call Factor" << endl;

    if      (current_token->get_token_type().compare("IDENTIFIER") == 0) return parseVariable();
    else if (current_token->get_token_type().compare("INTEGER") == 0)    return parseIntegerConstant();
    else if (current_token->get_token_type().compare("REAL") == 0)       return parseRealConstant();
    else if (current_token->get_token_type().compare("NOT") == 0)        return parseNot();

    else if (current_token->get_token_type().compare("LPAREN") == 0)
    {
        current_token = scanner->next_token();  // consume (
        Node *exprNode = parseExpression();

        if (current_token->get_token_type().compare("RPAREN") == 0)
        {
            current_token = scanner->next_token();  // consume )
        }
        else syntaxError("Expecting )");

        return exprNode;
    }
    else if (current_token->get_token_type().compare("MINUSOP") == 0)                   //In the case of negative number
    {
        current_token = scanner->next_token();                // consume MINUS
        Node *exprNode = new Node(NodeType::NEGATIVE);
        exprNode->adopt(parseExpression());
        return exprNode;
    }


    else syntaxError("Unexpected token");
    return nullptr;
}

Node *Parser::parseVariable()
{
    // The current token should now be an identifier.

    // cout << "Call variable" << endl;
    // Has the variable been "declared"?
    string variableName = current_token->get_text();
    SymtabEntry *variableId = symtab->find_variable(toLowerCase(variableName));
    if (variableId == nullptr) semanticError("Undeclared identifier");

    Node *node  = new Node(NodeType::VARIABLE);
    node->text  = variableName;
    node->entry = variableId;

    current_token = scanner->next_token();  // consume the identifier
    return node;
}

Node *Parser::parseIntegerConstant()
{
    // The current token should now be a number.

    // cout << "Call int cont=st" << endl;

    Node *integerNode = new Node(NodeType::INTEGER_CONSTANT);
    integerNode->value = stoi(current_token->get_text());

    current_token = scanner->next_token();  // consume the number
    return integerNode;
}

 Node *Parser::parseRealConstant()
 {
     // The current token should now be a number.

     // cout << "Call real double" << endl;

     Node *realNode = new Node(NodeType::REAL_CONSTANT);
     realNode->value = stoi(current_token->get_text());

     current_token = scanner->next_token();  // consume the number
     return realNode;
 }

 Node *Parser::parseStringConstant()
 {
     // The current token should now be string.

     // cout << "Call string const" << endl;

     Node *stringNode = new Node(NodeType::STRING_CONSTANT);
     stringNode->string_value = current_token->get_text();

     current_token = scanner->next_token();  // consume the string
     return stringNode;
 }

void Parser::syntaxError(string message)
{
    printf("SYNTAX ERROR at line %d: %s at '%s'\n",
           line_number, message.c_str(), current_token->get_text().c_str());
    error_count++;

    // Recover by skipping the rest of the statement.
    // Skip to a statement follower token.
    while (follow_token.find(current_token->get_token_type()) ==
                                                    follow_token.end())
    {
        current_token = scanner->next_token();
    }
}

void Parser::semanticError(string message)
{
    printf("SEMANTIC ERROR at line %d: %s at '%s'\n",
           line_number, message.c_str(), current_token->get_text().c_str());
    error_count++;
}

//added

Node *Parser::parseForStatement()
{

    // cout << "Call for" << endl;
	Node *forNode = new Node(NodeType::FOR_LOOP);                                         //Create for loop node
    Node *loopNode = new Node(NodeType::LOOP);                                            //Create loop node
	current_token = scanner->next_token();                                        //consume FOR

	forNode->adopt(parseAssignmentStatement());                           //adopt the statement as the first child
    Node *opNode1 = current_token->get_token_type().compare("TO") == 0     ? new Node(NodeType::LE)                //Create the node base on the statement are TO or DOWNTO
                                              : new Node(NodeType::GE);                  // to compare the counter

    Node *opNode2 = current_token->get_token_type().compare("TO") == 0     ? new Node(NodeType::UP)                //Create the node base on the statement are TO or DOWNTO
                                                 : new Node(NodeType::DOWN);            //to increase or decrease the counter


    opNode1->adopt(forNode->node_container[0]->node_container[0]);                  //adopt the variable in to the node for compare
    current_token = scanner->next_token();
    opNode1->adopt(parseIntegerConstant());                             //adopt the target number to compare

    opNode2->adopt(opNode1->node_container[0]);                               //adopt the variable to increase or decrease



    //Create test node to test the condition
    Node *testNode = new Node(NodeType::TEST);
    testNode->lineNumber = line_number;
    Node *notNode = new Node(NodeType::NOT_NODE);
    notNode->adopt(opNode1);
    testNode->adopt(notNode);
    loopNode->adopt(testNode);

    if (current_token->get_token_type().compare("DO") == 0)                               //Chech whether the DO exist
    {
        current_token = scanner->next_token();                    // consume DO
        if (current_token->get_token_type().compare("BEGIN") == 0)                        // Check whether it a compound or single statement
        {
            loopNode->adopt(parseCompoundStatement());
        }
        else
        {
            loopNode->adopt(parseStatement());
        }
    }
    else syntaxError("Expecting DO");
    //Adopt the assignNode as the last childrent of loopNode to increase or decrease the counter after each loop
    loopNode->adopt(opNode2);
    forNode->adopt(loopNode);

    return forNode;

}

Node *Parser::parseWhileStatement()
{
    // The current node should now be WHILE
    // Create a LOOP node

    // cout << "Call while" << endl;
    Node *loopNode = new Node(NodeType::LOOP);
    current_token = scanner->next_token(); // consume WHILE

    // Create a TEST node -> it adopts test expression node
    Node *testNode = new Node(NodeType::TEST);
    Node *notNode = new Node(NodeType::NOT_NODE);                     //Create not node for testing purpose
    line_number = current_token->get_line_number();
    testNode->lineNumber = line_number;
    notNode->adopt(parseExpression());
    testNode->adopt(notNode);
    loopNode->adopt(testNode);


    if (current_token->get_token_type().compare("DO") == 0)
    {
        current_token = scanner->next_token();                // consume DO
        if (current_token->get_token_type().compare("BEGIN") == 0)
        {
            loopNode->adopt(parseCompoundStatement());
        }
        else
        {
            loopNode->adopt(parseStatement());
        }
    }
    else syntaxError("Expecting DO");

    return loopNode;

}

Node *Parser::parseIfStatement()
{

    // cout << "Call if" << endl;
    Node *ifNode = new Node(NodeType::CONDITION);
    current_token = scanner->next_token();                               // consume IF

    // Create a TEST node -> it adopts test expression node
    Node *testNode = new Node(NodeType::TEST);
    line_number = current_token->get_line_number();
    testNode->lineNumber = line_number;
    testNode->adopt(parseExpression());
    ifNode->adopt(testNode);
    if(current_token->get_token_type().compare("THEN") == 0)
    {
        current_token = scanner->next_token();                            // consume THEN
        Node *trueNode = new Node(NodeType::TRUE_STATEMENT);
        if (current_token->get_token_type().compare("BEGIN") == 0) {                              // Check whether it a compound or single statement
            trueNode->adopt(parseCompoundStatement());
        } else {
            trueNode->adopt(parseStatement());
        }
        ifNode->adopt(trueNode);

        if (current_token->get_token_type().compare("ELSE") == 0)                                 //Check if the else statement exist
        {
            current_token = scanner->next_token(); // consume ELSE
            Node *falseNode = new Node(NodeType::FALSE_STATEMENT);
            if (current_token->get_token_type().compare("BEGIN") == 0)                            // Check whether it a compound or single statement
            {
                falseNode->adopt(parseCompoundStatement());
            }
            else
            {
                falseNode->adopt(parseStatement());
            }
            ifNode->adopt(falseNode);
        }
    }
    else syntaxError("Expecting THEN");                         //Raise error if missing THEN

    return ifNode;
}

Node *Parser::parseNot()                                                //parse for a not statement
{

    // cout << "Call not" << endl;
    Node *notNode = new Node(NodeType::NOT_NODE);
    current_token = scanner->next_token();
    notNode->adopt(parseExpression());
    return notNode;
}

Node *Parser::parseCaseStatement()
{

    // cout << "Call case" << endl;
    Node *caseNode = new Node(NodeType::CASE_STATEMENT);
    current_token = scanner->next_token();                        //consume CASE
    caseNode->adopt(parseExpression());
    if(current_token->get_token_type().compare("OF") == 0)
    {
        current_token = scanner->next_token();                    //Consume OF
        while(current_token->get_token_type().compare("END") != 0)                        //Read until meet the END of CASE
        {
            Node *listNode = new Node(NodeType::LIST);                    //Create list node
            while(current_token->get_token_type().compare("COLON") != 0)
            {
                listNode->adopt(parseFactor());            //adopt all the integer of the case
                if(current_token->get_token_type().compare("COLON") == 0)                 //reach COLON, fishish reading all number of the case
                    break;
                else
                    current_token = scanner->next_token();

            }
            current_token = scanner->next_token();                    //Consume COLON

            if (current_token->get_token_type().compare("BEGIN") == 0)                        // Check whether it a compound or single statement
            {                                                       //Adopt the statement node as the last child of listNode
                listNode->adopt(parseCompoundStatement());
            }
            else
            {
                listNode->adopt(parseStatement());
            }
            if(current_token->get_token_type().compare("SEMICOLON") == 0)
                current_token = scanner->next_token();
            caseNode->adopt(listNode);
        }
        if (current_token->get_token_type().compare("END") == 0)                              //Check if END exist as the end of CASE statement
        {
            current_token = scanner->next_token();                        // consume END
        }
        else syntaxError("Expecting END");                  // if not raise error
    }
    else syntaxError("Expecting OF");
    return caseNode;
}
