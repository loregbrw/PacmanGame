#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
    bool alive;
    bool win;
    Node_T route[ROWS][COLS];
    int x, y;
} Character;


Character pacman_player;
Character ghosts[4];

char user_input;
bool recalculate = true;

ma_result result;
ma_engine engine;

int source[ROWS][COLS], background[ROWS][COLS], score;
int parent_x = -1, parent_y = -1, lastx = -1, lasty = -1;

int getInput() //constantly gets the user input
{
    if (_kbhit())
    {
        user_input = (char)_getch();

        int int_input = (int)user_input;
        return int_input;
    }
    return -1;
}

void changePositions(Character* character, int new_y, int new_x) //defines a character's position
{
    if (background[new_y][new_x] != 1)
    {
        character->x = new_x;
        character->y = new_y;
    }
}

void redefineBackground() //resets the background
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            background[i][j] = source[i][j];
        }
    }
}

void defineBackground() //resets the matrix to initial default
{
    FILE *matrix = fopen("./txts/background.txt", "r");

    int line = 0, col = 0;
    char c;

    while ((c = fgetc(matrix)) != EOF)
    {
        if (c == '\r')
        {
            continue;
        }
        if (c == '\n')
        {
            col = 0;
            line++;
            continue;
        }
        source[line][col++] = c - '0';
    }
    fclose(matrix);

    changePositions(&pacman_player, 18, 1);
    changePositions(&ghosts[0], 9, 10);
    changePositions(&ghosts[1], 10, 9);
    changePositions(&ghosts[2], 10, 10);
    changePositions(&ghosts[3], 9, 9);
}

void circles() //set the balls in the maze
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++)
        {
            if (source[i][j] == 0)
            {
                source[i][j] = 2;

            }
        }
    }
}

void specialFruit() //generates the special fruit
{
    int position = 0, n;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (source[i][j] == 2)

            {
                position++;
            }
        }
    }
    srand(time(NULL));
    n = rand() % (position + 1);
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (source[i][j] == 2)

            {
                n--;
                if (n == 0)
                {
                    source[i][j] = 5;

                    break;
                }
            }
        }
    }
}


// MOVE PACMAN ===========================================


void moveUp () 
{
    if (background[pacman_player.y - 1][pacman_player.x] != 1)
    {
        if (background[pacman_player.y - 1][pacman_player.x] == 2)
        {
            score += 10;
        }
        else if (background[pacman_player.y - 1][pacman_player.x] == 5)
        {
            score += 50;
            // poder especial
        }
        source[pacman_player.y][pacman_player.x] = 0;
        pacman_player.y--;
    }
}

void moveLeft ()
{
    if (background[pacman_player.y][(pacman_player.x) - 1] != 1)
    {
        if (background[pacman_player.y][pacman_player.x - 1] == 2)
        {
            score += 10;
        }
        else if (background[pacman_player.y][pacman_player.x - 1] == 5)
        {
            score += 50;
            // poder especial
        }
        source[pacman_player.y][pacman_player.x] = 0;
        pacman_player.x--;
    }
}

void moveDown ()
{
    if (background[(pacman_player.y) + 1][pacman_player.x] != 1)
    {
        if (background[pacman_player.y + 1][pacman_player.x] == 2)
        {
            score += 10;
        }
        else if (background[pacman_player.y + 1][pacman_player.x] == 5)
        {
            score += 50;
            // poder especial
        }
        source[pacman_player.y][pacman_player.x] = 0;
        pacman_player.y++;
    }
}

void moveRight ()
{
    if (background[pacman_player.y][(pacman_player.x) + 1] != 1)
    {
        if (background[pacman_player.y][pacman_player.x + 1] == 2)
        {
            score += 10;
        }
        else if (background[pacman_player.y][pacman_player.x + 1] == 5)
        {
            score += 50;
            // poder especial
        }
        source[pacman_player.y][pacman_player.x] = 0;
        pacman_player.x++;
    }
}


