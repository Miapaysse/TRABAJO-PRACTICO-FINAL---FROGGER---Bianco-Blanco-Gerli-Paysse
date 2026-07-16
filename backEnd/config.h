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
//MAP SETTINGS////////////////////////////////////////////////////////// 
#define MAP_WIDTH 15

#define MAP_HEIGHT 15

#define FINISH_LINE MAP_HEIGHT

#define MAX_PLAYING_ZONE_HEIGHT 6

//ENTITIES SETTINGS/////////////////////////////////////////////////////
#define MAX_OBSTACLES 15

#define MAX_FLOATERS 15

//FROG SETTINGS//////////////////////////////////////////////////////////

#define X0 (MAP_WIDTH/2)

#define Y0 0

//GAME SETTINGS/////////////////////////////////////////////////////////
#define MAX_LIVES 3

#define POINT_WEIGHT 50

#define MAX_SCORE 999

#define MIN_SCORE 0

#define TOP10_SIZE 10

#define TOP10_FILE "top10.txt"

///////////////////////////////////////////////////////////////////////////////
#define ISEVEN(x) ((x)%2==0)
////////////////////////////////////////////////////////////////
typedef enum{
  ERROR_TOO_MANY_OBSTACLES,
  ERROR_TOO_MANY_FLOATERS
}ErrorType;
/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


#endif // _CONFIG_H_
