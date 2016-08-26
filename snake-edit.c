#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define XSIZE 24
#define YSIZE 50

#define CURSOR_STRING "+"
#define WALL_STRING "*"
#define OPEN_STRING " "

#define WALL_BOARD_IDENTIFIER 1
#define OPEN_BOARD_IDENTIFIER 0

void redraw(int [XSIZE][YSIZE], const int, const int);
void modifyArray(int [XSIZE][YSIZE], int, int *, int *);
void saveMap(int [XSIZE][YSIZE]);

int main() {
    int x = 12;
    int y = 25;
    int board[XSIZE][YSIZE] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

    char move = '\0';
    WINDOW *myWindow = initscr();
    cbreak();
    noecho();
    keypad(myWindow, TRUE);

    redraw(board, x, y);

    while (move != 'q') {
        move = getch();
        modifyArray(board, move, &x, &y);
        redraw(board, x, y);
    }
    endwin();
    return 0;
}


void redraw(int board[24][50], const int x, const int y) {
    int i;
    int i2;
    clear();

    for (i = 0; i < 24; i++) {
        for (i2 = 0; i2 < 50; i2++) {
            if (board[i][i2] == WALL_BOARD_IDENTIFIER) {
                if (i != (x - 1) || i2 != (y - 1)) {
                    printw(WALL_STRING);
                }
            }
            if (board[i][i2] == OPEN_BOARD_IDENTIFIER) {
                if (i != (x - 1) || i2 != (y - 1)) {
                    printw(OPEN_STRING);
                }
            }
            if ((i == (x - 1)) && (i2 == (y - 1))) {
                printw(CURSOR_STRING);
            }

        }
        printw("\n");
    }
    return;
}


void modifyArray(int board[XSIZE][YSIZE], int move, int *x, int *y) {
    switch (move) {
        case KEY_UP:
            *x = *x - 1;
            break;
        case KEY_DOWN:
            *x = *x + 1;
            break;
        case KEY_LEFT:
            *y = *y - 1;
            break;
        case KEY_RIGHT:
            *y = *y + 1;
            break;
        case 'a':
            if (board[*x - 1][*y - 1] == WALL_BOARD_IDENTIFIER) {
                board[*x - 1][*y - 1] = 0;
            } else {
                board[*x - 1][*y - 1]  = WALL_BOARD_IDENTIFIER;
            }
            break;
        case 's':
            saveMap(board);
            break;
        default:
            break;
    }
  return;
}

void saveMap(int board[XSIZE][YSIZE]) {
    FILE *saveFile;
    int i;
    int i2;
    int m = 0;
    int save;
    char option;
    char fileName;
    int level[1200];

    for (i = 0; i < 24; i++) {
        for (i2 = 0; i2 < 50; i2++) {
            level[m] = board[i][i2];
            m++;
        }
    }

    clear();
    printw("(A)dd to levels.dat or Save to (n)ew file?\n");
    option = getch();

    echo();

    switch(option) {
        case 'a':
            printw("What level is this (however many you currently have plus 1): ");
            scanw("%d", &save);
            printw("\n");

            if ((saveFile = fopen("levels.dat", "a+")) == NULL) {
                printw("Could not open levels.dat\n");
            } else {
                save--;
                fseek(saveFile, (save * sizeof(level)) - 1, SEEK_SET);
                fwrite(level, sizeof(level), 1, saveFile);
                fclose(saveFile);
            }
            break;
        case 'n':
            printw("Enter name of file to save to: ");
            scanw("%s", &fileName);
            printw("\n");
            printw("Which level is this (current levels saved to the file plus 1): ");
            scanw("%d", &save);
            printw("\n");

            if ((saveFile = fopen(&fileName, "a+")) == NULL) {
                printw("Could not open save file.\n");
            } else {
                save--;
                fseek(saveFile, (save * sizeof(level)) - 1, SEEK_SET);
                fwrite(level, sizeof(level), 1, saveFile);
                fclose(saveFile);
            }
            break;
        default:
            printw("Not a valid option.\n");
            break;
    }
    noecho();
    return;
}
