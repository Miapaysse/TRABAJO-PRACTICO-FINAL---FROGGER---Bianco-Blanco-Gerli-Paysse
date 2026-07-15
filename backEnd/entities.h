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



/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef enum{
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef struct{
    int x;
    int y;
    int lastSafeSpot;
} Frog;

typedef struct{
    int x;
    int y;
    int length;
    int height; 
    int speed;
    Direction direction;
    int type;
    bool active;
}Entity;

typedef struct{
    Entity obstacles[MAX_OBSTACLES];
    Entity floaters[MAX_FLOATERS];
}GameEntities;

typedef struct{

    Zone zone;

    Entity* firstEntity;

    int entityCount;

    int gap;

} Row;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/



/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void createFrog();
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

void resetFrog();
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

void moveFrog();
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

void moveFrogWithFloater();

void createEntities();
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

void updateEntities();
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

/******************************************************************************/

#endif // _ENTITIES_H_
