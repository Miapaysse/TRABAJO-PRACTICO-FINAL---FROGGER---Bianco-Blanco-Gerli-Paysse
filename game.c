/***************************************************************************//**
  @file     +game.c+
  @brief    +funciones del juego+
  @author   +Mia Paysse+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "game.h"

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

 void updateGame(Game * game, Input input){
    switch ((game->state).id){
        case MENU: //pienso un caso todo de una y dsps lo divido en funciones como en playing
            processInputMenu(game, input);
        break;
        case PLAYING:

            processInputPlaying();

            updateEntities();

            checkCollisions();

            updateScore();

            checkLevel();

        break;
        case PAUSE:
            processInputPaused(game, input);
        break;
        case VICTORY:
            processInputVictory(game, input);
        break;
        case GAME_OVER:
            processInputGameOver(game, input);
        break;
        case POINTS:
            processInputPoints(game, input);
        break;
        case EXIT:
        break;


    }
 }

 void endGame(){
    deleteFrog();
    deleteEntities();
    deleteGame();
 }
 void gameInit(){
    createGame();
    createFrog();
    createEntities();
 }
 void renderGame(){}
 void showMenu(){}
 void showPause(){}

///////////////////////////////////////////MENUES///////////////
void menuPrevious(MenuState *menu){
    if(menu->selected == 0)
        menu->selected = menu->optionCount - 1;
    else
        menu->selected--;
}

void menuNext(MenuState *menu){
    menu->selected++;

    if(menu->selected >= menu->optionCount)
        menu->selected = 0;
}

/////////////////////////////////////////////////////////////////MENU
void processInputMenu(Game * game, Input input){
        switch(input){
                case SELECT:
                    switch ( ((game->state).menu.selected) ){
                        case MENU_POINTS: 
                            (game->state).id = POINTS;
                        break;
                        case MENU_PLAY:
                            (game->state).id = PLAYING;
                        break;
                        case MENU_EXIT:
                            (game->state).id = EXIT;
                        break;
                    }
                break;
                case UP:
                    menuPrevious(&((game->state).menu));
                break;

                case DOWN:
                    menuNext(&((game->state).menu));
                break;
        }
}

////////////////////////////////////////////////////////////////////////PAUSED
void processInputPaused(Game * game, Input input){
    switch(input){
                case SELECT:
                    switch ( ((game->state).paused.selected) ){
                        case PAUSED_MENU: 
                            (game->state).id = MENU;
                        break;
                        case PAUSED_PLAY:
                            (game->state).id = PLAYING; //////////////ANALIZAR TEMA VIDAS REPLAY
                        break;
                        case PAUSED_EXIT:
                            (game->state).id = EXIT;
                        break;
                    }
                break;
                case UP:
                    menuPrevious(&((game->state).paused));
                break;

                case DOWN:
                    menuNext(&((game->state).paused));
                break;
    }
}

///////////////////////////////////////////////////////////GAME OVER
void processInputGameOver(Game * game, Input input){}

///////////////////////////////////////////////////////////VICTORY
void processInputVictory(Game * game, Input input){}
//////////////////////////////////////////////////////////POINTS
void processInputPoints(Game * game, Input input){}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 