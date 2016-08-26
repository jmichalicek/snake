CC = gcc
CFLAGS = -Wall -pedantic -ansi -lcurses

all: snake snake-editor

snake: snake.o
	${CC} ${CFLAGS} -g -o snake snake.o

snake.o: snake.c
	${CC} ${CFLAGS} -c snake.c

snake-editor: snake-edit.o
	${CC} ${CFLAGS} -g -o snake-editor snake-edit.o

snake-edit.o: snake-edit.c
	${CC} ${CFLAGS} -c snake-edit.c

.PHONY: clean

clean:
	-rm snake snake-editor *.o
