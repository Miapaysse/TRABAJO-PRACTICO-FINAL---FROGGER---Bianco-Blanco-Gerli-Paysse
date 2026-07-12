/***************************************************************************//**
  @file     +raspiFrontend.h+
  @brief    +Funcionees para el frontend de la raspi+
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
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


 ***************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Dibuja la rana segun las coordenadas recibidas del backend
*/
void moveFrog(int x, int y);

/**
 * @brief Dibuja la obstaculos segun las coordenadas recibidas del backend y que tipo de obstaculo es auto/tronco
*/
void drawObstacle(int x, int y, int length, uint8_t type);

/**
 * @brief Imprime puntaje en display segun las calculos del backend
*/
void printScore(int score, int mode);

/**
 * @brief Funciones para incializar, actualizar y apagar frontend segun backend
*/
void frontendInit(void);
Input frontendGetInput(void);
void frontendRender(Game * game);
void frontendDestroy(void);

#endif

