#include <stdio.h>
#define WALLS 1

int background[20][20];

void null()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            background[i][j] = 0;
        }  
    }
}

void walls()
{
    for (int i = 0; i < 20; i++)
    {
        background[0][i] = WALLS;
        background[19][i] = WALLS;
        background[i][0] = WALLS;
        background[i][19] = WALLS;

        background[1][9] = WALLS;

        if (i != 3 && i != 5 && i != 10 && i != 16 && i != 18)
        {
            background[2][i] = WALLS;
        }

        if (i == 3 || i == 12 || i == 17)
        {
            background[3][i] = WALLS;
        }

        if (i != 1 && i != 3 && i != 8 && i != 11 && i != 12 && i != 13 && i != 16 && i != 18)
        {
            background[4][i] = WALLS;
        }
        
        
    }
}

int main(void)
{
    null();
    walls();

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            printf("%i ", background[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}