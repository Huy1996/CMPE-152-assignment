//
// Created by Huy Duong on 9/1/22.
//

#include "Scanner.h"


Token *Scanner::next_token() {

    char ch = next_available_char();

    Token* token = new Token(source->lineNumber());

    if (ch == EOF){
        token->end_of_file();
        return token;
    };

    while(true){
        token->scan(ch);
        if (token->is_done()) break;
        ch = source->nextChar();
    }

    return token;
}

// void Scanner::scan() throw(std::string) {
//     ch = source->nextChar();

//     while (!source->is_fail()){
//         Token *token = next_token();

//         if (token->get_text() != ""){
//             cout << "=> \"" << token->get_text() << "\" ";
//             cout << token->get_token_type() << endl;
//         }
//     }
// }

char Scanner::next_available_char() {
    char ch = source->currentChar();

    while ((ch == '{') || isspace(ch) || int(ch) == 0)
    {
        if (ch == '{')
        {
            while ((ch != '}') && (ch != EOF)) ch = source->nextChar();
        }

        ch = source->nextChar();  // consume character
    }

    return ch;
}