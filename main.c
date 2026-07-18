#include "backend/game.h"
#include "frontend/frontend.h"

int main(void)
{
    Game game = {0};
    gameInit(&game);
    frontendInit();

    while(game.state.id != EXIT)
    {
        Input input = frontendGetInput();
        updateGame(&game, input);
        frontendRender(&game);
    }
    return 0;
}
