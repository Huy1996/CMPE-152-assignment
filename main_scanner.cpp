#include <iostream>
#include "frontend/Scanner.h"
#include "frontend/Source.h"

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
    for (Token *token = scanner->next_token();
         token->get_token_type().compare("END_OF_FILE") != 0;
         token = scanner->next_token())
    {
        printf("%14s : %s\n",
               token->get_token_type().c_str(),
               token->get_text().c_str());
    }

    return 0;
}
