GCC=g++ -std=c++11
FRONTEND=./frontend

.PHONY: all
all: Token.o Scanner.o main.o main.exe

test: test-in.txt main.exe
	./main.exe test-in.txt > test-out.txt

main.exe: Scanner.o Token.o main.o
	$(GCC) Scanner.o Token.o main.o -o $@

main.o: main.cpp
	$(GCC) -c main.cpp

Scanner.o: $(FRONTEND)/Scanner.cpp $(FRONTEND)/Scanner.h $(FRONTEND)/Source.h
	$(GCC) -c $(FRONTEND)/Scanner.cpp

Token.o: $(FRONTEND)/Token.cpp $(FRONTEND)/Token.h
	$(GCC) -c $(FRONTEND)/Token.cpp
clean:
	rm *.o *.exe

