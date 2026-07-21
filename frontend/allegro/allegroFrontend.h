/***************************************************************************//**
@file     +allegroFrontend.h+
  @brief    +Funcionees para el frontend de la raspi+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

 #ifndef ALLEGRO_FRONTEND_H
 #define ALLEGRO_FRONTEND_H
 
 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/
 
 #include <stdint.h>
 #include "game.h"
 #include "config.h"

 /*******************************************************************************
  * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
  ******************************************************************************/
 #define ALLEGRO_DIR "frontend/allegro/"
 /***************************************************************************
  * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
 
 /**
  * @brief Funciones para incializar, actualizar y apagar frontend 
 */
int frontendInit(void);
Input_t frontendGetInput(void);
void frontendRender(Game_t * game);
void frontendDestroy(void);
void frontManageError(ErrorCode_t err);

#endif
 
 