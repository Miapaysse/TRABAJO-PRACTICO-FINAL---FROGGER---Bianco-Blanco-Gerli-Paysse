/***************************************************************************//**
  @file     +raspiFrontend.h+
  @brief    +Constantes y typedef para la raspi+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

#ifndef RASPI_H
#define RASPI_H

#include <stdint.h>
#include "game.h"
#include "config.h"

#define JOY_LIM 50 //Limite para detectar movimiento del joystic
typedef int DISP[MAP_WIDTH + 1][MAP_HEIGHT + 1]; //matriz 2D que simula display
#define ROW(r) ((MAP_HEIGHT) - r)

//------ Macros para definir coordenadas score y espacio entre digitos del score -----
#define SCORE_YCOORD 4
#define SCORE_XCOORD 2
#define SPACE_DIGITS 1
#define DIGITS 3
#define DIGIT_WIDTH 3
#define DIGIT_HEIGHT 5

#define SCORE_ID_YCOOR 11
#define SCORE_ID_XCOOR 3

#define TIME_BLINK_FROG 750
#define TIME_BLINK_BOX 900

#define DISPLAY_MENU_TIME 800000
#define DISPLAY_INFO_TIME 1000000


void frontendInit(void);
Input frontendGetInput(void);
void frontendRender(Game * game);
void frontendDestroy(void);

#endif