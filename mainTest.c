#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

// #include "backgroundgen.h"
// #include "events.h"

#define ROWS 20
#define COLS 20

typedef struct
{
    int x, y, value1, value2;
} Character;

typedef struct
{
    int x, y;
    bool eaten;
} Fruit;

Fruit special_fruit, circles;
Character pacman_player;
Character ghosts[4];

char user_input;
bool game_over;

int source[ROWS][COLS];
int background[ROWS][COLS], score;

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

void setBackround() {
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            background[i][j] = source[i][j];
        }
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
        source[line][col++] = c - '0';
    }
    fclose(matrix);


    changePositions(&pacman_player, 18, 1);
    changePositions(&ghosts[0], 9, 10);
    changePositions(&ghosts[1], 10, 9);
    changePositions(&ghosts[2], 10, 10);
    changePositions(&ghosts[3], 9, 9);
}

void circles() // coloca as bolinhas no labirinto
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++)
        {
            if (source[i][j] == 0)
            {
                source[i][j] = 2;
            }
        }
    }
}

void specialFruit() // gera a frutinha especial
{
    int position = 0, n;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (background[i][j] == 2)
            {
                position++;
            }
        }
    }
    srand(time(NULL));
    n = rand() % (position + 1);
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (background[i][j] == 2)
            {
                n--;
                if (n == 0)
                {
                    special_fruit.x = i;
                    special_fruit.y = i;
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

// move character ============================================================

void moveUp () 
{
    if (background[pacman_player.y - 1][pacman_player.x] != 1)
    {
        if (background[pacman_player.y - 1][pacman_player.x] == 2)
        {
            score++;
        }
        else if (background[pacman_player.y - 1][pacman_player.x] == 5)
        {
            score += 5;
            // poder especial
        }
        source[pacman_player.y][pacman_player.x] = 0;
        pacman_player.y--;
    }
}

void moveLeft ()
{
    if (background[pacman_player.y][(pacman_player.x) - 1] != 1)
    {
        if (background[pacman_player.y][pacman_player.x - 1] == 2)
        {
            score++;
        }
        else if (background[pacman_player.y][pacman_player.x - 1] == 5)
        {
            score += 5;
            // poder especial
        }
        source[pacman_player.y][pacman_player.x] = 0;
        pacman_player.x--;
    }
}

void moveDown ()
{
    if (background[(pacman_player.y) + 1][pacman_player.x] != 1)
    {
        if (background[pacman_player.y + 1][pacman_player.x] == 2)
        {
            score++;
        }
        else if (background[pacman_player.y + 1][pacman_player.x] == 5)
        {
            score += 5;
            // poder especial
        }
        source[pacman_player.y][pacman_player.x] = 0;
        pacman_player.y++;
    }
}

void moveRight ()
{
    if (background[pacman_player.y][(pacman_player.x) + 1] != 1)
    {
        if (background[pacman_player.y][pacman_player.x + 1] == 2)
        {
            score++;
        }
        else if (background[pacman_player.y][pacman_player.x + 1] == 5)
        {
            score += 5;
            // poder especial
        }
        source[pacman_player.y][pacman_player.x] = 0;
        pacman_player.x++;
    }
}

// move ghosts ===============================================================

typedef struct Node
{
    int x,y;
    bool visited;
    int value;
    struct Node* parent;
} Node_T;

int parent_x = -1, parent_y = -1, lastx = -1, lasty = -1;

bool flood(Node_T background[ROWS][COLS], int x, int y, int x_destiny, int y_destiny) {
    
    if (parent_x == -1) //Primeira execução
    {
        parent_x = x;
    }
    if (parent_y == -1)
    {
        parent_y = y;
    }

    if(background == NULL) {
        exit(-2);
    }


    if (y >= ROWS || x >= COLS || x < 0 || y < 0)
    {
        return false;
    }

    
    if (background[y][x].visited)
    {
        return false;
    }
    

    if (background[y][x].value == 1)
    {
        return false;
    }

    background[y][x].parent = &background[parent_y][parent_x];

    if (x == x_destiny && y == y_destiny) //Encontrado
    {
        lastx = x; //Cordenadas destion/ultimo
        lasty = y;

        return true;
    }
    
    background[y][x].visited = true;
    
    parent_x = x;
    parent_y = y;

    if (flood(background, x+1, y, x_destiny, y_destiny))
    {        
        return true;
    }
    if (flood(background, x, y+1, x_destiny, y_destiny))
    {        
        return true;
    }
    if (flood(background, x-1, y, x_destiny, y_destiny))
    {        
        return true;
    }
    if (flood(background, x, y-1, x_destiny, y_destiny))
    {        
        return true;
    }

    return false;
}

void ghostsMovements(Character* ghost)
{
    Node_T new_map[ROWS][COLS];

    for (int i = 0 ; i < ROWS; i++)
    {
        for (int j = 0 ; j < ROWS; j++)
        {
            new_map[i][j].x = j;
            new_map[i][j].y = i;
            new_map[i][j].value = background[i][j];
            new_map[i][j].visited = false;
        }
    }

    bool result = flood(new_map, pacman_player.x, pacman_player.y, ghost->x, ghost->y);

    Node_T* curr = &new_map[lasty][lastx];

    int x = curr->parent->x, y = curr->parent->y;


    background[ghost->y][ghost->x] = ghost->value1;

    ghost->value2 = background[y][x];
    background[ghost->y][ghost->x] = ghost->value1;
    ghost->x = x;
    ghost->y = y;
    ghost->value1 = ghost->value2;

    // guardar o valor da casa do pacman na variavel!!!
}

// gameloop ==================================================================

void commands(int input)
{
    if (input == 119)
    {
        moveUp(); // Tecla W, subir
    }
    else if (input == 97)
    {
        moveLeft(); // Tecla A, esquerda
    }
    else if (input == 115)
    {
        moveDown(); // Tecla S, descer
    }
    else if (input == 100)
    {
        moveRight(); // Tecla D, direita
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

void gameLoop()
{
    for (int i = 0; i < 4; i++) {
        ghosts[i].value1 = 2;
    }

    while (1)
    {
        commands(getInput());

        for (int i = 0; i < 4; i++)
        {
            ghostsMovements(&ghosts[i]);
        }

        // ghostsMovements(&ghosts[0]);

        background[pacman_player.y][pacman_player.x] = 3;
        for(int i = 0 ; i < 4; i++)
        {
            background[ghosts[i].y][ghosts[i].x] = 4;
        }

        system("cls");
        for (int i = 0; i < ROWS; i++)
        {
            for (int  j = 0; j < COLS; j++)
            {
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

int main (void)
{
    startGame();
    gameLoop();
}