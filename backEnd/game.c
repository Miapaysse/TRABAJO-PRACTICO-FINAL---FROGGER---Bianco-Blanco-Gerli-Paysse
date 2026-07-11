/***************************************************************************//**
  @file     +game.c+
  @brief    +funciones del juego+
  @author   +Bianco-Blanco-Gerli-Paysse+
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
        case MENU: 
            processInputMenu(&(game->state), input);
        break;
        case PLAYING:

            processInputPlaying(&(game->state),input);

            updateEntities();

            updateZone();

            manageInteractions(game);

            checkLevel();

        break;
        case PAUSE:
            processInputPaused(&(game->state), input);
        break;
        case VICTORY:
            processInputVictory(&(game->state), input);
        break;
        case GAME_OVER:
            processInputGameOver(&(game->state), input);
        break;
        case POINTS:
            processInputPoints(&(game->state), input);
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

///////////////////////////////////////////MENUS///////////////
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
void processInputMenu(gameState * state, Input input){
        switch(input){
                case SELECT:
                    switch ( (state->menu).selected ){
                        case MENU_POINTS: 
                            state->id = POINTS;
                        break;
                        case MENU_PLAY:
                            state->id = PLAYING;
                        break;
                        case MENU_EXIT:
                            state->id = EXIT;
                        break;
                    }
                break;
                case UP:
                    menuPrevious(&((state->menu)));
                break;

                case DOWN:
                    menuNext(&((state->menu)));
                break;
        }
}

////////////////////////////////////////////////////////////////////////PAUSED
void processInputPaused(gameState * state, Input input){
    switch(input){
                case SELECT:
                    switch ( (state->paused).selected ){
                        case PAUSED_MENU: 
                            state->id = MENU;
                        break;
                        case PAUSED_PLAY:
                            state->id = PLAYING; //////////////ANALIZAR TEMA VIDAS REPLAY
                        break;
                        case PAUSED_EXIT:
                            state->id = EXIT;
                        break;
                    }
                break;
                case UP:
                    menuPrevious(&(state->paused));
                break;

                case DOWN:
                    menuNext(&(state->paused));
                break;
    }
}

///////////////////////////////////////////////////////////GAME OVER
void processInputGameOver(gameState * state, Input input){
        switch(input){
                case SELECT:
                    switch ( (state->gameOver).selected ){
                        case GAME_OVER_MENU: 
                            state->id = MENU;
                        break;
                        case GAME_OVER_EXIT:
                            state->id = EXIT;
                        break;
                    }
                break;
                case UP:
                    menuPrevious(&(state->gameOver));
                break;

                case DOWN:
                    menuNext(&(state->gameOver));
                break;
    }
}

///////////////////////////////////////////////////////////VICTORY
void processInputVictory(gameState * state, Input input){
        switch(input){
                case SELECT:
                    switch ( (state->victory).selected ){
                        case VICTORY_MENU: 
                            state->id = MENU;
                        break;
                        case VICTORY_EXIT:
                            state->id = EXIT;
                        break;
                    }
                break;
                case UP:
                    menuPrevious(&(state->victory));
                break;

                case DOWN:
                    menuNext(&(state->victory));
                break;
    }
}
//////////////////////////////////////////////////////////POINTS
void processInputPoints(gameState * state, Input input){
        switch(input){
                case SELECT:
                    switch ( (state->points).selected ){
                        case POINTS_MENU: 
                            state->id = MENU;
                        break;
                        case POINTS_EXIT:
                            state->id = EXIT;
                        break;
                    }
                break;
                case UP:
                    menuPrevious(&(state->points));
                break;

                case DOWN:
                    menuNext(&(state->points));
                break;
    }
}
/////////////////////////////GAME LOGIC///////////////////////
void processInputPlaying(gameState * state, Input input){
    switch(input){
                case SELECT:
                    state->id = PAUSED;
                break;

                case UP:
                    moveFrog(UP);
                break;

                case DOWN:
                    moveFrog(DOWN);
                break;

                case RIGHT:
                    moveFrog(RIGHT);
                break;

                case LEFT:
                    moveFrog(LEFT);
                break;
    }
}

////////////////////////ZONES & SCORES
void updateScore();

void updateZone();

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 