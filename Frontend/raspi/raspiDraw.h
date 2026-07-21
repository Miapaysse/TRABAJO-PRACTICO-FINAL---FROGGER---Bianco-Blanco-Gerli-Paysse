/***************************************************************************//**
  @file     +raspiDraw.h+
  @brief    +Parametros y prototipos de funciones para dibujar sobre el display+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

#ifndef RASPI_DRAW_H
#define RASPI_DRAW_H


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/


#include <stdint.h>
#include "config.h"
#include "levels.h"
// Para usar el typedef DISP y los macros


/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

// Enumerador de mensajes para acceder a la matriz
enum msgs {
	MSG_HOME,
	MSG_PAUSE,
	MSG_TOP_10,
	MSG_PLAY,
	MSG_GO_HOME,
	MSG_DESPAUSE,
	MSG_GO_TOP_10,
	MSG_GO_BACK,
	MSG_EXIT,
	MSG_GAME_OVER,
	MSG_YOU_WIN,
	LIVE_LOSED,
	NEXT_LEVEL,
	MY_RANKING,
	MSG_ERROR,
	MSG_MAX_MENUS
};


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// Exponemos la matriz de mensajes para que frontendRender pueda usarla
extern const uint16_t msgsDisp[MSG_MAX_MENUS][MAP_HEIGHT + 1];


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void drawZone(const Row_t * rows);
/**
 * @brief TODO: dibuja zona en display, fila por fila según backend
 * @param param1 rows puntero a arreglo con las caracteristicas de cada fila
 * @return Nada
*/

void drawObstacles(const Entity_t obstacles[]);
/**
 * @brief TODO: dibuja obstáculos 
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Nada
*/

void drawFloaters(const Entity_t floaters[]);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Nada
*/

void drawFrog(const Frog_t * frog, int blink);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Nada
*/

void drawMSG(const uint16_t bitmap[MAP_HEIGHT+1]);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Nada
*/

void drawScore(int idxScore, uint16_t score);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Devuelve un entero para manejo de errores
*/

void drawBoxes (FinishBox_t boxes[], int blink);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Nada
*/

void showRank(const Top10Status_t status);
void showScore(const uint16_t score);
void showLevelNextLevel(const LevelId_t currentLevel, LevelId_t* lastLevel);
void showLives(const uint8_t currentLives, uint8_t * lastLives);
#endif