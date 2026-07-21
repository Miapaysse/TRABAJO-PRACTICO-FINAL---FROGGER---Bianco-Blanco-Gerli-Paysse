/***************************************************************************//**
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "entities.h"
#include "game.h"
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

static double getElapsedEntityTime(Game_t *game);
static void resetEntityTimer(Game_t *game);
static int entityUpdateRequired(Game_t *game);
static void moveRow(Row_t *row);
static void wrapEntity(Entity_t *entity);

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
int moveFrog(Frog_t * frog , Input_t input){ //Cambiamos las coordenadas de la rana segun las indicaciones del jugador 
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
        default:
        break;
      }
  }
  return 0;
}

int moveFrogWithFloater(Frog_t * frog , Entity_t* floater){ 
  if(frog == NULL){
    return ERR_INVALID_FROG_POINTER;
  }
  if(floater == NULL){
    return ERR_INVALID_FLOATER_POINTER;
  }

  frog->speed = floater->speed;
  frog->direction = floater->direction;

  return 0;
}

int resetFrog(Frog_t * frog){
  if(frog == NULL){
    return ERR_INVALID_FROG_POINTER;
  }

  else{
    (frog->y)=FROG_Y0; //Ubicamos la rana en sus coordenadas iniciales, reseteamos su ultima zona segura y su velocidad
    (frog->x)=FROG_X0; 
    frog->speed = 0;
    return 0;
  }
  
}

int initFrog(Frog_t * frog){
  if(frog == NULL){
    return ERR_INVALID_FROG_POINTER;
  }
  else{
    resetFrog(frog); //Ubicamos la rana en sus coordenadas iniciales
    return 0;
  }
}

int frogDies(Frog_t* frog , uint8_t* lives, GameStateId_t* id ){
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
      *lives = MAX_LIVES; //Reseteamos las vidas para la proxima partida
      frog->lastCheckpoint = NO_CHECKPOINT;
      resetFrog(frog);
    }
    return 0;
  }
}

int updateEntities(Game_t *game){ //Actualizamos la posicion de las entidades del juego, si paso el tiempo suficiente desde la ultima actualizacion
  if(game == NULL){
    return ERR_INVALID_GAME_POINTER;
  }
  else{
    int i;

    if(entityUpdateRequired(game)){

      if ((game->frog).speed != 0) { //Si la rana esta sobre un floater, se mueve con el mismo sentido y velocidad que ese
        if ((game->frog).direction == DIR_RIGHT) {
          (game->frog).x += (game->frog).speed;
        } else {
          (game->frog).x -= (game->frog).speed;
        }
      }
      for(i=0; i<MAP_HEIGHT; i++){
          Row_t *row = &(game->level.rows[i]);
          if(row == NULL){
              return ERR_INVALID_ROW_POINTER;
          }
          if(row->entityCount > 0){
                moveRow(row);
          }
      }
    }
    return 0;
  }
}

int frogInFinishBox(Frog_t *frog, FinishBox_t *finishBox){
  if(frog == NULL){
    return ERR_INVALID_FROG_POINTER;
  }
  if(finishBox == NULL){
    return ERR_INVALID_FINISHBOX_POINTER;
  }
  else{
    if((frog->x == finishBox->x)&& (frog->x <= finishBox->x + finishBox->length - 1)){
        return 1;
    }

    return 0;
  }
}

int resetFinishBoxes(FinishBox_t *finishBox){
  if(finishBox == NULL){
    return ERR_INVALID_FINISHBOX_POINTER;
  }
  else{
    int i;
      for(i = 0; i < FINISH_BOX_COUNT; i++){
          finishBox[i].occupied = false;
      }
      return 0;
  }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static double getElapsedEntityTime(Game_t *game){
    return (double)(clock() - game->lastEntityUpdate) / CLOCKS_PER_SEC;
}

static void resetEntityTimer(Game_t *game){
    game->lastEntityUpdate = clock();
}

static int entityUpdateRequired(Game_t *game){
    if(getElapsedEntityTime(game) < ENTITY_UPDATE_PERIOD){
      return 0;
    }
    else{
      resetEntityTimer(game);
      return 1;
    }
}


static void moveRow(Row_t *row){
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

static void wrapEntity(Entity_t *entity){

    int width = MAP_WIDTH + 1;

    while (entity->x >= width) {
        entity->x -= width;
    }
    while (entity->x < 0) {
        entity->x += width;
    }

}

/******************************************************************************/
 