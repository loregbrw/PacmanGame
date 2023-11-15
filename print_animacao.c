#define MINIAUDIO_IMPLEMENTATION
#include <stdio.h>
#include "terminal.h"
#include <conio.h>
#include "miniaud.h"
#include <stdlib.h>
#include <stdbool.h>

ma_result result;
ma_engine engine;

int animacao_um[20][20];
int animacao_dois[20][20];
int animacao_tres[20][20];

void AnimacaoUm() // redefine o fundo para a tela de game over
    {
    FILE *matrix = fopen("./animacao1.txt", "r");

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
        animacao_um[line][col++] = c - '0';
    }
    fclose(matrix);
    }

    void AnimacaoDois() // redefine o fundo para a tela de game over
    {
    FILE *matrix = fopen("./animacao2.txt", "r");

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
        animacao_dois[line][col++] = c - '0';
    }
    fclose(matrix);
    }

    void AnimacaoTres() // redefine o fundo para a tela de game over
    {
    FILE *matrix = fopen("./animacao3.txt", "r");

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
        animacao_tres[line][col++] = c - '0';
    }
    fclose(matrix);
    }

    void Coloridinho(int animacao[20][20])
    {
        HIDE_CURSOR();
        MOVE_HOME();

        for (int i = 0; i < 20; i++)
        {
            for (int  j = 0; j < 20; j++)
            {
                if (animacao[i][j] == 0)
                {
                    printf("  ");
                }
                if (animacao[i][j] == 1)
                {
                    FOREGROUND_COLOR(250, 177, 7);
                    printf("%c ", 254);
                    RESET_FOREGROUND();
                }
                if (animacao[i][j] == 2)
                {
                    FOREGROUND_COLOR(196, 173, 153);
                    printf("%c ", 254);
                    RESET_FOREGROUND();
                }
                if (animacao[i][j] == 3)
                {
                    printf("p");
                }
                if (animacao[i][j] == 4)
                {
                    printf("r");
                }
                if (animacao[i][j] == 5)
                {
                    printf("e");
                }
                if (animacao[i][j] == 6)
                {
                    printf("s");
                }
                if (animacao[i][j] == 7)
                {
                    printf("n");
                }
                if (animacao[i][j] == 8)
                {
                    printf("t");
                }

            }
            printf("\n");
    }

    ERASE_LEND();

    fflush(stdout);
    }

    void printWall(int x, int y, int animacao[20][20])
    {
        int up = 0, down = 0, left = 0, right = 0;

        if (x != 19)
        {
            if (animacao[y][x+1] == 1) {right = 1;}
        }
        if (x != 0)
        {
            if (animacao[y][x-1] == 1) {left = 1;}
        }
        if (y != 19)
        {
            if (animacao[y+1][x] == 1) {down = 1;}
        }
        if (y != 0)
        {
            if (animacao[y-1][x] == 1) {up = 1;}
        }

        else if (up && right && down)
        {
            printf("%c%c", 204, 205);
        }
        else if (left && up)
        {
            printf("%c ", 188);
        }
        else if (left && down)
        {
            printf("%c ", 187);
        }
        else if (up && right)
        {
            printf("%c%c", 200, 205);
        }
        else if (right && down)
        {
            printf("%c%c", 201, 205);
        }
        else if (up || down)
        {
            printf("%c ", 186);
        }
        else if (left || right)
        {
            if (left && !right)
            {
                printf("%c ", 205);
            }
            else
            {
                printf("%c%c", 205, 205);
            }
    }
    }

int main(){
    
    configureTerminal();
    AnimacaoUm();
    AnimacaoDois();
    AnimacaoTres();

    result = ma_engine_init(NULL, &engine);  
    ma_engine_play_sound(&engine, "musica.mp3", NULL);
    Sleep(5000);
    for (int i = 0; i < 10; i++)
    {   
        Coloridinho(animacao_um);
        Sleep(100);
        Coloridinho(animacao_dois);
        Sleep(100);
        Coloridinho(animacao_tres);
        Sleep(100);
        Coloridinho(animacao_dois);
        Sleep(100);
    }
}