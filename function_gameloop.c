void gameLoop()
{
    while (1)
    {
        pacman_player.value1 = 0;
        ghost1.value1 = 0;
        // ghost3.value1 = 0;
        // ghost3.value1 = 0;
        // ghost4.value1 = 0;
        
        commands(getInput());
        ghostsMovements(&ghost1);
        // ghostsMovements(&ghost2);
        // ghostsMovements(&ghost3);
        // ghostsMovements(&ghost4);

        background[pacman_player.y][pacman_player.x] = 3;
        background[ghost1.y][ghost1.x] = 4;
        // background[ghost2.y][ghost2.x] = 4;
        // background[ghost3.y][ghost3.x] = 4;
        // background[ghost4.y][ghost4.x] = 4;

        system("cls");
        for (int i = 0; i < 20; i++)
        {
            for (int  j = 0; j < 20; j++)
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