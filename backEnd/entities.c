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

void createEntities(GameEntities* gameEntities, Level* level){
    //inicializamos para que no haya entidades activas en un principio
    int i, j, y;
    for (i=0; i<MAX_OBSTACLES; i++){
        (gameEntities -> obstacles[i]).active = false;
    }
    for (j=0; j<MAX_FLOATERS; j++){
        (gameEntities -> floaters[j]).active = false;
    }

    //recorremos filas y vamos creando obstáculos en cada una
    
      for (int y = 0; y < MAP_HEIGHT; y++) {

        ZoneType zone_type = ((level -> zones)[y]).type; //guardamos qué tipo de zona es esta fila particular


        switch(zone_type){
          case ROAD:

          break;

        } 
       
      }
}


void initObstacles(Entity* obstacles, int levelId){
    int num_obs = rand() % MAX_OBSTACLES + MIN_OBSTACLES; //da MIN_OBSTACLES o MAX_OBSTACLES
    int obs_length = 1 + rand() % 2;
    int space_btween = MAP_WIDTH / num_obs ;
    

    //recorro arreglo de obstaculos
    int t;
    for (t=0; t<MAX_OBSTACLES; t++){
      (obstacles[t]).active = true;
      (obstacles[t]).y = y;
      (obstacles[t]).x = t + space_btween + 1;
      (obstacles[t]).y = y;
      (obstacles[t]).height = 1;
      (obstacles[t]).length = obs_length;
      (obstacles[t]).speed= 1 + (levelId/2);

      //si la fila es nro. par los obstaculos van en un sentido, sino en el contrario
              if (y/2){
                  (obstacles[t]).direction = DIR_LEFT;
              }
              else {
                  (obstacles[t]).direction = DIR_RIGHT;
              }

              (obstacles[t]).type = OBSTACLE;
            }
}


void initObstacles(Entity* obstacles, int levelId){
    int obs_base = 2 + (levelId / 2); 
    int num_obs = rand() % MAX_OBSTACLES + obs_base; //da obs_base o MAX_OBSTACLES

    int space_btween = MAP_WIDTH / num_obs ;
    int obs_length = 1 + rand() % 2;

    //recorro arreglo de obstaculos
    int t;
    for (t=0; t<num_obs; t++){
      (obstacles[t]).active = true;
      (obstacles[t]).y = y;
      (obstacles[t]).x = t + space_btween + 1;
      (obstacles[t]).y = y;
      (obstacles[t]).height = 1;
      (obstacles[t]).length = obs_length;
      (obstacles[t]).speed= 1 + (levelId/2);

      //si la fila es nro. par los obstaculos van en un sentido, sino en el contrario
              if (y/2){
                  (obstacles[t]).direction = DIR_LEFT;
              }
              else {
                  (obstacles[t]).direction = DIR_RIGHT;
              }

              (obstacles[t]).type = OBSTACLE;
            }
}

void updateEntities(){

  
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 