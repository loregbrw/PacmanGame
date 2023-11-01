#include <stdio.h>
#include <conio.h>

typedef struct
{
    int x, y;
} Character;

char user_input;
Character pacman_player, ghost1, ghost2, ghost3, ghost4; 


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

void findPacman()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            // achar o pacman
        }
    }
}


void moveUp(Character character)
{
    if (character.y-- == 0)
    {
        // andar
    }
    else if (character.y-- == 1)
    {
        // não fazer nada
    }
    else if (character.y-- == 2)
    {
        // andar e comer bolinha
        // ganhar pontuação
    }
    else if (character.y-- == 4)
    {
        // morrer
    }
    else if (character.y-- == 5)
    {
        // andar e comer frutinha
        // ganhar pontuação
        // poder especial
    }
}

int commands(int input)
{
    if (input == 119)
    {
        // Tecla W, subir
    }
    else if (input == 97)
    {
        // Tecla A, esquerda
    }
    else if (input == 115)
    {
        // Tecla S, descer
    }
    else if (input == 100)
    {
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