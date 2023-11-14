#define MINIAUDIO_IMPLEMENTATION
#include <stdio.h>
#include "terminal.h"
#include <conio.h>
#include "miniaud.h"
#include <stdlib.h>
#include <stdbool.h>

ma_result result;
ma_engine engine;

typedef struct
{
    int x, y, value1, value2;
} Character;

char user_input;
Character pacman_player, ghost1, ghost2, ghost3, ghost4;
int background[20][20], game_over_background[20][20], score;
bool game_over;

int animacao_um[20][20];
int animacao_dois[20][20];
int animacao_tres[20][20];

void printWall(int x, int y);

void defineBackground() // redefine o fundo para o padrão inicial
{
    FILE *matrix = fopen("./bg_menu.txt", "r");

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

    //changePositions(&pacman_player, 18, 1);
    
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
                FOREGROUND_COLOR(222, 7, 50);
                printf("%c ", 208);
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
                printf("\e[1C");
            }
            else if (background[i][j] == 3)
            {
                FOREGROUND_COLOR(250, 177, 7);
                printf("C ");
                RESET_FOREGROUND();
            }
            else if (background[i][j] == 4)
            {
                FOREGROUND_COLOR(50, 201, 68);
                printf("W ");
                RESET_FOREGROUND();
            }
            else
            {
                FOREGROUND_COLOR(5, 125, 245);
                printWall(j, i);
                RESET_FOREGROUND();
            }
        }
        printf("\n");
    }
    printf("\n y: %i - x: %i - score: %i", pacman_player.y, pacman_player.x, score);
    ERASE_LEND();
    MOVE_HOME();

    fflush(stdout);        
}

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

    printMatrix();

    ERASE_LEND();

    fflush(stdout);
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
        defineBackground();
        
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

//ARRUMAR A CAGADA QUE O ANDREY FEZ