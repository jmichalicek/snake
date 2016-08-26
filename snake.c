#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>

#define printf printw
#define getchar getch

#define XSIZE 24
#define YSIZE 50
#define MAX_SNAKE_LENGTH 100

struct player {
    int score;
    int length;
};

typedef struct player player;

void redraw(int [XSIZE][YSIZE], const int, const int);
void makeMouse(int [XSIZE][YSIZE], int *);
int moveSnake(int [XSIZE][YSIZE], int [2][MAX_SNAKE_LENGTH], int, int *, int *, int *);
int getScores(const int);
void saveScores(const int, const int);
void gameOver();
void titleScreen();
int makeLevel(int [XSIZE][YSIZE], int [2][MAX_SNAKE_LENGTH], int *, int *);


int main() {
    int game[XSIZE][YSIZE] =
        {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};
    int go = 3;
    int go2 = 3;
    int speed = 2;
    int mouse = 0;
    player snake = {0, 5};
    int coords[2][100] = {{12}, {25}};
    int alive = 0;
    int level = 0;
    int levelMade;

    FILE *savePos;

    WINDOW *myWindow = initscr();
    noecho();
    titleScreen();
    keypad(myWindow, TRUE);
    halfdelay(speed);

     /*open the .save file, check the last position of the snake.
    in future will be used for saving the last score and high score*/

    /* end file open*/

    /*draw playfield for first time*/
    game[12][25] = 2;

    levelMade = makeLevel(game, coords, &snake.length, &level);
    if (levelMade != 0) {
        endwin();
        return 0;
    }
    redraw(game, snake.length, snake.score);

    /*get user input for which direction to go*/
    while ( go != 'q' && alive == 0) {
        go = getch();
        if (go == ERR) {
            go = go2;
        }

        if (snake.length == 100) {
            levelMade = makeLevel(game, coords, &snake.length, &level);
            if (levelMade != 0) {
                endwin();
                return 0;
            }
        }

        /* if mouse == 0 (no mouse exists), check to see if a mouse appears*/
        if (mouse == 0) {
            makeMouse(game, &mouse);
        }

        /* update the position of the snake */

        alive = moveSnake(game, coords, go, &snake.length, &snake.score, &mouse);
        if (alive == 1) {
            gameOver();
        }

        /* draw the playfield with any changes due to movement of snake, new
        mouse, etc*/
        if(alive == 0) {
            redraw(game, snake.length, snake.score);
        }
        go2 = go;
    }

    /*open .save file to save scores*/
    saveScores(snake.length, snake.score);
    endwin();
    return 0;
}


int moveSnake(int board[XSIZE][YSIZE], int coords[2][MAX_SNAKE_LENGTH], int go, int *length, int *score, int *mouse) {
    int oldX = coords[0][*length - 1];
    int oldY = coords[1][*length - 1];
    int i;
    int hold;
    int alive = 0;

    /*figure out which way snake moves, update the array to match*/
    switch (go) {
        case KEY_UP:
            if (board[coords[0][0] - 1][coords[1][0]] != 1) {
                if (board[coords[0][0] - 1][coords[1][0]] == 3) {
                    *score = *score + 1;
                    *length = *length + 5;
                    *mouse = 0;
                }
                hold = (coords[0][0] - 1);
            }
            if (board[coords[0][0] - 1][coords[1][0]] == 1 ||
                board[coords[0][0] - 1][coords[1][0]] == 2) {
                    alive = 1;
            }
            break;
        case KEY_DOWN:
            if (board[coords[0][0] + 1][coords[1][0]] != 1) {
                if (board[coords[0][0] + 1][coords[1][0]] == 3) {
                    *score = *score + 1;
                    *length = *length + 5;
                    *mouse = 0;
                }
                hold = coords[0][0] + 1;
            }
            if (board[coords[0][0] + 1][coords[1][0]] == 1 ||
                board[coords[0][0] + 1][coords[1][0]] == 2) {
                    alive = 1;
            }
            break;
        case KEY_LEFT:
            if (board[coords[0][0]][coords[1][0] - 1] != 1) {
                if (board[coords[0][0]][coords[1][0] - 1] == 3) {
                    *score = *score + 1;
                    *length = *length + 5;
                    *mouse = 0;
                }
                hold = coords[1][0] - 1;
            }
            if (board[coords[0][0]][coords[1][0] - 1] == 1 ||
                board[coords[0][0]][coords[1][0] - 1] == 2) {
                    alive = 1;
            }
            break;
        case KEY_RIGHT:
            if (board[coords[0][0]][coords[1][0] + 1] != 1) {
                if (board[coords[0][0]][coords[1][0] + 1] == 3) {
                    *score = *score + 1;
                    *length = *length + 5;
                    *mouse = 0;
                }
                hold = coords[1][0] + 1;
            }
            if (board[coords[0][0]][coords[1][0] + 1] == 1 ||
                board[coords[0][0]][coords[1][0] + 1] == 2) {
                    alive = 1;
            }
            break;
        default:
            break;
    }

    if (alive != 1) {
        for (i = *length - 1; i > 0; i--) {
            coords[0][i] = coords[0][i - 1];
            coords[1][i] = coords[1][i - 1];
        }

        if (go == KEY_UP || go == KEY_DOWN) {
            coords[0][0] = hold;
        }
        if (go == KEY_LEFT || go == KEY_RIGHT) {
            coords[1][0] = hold;
        }
        /* figure out how to move the body of the snake*/
        board[oldX][oldY] = 0;

        for (i = 0; i < *length; i++) {
            board[coords[0][i]][coords[1][i]] = 2;
        }
    }
    return alive;
}


