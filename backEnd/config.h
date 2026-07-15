/***************************************************************************//**
  @file     +config.h+
  @brief    +Constantes de configuracion del juego+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

#ifndef _CONFIG_H_
#define _CONFIG_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/



/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/


#define MAX_OBSTACLES 15

#define MAX_FLOATERS 15

#define MAX_ZONES 3

#define MAX_LIVES 3

#define MAP_WIDTH 16

#define MAP_HEIGHT 16

#define FINISH_LINE MAP_HEIGHT

#define X0 (MAP_WIDTH/2)

#define Y0 0

#define POINT_WEIGHT 50

#define MAX_SCORE 999

#define TOP10_SIZE 10

#define TOP10_FILE "top10.txt"
/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


#endif // _CONFIG_H_
