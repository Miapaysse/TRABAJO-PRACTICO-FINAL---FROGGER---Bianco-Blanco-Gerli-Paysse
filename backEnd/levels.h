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

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum{
    SLOW=1,
    MEDIUM_SPEED,
    FAST
}Speed

typedef enum{
    SMALL=2,
    MEDIUM,
    LARGE
}FloaterLength

typedef enum{
    CAR_LENGTH=1,
    TRUCK_LENGTH
}ObstacleLength

typedef enum{
    MIN_GAP=1,
    MEDIUM_GAP,
    MAX_GAP
}RowGap

typedef enum{
    ROAD,
    SAFE,
    WATER,
    START,
    DEFAULT
} Zone;

typedef enum{
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_COUNT
} LevelId;

typedef struct{

    Zone zone;

    Entity* firstEntity;

    int entityCount;

    RowGap gap;

}Row;

typedef struct{

    Entity* firstEntity;

    Zone zone;

    int entityCount;

    int speed;

    int entityLength;

    int gap;

}Row;

typedef struct {
    LevelId id;
    GameEntities* entities;
    Row rows[MAP_HEIGHT];
} Level;


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

 void createLevel();
 void deleteLevel();
 void checkLevel();
 void goToNextLevel(Level* level);
 
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

bool arrivedAtFinishLine(int y);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
 */

/**************************PRIVATE****************************************************/
static void createLevel1(Game * game);
s
static void loadZones(Level * level);

static void loadLevel1Obstacles(Game * game);

static void loadLevel1Floaters(Game * game);

/*
static void configureObstacleRow(Game * game,
                                 uint8_t row,
                                 uint8_t entityCount,
                                 uint8_t entityLength,
                                 uint8_t gap,
                                 uint16_t speed,
                                 Direction direction);

static void configureFloaterRow(Game * game,
                                uint8_t row,
                                uint8_t entityCount,
                                uint8_t entityLength,
                                uint8_t gap,
                                uint16_t speed,
                                Direction direction);

*/ //ESTAS SE CAMBIAN POR:

static void configureRow(Game *game,
                         Zone zone,
                         EntityType type,
                         uint8_t row,
                         uint8_t entityCount,
                         uint8_t entityLength,
                         uint8_t gap,
                         uint16_t speed,
                         Direction direction);


#endif // _LEVELS_H_
