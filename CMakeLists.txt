cmake_minimum_required(VERSION 3.19)
project(Team5_Assignment2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Team5_Assignment2_Parser main_parser.cpp frontend/Source.h frontend/Token.cpp frontend/Token.h
        frontend/Scanner.cpp frontend/Scanner.h frontend/Parser.cpp frontend/Parser.h intermediate/Node.h
        intermediate/Symtab.h intermediate/SymtabEntry.h intermediate/TreeWalker.cpp intermediate/TreeWalker.h
)

add_executable(Team5_Assignment2_Scanner main_scanner.cpp frontend/Source.h frontend/Token.cpp frontend/Token.h
        frontend/Scanner.cpp frontend/Scanner.h)