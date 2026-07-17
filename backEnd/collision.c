/***************************************************************************//**
  @file     +collision.c+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
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

    int runOverFrog(Frog *frog, Entity *obstacles, int obstacleCount){
        //VALIDAR PUNTEROS
        int i;
        for(i=0; i<obstacleCount; i++){
            if(collided(frog,&(obstacles[i])) ){
                return 1;
            }
        }
        return 0;
    }

    Entity *frogOnFloater(Frog *frog, Entity *floaters, int floaterCount){
        //VALIDAR PUNTEROS
        int i;
        for(i=0; i<floaterCount; i++){
            if(collided(frog,&(floaters[i])) ){
                return &(floaters[i]);
            }
        }
        return NULL;
    }


    void manageInteractions(Game *game){
        
        if (frogOutOfBounds(&game->frog)) {
            frogDies(&(game->lives), &game->state.id);
            return;
        }

        Row *currentRow = &(game->level.rows[game->frog.y]);


        switch(currentRow->zone){

            case ROAD:

                if(runOverFrog(&(game->frog), currentRow->firstEntity, currentRow->entityCount)){
                    frogDies(&(game->lives), &((game->state).id));
                }

            break;

            case WATER:
            
                Entity *floaterP = frogOnFloater(&(game->frog), currentRow->firstEntity, currentRow->entityCount);

                if(floaterP != NULL){
                    moveFrogWithFloater(&(game->frog), floaterP);
                }
                else{
                    frogDies(&(game->lives), &((game->state).id));
                }
            
            break;

            case SAFE:
                updateScore(&(game->frog), &(game->score));
            break;

            case START:
            break;
        }
    }


    int collided(Frog* frog , Entity* entity){
            if( ( (frog->x) >= entity->x ) && ( (frog->x) <= (entity->x + entity->length - 1) )){
                return 1;
            }

            else{
                return 0;
            }
    }

    void updateScore(Frog * frog , int* score){
        if(frog->lastSafeSpot != frog->y){
            (*score)+=POINT_WEIGHT;
            frog->lastSafeSpot = frog->y;
        }
    }

    int frogOutOfBounds(Frog *frog){
        if (frog == NULL){
            return ERR_INVALID_LEVEL_POINTER;
        }   

        if (frog->x < 0){
            return 1;
        }

        if (frog->x >= MAP_WIDTH){
            return 1;
        }

        if (frog->y < 0){
            return 1;
        }

        if (frog->y >= MAP_HEIGHT){
            return 1;
        }

        return 0;
    }


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 