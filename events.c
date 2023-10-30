#include <stdio.h>
#include <conio.h>

char user_input;

int get_input()
{

        user_input = (char)_getch();

        int int_input = (int)user_input;
        return int_input;

}

int main(void)
{
    while (1)
    {

        printf("%i\n", get_input());

        
    }
    
    return 0;
}