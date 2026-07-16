/***************************************************************************//**
  @file     +raspiFrontend.h+
  @brief    +Constantes y typedef para la raspi+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

#ifndef RASPI_H
#define RASPI_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include "game.h"
#include "config.h"

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

#define JOY_LIM 50 //Limite para detectar movimiento del joystic
typedef int DISP[MAP_WIDTH][MAP_HEIGHT]; //matriz 2D que simula display


//------ Macros para definir coordenadas score y espacio entre digitos del score -----
#define SCORE_YCOORD 4
#define SCORE_XCOORD 2
#define SPACE_DIGITS 1
#define DIGITS 3
#define DIGIT_WIDTH 3
#define DIGIT_HEIGHT 5

#define SCORE_ID_YCOOR 11
#define SCORE_ID_XCOOR 3

//------ Macros para dibujar menus en matriz
#define MAX_MENUS 10

/***************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void frontendInit(void);
Input frontendGetInput(void);
void frontendRender(Game * game);
void frontendDestroy(void);


#endif
