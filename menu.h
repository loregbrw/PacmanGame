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

void firstAnimation()
{
    FILE *animation1 = fopen("../firstFrame.txt", "r");

    int line = 0, col = 0;
    char c;

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
    FILE *animation2 = fopen("../secondFrame.txt", "r");

    int line = 0, col = 0;
    char c;

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
    FILE *animation3 = fopen("../thirdFrame.txt", "r");

    int line = 0, col = 0;
    char c;

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

void initialMenu()
{
    firstAnimation();
    secondAnimation();
    thirdAnimation();

    uint64_t ticks = 0;

    while (getInput() != 13)
    {
        printMatrix(first_frame);
        Sleep(200);
        printMatrix(second_frame);
        Sleep(200);
        printMatrix(third_frame);
        Sleep(200);
    }
    
    
}

#endif