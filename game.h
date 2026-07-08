/***************************************************************************//**
  @file     +game.h+
  @brief    +game data types and functions+
  @author   +Mia Paysse+
 ******************************************************************************/

#ifndef _GAME_H_
#define _GAME_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "config.h"
#include "entities.h"


/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum{
   UP,
   DOWN,
   LEFT,
   RIGHT
} Direction;

typedef enum{
   MENU=5,
   PLAYING,
   PAUSED,
   GAME_OVER,
   OFF
} GameState;

typedef struct{
   int y,
   int x,
} Position;

int userAction;

typedef struct {

   Frog frog;

   Obstacle obstacles[MAX_OBSTACLES];

   Log logs[MAX_LOGS];

   //int obstacleCount;

   int score;

   int lives;

   int level;

   GameState state;

} Game;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
 
 void updateGame();
 /**
 * @brief TODO: updates the game
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
 void endGame();
 /**
 * @brief TODO: ends the game
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
 void startGame();
 /**
 * @brief TODO: initialize the game
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

 void renderGame();
  /**
 * @brief TODO: initialize the game
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

void showMenu();

void showPause();
/******************************************************************************/

#endif // _GAME_H_
