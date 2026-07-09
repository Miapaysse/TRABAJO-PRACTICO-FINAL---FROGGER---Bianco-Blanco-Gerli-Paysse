int main(void)
{
    Game game;

    gameInit(&game);

    frontendInit();

    while(game.state != OFF)
    {
        Input input = frontendGetInput();

        updateGame(&game, input);

        frontendRender(&game);
    }

    frontendDestroy();

    return 0;
}