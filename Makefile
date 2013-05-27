EXEC=dominos
CC=gcc
CFLAGS=-ansi -pedantic -Wall -O1 -lm -g
DEPS=list.h stack.h tarjan.h testcase.h util.h
OBJ=dominos.o list.o stack.o tarjan.o testcase.o

default: $(EXEC)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

test: default
	./runtests.sh

clean:
	$(RM) -rf *.o $(EXEC) *.diff *.out $(EXEC).dSYM
