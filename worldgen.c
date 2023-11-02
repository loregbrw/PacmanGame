#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "worldgen.h"

#define WALLS 1

int background[20][20];
int n;

void defineBackground()
{
    FILE *matrix = fopen("../background.txt", "r");

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
        background[line][col++] = c - '0';
    }
    fclose(matrix);
}

void circles()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (background[i][j] == 0)
            {
                background[i][j] = 2;
            }
        }
    }
}

void specialFruit()
{
    int position = 0;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (background[i][j] == 2)
            {
                position++;
            }
        }
    }
    srand(time(NULL));
    n = rand() % (position + 1);
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (background[i][j] == 2)
            {
                n--;
                if (n == 0)
                {
                    background[i][j] = 5;
                    break;
                }
            }
        }
    }
}

int main(void)
{
    defineBackground();
    circles();
    specialFruit();
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (background[i][j] == 5)
            {
                printf("Y ");
            }
            else if (background[i][j] == 2)
            {
                printf("* ");
            }
            else if (background[i][j] == 0)
            {
                printf("  ");
            }
            else if (background[i][j] == 3)
            {
                printf("X ");
            }
            else
            {
                printf("o ");
            }
        }
        printf("\n");
    }

    return 0;
}