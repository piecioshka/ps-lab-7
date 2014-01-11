CC = gcc
CFLAGS = -Wall -Werror -pedantic -pedantic-errors
TARGET = bin/
SRC = source/

zad1:
	${CC} ${CFLAGS} ${SRC}$@/pipedemo.c -o ${TARGET}$@/pipedemo.o

zad2:
	${CC} ${CFLAGS} ${SRC}$@/simpleredirect.c -o ${TARGET}$@/simpleredirect.o

zad3:
	${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

zad4:
	#${CC} ${CFLAGS} ${SRC}$@/shell.c -o ${TARGET}$@/shell.o

zad5:
	#${CC} ${CFLAGS} ${SRC}$@/raise.c -o ${TARGET}$@/raise.o

zad6:
	#${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

zad7:
	#${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

zad8:
	#${CC} ${CFLAGS} ${SRC}$@/main.c -o ${TARGET}$@/main.o

clean:
	find . -name "*.o" | xargs rm

