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
}MenuOption;

typedef enum{
    PAUSED_TITLE,
    PAUSED_MENU,
    PAUSED_PLAY, 
    PAUSED_EXIT,
    PAUSED_COUNT
}PausedOption;

typedef enum{
    GAME_OVER_TITLE,
    GAME_OVER_MENU,
    GAME_OVER_EXIT,
    GAME_OVER_COUNT
}GameOverOption;

typedef enum{
    VICTORY_TITLE,
    VICTORY_MENU,
    VICTORY_EXIT,
    VICTORY_COUNT
}VictoryOption;

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
}PointsOption;

typedef struct{

    int selected;

    int optionCount;

} MenuState;

typedef struct{

    MenuState menu;
    MenuState paused;
    MenuState gameOver;
    MenuState victory;
    MenuState points;

    GameStateId id;

} GameState;



typedef struct Game {

   Frog frog;

   GameEntities entities;

   uint16_t score;
   
   Top10_t top10;

   uint8_t  lives;

   Level level;

   GameState state;

   clock_t lastEntityUpdate;

   clock_t timeNow;
   
} Game;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


 void updateGame(Game * game, Input input);
 /**
 * @brief TODO: updates the game
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

 int gameInit(Game*game);
 /**
 * @brief TODO: initialize the game
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

void menuNext(MenuState *menu);
void menuPrevious(MenuState *menu);

/******************************************************************************/

#endif // _GAME_H_
