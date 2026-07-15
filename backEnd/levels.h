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



/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/


typedef enum{
    ROAD,
    SAFE,
    WATER,
    START
} Zone;

typedef enum{
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_COUNT
} LevelId;

typedef struct {
    LevelId id;
    Row rows[MAP_HEIGHT];
    GameEntities entities;
} Level;

typedef struct{

    Zone zone;

    uint8_t firstEntity;

    uint8_t entityCount;

    uint16_t speed;

    Direction direction;

    uint8_t gap;

    uint8_t entityLength;

} Row;


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

static void loadLevel1Zones(Level * level);

static void loadLevel1Obstacles(Game * game);

static void loadLevel1Floaters(Game * game);

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

static Entity createEntity(Position pos,
                           uint8_t length,
                           Direction direction,
                           EntityType type);

#endif // _LEVELS_H_
