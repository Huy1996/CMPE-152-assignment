//
// Created by Huy Duong on 9/1/22.
//

#ifndef CMPE152_ASSIGNMENT2_SOURCE_H
#define CMPE152_ASSIGNMENT2_SOURCE_H

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Source
{
private:
    ifstream source;
    string line;
    int line_number;
    int line_pos;
    char currentCh;

public:
    static const char EOL = '\n';

    Source(string sourceFileName) : line_number(0), line(""), line_pos(-1), currentCh(0)
    {
        source.open(sourceFileName);

        if (source.fail())
        {
            cout << "*** ERROR: Failed to open " << sourceFileName << endl;
            exit(-1);
        }
        currentCh = nextChar();
    }


    int lineNumber() const { return line_number; }

    char currentChar() const { return currentCh; }

    bool is_fail() const { return source.fail(); }

    char nextChar() {
        currentCh = source.get();

        if (source.eof()) currentCh = EOF;
        else if (currentCh == EOL) line_number++;

        else if (source.fail())
        {
            cout << "*** ERROR: Failed to read " << endl;
            exit(-1);
        }

        return currentCh;
    }
};


#endif //CMPE152_ASSIGNMENT2_SOURCE_H
