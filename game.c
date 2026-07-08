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
Game game;

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

 void updateGame(){
    switch (game.state){
        case MENU:
        break;
        case PLAYING:
            renderGame();
            switch (userAction){
                case DOWN: 
                    (game.frog).y-=1;
                break;
                case UP:
                    (game.frog).y+=1;
                break;
                case RIGHT:
                    (game.frog).x+=1;
                break;
                case LEFT:
                    (game.frog).x-=1;
                break;
                case PAUSE:
                    game.state = PAUSE;
                break;
            }
            if(runOverFrog(parametros)){}
            if(drownedFrog(parametros)){}
            if(arrivedAtFinishLine(parametros)){}

        break;
        case PAUSE:
        break;
        case GAME_OVER:
        break;
        case OFF:
        break;


    }
 }

 void endGame(){}
 void startGame(){
    int i;
    game.frog = frog;
    for(i=0; i<MAX_OBSTACLES; i++){
        (game.obstacles)[i]=createObstacle();
    }
    for(i=0; i<MAX_LOGS; i++){
        (game.logs)[i]=createLog();
    }
 }
 void renderGame(){}
 void showMenu(){}
 void showMenu(){}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 