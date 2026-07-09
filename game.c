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
            switch(input){
                case SELECT:
                    switch ( ((game->state).menu) ){
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
                    if(((game->state).menu) == max())
                break;

                case DOWN:
                break;
            }

        break;
        case PLAYING:

            processInput();

            updateEntities();

            checkCollisions();

            updateScore();

            checkLevel();

        break;
        case PAUSE:
            switch (((game->state).paused)){
                case PAUSED_MENU: 
                break;
                case PAUSED_PLAY:
                break;
                case PAUSED_EXIT:
                break;
            }
        break;
        case VICTORY:
            switch (((game->state).victory)){
                case VICTORY_MENU: 
                break;
                case VICTORY_EXIT:
                break;
            }
        break;
        case GAME_OVER:
            switch (((game->state).gameOver)){
                case GAME_OVER_MENU: 
                break;
                case GAME_OVER_EXIT:
                break;
            }
        break;
        case POINTS:
            switch (((game->state).points)){
                case GAME_OVER_MENU: 
                break;
                case GAME_OVER_EXIT:
                break;
            }
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


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 