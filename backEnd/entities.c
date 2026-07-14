/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "entities.h"
#include <time.h>   

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
void createFrog(){}
void moveFrog(Frog * frog , Input input){
  switch(input){
    case UP:
      (frog->y)++;
    break;
    case DOWN:
      (frog->y)--;
    break;
    case RIGHT:
      (frog->x)++;
    break;
    case LEFT:
      (frog->x)--;
    break;
  }
}
void moveFrogWithFloater(Frog * frog , Entity* floater){
  (frog->y)=(floater->y);
  (frog->x)=(floater->x);
}

void resetFrog(Frog * frog){
  (frog->y)=Y0;
  (frog->x)=X0;
}

void frogDies(int* lives, GameStateId * id ){
  if(*lives > 1){
    (*lives)--;
    resetFrog();
  }
  else{
    *id = GAME_OVER;
    resetFrog();
  }
}

void createEntities(Game* p2game, GameEntities* p2GameEntities, Level* p2level){
    //inicializamos para que no haya entidades activas en un principio
    int i, j, y;
    for (i=0; i<MAX_OBSTACLES; i++){
        (p2GameEntities -> obstacles[i]).active = false;
    }
    for (j=0; j<MAX_FLOATERS; j++){
        (p2GameEntities -> floaters[j]).active = false;
    }

    //recorremos filas y vamos creando obstáculos en cada una
    int num_level; //FALTA SABER DE DONDE SACO EL NRO DE NIVEL
    for (int y = 0; y < MAP_HEIGHT; y++) {

        Zone zone_type = p2level -> zones[y]; //guardamos qué tipo de zona es esta fila particular

        if (zone_type == ROAD) {
          int obs_base = 2 + (num_level / 2); 
          int obs_variation = rand() % 2; //da 1 o 0
          int num_obs = obs_base + obs_variation;

          int space_btween = MAP_WIDTH / num_obs;
          int obs_length = 1 + (rand() % 2);

          //recorro arreglo de obstaculos
          int t;
          for (t=0; t<num_obs; t++){
            (p2GameEntities->obstacles[t]).active = true;
            (p2GameEntities->obstacles[t]).y = y;
            (p2GameEntities->obstacles[t]).x = t + space_btween + 1;
            (p2GameEntities->obstacles[t]).y = y;
            (p2GameEntities->obstacles[t]).height = 1;
            (p2GameEntities->obstacles[t]).length = obs_length;
            (p2GameEntities->obstacles[t]).speed= 1 + (num_level/2);

            //si la fila es nro. par los obstaculos van en un sentido, sino en el contrario
            if (y/2){
                (p2GameEntities->obstacles[t]).direction = DIR_LEFT;
            }
            else {
                (p2GameEntities->obstacles[t]).direction = DIR_RIGHT;
            }

            (p2GameEntities->obstacles[t]).type = OBSTACLE;
          }

        } 
        else if (zone_type == WATER) {
            
        }
    }
}

void updateEntities(){
    for(i=0; i<MAX_OBSTACLES; i++){
        if(collided(frog,&(obstacles[i])) ){
            return 1;
        }
    }
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 