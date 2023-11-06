#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

typedef struct
{
    int x, y, value1, value2;
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
    changePositions(&ghost1, 9, 9);
    changePositions(&ghost2, 9, 10);
    changePositions(&ghost3, 10, 9);
    changePositions(&ghost4, 10, 10);
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

void startGame() // funções para começar o jogo
{
    defineBackground();
    circles();
    specialFruit();
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
            score += 5;
            // poder especial
        }
        background[character->y][character->x] = character->value1;
        character->x++;
    }
}

// void ghostsMovements(Character* character)
// {
//     if (character->y < pacman_player.y)
//     {
//         if (background[(character->y) + 1][character->x] != 1 && background[(character->y) + 1][character->x] != 4)
//         {
//             character->value2 = background[(character->y) + 1][character->x];
//             moveDown(character);
//             character->value1 = character->value2;
//         }
//     }
//     else if (character->y > pacman_player.y)
//     {
//         if (background[(character->y) - 1][character->x] != 1 && background[(character->y) - 1][character->x] != 4)
//         {
//             character->value2 = background[(character->y) - 1][character->x];
//             moveUp(character);
//             character->value1 = character->value2;
//         }
//     }
//     else
//     {
//         if (character->x < pacman_player.x)
//         {
//             if (background[character->y][(character->x) + 1] != 1 && background[character->y][(character->x) + 1] != 4)
//             {
//                 character->value2 = background[character->y][(character->x) + 1];
//                 moveRight(character);
//                 character->value1 = character->value2;
//             }
//         }
//         else if (character->x > pacman_player.x)
//         {
//             if (background[character->y][(character->x) - 1] != 1 && background[character->y][(character->x) - 1] != 4)
//             {
//                 character->value2 = background[character->y][(character->x) - 1];
//                 moveRight(character);
//                 character->value1 = character->value2;
//             }
//         }
//         else
//         {
//             // comeu o pacman
//         }
//     }
// }

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
    // GAMEOVER
}

void gameLoop()
{
    while (1)
    {
        pacman_player.value1 = 0;
        ghost1.value1 = 0;
        ghost3.value1 = 0;
        ghost3.value1 = 0;
        ghost4.value1 = 0;
        
        commands(getInput());
        // ghostsMovements(&ghost1);
        // ghostsMovements(&ghost2);
        // ghostsMovements(&ghost3);
        // ghostsMovements(&ghost4);

        background[pacman_player.y][pacman_player.x] = 3;
        background[ghost1.y][ghost1.x] = 4;
        background[ghost2.y][ghost2.x] = 4;
        background[ghost3.y][ghost3.x] = 4;
        background[ghost4.y][ghost4.x] = 4;

        system("cls");
        for (int i = 0; i < 20; i++)
        {
            for (int  j = 0; j < 20; j++)
            {
                // printf("%i ", background[i][j]);
                if (background[i][j] == 5)
                {
                    printf("Y ");
                }
                else if (background[i][j] == 2)
                {
                    printf(". ");
                }
                else if (background[i][j] == 0)
                {
                    printf("  ");
                }
                else if (background[i][j] == 3)
                {
                    printf("C ");
                }
                else if (background[i][j] == 4)
                {
                    printf("W ");
                }
                else
                {
                    printf("o ");
                }
            }
            printf("\n");
        }
        printf("\n y: %i - x: %i - score: %i", pacman_player.y, pacman_player.x, score);
        
    }
}

// MAIN ===============================================

int main(void)
{
    score = 0;
    game_over = false;

    startGame();
    gameLoop();
    
    return 0;
}