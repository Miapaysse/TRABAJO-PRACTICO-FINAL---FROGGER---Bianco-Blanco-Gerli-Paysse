/***************************************************************************//**
  @file     +game.h+
  @brief    +game data types and functions+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

#ifndef _GAME_H_
#define _GAME_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "config.h"
#include "entities.h"
#include "levels.h"
#include <time.h>
#include <stdint.h>
#include "top10.h"

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef enum{
    MENU_TITLE,
    MENU_PLAY,
    MENU_POINTS,
    MENU_EXIT,
    MENU_COUNT
} MenuOption_t;

typedef enum{
    PAUSED_TITLE,
    PAUSED_MENU,
    PAUSED_PLAY, 
    PAUSED_EXIT,
    PAUSED_COUNT
}PausedOption_t;

typedef enum{
    GAME_OVER_TITLE,
    GAME_OVER_MENU,
    GAME_OVER_EXIT,
    GAME_OVER_COUNT
}GameOverOption_t;

typedef enum{
    VICTORY_TITLE,
    VICTORY_MENU,
    VICTORY_EXIT,
    VICTORY_COUNT
}VictoryOption_t;

typedef enum{
    POINTS_TITLE,
    POINT_1,
    POINT_2,
    POINT_3,
    POINT_4,
    POINT_5,
    POINT_6,
    POINT_7,
    POINT_8,
    POINT_9,
    POINT_10,
    POINTS_MENU,
    POINTS_EXIT,
    POINTS_COUNT
}PointsOption_t;

typedef struct{

    int selected;

    int optionCount;

} MenuState_t;

typedef struct{

    MenuState_t menu;
    MenuState_t paused;
    MenuState_t gameOver;
    MenuState_t victory;
    MenuState_t points;

    GameStateId_t id;

} GameState_t;



typedef struct Game {

   Frog_t frog;

   GameEntities_t entities;

   uint16_t score;
   
   Top10_t top10;

   uint8_t  lives;

   Level_t level;

   GameState_t state;

   clock_t lastEntityUpdate;

   clock_t timeNow;
   
} Game_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


int updateGame(Game_t * game, Input_t input);
 /**
 * @brief TODO: updates the game
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

 int gameInit(Game_t* game);
 /**
 * @brief TODO: initialize the game
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

void menuNext(MenuState_t *menu);
void menuPrevious(MenuState_t *menu);

/******************************************************************************/

#endif // _GAME_H_
