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
    
    loadZones(&(game->level));
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
    level1={
        1,
        &(game->entities),
        {
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
            {},
        } 
        
    };

    loadZones(&level1);
}

static void createLevel1(Game * game)
{
    level1.id = LEVEL_1;
    level1.entities = &(game->entities),
    loadZones(&level1);
}


    level->id = LEVEL_1;

    loadLevel1Obstacles(game);

    loadLevel1Floaters(game);

/******************************************************************************/
 