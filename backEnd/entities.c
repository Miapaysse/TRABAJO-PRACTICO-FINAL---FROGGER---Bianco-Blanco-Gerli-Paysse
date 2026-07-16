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

void initEntities(){
}

void initObstacles(Entity* obstacles, Level * level){

}


void initFloaters(Entity* obstacles, int levelId){

}

void updateEntities(){
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 