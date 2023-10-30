#include <stdio.h>

int background[20][20];

void walls()
{
    for (int i = 0; i < 20; i++)
    {
        background[0][i] = 1;
        background[20][i] = 1;
        background[i][0] = 1;
        background[i][20] = 1;
    }
}

int main(void)
{
    return 0;
}