#define MINIAUDIO_IMPLEMENTATION
#include <stdio.h>
#include "terminal.h"
#include <conio.h>
#include "miniaud.h"

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
            }
            printf("\n");
    }

    ERASE_LEND();

    fflush(stdout);
    }

    void Start()
    {
        
    }

int main(){
    
    configureTerminal();
    AnimacaoUm();
    AnimacaoDois();
    AnimacaoTres(); 
    ma_result result;
    ma_engine engine;

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