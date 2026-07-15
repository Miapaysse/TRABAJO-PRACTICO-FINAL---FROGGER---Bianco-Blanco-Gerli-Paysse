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
  }

  void loadLevels(Level* level, LevelId id){
    switch(id){
        case LEVEL_1:
            createLevel1(level);
            break;

        case LEVEL_2:
            createLevel2(level);
            break;

        case LEVEL_3:
            createLevel3(level);
            break;

        default:
            createLevel1(level);
            break;
    }
  }

  static void createLevel1(Level *level){
    level->id = LEVEL_1;

    /* Inicializar zonas */
    loadLevel1Zones(level);

    /* Inicializar obstáculos */
    loadLevel1Obstacles(level);

    /* Inicializar troncos */
    loadLevel1Floaters(level);

    /* Inicializar velocidades */

    /* Inicializar cantidad de entidades --> */
 }

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void createLevel1(Game * game)
{
    Level * level = &game->level;

    level->id = LEVEL_1;

    loadLevel1Zones(level);

    loadLevel1Obstacles(game);

    loadLevel1Floaters(game);
}

static void loadLevel1Zones(Level * level)
{
    level->rows[0].zone = SAFE_ZONE;
    level->rows[1].zone = WATER;
    level->rows[2].zone = WATER;
    level->rows[3].zone = WATER;
    level->rows[4].zone = GRASS;
    level->rows[5].zone = ROAD;
    level->rows[6].zone = ROAD;
    level->rows[7].zone = ROAD;
    level->rows[8].zone = START_ZONE;
}

static void loadLevel1Obstacles(Game * game)
{
    configureObstacleRow(game,
                         5,          // fila
                         3,          // cantidad
                         2,          // largo
                         4,          // separación
                         250,        // ms
                         RIGHT);

    configureObstacleRow(game,
                         6,
                         2,
                         3,
                         6,
                         350,
                         LEFT);

    configureObstacleRow(game,
                         7,
                         4,
                         2,
                         3,
                         180,
                         RIGHT);
}

/******************************************************************************/
 