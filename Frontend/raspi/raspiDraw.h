#ifndef RASPI_DRAW_H
#define RASPI_DRAW_H

#include <stdint.h>
#include "config.h"
#include "levels.h"
// Para usar el typedef DISP y los macros

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
	MSG_MAX_MENUS
};

// Exponemos la matriz de mensajes para que frontendRender pueda usarla
extern const uint16_t msgsDisp[MSG_MAX_MENUS][MAP_HEIGHT + 1];

// Prototipos de funciones de dibujo

void drawZone(const Row * rows);
void drawObstacles(const Entity obstacles[]);
void drawFloaters(const Entity floaters[]);
void drawFrog(const Frog * frog, int blink);

void drawMSG(const uint16_t bitmap[MAP_HEIGHT+1]);
void drawScore(int idxScore, uint16_t score);
void drawBoxes (FinishBox boxes[], int blink);

void showRank(const Top10Status status);
void showScore(const uint16_t score);
void showLevelNextLevel(const LevelId currentLevel, LevelId * lastLevel);
void showLives(const uint8_t currentLives, uint8_t * lastLives);
#endif