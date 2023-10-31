#include <stdio.h>
#include <conio.h>

char user_input;

typedef struct
{
    int x, y;
} Pacman;

int get_input()
{
    if (_kbhit())
    {
        user_input = (char)_getch();

        int int_input = (int)user_input;
        return int_input;
    }
    return -1;
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
        printf("%i\n", get_input());
    }
    
    return 0;
}