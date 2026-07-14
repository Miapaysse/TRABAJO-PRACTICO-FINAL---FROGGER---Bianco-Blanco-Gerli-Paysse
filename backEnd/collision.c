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

    bool runOverFrog(Frog* frog, Entity  obstacles[MAX_OBSTACLES]){
        //VALIDAR PUNTEROS
        int i;
        for(i=0; i<MAX_OBSTACLES; i++){
            if(collided(frog,&(obstacles[i])) ){
                return 1;
            }
        }
        return 0;
    }

    Entity * frogOnFloater(Frog* frog, Entity  floaters[MAX_FLOATERS]){
        //VALIDAR PUNTEROS
        int i;
        for(i=0; i<MAX_FLOATERS; i++){
            if(collided(frog,&(floaters[i])) ){
                return &(floaters[i]);
            }
        }
        return NULL;
    }


    void manageInteractions(Game* game){
        //VALIDAR PUNTEROS
        //CHEQUEAR LIMITES DEL JUEGO
        
            switch(game->currentZone){
                case ROAD:
                    if(runOverFrog(&(game->frog), (game->entities).obstacles)){
                        frogDies(&(game->lives), &((game->state).id));
                    }
                break;
            
                case WATER:
                    Entity* floaterP = frogOnFloater(&(game->frog), (game->entities).floaters);
                    if( floaterP != NULL){
                        moveFrogWithFloater(&(game->frog), floaterP);
                    }
                    else{
                        frogDies(&(game->lives), &((game->state).id));
                    }
                break;

                case SAFE:
                    updateScore(&(game->frog), &(game->score));
                break;
            }
        


    }


    bool collided(Frog* frog , Entity* entity){
            if( (( (frog->x) > (entity->x - (entity->length)/2) ) || ( (frog->x) < (entity->x + (entity->length)/2) ) )&& ( frog->y == entity->y) ){
                return 1;
            }

            else{
                return 0;
            }
    }

    void updateScore(Frog * frog , int* score){
        if(frog->lastSafeSpot != frog->y){
            (*score)++;
            frog->lastSafeSpot = frog->y;
        }
    }


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 