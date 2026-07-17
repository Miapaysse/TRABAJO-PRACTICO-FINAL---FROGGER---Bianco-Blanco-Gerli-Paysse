/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

#ifndef _ENTITIES_H_
#define _ENTITIES_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "config.h"
#include "game.h"

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef enum{
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef enum{
    SLOW=1,
    MEDIUM_SPEED,
    FAST
}Speed

typedef struct{
    uint8_t  x;
    uint8_t  y;
    Speed speed;
    uint8_t  lastSafeSpot;
} Frog;

typedef struct{
    uint8_t  x;
    uint8_t  y;
    uint8_t  length;
    //int height; 
    Speed speed;
    Direction direction;
    int type;
    bool active;
}Entity;

typedef struct{
    Entity obstacles[MAX_OBSTACLES];
    Entity floaters[MAX_FLOATERS];
}GameEntities;



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/



/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

int initFrog(Frog * frog);
/**
 * @brief TODO: Inicializamos la rana, la ubicamos en su posicion inical 
 * @param frog Recibimos un puntero a la rana del juego para settear sus condiciones iniciales
 * @return Devuelve un entero para manejo de errores
*/

int resetFrog(Frog * frog);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

int moveFrog(Frog * frog , Input input);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

int moveFrogWithFloater(Frog * frog , Entity* floater);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

int updateEntities();
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

/******************************************************************************/

#endif // _ENTITIES_H_