// MOVE GHOSTS ===========================================


bool flood(Node_T background[ROWS][COLS], int x, int y, int x_destiny, int y_destiny)
{
    if (parent_x == -1) //Primeira execução
    {
        parent_x = x;
    }
    if (parent_y == -1)
    {
        parent_y = y;
    }

    if(background == NULL)
    {
        exit(-2);
    }

    if (y >= ROWS || x >= COLS || x < 0 || y < 0)
    {
        return false;
    }
    
    if (background[y][x].visited)
    {
        return false;
    }

    if (background[y][x].value == 1)
    {
        return false;
    }

    background[y][x].parent = &background[parent_y][parent_x];

    if (x == x_destiny && y == y_destiny) //Encontrado
    {
        lastx = x; //Cordenadas destion/ultimo
        lasty = y;

        return true;
    }
    
    background[y][x].visited = true;
    
    parent_x = x;
    parent_y = y;

    int nums[4] = {0, 1, 2, 3};
    int length = 4;

    for (int i = 0; i < length; i++)
    {
        int num1 = rand() % length;
        int num2 = rand() % length;

        if (num1 == num2)
        {
            continue;
        }

        nums[num1] = nums[num1] ^ nums [num2];
        nums[num2] = nums[num1] ^ nums [num2];
        nums[num1] = nums[num1] ^ nums [num2];
    }
    
    for (int i = 0; i < length; i++)
    {
        switch (nums[i])
        {
        case 0:
            if (flood(background, x+1, y, x_destiny, y_destiny))
            {        
                return true;
            }
            break;

        case 1:
            if (flood(background, x, y+1, x_destiny, y_destiny))
            {        
                return true;
            }
            break;
        
        case 2:
            if (flood(background, x-1, y, x_destiny, y_destiny))
            {        
                return true;
            }
            break;

        case 3:
            if (flood(background, x, y-1, x_destiny, y_destiny))
            {        
                return true;
            }
            break;
        default:
            break;
        }
    }

    return false;
}

void ghostsMovements(Character* ghost)
{
    for (int i = 0 ; i < ROWS; i++)
    {
        for (int j = 0 ; j < ROWS; j++)
        {
            ghost->route[i][j].x = j;
            ghost->route[i][j].y = i;
            ghost->route[i][j].value = background[i][j];
            ghost->route[i][j].visited = false;
        }
    }

    if (ghost->recalculate) 
    {
        parent_x = -1;
        parent_y = -1;
        lastx = -1;
        lasty = -1;
        flood(ghost->route, ghost->x, ghost->y, pacman_player.x, pacman_player.y);
        ghost->recalculate = false;
    }

    Node_T* curr = &ghost->route[lasty][lastx];

    while (true)
    {
        
        if (curr->parent->x == ghost->x && curr->parent->y == ghost->y)
        {
            break;
        }

        curr = curr->parent;
    }

    int x = curr->x;
    int y = curr->y;
    
    ghost->x = x;
    ghost->y = y;
}


// GAME LOOP =============================================


void commands(int input)
{
    if (input == 119)
    {
        for(int i = 0; i <4; i++)
        {
            ghosts[i].recalculate = true;
        }
        moveUp(); // W key, up
    }
    else if (input == 97)
    {
        for(int i = 0; i <4; i++)
        {
            ghosts[i].recalculate = true;
        }
        moveLeft(); // A key, left
    }
    else if (input == 115)
    {
        for(int i = 0; i <4; i++)
        {
            ghosts[i].recalculate = true;
        }
        moveDown(); // S key, down
    }
    else if (input == 100)
    {
        for(int i = 0; i <4; i++){
            ghosts[i].recalculate = true;
        }
        moveRight(); // D key, right
    }
    else if (input == 13)
    {
        // Tecla enter
    }
}

