#include <iostream>
#include "frontend/Scanner.h"
#include "frontend/Source.h"
#include "frontend/Parser.h"
#include "intermediate/Node.h"
#include "intermediate/TreeWalker.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc < 2){
        cout << "Missing argument" << endl;
        exit(0);
    }

    string sourceFileName = argv[1];
    Source *source = new Source(sourceFileName);

    cout << "---------Team 5----------" << endl;
    cout << "Member: " << endl;
    cout << "\t\tChavez, Alberto Francisco" << endl;
    cout << "\t\tDuong, Nguyen Minh Huy" << endl;
    cout << "\t\tFitzgerald, Daniel" << endl << endl;

    Scanner *scanner = new Scanner(source);  // create the scanner
    Symtab *symtab = new Symtab();
    
    Parser *parser = new Parser(scanner, symtab);
    Node *program = parser->parseProgram();
    int error = parser->get_error();

    if(error == 0){
        cout << "Parse tree:" << endl << endl;
        TreeWalker *walk = new TreeWalker();
        walk->print(program);
    }
    else{
        cout << endl << "There were " << error << " errors." << endl;
    }

    return 0;
}
