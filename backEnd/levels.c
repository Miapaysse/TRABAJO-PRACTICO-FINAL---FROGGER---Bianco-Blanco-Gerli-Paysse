/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

// +Incluir el header propio (ej: #include "template.h")+


/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/
    Level level1;
    Level level2;
    Level level3;

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static void falta_envido (int);+


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
  bool arrivedAtFinishLine(int y){
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
            break;

        case LEVEL_2:
            break;

        case LEVEL_3:
            break;
    }
  }

  void loadLevels(Game * game){
    createLevel1(game);
    loadZones(&(game->level)); //ACA HAY ALGO RARO, ESTOY LODEANDO 2 VECES LAS ZONAS, PUEDO MEJORARLO
  }



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


static void loadZones(Level* level){
    level->rows[1].zone = START;
    level->rows[0].zone = START;
    
    level->rows[2].zone = ROAD;
    level->rows[3].zone = ROAD;
    level->rows[4].zone = ROAD;
    level->rows[5].zone = ROAD;
    level->rows[6].zone = ROAD;
    level->rows[7].zone = ROAD;


    level->rows[8].zone = SAFE;

    level->rows[9].zone = WATER;
    level->rows[10].zone = WATER;
    level->rows[11].zone = WATER;
    level->rows[12].zone = WATER;
    level->rows[13].zone = WATER;
    level->rows[14].zone = WATER;

    level->rows[15].zone = SAFE;
}


static void createLevel1(Game * game)
{
    level1.id = LEVEL_1;
    level1.entities = &(game->entities);
    loadZones(&level1);
    loadLevel1Entities(&level1);
}

static void loadLevel1Entities(Level* level){
    int i, j, k;
    Entity * previousObstacle, previousFloater;
    firstObstacle = level->entities->obstacles;
    firstFloater = level->entities->floaters;
    int x0 = 0;
    int y0 = 0;
    for(i=0; i<MAP_HEIGHT; i++){
        switch(level->rows[i].zone){
            case SAFE:
                level->rows[i].entityCount = 0;
                level->rows[i].gap = 0;
                level->rows[i].firstEntity = NULL;
            break;
            case ROAD:
                for(j=0; j<MAX_PLAYING_ZONE_HEIGHT; j++ ){ // COUNT, FIRST: (SPEED, DIRECTION, LENGTH), GAP, 
                    level->rows[i+j].entityCount = 3;
                    level->rows[i+j].firstEntity = firstObstacle + (level->rows[i+j].entityCount)*j;
                    if(ISEVEN((i+j))){ //LAS FILAS PARES 
                        for(k = 0; k<(level->rows[i+j].entityCount); k++){
                            ((level->rows[i+j]).firstEntity[k]).speed = 2;  //MEDIUM_SPEED
                            ((level->rows[i+j]).firstEntity[k]).direction = DIR_RIGHT;
                        }
                    }
                    else{ //LAS IMPARES
                        for(k = 0; k<(level->rows[i+j].entityCount); k++){
                            ((level->rows[i+j]).firstEntity[k]).speed = 1; //SLOW_SPEED
                            ((level->rows[i+j]).firstEntity[k]).direction = DIR_LEFT;
                        }

                    }

                    if(j == 5){//ULTIMA FILA
                        level->rows[i+j].gap = 4; //MAX_GAP
                        for(k = 0; k<(level->rows[i+j].entityCount); k++){
                            ((level->rows[i+j]).firstEntity[k]).length = 2; // LENGTH_TRUCK
                            ((level->rows[i+j]).firstEntity[k]).x = x0 + (((level->rows[i+j]).firstEntity[k]).length+level->rows[i+j].gap)*k;
                        }
                        
                    }

                    else{//PRIMERAS FILAS 
                        level->rows[i+j].gap = 3; 
                        for(k = 0; k<(level->rows[i+j].entityCount); k++){
                            ((level->rows[i+j]).firstEntity[k]).length = 1; //LENGHT_CAR 
                            ((level->rows[i+j]).firstEntity[k]).x = x0 + (((level->rows[i+j]).firstEntity[k]).length+level->rows[i+j].gap)*k;
                        }
                        
                    }
                }
                i+=MAX_PLAYING_ZONE_HEIGHT-1;
            break;
            case WATER:
                for(j=0; j<MAX_PLAYING_ZONE_HEIGHT; j++ ){ // COUNT, FIRST: (SPEED, DIRECTION, LENGTH), GAP, 
                    level->rows[i+j].entityCount = 3;
                    level->rows[i+j].firstEntity = firstFloater + (level->rows[i+j].entityCount)*j;
                    if(ISEVEN((i+j))){
                        for(k = 0; k<(level->rows[i+j].entityCount); k++){
                            ((level->rows[i+j]).firstEntity[k]).speed = 2;  //MEDIUM_SPEED
                            ((level->rows[i+j]).firstEntity[k]).direction = DIR_RIGHT;
                        }
                    }
                    else{
                        for(k = 0; k<(level->rows[i+j].entityCount); k++){
                            ((level->rows[i+j]).firstEntity[k]).speed = 1; //SLOW_SPEED
                            ((level->rows[i+j]).firstEntity[k]).direction = DIR_LEFT;
                        }

                    }

                    if(j == 5){
                        level->rows[i+j].gap = 4; //MAX_GAP
                        for(k = 0; k<(level->rows[i+j].entityCount); k++){
                            ((level->rows[i+j]).firstEntity[k]).length = 2; // LENGTH_TRUCK
                            ((level->rows[i+j]).firstEntity[k]).x = x0 + (((level->rows[i+j]).firstEntity[k]).length+level->rows[i+j].gap)*k;
                        }
                        
                    }

                    else{
                        level->rows[i+j].gap = 3; 
                        for(k = 0; k<(level->rows[i+j].entityCount); k++){
                            ((level->rows[i+j]).firstEntity[k]).length = 1; //LENGHT_CAR 
                            ((level->rows[i+j]).firstEntity[k]).x = x0 + (((level->rows[i+j]).firstEntity[k]).length+level->rows[i+j].gap)*k;
                        }
                        
                    }
                }
                i+=MAX_PLAYING_ZONE_HEIGHT-1;
            break;
        }
    }
}


/******************************************************************************/
 