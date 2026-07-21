/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.c)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "errors.h"

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
const char *errorMessage(ErrorCode_t error){
    switch(error){
        case ERR_INVALID_GAME_POINTER:
            return "Invalid Game pointer";
        break;
        case ERR_INVALID_LEVEL_POINTER:
            return "Invalid Level pointer"; 
        break;
        case ERR_INVALID_FROG_POINTER:
            return "Invalid Frog pointer";
        break;
        case ERR_INVALID_ENTITY_POINTER:  
          return "Invalid Entity pointer";
        break;
        case ERR_INVALID_OBSTACLE_POINTER:
            return "Invalid Obstacle pointer";
        break;
        case ERR_INVALID_FLOATER_POINTER:
            return "Invalid Floater pointer";
        break;
        case ERR_INVALID_SCORE_POINTER:
            return "Invalid Score pointer";
        break;
        case ERR_INVALID_LIVES_POINTER:
            return "Invalid Lives pointer";
        break;
        case ERR_INVALID_ROW_POINTER:
            return "Invalid Row pointer"; 
        break;
        case ERR_INVALID_ID_POINTER:
            return "Invalid ID pointer";
        break;
        case ERR_INVALID_FINISHBOX_POINTER:
            return "Invalid FinishBox pointer";
        break;
        
        case ERR_INVALID_FLOATER_COUNT:
            return "Invalid Floater count";
        break;
        case ERR_INVALID_OBSTACLE_COUNT:
            return "Invalid Obstacle count";
        break;

        case ERR_MAX_FLOATERS_EXCEEDED:
            return "Maximum number of floaters exceeded";
        break;

        case ERR_MAX_OBSTACLES_EXCEEDED:
            return "Maximum number of obstacles exceeded";
        break;
        
                case ERR_ALLEGRO_INIT_FAILED:
            return "Unable to start allegro";
        break;
        case ERR_DISPLAY_INIT_FAILED:
            return "Unable to start display";
        case ERR_INIT_TTF_FAILED:
            return "Unable to start ttf addon";

        case ERR_KEYBOARD_INIT_FAILED:
            return "Unable to show display";
        break;     
        case ERR_IMAGE_ADDON_FAILED:
            return "Unable to start image addon";
        break;
        case ERR_PRIMITIVES_ADDON_FAILED:
            return "Unable to start primitives addon";
        break;
        case ERR_FONT_ADDON_FAILED:
            return "Unable to start font addon";
        break;
        case ERR_EVENT_QUEUE_FAILED:
            return "Unable to start event queue";
        break;
        case ERR_LOAD_IMAGES_FAILED:
            return "Unable to load files";
        break;
        case ERR_LOAD_FONTS_FAILED:
            return "Unable to load fonts";
        
    }

    return "Unknown error";
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/
 