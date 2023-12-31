#define MINIAUDIO_IMPLEMENTATION

#include "miniaud.h"
#include "terminal.h"
#include "functions.h"
#include "menu.h"

int main(void)
{
    result = ma_engine_init(NULL, &engine);    

    configureTerminal();

    while (1)
    {
        score = 0;

        initialMenu();

        startGame();
        
        gameLoop();

        if (pacman_player.alive == false) {gameOver(&engine);}
        else {winner();}
    }
    
    ma_engine_uninit(&engine);

    return 0;
}