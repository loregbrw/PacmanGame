#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "backgroundgen.h"

char user_input;
bool game_over;

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

void startGame() // funções para começar o jogo
{
    defineBackground();
    circles();
    specialFruit();
}

void ghostsMovements(Character* character)
{
    // pathfinding
}