void makeMouse(int board[XSIZE][YSIZE], int *mouse) {
    int newMouse;
    int x;
    int y;
    int done = 1;

    srand(time(NULL));
    newMouse = (rand() % 10 + 1);

    if (newMouse < 8) {
        while (done == 1) {
            x = (rand() % (XSIZE-2) + 1);
            y = (rand() % (YSIZE-2) + 1);
            if(board[x][y] != 1 && board[x][y] != 2) {
                board[x][y] = 3;
                *mouse = 1;
                done = 0;
            }
        }
    }
    return;
}


void redraw(int board[XSIZE][YSIZE], const int length, const int score) {
    int i;
    int i2;

    clear();

    for (i = 0; i < XSIZE; i++) {
        for (i2 = 0; i2 < YSIZE; i2++) {
            switch(board[i][i2]) {
                case 0:
                    printw(" ");
                    break;
                case 1:
                    printw("*");
                    break;
                case 2:
                    printw("&");
                    break;
                case 3:
                    printw("M");
                    break;
            }
        }
        printw("\n");
    }

    printw("Score: %d \t\t\t Length: %d", score, length);
    return;
}


void saveScores(const int length, const int score) {
    FILE *saveFile;

    if ((saveFile = fopen(".snakeSave", "w")) == NULL) {
        printw("Could not save data.\n");
    } else {
        fprintf(saveFile, "%d %d\n", length, score);
        fclose(saveFile);
    }

    return;
}


int getScores(const int which) {
    FILE *saveFile;
    int length;
    int score;

    if ((saveFile = fopen(".snakeSave", "r")) == NULL) {
        printw("Unable to open score file.\n");
    } else {
        fscanf(saveFile, "%d %d", &length, &score);
        fclose(saveFile);
    }

    if (which == 0) {
        return length;
    } else {
        return score;
    }
}


void gameOver() {
    clear();
    printw("Game Over!\n");
}


void titleScreen() {
    int high;
    int length;
    char cont;

    high = getScores(1);
    length = getScores(0);
    clear();
    printw("SNAKE!\n\n");
    printw("Last Score: %d \t\t\t Last Length: %d\n\n", high, length);
    printw("Try to eat the Mouse (M), don't run into walls or yourself!\n\n\n");
    printw("Press a key to start playing!\n");

    cont = getch();

    return;
}


int makeLevel(int board[XSIZE][YSIZE], int coords[2][100], int *length, int *level) {
    FILE *levelFile;
    int i;
    int i2;
    int board2[1200];
    int m = 0;
    int thing;

    *level = *level + 1;
    thing = *level;

    if ((levelFile = fopen("levels.dat", "r")) == NULL) {
        printw("Could not open level database.\n");
        return 1;
    } else {
        if (thing == 1) {
            fseek(levelFile, 0, SEEK_SET);
        } else {
            fseek(levelFile, (thing * sizeof(board2)) - 1, SEEK_SET);
        }
        fread(board2, sizeof(board2), 1, levelFile);
        for (i = 0; i < 24; i++) {
            for (i2 = 0; i2 < 50; i2++) {
                board[i][i2] = board2[m];
                m++;
            }
        }
    }
    fclose(levelFile);

    for (i = 99; i >= 0; i--) {
        coords[0][i] = 0;
        coords[1][i] = 0;
    }
    coords[0][0] = 12;
    coords[1][0] = 25;
    *length = 5;
    return 0;
}
