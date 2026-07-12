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
 * @brief Funciones para incializar, actualizar y apagar frontend segun backend
*/
void frontendInit(void);
Input frontendGetInput(void);
void frontendRender(Game * game);
void frontendDestroy(void);

#endif

