/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "entities.h"
#include <stddef.h>

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
int moveFrog(Frog * frog , Input input){ //Cambiamos las coordenadas de la rana segun las indicaciones del jugador 
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

int  moveFrogWithFloater(Frog * frog , Entity* floater){ //Para que la rana se mueva con el flotador tiene que tener su misma velocidad y direccion 

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
    (frog->y)=FROG_Y0; //Ubicamos la rana en sus coordenadas iniciales, reseteamos su ultima zona segura y su velocidad
    (frog->x)=FROG_X0; 
    frog->lastSafeSpot=frog->y;
    frog->speed = 0;
  }
}

int initFrog(Frog * frog){
  if(frog == NULL){
    return ERR_INVALID_FROG_POINTER;
  }
  else{
    resetFrog(frog); //Ubicamos la rana en sus coordenadas iniciales
    return 0;
  }
}

int frogDies(Frog* frog , uint8_t* lives, GameStateId* id ){
  if(lives == NULL){
    return ERR_INVALID_LIVES_POINTER;
  }

  if(id == NULL){
    return ERR_INVALID_ID_POINTER;
  }

  else{
    if(*lives > 1){   //Si la rana no perdio todas sus vidas, le quitamos una 
      (*lives)--;   
      resetFrog(frog);
    }
    else{
      *id = GAME_OVER; //Si la rana perdio todas sus vidas el juego se termina
      resetFrog(frog);
    }
    return 0;
  }
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static int entityUpdateRequired(Game *game){
    clock_t now = clock();

    double elapsed = (double)(now - game->lastEntityUpdate) /CLOCKS_PER_SEC;

    if(elapsed >= ENTITY_UPDATE_PERIOD){
        game->lastEntityUpdate = now;
        return 1;
    }

    return 0;
}

void updateEntities(Game *game){
    int i;

    if(!entityUpdateRequired(game))
        return;

    for(i=0; i<MAP_HEIGHT; i++)
    {
        Row *row = &(game->level.rows[i]);

        if(row->entityCount > 0)
        {
            moveRow(row);
        }
    }
}

static void moveRow(Row *row){
    int i;
    for(i=0; i<row->entityCount; i++){
        if(row->direction == DIR_RIGHT){
            row->firstEntity[i].x += row->speed;
        }
        else{
            row->firstEntity[i].x -= row->speed;
        }

        wrapEntity(&(row->firstEntity[i]));
    }
}

static void wrapEntity(Entity *entity)
{
    if(entity->direction == DIR_RIGHT)
    {
        if(entity->x >= MAP_WIDTH)
        {
            entity->x = -entity->length;
        }
    }
    else
    {
        if(entity->x + entity->length < 0)
        {
            entity->x = MAP_WIDTH;
        }
    }
}

/******************************************************************************/
 