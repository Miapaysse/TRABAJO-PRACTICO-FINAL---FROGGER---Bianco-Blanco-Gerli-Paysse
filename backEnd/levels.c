/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "levels.h"

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

    static Level level1={
        LEVEL_1,
        NULL, 
        {
            {NULL, START, 0, 0, 0, 0 },
            {NULL, START, 0, 0, 0, 0 },

            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_RIGHT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_RIGHT},

            {NULL, SAFE, 0, 0, 0, 0 },
            {NULL, SAFE, 0, 0, 0, 0 },

            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,SMALL,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            
            {NULL, SAFE, 0, 0, 0, 0 },
            {NULL, SAFE, 0, 0, 0, 0 },

        }
    };

    static Level level2={
        LEVEL_2,
        NULL, 
        {
            {NULL, START, 0, 0, 0, 0 },
            {NULL, START, 0, 0, 0, 0 },

            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_RIGHT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_RIGHT},

            {NULL, SAFE, 0, 0, 0, 0 },
            {NULL, SAFE, 0, 0, 0, 0 },

            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,SMALL,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            
            {NULL, SAFE, 0, 0, 0, 0 },
            {NULL, SAFE, 0, 0, 0, 0 },

        }
    };

    static Level level3={
        LEVEL_3,
        NULL, 
        {
            {NULL, START, 0, 0, 0, 0 },
            {NULL, START, 0, 0, 0, 0 },

            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_RIGHT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,ROAD,3,CAR_LENGTH,MEDIUM_GAP,MEDIUM_SPEED,DIR_RIGHT},
            
            {NULL, SAFE, 0, 0, 0, 0 },
            {NULL, SAFE, 0, 0, 0, 0 },

            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,SMALL,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            
            {NULL, SAFE, 0, 0, 0, 0 },
            {NULL, SAFE, 0, 0, 0, 0 },

        }
    };

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

    static void loadLevel(Level * level);

    static void loadLevelEntities(Level* level);
    static void loadZoneEntities(Row* rows, uint8_t  zoneStart, Entity* firstEntity);
    static void loadRowEntities(Row* row, uint8_t  row);

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
        if (y==FINISH_LINE){
            return 1;
        }
        return 0;
  }

  void checkLevel(Game * game){
    
      if (arrivedAtFinishLine((game->frog).y)){
            goToNextLevel(game);
            resetFrog(&(game->frog));
      }
  }

  int goToNextLevel(Game * game){
    if(game != NULL){ 
        switch((game->level).id){
            case LEVEL_1:
                game->level = level2;
                game->level.entities = &game->entities;
                if(errorType=loadLevel(&game->level)){ //Se inicializan las entidades del juego con las caracteristicas del nivel
                    return errorType;
                }
                else{
                    return 0;
                }
            break;

            case LEVEL_2:
                game->level = level3;
                game->level.entities = &game->entities;
                if(errorType=loadLevel(&game->level)){ //Se inicializan las entidades del juego con las caracteristicas del nivel
                    return errorType;
                }
                else{
                    return 0;
                }
            break;

            default:
                return;
        }
    }
    else {
        return ERR_INVALID_GAME_POINTER;
    }
  }

  int initLevel(Game * game){
    int errorType;
    if(game != NULL){ //Validacion de puntero
        game->level = level1;//Se inicializa el nivel con nivel1
        game->level.entities = &game->entities;
        if(errorType=loadLevel(&game->level)){ //Se inicializan las entidades del juego con las caracteristicas del nivel
            return errorType;
        }
        else{
            return 0;
        }
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

static int loadLevel(Level * level){
 if(level != NULL){ 
    int errorType;
    loadLevelEntities(level);
    if(errorType = checkLevelEntities(level)){
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


static void loadLevelEntities(Level* level){
    uint8_t  i;
    Entity * firstObstacle;
    Entity * firstFloater;
    firstObstacle = level->entities->obstacles;
    firstFloater = level->entities->floaters;
    for(i=0; i<MAP_HEIGHT; i++){
        switch(level->rows[i].zone){
            case ROAD:
                loadZoneEntities(level->rows, i, firstObstacle);
                i+=MAX_PLAYING_ZONE_HEIGHT-1;
            break;
            case WATER:
                loadZoneEntities(level->rows, i, firstFloater);
                i+=MAX_PLAYING_ZONE_HEIGHT-1;
            break;
        }
    }
}


static void loadRowEntities(Row* row, uint8_t rowNumber){
    uint8_t  k;
    int x0 = 0;
    for(k = 0; k<(row->entityCount); k++){
        ((row->firstEntity)[k]).x = x0 + (row->entityLength+row->gap)*k;
        ((row->firstEntity)[k]).y = rowNumber;
        ((row->firstEntity)[k]).speed = row->speed;
        ((row->firstEntity)[k]).direction = row->direction;
        ((row->firstEntity)[k]).length = row->entityLength;
    }
}

static void loadZoneEntities(Row* rows, uint8_t  zoneStart, Entity* firstEntity){
    uint8_t  j;
    Entity *current = firstEntity;
    for(j=0; j<MAX_PLAYING_ZONE_HEIGHT; j++ ){ 
        rows[zoneStart + j].firstEntity = current;
        current += rows[zoneStart + j].entityCount;
        loadRowEntities(&(rows[zoneStart+j]), zoneStart+j); 
    }
}

static int checkLevelEntities(Level* level){

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



/******************************************************************************/
 