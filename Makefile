GCC=g++ -std=c++11
FRONTEND=./frontend
INTERMEDIATE=./intermediate

.PHONY: all
all: Token.o Scanner.o main.o main.exe

test_scanner: test-in.txt main_scanner.exe
	./main.exe test-in.txt > test-out.txt

main_scanner.exe: Scanner.o Token.o main_scanner.o
	$(GCC) Scanner.o Token.o main_scanner.o -o $@
	
main_parser.exe: Scanner.o Token.o main_parser.o Parser.o TreeWalker.o
	$(GCC) Scanner.o Token.o main_parser.o Parser.o TreeWalker.o -o $@

main_parser.o: main_parser.cpp
	$(GCC) -c main_parser.cpp

main_scanner.o: main_scanner.cpp
	$(GCC) -c main_scanner.cpp

TreeWalker.o: $(INTERMEDIATE)/TreeWalker.h INTERMEDIATE/TreeWalker.cpp
	$(GCC) -c $(INTERMEDIATE)/TreeWalker.cpp

Parser.o: Scanner.o $(FRONTEND)/Parser.cpp $(FRONTEND)/Parser.h
	$(GCC) -c $(FRONTEND)/Parser.cpp

Scanner.o: $(FRONTEND)/Scanner.cpp $(FRONTEND)/Scanner.h $(FRONTEND)/Source.h
	$(GCC) -c $(FRONTEND)/Scanner.cpp

Token.o: $(FRONTEND)/Token.cpp $(FRONTEND)/Token.h helper.h
	$(GCC) -c $(FRONTEND)/Token.cpp
	
clean:
	rm *.o *.exe