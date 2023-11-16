#ifndef FUNCTIONS_H
#define FUNCIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <stdint.h>

#include "miniaud.h"
#include "terminal.h"

#define ROWS 20
#define COLS 20

typedef struct Node
{
    int x,y;
    bool visited;
    int value;
    struct Node* parent;
} Node_T;

typedef struct
{
    bool recalculate;
    Node_T route[ROWS][COLS];
    int x, y;
} Character;


Character pacman_player;
Character ghosts[4];

char user_input;
bool game_over, recalculate = true;

ma_result result;
ma_engine engine;

int source[ROWS][COLS], background[ROWS][COLS], game_over_matrix[ROWS][COLS], score;
int parent_x = -1, parent_y = -1, lastx = -1, lasty = -1;

int getInput();
void changePositions(Character* character, int new_y, int new_x);
void redefineBackground();
void defineBackground();
void circles();
void specialFruit();
void moveUp ();
void moveLeft ();
void moveDown ();
void moveRight ();
bool flood(Node_T background[ROWS][COLS], int x, int y, int x_destiny, int y_destiny);
void ghostsMovements(Character* ghost);
void commands(int input);
void gameOver();
void printWall(int x, int y);
void printMatrix();
void gameLoop();
void startGame();


#endif