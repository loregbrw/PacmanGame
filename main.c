#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

// #include "events.h"
// #include "worldgen.h"

typedef struct
{
    int x, y;
} Character;

char user_input;
Character pacman_player, ghost1, ghost2, ghost3, ghost4;
int background[20][20], score;
bool game_over;

// FUNÇÕES ===============================================

int getInput() // pegar o input do usuario
{
    if (_kbhit())
    {
        user_input = (char)_getch();

        int int_input = (int)user_input;
        return int_input;
    }
    return -1;
}

void changePositions (Character* character, int new_y, int new_x) // definir a posição de um personagem
{
    if (background[new_y][new_x] != 1)
    {
        character->x = new_x;
        character->y = new_y;
    }
    
}

void defineBackground() // redefine o fundo para o padrão inicial
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

    changePositions(&pacman_player, 18, 1);
}

void circles() // coloca as bolinhas no labirinto
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

void specialFruit() // gera a frutinha especial
{
    int position = 0, n;
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

void moveUp (Character* character) 
{
    // if (background[character->y--][character->x] != 1)
    {
        background[character->y][character->x] = 0;
        character->y--;

        // if (background[character->y--][character->x] == 2)
        // {
        //     score++;
        // }
        // else if (background[character->y--][character->x] == 4)
        // {
        //     game_over = true;
        // }
        // else if (background[character->y--][character->x] == 5)
        // {
        //     score += 5;
        //     // função do poder da frutinha
        // }
    }
    
}

void moveLeft (Character* character)
{
    background[character->y][character->x] = 0;
    character->x--;
}

void moveDown (Character* character)
{
    background[character->y][character->x] = 0;
    character->y++;
}

void moveRight (Character* character)
{
    background[character->y][character->x] = 0;
    character->x++;
}

void commands(int input)
{
    if (input == 119)
    {

        moveUp(&pacman_player); // Tecla W, subir

    }
    else if (input == 97)
    {
        moveLeft(&pacman_player); // Tecla A, esquerda
    }
    else if (input == 115)
    {
        moveDown(&pacman_player); // Tecla S, descer
    }
    else if (input == 100)
    {
        moveRight(&pacman_player); // Tecla D, direita
    }
    else if (input == 13)
    {
        // Tecla enter
    }
    else if (input == 32)
    {
        // Tecla espaço
    }
}

// MAIN ===============================================

int main(void)
{
    defineBackground();
    circles();
    specialFruit();
    while (1)
    {
        commands(getInput());
        
        background[pacman_player.y][pacman_player.x] = 3;
        system("cls");
        for (int i = 0; i < 20; i++)
        {
            for (int  j = 0; j < 20; j++)
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
        printf("\n y: %i - x: %i", pacman_player.y, pacman_player.x);
        
    }
    
    return 0;
}