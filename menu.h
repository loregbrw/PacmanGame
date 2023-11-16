#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <stdint.h>

#include "miniaud.h"
#include "terminal.h"
#include "functions.h"

int first_frame[ROWS][COLS], second_frame[ROWS][COLS], third_frame[ROWS][COLS];
int line, col;
char c;

void firstAnimation()
{
    FILE* animation1 = fopen("firstFrame.txt", "r");

    line = 0;
    col = 0;

    while ((c = fgetc(animation1)) != EOF)
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
        first_frame[line][col++] = c - '0';
    }
    fclose(animation1);
}

void secondAnimation()
{
    FILE* animation2 = fopen("secondFrame.txt", "r");

    line = 0;
    col = 0;

    while ((c = fgetc(animation2)) != EOF)
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
        second_frame[line][col++] = c - '0';
    }
    fclose(animation2);
}

void thirdAnimation()
{
    FILE *animation3 = fopen("thirdFrame.txt", "r");

    line = 0;
    col = 0;

    while ((c = fgetc(animation3)) != EOF)
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
            else
            {
                FOREGROUND_COLOR(7, 41, 179);
                printWall(j, i, matrix);
                RESET_FOREGROUND();
            }
        }
        printf("\n");
    }
    printf("\n y: %i - x: %i - score: %i", pacman_player.y, pacman_player.x, score);
    ERASE_LEND();

    fflush(stdout);        
}

void initialMenu()
{
    firstAnimation();
    secondAnimation();
    thirdAnimation();

    uint64_t ticks = 0;

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