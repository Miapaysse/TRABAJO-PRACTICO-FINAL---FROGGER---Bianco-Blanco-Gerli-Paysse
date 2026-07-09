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

#define MAX_OBSTACLES 30

#define MAX_LOGS 30

#define LIVES 3

#define MAP_WIDTH 20

#define MAP_HEIGHT 15

#define START_ROWS 2
#define SAFE_ROWS  1
#define FINISH_ROWS  1

#define FISHIN_LINE (MAP_HEIGHT)



#define ROAD_ROWS  ((MAP_HEIGHT - START_ROWS - SAFE_ROWS - GOAL_ROWS) / 2)
#define WATER_ROWS (MAP_HEIGHT - START_ROWS - SAFE_ROWS - GOAL_ROWS - ROAD_ROWS)


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


#endif // _CONFIG_H_
