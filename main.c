#define MINIAUDIO_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include "miniaud.h"

#include "terminal.h"

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
    FILE *matrix = fopen("./background.txt", "r");

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

void defineGameOver() // redefine o fundo para a tela de game over
{
    FILE *matrix = fopen("./game_over.txt", "r");

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
        game_over_background[line][col++] = c - '0';
    }
    fclose(matrix);
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
    if (background[(character->y) - 1][character->x] != 1)
    {
        if (background[(character->y) - 1][character->x] == 2)
        {
            score++;
        }
        else if (background[(character->y) - 1][character->x] == 5)
        {
            ma_engine_play_sound(&engine, "frutinha.mp3", NULL);
            score += 5;
            // poder especial
        }
        background[character->y][character->x] = character->value1;
        character->y--;
    }
}

void moveLeft (Character* character)
{
    if (background[character->y][(character->x) - 1] != 1)
    {
        if (background[character->y][(character->x) - 1] == 2)
        {
            score++;
        }
        else if (background[character->y][(character->x) - 1] == 5)
        {
            ma_engine_play_sound(&engine, "frutinha.mp3", NULL);
            score += 5;
            // poder especial
        }
        background[character->y][character->x] = character->value1;
        character->x--;
    }
}

void moveDown (Character* character)
{
    if (background[(character->y) + 1][character->x] != 1)
    {
        if (background[(character->y) + 1][character->x] == 2)
        {
            score++;
        }
        else if (background[(character->y) + 1][character->x] == 5)
        {
            ma_engine_play_sound(&engine, "frutinha.mp3", NULL);
            score += 5;
            // poder especial
        }
        background[character->y][character->x] = character->value1;
        character->y++;
    }
}

void moveRight (Character* character)
{
    if (background[character->y][(character->x) + 1] != 1)
    {
        if (background[character->y][(character->x) + 1] == 2)
        {
            score++;
        }
        else if (background[character->y][(character->x) + 1] == 5)
        {
            ma_engine_play_sound(&engine, "frutinha.mp3", NULL);
            score += 5;
            // poder especial
        }
        background[character->y][character->x] = character->value1;
        character->x++;
    }
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

void gameOver()
{
    // ma_engine_play_sound(&engine, "morte.mp3", NULL);
    // GAMEOVER
}

void printWall(int x, int y) 
{
    int up = 0, down = 0, left = 0, right = 0;

    if (x != 19)
    {
        if (background[y][x+1] == 1) {right = 1;}
    }
    if (x != 0)
    {
        if (background[y][x-1] == 1) {left = 1;}
    }
    if (y != 19)
    {
        if (background[y+1][x] == 1) {down = 1;}
    }
    if (y != 0)
    {
        if (background[y-1][x] == 1) {up = 1;}
    }

    // if (up && down && right && left)
    // {
    //     printf("%c", 206);
    // }


    if (up && down && right)
    {
        printf("%c%c", 204, 205);
    }
    else if (left && up && right)
    {
        printf("%c%c", 202, 205);
    }
    else if (left && down && right)
    {
        printf("%c%c", 203, 205);
    }
    else if (up && left && down)
    {
        printf("%c ", 185);
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
    // else if (left)
    // {
    //     printf("%c ", 205);
    // }
    // else if (right)
    // {
    //     printf("%c%c", 205);
    // }
    else 
    {
        printf("o ");
    } 
    
    
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

    fflush(stdout);        
}

void gameLoop()
{
    pacman_player.value1 = 0;

    while (1)
    {
        commands(getInput());
        background[pacman_player.y][pacman_player.x] = 3;
        printMatrix();
    }
}

void startGame() // funções para começar o jogo
{
    ma_engine_play_sound(&engine, "abertura.mp3", NULL);
    
    defineBackground();
    circles();
    specialFruit();
    background[pacman_player.y][pacman_player.x] = 3;
    printMatrix();
    Sleep(5000);
}
// MAIN ===============================================

int main(void)
{
    result = ma_engine_init(NULL, &engine);    

    configureTerminal();
    
    score = 0;
    game_over = false;

    startGame();
    
    gameLoop();
    
    ma_engine_uninit(&engine);
    return 0;
}