#define MINIAUDIO_IMPLEMENTATION

#include "miniaud.h"
#include "terminal.h"
#include "functions.h"
#include "characters.h"


int main(void)
{
    result = ma_engine_init(NULL, &engine);    

    configureTerminal();
    
    score = 0;
    game_over = false;

    startGame();
    
    gameLoop();
    
    ma_engine_uninit(&engine);

    return 0;
}