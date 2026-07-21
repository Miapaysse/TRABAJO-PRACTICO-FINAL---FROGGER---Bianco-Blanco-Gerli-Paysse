/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

#ifndef _LEVELS_H_
#define _LEVELS_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "entities.h"
#include "config.h"
#include <stdint.h>
  
/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct Game Game_t; //va aca

typedef enum{
    SMALL=2,
    MEDIUM,
    LARGE
}FloaterLength_t;

typedef enum{
    CAR_LENGTH=1,
    TRUCK_LENGTH
}ObstacleLength_t;

typedef enum{
    MIN_GAP=1,
    MEDIUM_GAP,
    MAX_GAP
}RowGap_t;

typedef enum{
    ROAD,
    SAFE,
    WATER,
    START,
    DEFAULT
} Zone_t;

typedef enum{
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_COUNT
} LevelId_t;



typedef struct{

    CheckpointId_t checkpoint;

    Entity_t* firstEntity;

    EntityType_t type;

    Zone_t zone;

    uint8_t  entityCount;

    int  entityLength;

    RowGap_t gap;

    Speed_t speed;

    Direction_t direction;

}Row_t;

typedef struct {
    LevelId_t id;
    GameEntities_t* entities;
    Row_t rows[MAP_HEIGHT+1];
    FinishBox_t finishBoxes[5];
} Level_t;


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
int initLevel(Game_t * game);
int checkLevel(Game_t * game);
int goToNextLevel(Game_t * game);
int arrivedAtFinishLine(uint8_t  y);

/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/



#endif // _LEVELS_H_
