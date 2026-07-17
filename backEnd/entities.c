/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "entities.h"

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
int moveFrog(Frog * frog , Input input){
  if(frog == NULL){
    return ERR_INVALID_FROG_POINTER;
  }
  else{
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
}

int  moveFrogWithFloater(Frog * frog , Entity* floater){

  if(frog == NULL){
    return ERR_INVALID_FROG_POINTER;
  }
  if(floater == NULL){
    return ERR_INVALID_FLOATER_POINTER;
  }
    frog->speed = floater->speed;
    frog->direction = floater->direction;
}

int resetFrog(Frog * frog){
  if(frog == NULL){
    return ERR_INVALID_FROG_POINTER;
  }

  else{
    (frog->y)=FROG_Y0;
    (frog->x)=FROG_X0;
    frog->lastSafeSpot=frog->y;
  }
}

int initFrog(Frog * frog){
  if(frog == NULL){
    return ERR_INVALID_FROG_POINTER;
  }
  else{
    resetFrog(frog); //Ubicamos la rana en sus coordenadas iniciales
    frog->speed = 0; //Establecemos la velocidad de la rana en 0
    return 0;
  }
}

int frogDies(uint8_t* lives, GameStateId* id ){
  if(lives == NULL){
    return ERR_INVALID_LIVES_POINTER;
  }

  if(id == NULL){
    return ERR_INVALID_ID_POINTER;
  }

  else{
    if(*lives > 1){
      (*lives)--;
      resetFrog();
    }
    else{
      *id = GAME_OVER;
      resetFrog();
    }
    return 0;
  }
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 