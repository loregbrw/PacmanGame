# PacmanGame

w = 119
a = 97
s = 115
d = 100
enter = 13
espaço = 32

fundo = 0
paredes = 1
bolinhas = 2
pacman = 3
fantasmas = 4
frutinhas = 5

fundo = 199





void moveUp (Character* character) 
{
    // if (background[character->y--][character->x] != 1)
    {
        background[character->y][character->x] = 0;
        character->y--;

        // if (background[character->y--][character->x] == 2)
        // {
        //     score++;
        // }
        // else if (background[character->y--][character->x] == 4)
        // {
        //     game_over = true;
        // }
        // else if (background[character->y--][character->x] == 5)
        // {
        //     score += 5;
        //     // função do poder da frutinha
        // }
    }
    
}