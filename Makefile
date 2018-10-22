PROG = main
CC = g++
FLAGS = --std=c++11 -g -Wall
OBJS = polynomial.o monomial.o main.o
LIB = polynomial.lib

$(PROG) : $(OBJS)
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)
	make clean
main.o : polynomial.o monomial.o
	$(CC) $(FLAGS) -c main.cpp
polynomial.o : polynomial.h
	$(CC) $(FLAGS) -c polynomial.cpp
monomial.o : monomial.h
	$(CC) $(FLAGS) -c monomial.cpp
clean:
	rm -f $(OBJS)