void printWall(int x, int y, int matrix[ROWS][COLS]) 
{
    int up = 0, down = 0, left = 0, right = 0;

    if (x != 19)
    {
        if (matrix[y][x+1] == 1) {right = 1;}
    }
    if (x != 0)
    {
        if (matrix[y][x-1] == 1) {left = 1;}
    }
    if (y != 19)
    {
        if (matrix[y+1][x] == 1) {down = 1;}
    }
    if (y != 0)
    {
        if (matrix[y-1][x] == 1) {up = 1;}
    }

    if (up && down && right) {printf("%c%c", 204, 205);}

    else if (left && up && right) {printf("%c%c", 202, 205);}

    else if (left && down && right) {printf("%c%c", 203, 205);}

    else if (up && left && down) {printf("%c ", 185);}

    else if (up && right && down) {printf("%c%c", 204, 205);}

    else if (left && up) {printf("%c ", 188);}

    else if (left && down) {printf("%c ", 187);}

    else if (up && right) {printf("%c%c", 200, 205);}

    else if (right && down) {printf("%c%c", 201, 205);}

    else if (up || down) {printf("%c ", 186);}

    else if (left || right)
    {
        if (left && !right) {printf("%c ", 205);}

        else {printf("%c%c", 205, 205);}
    }
    else {printf("o ");}
}

void printMatrix()
{
    HIDE_CURSOR();
    MOVE_HOME();

    for (int i = 0; i < 20; i++)
    {
        for (int  j = 0; j < 20; j++)
        {
            if (background[i][j] == 5)
            {
                FOREGROUND_COLOR(191, 24, 237);
                printf("%c ", 254);
                RESET_FOREGROUND();
            }
            else if (background[i][j] == 2)
            {
                FOREGROUND_COLOR(196, 173, 153);
                printf("%c ", 250);
                RESET_FOREGROUND();
            }
            else if (background[i][j] == 0)
            {
                printf("  ");
            }
            else if (background[i][j] == 3)
            {
                FOREGROUND_COLOR(250, 177, 7);
                printf("C ");
                RESET_FOREGROUND();
            }
            else if (background[i][j] == 4)
            {
                FOREGROUND_COLOR(7, 179, 165);
                printf("W ");
                RESET_FOREGROUND();
            }
            else if (background[i][j] == 6)
            {
                FOREGROUND_COLOR(255, 46, 122);
                printf("W ");
                RESET_FOREGROUND();
            }
            else
            {
                FOREGROUND_COLOR(7, 41, 179);
                printWall(j, i, background);
                RESET_FOREGROUND();
            }
        }
        printf("\n");
    }
    printf("\n y: %i - x: %i - score: %i", pacman_player.y, pacman_player.x, score);
    ERASE_LEND();

    fflush(stdout);        
}


void gameLoop()
{
    uint64_t ticks = 0;

    while (1)
    {
        pacman_player.alive = false;
        pacman_player.win = true;
        ticks++;
        commands(getInput());

        if (ticks % 150 == 0)
        {
            for (int i = 0; i < 4; i++)
            {
                ghostsMovements(&ghosts[i]);
            }
        }

        redefineBackground();

        background[pacman_player.y][pacman_player.x] = 3;
        background[ghosts[0].y][ghosts[0].x] = 4;
        background[ghosts[1].y][ghosts[1].x] = 4;
        background[ghosts[2].y][ghosts[2].x] = 6;
        background[ghosts[3].y][ghosts[3].x] = 6;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (background[i][j] == 3)
                {
                    pacman_player.alive = true;
                }
                if (background[i][j] == 2 || background[i][j] == 5)
                {
                    pacman_player.win = false;
                }
                
            }
        }

        if (pacman_player.alive == false || pacman_player.win == true)
        {
            return;
        }
        printMatrix();
    }
}

void startGame() // funções para começar o jogo
{
    ma_engine_play_sound(&engine, "./sounds/abertura.mp3", NULL);
    
    defineBackground();
    circles();
    specialFruit();

    for(int i = 0; i <4; i++)
    {
        ghosts[i].recalculate = true;
    }
    
    printMatrix();
    // Sleep(5000);
}


#endif