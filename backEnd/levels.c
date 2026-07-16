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
            {NULL,ROAD,3,TRUCK_LENGTH,MAX_GAP,MEDIUM_SPEED,DIR_LEFT},

            {NULL, SAFE, 0, 0, 0, 0 },

            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,SMALL,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,SLOW,DIR_RIGHT},

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
            {NULL,ROAD,3,TRUCK_LENGTH,MAX_GAP,MEDIUM_SPEED,DIR_LEFT},

            {NULL, SAFE, 0, 0, 0, 0 },

            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,SMALL,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,SLOW,DIR_RIGHT},

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
            {NULL,ROAD,3,TRUCK_LENGTH,MAX_GAP,MEDIUM_SPEED,DIR_LEFT},

            {NULL, SAFE, 0, 0, 0, 0 },

            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,SMALL,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,SLOW,DIR_RIGHT},
            {NULL,WATER,3,LARGE,MEDIUM_GAP,MEDIUM_SPEED,DIR_LEFT},
            {NULL,WATER,3,MEDIUM,MEDIUM_GAP,SLOW,DIR_RIGHT},

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
    static void loadZoneEntities(Row* rows, int zoneStart, Entity* firstEntity);
    static void loadRowEntities(Row* row, int row);

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
  int arrivedAtFinishLine(int y){
        //VALIDAR PUNTEROS

        if (y==FINISH_LINE){
            return 1;
        }
        return 0;
  }

  void checkLevel(Frog* frog, Level* level){
      if (arrivedAtFinishLine(frog->y)){
            goToNextLevel(level);
            resetFrog(frog);
      }
  }

  void goToNextLevel(Level* level){
    level->id ++;
    switch(game->level.id){
        case LEVEL_1:
            loadLevel(&level1);
            *level=level1;
        break;

        case LEVEL_2:
            loadLevel(&level2);
            *level=level2;

        break;

        case LEVEL_3:
            loadLevel(&level3);
            *level=level3;

        break;
    }
  }

  void initLevel(Game * game){
    game->level->entities = &(game->entities);
    loadLevel(&level1);
    game->level=level1;
  }

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void loadLevel(Level * level){
    loadLevelEntities(level);
    checkLevelEntities(level);
}


static void loadLevelEntities(Level* level){
    int i;
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


static void loadRowEntities(Row* row, int row){
    int k;
    int x0 = 0;
    for(k = 0; k<(row->entityCount); k++){
        ((row->firstEntity)[k]).x = x0 + (row->entityLength+row->gap)*k;
        ((row->firstEntity)[k]).y = row;
        ((row->firstEntity)[k]).speed = row->speed;
        ((row->firstEntity)[k]).direction = row->direction;
        ((row->firstEntity)[k]).length = row->entityLength;
    }
}

static void loadZoneEntities(Row* rows, int zoneStart, Entity* firstEntity){
    int j;
    Entity *current = firstEntity;
    for(j=0; j<MAX_PLAYING_ZONE_HEIGHT; j++ ){ 
        rows[zoneStart + j].firstEntity = current;
        current += rows[zoneStart + j].entityCount;
        loadRowEntities(rows[zoneStart+j], zoneStart+j); 
    }
}

static int checkLevelEntities(){
    int obstacleCount = 0;
    int floaterCount = 0;

    for (int i = 0; i < MAP_HEIGHT; i++) {

        if (level->rows[i].zone == ROAD){
            obstacleCount += level->rows[i].entityCount;
        }

        if (level->rows[i].zone == WATER){
            floaterCount += level->rows[i].entityCount;
        }
    }
}



/******************************************************************************/
 