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

            processInputPlaying(&(game->state),input, &(game->frog));

            updateEntities(game);

            manageInteractions(game);

            checkLevel(&(game->frog), &(game->level));

        break;
        case PAUSED:
            processInputPaused(&(game->state), input);
        break;
        case VICTORY:
            resetFrog(&(game->frog));
            processInputVictory(&(game->state), input);
        break;
        case GAME_OVER:
            resetFrog(&(game->frog));
            processInputGameOver(&(game->state), input);
        break;
        case POINTS:
            processInputPoints(&(game->state), input);
        break;

        case EXIT: //tira warning si no lo ponemos
            //no hace nada, main lo lee y termina programa
        break;
    }
 }

 void gameInit(Game* game){
    initLevel(game);
    initFrog(&(game->frog));
    game->score=MIN_SCORE;
    game->lives=MAX_LIVES;
    game->lastEntityUpdate = clock();

    (game->state).id = MENU;

    // Menu principal
    game->state.menu = (MenuState){ MENU_TITLE, MENU_COUNT };

    // Pausa
    game->state.paused = (MenuState){ PAUSED_TITLE, PAUSED_COUNT };

    // Game Over
    game->state.gameOver = (MenuState){ GAME_OVER_TITLE, GAME_OVER_COUNT };

    // Victory
    game->state.victory = (MenuState){ VICTORY_TITLE, VICTORY_COUNT };

    // Puntos (Top 10)
    game->state.points = (MenuState){ POINTS_TITLE, POINTS_COUNT };

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
void processInputMenu(GameState * state, Input input){
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
                    (state->menu).selected = MENU_TITLE; //reseteo menu
                    
                break;
                case UP:
                    menuPrevious(&((state->menu)));
                break;

                case DOWN:
                    menuNext(&((state->menu)));
                break;
                
                case NONE: case RIGHT: case LEFT: default: //tira warning si no lo ponemos
                //se queda en el mismo menu, no hace nada
                break;
        }
}

////////////////////////////////////////////////////////////////////////PAUSED
void processInputPaused(GameState * state, Input input){
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
                    (state->paused).selected = PAUSED_TITLE; //resteo menu
                break;
                case UP:
                    menuPrevious(&(state->paused));
                break;

                case DOWN:
                    menuNext(&(state->paused));
                break;

                case NONE: case RIGHT: case LEFT: default:
                //se queda en el mismo menu, no hace nada
                break;
    }
}

///////////////////////////////////////////////////////////GAME OVER
void processInputGameOver(GameState * state, Input input){
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
                    (state->gameOver).selected = GAME_OVER_TITLE; //reset menu
                break;
                case UP:
                    menuPrevious(&(state->gameOver));
                break;

                case DOWN:
                    menuNext(&(state->gameOver));
                break;

                case NONE: case RIGHT: case LEFT: default:
                //se queda en el mismo menu, no hace nada
                break;
    }
}

///////////////////////////////////////////////////////////VICTORY
void processInputVictory(GameState * state, Input input){
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
                    (state->victory).selected = VICTORY_TITLE; //reset menu
                break;
                case UP:
                    menuPrevious(&(state->victory));
                break;

                case DOWN:
                    menuNext(&(state->victory));
                break;

                case NONE: case RIGHT: case LEFT: default:
                //se queda en el mismo menu, no hace nada
                break;
    }
}
//////////////////////////////////////////////////////////POINTS
void processInputPoints(GameState * state, Input input){
        switch(input){
                case SELECT:
                    switch ( (state->points).selected ){
                        case POINTS_MENU: 
                            state->id = MENU;
                        break;

                        //agrego estos case para que no tire warning, pero no hacen nada
                        case POINT_1: case POINT_2: case POINT_3: case POINT_4: case POINT_5:
                        case POINT_6: case POINT_7: case POINT_8: case POINT_9: case POINT_10:
                            //todavia nada 
                        break;
                        
                        case POINTS_EXIT:
                            state->id = EXIT;
                        break;
                    }
                    (state->points).selected = POINTS_TITLE; //para que no se pueda seleccionar nada mas
                break;
                case UP:
                    menuPrevious(&(state->points));
                break;

                case DOWN:
                    menuNext(&(state->points));
                break;

                case NONE: case RIGHT: case LEFT: default:
                //se queda en el mismo menu, no hace nada
                break;
    }
}
/////////////////////////////GAME LOGIC///////////////////////
void processInputPlaying(GameState * state, Input input, Frog * frog){
    switch(input){
                case SELECT:
                    state->id = PAUSED;
                break;

                case UP:
                    moveFrog(frog,UP);
                break;

                case DOWN:
                    moveFrog(frog,DOWN);
                break;

                case RIGHT:
                    moveFrog(frog,RIGHT);
                break;

                case LEFT:
                    moveFrog(frog,LEFT);
                break;
    }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 