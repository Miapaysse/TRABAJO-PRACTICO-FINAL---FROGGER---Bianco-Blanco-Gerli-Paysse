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


/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum{
   UP,
   DOWN,
   LEFT,
   RIGHT,
   SELECT,
   NONE
} Input;

typedef enum{
   MENU,
   PLAYING,
   PAUSED,
   VICTORY,
   GAME_OVER,
   POINTS,
   EXIT
} GameStateId;

typedef enum{
    MENU_PLAY,
    MENU_POINTS,
    MENU_EXIT,
    MENU_COUNT
}MenuOption;

typedef enum{
    PAUSED_MENU,
    PAUSED_PLAY, //DISTINTO SERIA REPLAY!!!!! MANTENER VIDAS 
    PAUSED_EXIT,
    PAUSED_COUNT
}PausedOption;

typedef enum{
    GAME_OVER_MENU,
    GAME_OVER_EXIT,
    GAME_OVER_COUNT
}GameOverOption;

typedef enum{
    VICTORY_MENU,
    VICTORY_EXIT,
    VICTORY_COUNT
}VictoryOption;

typedef enum{
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


typedef struct {

   Frog frog;

   GameEntities entities;

   int score;

   int lives;

   Level level;

   Zone currentZone;

   GameState state;
   
} Game;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
 void processInputPlaying(GameState * state, Input input);
 void processInputMenu(GameState * state, Input input);
 void processInputPaused(GameState * state, Input input);
 void processInputGameOver(GameState * state, Input input);
 void processInputVictory(GameState * state, Input input);
 void processInputPoints(GameState * state, Input input);


 void updateGame(Game * game, Input input);
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
 void gameInit();
 /**
 * @brief TODO: initialize the game
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

void menuNext(MenuState *menu);
void menuPrevious(MenuState *menu);

void updateScore();

void updateZone();



/******************************************************************************/

#endif // _GAME_H_
