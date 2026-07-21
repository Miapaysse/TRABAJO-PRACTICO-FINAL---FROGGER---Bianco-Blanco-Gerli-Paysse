/***************************************************************************//**
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

#ifndef _ENTITIES_H_
#define _ENTITIES_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "config.h"
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct Game Game_t; //necesario aca 

typedef enum{//enum para la direccion de las entidades
    DIR_LEFT,
    DIR_RIGHT
} Direction_t;

typedef enum {//enum para la orientacion de la rana
    FROG_UP,
    FROG_DOWN,
    FROG_LEFT,
    FROG_RIGHT
} FrogOrientation_t;

typedef enum{//enum para la velocidad de las entidades
    SLOW=1,
    MEDIUM_SPEED,
    FAST
} Speed_t;

typedef enum{//enum para los checkpoints
    NO_CHECKPOINT,
    CHECKPOINT_1,
    CHECKPOINT_FINISH_LINE,
    CHECKPOINT_COUNT
} CheckpointId_t;

typedef enum{//enum para los tipos de entidades
    NO_TYPE,
    CAR,
    TRUCK,
    TRUNK_FLOATER,
    LEAF
} EntityType_t;

typedef struct{ //struct para la rana
    int  x; 
    int  y;
    Speed_t speed;
    Direction_t direction;
    FrogOrientation_t frogOrientation;
    CheckpointId_t lastCheckpoint;
} Frog_t;

typedef struct{//struct para las entidades
    int  x; 
    int  y;
    uint8_t  length;
    Speed_t speed;
    Direction_t direction;
    EntityType_t type;
    bool active;
} Entity_t;

typedef struct{//struct para las entidades del juego
    Entity_t obstacles[MAX_OBSTACLES];
    Entity_t floaters[MAX_FLOATERS];
} GameEntities_t;

typedef struct{//struct para los espacios de llegada
    uint8_t x;
    uint8_t length;
    bool occupied;
} FinishBox_t;




/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/



/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

int initFrog(Frog_t * frog);
/**
 * @brief TODO: Inicializamos la rana, la ubicamos en su posicion inical 
 * @param frog Recibimos un puntero a la rana del juego para settear sus condiciones iniciales
 * @return Devuelve un entero para manejo de errores
*/

int resetFrog(Frog_t * frog);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Devuelve un entero para manejo de errores
*/

int moveFrog(Frog_t * frog , Input_t input);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Devuelve un entero para manejo de errores
*/

int moveFrogWithFloater(Frog_t * frog , Entity_t* floater);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

int updateEntities(Game_t *game);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
int frogDies(Frog_t * frog, uint8_t* lives, GameStateId_t* id);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
int frogInFinishBox(Frog_t * frog, FinishBox_t *finishBox);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/

int resetFinishBoxes(FinishBox_t *finishBox);
/**
 * @brief TODO: completar descripcion
 * @param param1 Descripcion parametro 1
 * @param param2 Descripcion parametro 2
 * @return Descripcion valor que devuelve
*/
/******************************************************************************/

#endif // _ENTITIES_H_
