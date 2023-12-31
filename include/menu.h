#ifndef MENU_H
#define MENU_H
#define MINIAUDIO_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <stdint.h>

#include "miniaud.h"
#include "terminal.h"
#include "functions.h"

int first_frame[ROWS][COLS], second_frame[ROWS][COLS], third_frame[ROWS][COLS], game_over_matrix[ROWS][COLS], you_win[ROWS][COLS];
int line, col;
char c;

ma_result result;
ma_engine engine;

void youWin()
{
    FILE* youwin = fopen("./txts/youwin.txt", "r");

    line = 0;
    col = 0;

    while ((c = fgetc(youwin)) != EOF)
    {
        if (c == '\r') {continue;}

        if (c == '\n')
        {
            col = 0;
            line++;
            continue;
        }
        you_win[line][col++] = c - '0';
    }
    fclose(youwin);
}

void matrixGameover()
{
    FILE* gameover = fopen("./txts/gameover.txt", "r");

    line = 0;
    col = 0;

    while ((c = fgetc(gameover)) != EOF)
    {
        if (c == '\r') {continue;}

        if (c == '\n')
        {
            col = 0;
            line++;
            continue;
        }
        game_over_matrix[line][col++] = c - '0';
    }
    fclose(gameover);
}

void firstAnimation()
{
    FILE* animation1 = fopen("./txts/firstFrame.txt", "r");

    line = 0;
    col = 0;

    while ((c = fgetc(animation1)) != EOF)
    {
        if (c == '\r') {continue;}

        if (c == '\n')
        {
            col = 0;
            line++;
            continue;
        }
        first_frame[line][col++] = c - '0';
    }
    fclose(animation1);
}

void secondAnimation()
{
    FILE* animation2 = fopen("./txts/secondFrame.txt", "r");

    line = 0;
    col = 0;

    while ((c = fgetc(animation2)) != EOF)
    {
        if (c == '\r') {continue;}

        if (c == '\n')
        {
            col = 0;
            line++;
            continue;
        }
        second_frame[line][col++] = c - '0';
    }
    fclose(animation2);
}

void thirdAnimation()
{
    FILE *animation3 = fopen("./txts/thirdFrame.txt", "r");

    line = 0;
    col = 0;

    while ((c = fgetc(animation3)) != EOF)
    {
        if (c == '\r') {continue;}

        if (c == '\n')
        {
            col = 0;
            line++;
            continue;
        }
        third_frame[line][col++] = c - '0';
    }
    fclose(animation3);
}

void printAnimation(int matrix[ROWS][COLS])
{
    HIDE_CURSOR();
    MOVE_HOME();

    for (int i = 0; i < ROWS; i++)
    {
        for (int  j = 0; j < COLS; j++)
        {
            if (matrix[i][j] == 2)
            {
                FOREGROUND_COLOR(196, 173, 153);
                printf("%c ", 254);
                RESET_FOREGROUND();
            }
            else if (matrix[i][j] == 0)
            {
                printf("  ");
            }
            else if (matrix[i][j] == 3)
            {
                FOREGROUND_COLOR(250, 177, 7);
                printf("%c ", 254);
                RESET_FOREGROUND();
            }

            else if (matrix[i][j] == 4) {printf("p ");}

            else if (matrix[i][j] == 5) {printf("r ");}

            else if (matrix[i][j] == 6) {printf("e ");}

            else if (matrix[i][j] == 7) {printf("s ");}

            else if (matrix[i][j] == 8) {printf("n ");}

            else if (matrix[i][j] == 9) {printf("t ");}

            else
            {
                FOREGROUND_COLOR(7, 41, 179);
                printWall(j, i, matrix);
                RESET_FOREGROUND();
            }
        }
        printf("\n");
    }
    FOREGROUND_COLOR(255, 46, 122);
    printf("\n   u s e   t h e   W A S D   k e y s   ");
    RESET_FOREGROUND();
    ERASE_LEND();

    fflush(stdout);        
}

void printScreen(int matrix[ROWS][COLS])
{
    HIDE_CURSOR();
    MOVE_HOME();

    for (int i = 0; i < ROWS; i++)
    {
        for (int  j = 0; j < COLS; j++)
        {
            if (matrix[i][j] == 0) {printf("  ");}

            else if (matrix[i][j] == 3)
            {
                FOREGROUND_COLOR(250, 177, 7);
                printf("%c ", 254);
                RESET_FOREGROUND();
            }
            else if (matrix[i][j] == 4)
            {
                FOREGROUND_COLOR(255, 46, 122);
                printf("%c ", 254);
                RESET_FOREGROUND();
            }
            else
            {
                FOREGROUND_COLOR(7, 41, 179);
                printWall(j, i, matrix);
                RESET_FOREGROUND();
            }
        }
        printf("\n");
    }
    FOREGROUND_COLOR(255, 46, 122);
    printf("\n     >>  p r e s s   e n t e r  <<      ");
    RESET_FOREGROUND();
    ERASE_LEND();

    fflush(stdout);        
}

void gameOver()
{
    ma_engine_play_sound(&engine, "sounds/morte.mp3", NULL);
    matrixGameover();
    while (getInput() != 13)
    {
        printScreen(game_over_matrix);
    }
}

void winner()
{
    youWin();
    while (getInput() != 13)
    {
        printScreen(you_win);
    }
}

void initialMenu()
{
    firstAnimation();
    secondAnimation();
    thirdAnimation();


    while (getInput() != 13)
    {
        printAnimation(first_frame);
        Sleep(200);
        printAnimation(second_frame);
        Sleep(200);
        printAnimation(third_frame);
        Sleep(200);
        printAnimation(second_frame);
        Sleep(200);
    }
}

#endif