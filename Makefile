CC = gcc
CFLAGS = -Wall -pedantic -ansi -lncurses

all: game

snake: snake.c
	${CC} ${CFLAGS} -g -o snake snake.c

snake-editor: snake-edit.c
	${CC} ${CFLAGS} -g -o snake-editor snake-edit.c
	
# game: utils.o
# 	${cc} ${CFLAGS} -g -o game game.c utils.o
#
# utils.o: utils.h
# 	${cc} ${CFLAGS} -g -c -o utils.o utils.c
#
# player.o: player.h
# 	${cc} ${CFLAGS} -g -c -o utils.o utils.c

.PHONY clean:
	-rm game *.o
