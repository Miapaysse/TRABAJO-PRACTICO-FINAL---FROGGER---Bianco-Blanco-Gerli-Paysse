/***************************************************************************//**
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "levels.h"
#include "game.h"
#include <stddef.h>
#include <string.h>
#include "stdio.h"
/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

static Level_t level1={
    LEVEL_1,
    NULL, 
    {
        {NO_CHECKPOINT, NULL,NO_TYPE,START, 0, 0, 0, 0, DIR_LEFT},
        {NO_CHECKPOINT, NULL,NO_TYPE,START, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL,TRUCK ,ROAD, 2, TRUCK_LENGTH, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL,CAR,ROAD, 4, CAR_LENGTH, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL,CAR,ROAD, 2, CAR_LENGTH, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL,TRUCK,ROAD, 3, TRUCK_LENGTH, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL,CAR,ROAD, 2, CAR_LENGTH, MAX_GAP, SLOW, DIR_RIGHT},

        {CHECKPOINT_1, NULL,NO_TYPE,SAFE, 0, 0, 0, 0, DIR_LEFT},
        {CHECKPOINT_1, NULL,NO_TYPE,SAFE, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL,TRUNK_FLOATER,WATER, 2, MEDIUM, MAX_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL,TRUNK_FLOATER,WATER, 3, SMALL, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL,TRUNK_FLOATER,WATER, 2, LARGE, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL,TRUNK_FLOATER,WATER, 2, MEDIUM, MEDIUM_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL,TRUNK_FLOATER,WATER, 2, LARGE, MAX_GAP, SLOW, DIR_LEFT},

        {CHECKPOINT_FINISH_LINE, NULL,NO_TYPE,SAFE, 0, 0, 3, 0,},
        {NO_CHECKPOINT, NULL,NO_TYPE,SAFE, 0,}

    },
    {
        {1, 1, false},
        {4, 1, false},
        {7, 1, false},
        {10, 1, false},
        {13, 1, false}
    }
};

static Level_t level2={
    LEVEL_2,
    NULL, 
    {
        {NO_CHECKPOINT, NULL, NO_TYPE,START, 0, 0, 0, 0, DIR_LEFT},
        {NO_CHECKPOINT, NULL, NO_TYPE,START, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL, TRUCK,ROAD, 3, TRUCK_LENGTH, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, CAR,ROAD, 3, CAR_LENGTH, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, CAR,ROAD, 3, CAR_LENGTH, MEDIUM_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, TRUCK,ROAD, 3, TRUCK_LENGTH, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, TRUCK,ROAD, 2, TRUCK_LENGTH, MAX_GAP, MEDIUM_SPEED, DIR_RIGHT},

        {CHECKPOINT_1, NULL, NO_TYPE,SAFE, 0, 0, 0, 0, DIR_LEFT},
        {CHECKPOINT_1, NULL, NO_TYPE,SAFE, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL, TRUNK_FLOATER,WATER, 3, LARGE, MIN_GAP, MEDIUM_SPEED, DIR_LEFT},
        {NO_CHECKPOINT, NULL, TRUNK_FLOATER,WATER, 3, MEDIUM, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, TRUNK_FLOATER,WATER, 3, MEDIUM, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, LEAF,WATER, 3, SMALL, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, TRUNK_FLOATER,WATER, 2, LARGE, MAX_GAP, SLOW, DIR_LEFT},

        {CHECKPOINT_FINISH_LINE, NULL, NO_TYPE,SAFE, 0, 0, 3, 0, DIR_LEFT},
        {NO_CHECKPOINT, NULL, NO_TYPE,SAFE, 0, 0, 0, 0, DIR_LEFT}
    },
    {
        {1, 1, false},
        {4, 1, false},
        {7, 1, false},
        {10, 1, false},
        {13, 1, false}
    }
};

static Level_t level3={
    LEVEL_3,
    NULL, 
    {
        {NO_CHECKPOINT, NULL, NO_TYPE,START, 0, 0, 0, 0, DIR_LEFT},
        {NO_CHECKPOINT, NULL, NO_TYPE,START, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL, TRUCK,ROAD, 3, TRUCK_LENGTH, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, CAR,ROAD, 3, CAR_LENGTH, MEDIUM_GAP, MEDIUM_SPEED, DIR_LEFT},
        {NO_CHECKPOINT, NULL, CAR,ROAD, 2, CAR_LENGTH, MAX_GAP, FAST, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, TRUCK,ROAD, 3, TRUCK_LENGTH, MEDIUM_GAP, SLOW, DIR_LEFT},
        {NO_CHECKPOINT, NULL, TRUCK,ROAD, 2, TRUCK_LENGTH, MAX_GAP, MEDIUM_SPEED, DIR_RIGHT},

        {CHECKPOINT_1, NULL, NO_TYPE,SAFE, 0, 0, 0, 0, DIR_LEFT},
        {CHECKPOINT_1, NULL, NO_TYPE,SAFE, 0, 0, 0, 0, DIR_LEFT},

        {NO_CHECKPOINT, NULL, TRUNK_FLOATER,WATER, 3, MEDIUM, MAX_GAP, MEDIUM_SPEED, DIR_LEFT},
        {NO_CHECKPOINT, NULL, LEAF,WATER, 3, SMALL, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, TRUNK_FLOATER,WATER, 2, LARGE, MEDIUM_GAP, MEDIUM_SPEED, DIR_LEFT},
        {NO_CHECKPOINT, NULL, LEAF,WATER, 3, SMALL, MAX_GAP, SLOW, DIR_RIGHT},
        {NO_CHECKPOINT, NULL, TRUNK_FLOATER,WATER, 2, LARGE, MAX_GAP, SLOW, DIR_LEFT},

        {CHECKPOINT_FINISH_LINE, NULL, NO_TYPE,SAFE, 0, 0, 3, 0, DIR_LEFT},
        {NO_CHECKPOINT, NULL, NO_TYPE,SAFE, 0, 0, 0, 0, DIR_LEFT}

    },
    {
        {1, 1, false},
        {4, 1, false},
        {7, 1, false},
        {10, 1, false},
        {13, 1, false}
    }
};


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static int loadLevel(Level_t * level);
static void loadLevelEntities(Level_t* level);
static void loadZoneEntities(Row_t* rows, uint8_t  zoneStart, Entity_t* firstEntity);
static void loadRowEntities(Row_t* row, uint8_t  rowNumber);
static int checkLevelEntities(Level_t* level);
static int occupyFinishBox(Game_t *game);
static int allFinishBoxesOccupied(Game_t *game);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int arrivedAtFinishLine(uint8_t  y){
    if (y==FINISH_LINE){ //Detectamos si la rana llego a la linea de meta
        return 1;
    }
    return 0;
}


int checkLevel(Game_t * game){ //Si llego a la linea de meta chequeamos si cayo en una casilla libre y la ocupamos, si no esta libre la rana muere
    if(game != NULL){
        if (arrivedAtFinishLine((game->frog).y)){
                occupyFinishBox(game); 
        }
        return 0;
    }
    else {
        return ERR_INVALID_GAME_POINTER;
    }
}

int goToNextLevel(Game_t * game){ //Avanzamos al siguiente nivel dependiendo del nivel en el que estamos 
    int errorType;
    if(game != NULL){ 
        game->lastEntityUpdate = clock();
        switch((game->level).id){
            case LEVEL_1:
                game->level = level2; //Igualamos el nivel a la estrucutra predeterminada del nivel correspondiente
                game->level.entities = &game->entities; //Apuntamos el puntero de entidades a las entidades del juego
                if((errorType = loadLevel(&game->level))){ //Se inicializan las entidades del juego con las caracteristicas del nivel
                    return errorType;
                }
                return 0;
            break;

            case LEVEL_2:
                game->level = level3;
                game->level.entities = &game->entities;
                if((errorType = loadLevel(&game->level))){ //Se inicializan las entidades del juego con las caracteristicas del nivel
                    return errorType;
                }
                return 0;
            break;

            case LEVEL_3:
                game->state.id = VICTORY;
                return 0;

            default:
                return 0;
        }
    }
    else {
        return ERR_INVALID_GAME_POINTER;
    }
}

int initLevel(Game_t * game){
    int errorType;
    if(game != NULL){ //Validacion de puntero
        initFrog(&game->frog);
        game->level = level1;//Igualamos el nivel a la estrucutra predeterminada del nivel correspondiente
        game->level.entities = &game->entities; //Apuntamos las entidades del nivel a las entidades del juego
        if((errorType = loadLevel(&game->level))){ //Se inicializan las entidades del juego con las caracteristicas del nivel
            return errorType;
        }
        return 0;
    }
    else {
        return ERR_INVALID_GAME_POINTER;
    }
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static int loadLevel(Level_t * level){
 if(level != NULL){ 
    int errorType;
    resetFinishBoxes(level->finishBoxes);
    loadLevelEntities(level); //Cargamos las entidades con las caracteristicas del nivel
    if((errorType = checkLevelEntities(level))){ //Chequeamos que no excedamos el maximo de entidades
        return errorType;
    }

    else {
        return 0;
    }
 }
 else {
    return ERR_INVALID_LEVEL_POINTER;
 }
}


static void loadLevelEntities(Level_t* level){
    uint8_t  i;
    Entity_t * firstObstacle;
    Entity_t * firstFloater;
    *(level->entities) = (GameEntities_t){0}; //inicializa en cero para sacar basura
    firstObstacle = level->entities->obstacles;
    firstFloater = level->entities->floaters;
    for(i=0; i <= MAP_HEIGHT; i++){ //Recorremos las filas del mapa 
        switch(level->rows[i].zone){
            case ROAD: //Si estamos en la calle cargamos los obstaculos 
                loadZoneEntities(level->rows, i, firstObstacle);
                i+= MAX_PLAYING_ZONE_HEIGHT-1;
            break;
            case WATER: //Si estamos en la calle cargamos los obstaculos 
                loadZoneEntities(level->rows, i, firstFloater);
                i+=  MAX_PLAYING_ZONE_HEIGHT-1;
            break;
            case SAFE:
            case START:
            case DEFAULT:
            default:
            break;
        }
    }
}

static void loadRowEntities(Row_t* row, uint8_t rowNumber){
    uint8_t  k;
    int x0 = 0;
    for(k = 0; k<(row->entityCount); k++){ //Inicializamos cada entidad de la fila con las caracteristicas del nivel
        ((row->firstEntity)[k]).x = x0 + (row->entityLength+row->gap)*k;
        ((row->firstEntity)[k]).y = rowNumber;
        ((row->firstEntity)[k]).speed = row->speed;
        ((row->firstEntity)[k]).direction = row->direction;
        ((row->firstEntity)[k]).length = row->entityLength;
        ((row->firstEntity)[k]).type = row->type;
        ((row->firstEntity)[k]).active = true;
    }
}

static void loadZoneEntities(Row_t* rows, uint8_t  zoneStart, Entity_t* firstEntity){
    uint8_t  j;
    Entity_t *current = firstEntity;
    for(j=0; j<MAX_PLAYING_ZONE_HEIGHT; j++ ){ 
        rows[zoneStart + j].firstEntity = current; //Apuntamos el primer elemento de la fila segun los ultimos de las otras 
        current += rows[zoneStart + j].entityCount;
        loadRowEntities(&(rows[zoneStart+j]), zoneStart+j); //Cargamos los elementos de la fila
    }
}

static int checkLevelEntities(Level_t* level){ //Chequeamos que no nos excedimos del maximo de cada tipo de entidad al disenar el nivel 

    if(level != NULL){
            uint8_t  i; 
            uint8_t  obstacleCount = 0;
            uint8_t  floaterCount = 0;

            for ( i = 0; i < MAP_HEIGHT; i++) {

                if (level->rows[i].zone == ROAD){
                    obstacleCount += level->rows[i].entityCount;
                }

                if (level->rows[i].zone == WATER){
                    floaterCount += level->rows[i].entityCount;
                }
            }

            if(obstacleCount>MAX_OBSTACLES){
                return  ERR_MAX_OBSTACLES_EXCEEDED;
            }
            if(floaterCount>MAX_FLOATERS){
                return ERR_MAX_FLOATERS_EXCEEDED;
            }

            else{
                return 0;
            }
    }

 else {
    return ERR_INVALID_LEVEL_POINTER;
 }

}

static int occupyFinishBox(Game_t *game){
    int i;

    for(i = 0; i < FINISH_BOX_COUNT; i++){

        FinishBox_t *box = &(game->level.finishBoxes[i]);

        if(!box->occupied && frogInFinishBox(&(game->frog), box)){

            box->occupied = true;

            game->score += POINT_WEIGHT;

            if(allFinishBoxesOccupied(game)){
                (game->frog).lastCheckpoint = NO_CHECKPOINT; //Cuando pasamos de nivel reseteamos el checkpoint de la rana para que no se quede en el ultimo
                goToNextLevel(game);
                resetFrog(&(game->frog));
            }
            else{
                resetFrog(&(game->frog));
            }

            return 1;
        }
    }

    /* Llegó a la meta pero no cayó en ninguna casilla libre */
    frogDies(&(game->frog), &(game->lives), &(game->state.id));

    return 0;
}

static int allFinishBoxesOccupied(Game_t *game){
    int i;

    for(i = 0; i < FINISH_BOX_COUNT; i++){
        if(!game->level.finishBoxes[i].occupied){
            return 0;   // Encontramos una libre
        }
    }

    return 1;   // Todas están ocupadas
}

/******************************************************************************/
 
