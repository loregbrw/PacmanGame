#include <stdio.h>
#include <conio.h>

// #include "events.h"

typedef struct
{
    int x, y;
} Character;

char user_input;
Character pacman_player, ghost1, ghost2, ghost3, ghost4; 



void moveUp (Character character)
{
    character.y--;
}

void moveLeft (Character character)
{
    character.x--;
}

void moveDown (Character character)
{
    character.y++;
}

void moveRight (Character character)
{
    character.x++;
}

void changePositions (Character character, int new_x, int new_y)
{
    character.x = new_x;
    character.y = new_y;
}

int getInput()
{
    if (_kbhit())
    {
        user_input = (char)_getch();

        int int_input = (int)user_input;
        return int_input;
    }
    return -1;
}

void commands(int input)
{
    if (input == 119)
    {
        moveUp(pacman_player);
        // Tecla W, subir
    }
    else if (input == 97)
    {
        moveLeft(pacman_player);
        // Tecla A, esquerda
    }
    else if (input == 115)
    {
        moveDown(pacman_player);
        // Tecla S, descer
    }
    else if (input == 100)
    {
        moveRight(pacman_player);
        // Tecla D, direita
    }
    else if (input == 13)
    {
        // Tecla enter
    }
    else if (input == 32)
    {
        // Tecla espaço
    }
    else
    {
        // Nada
    }    
}

int main(void)
{
    while (1)
    {
        printf("%i\n", getInput());
    }
    
    return 0;
}