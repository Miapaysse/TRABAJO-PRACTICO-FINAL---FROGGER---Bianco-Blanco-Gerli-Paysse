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

/**
 * @brief TODO: Esta funcion inicializa el frontend de Allegro. 
 * @param none 
 * @return devuelve un entero para control de errores
*/

Input_t frontendGetInput(void);

/**
 * @brief TODO: Esta funcion recibe input del usuario e informa al backend que tecla fue presionada.
 * @param none
 * @return Devuelve el tipo de input que fue recibido.
*/

void frontendRender(Game_t * game);

/**
 * @brief TODO: Esta funcion actualiza el puntaje cada vez que la rana llega a una zona segura. 
 * @param frog Recibe el puntero a la rana para analizar si llego a una zona segura
 * @param score Recibe el puntero al puntaje 
 * @return devuelve un entero para control de errores
*/

void frontendDestroy(void);

/**
 * @brief TODO: Esta funcion libera memoria y cierra recursos del frontend al finalizar. 
 * @param none
 * @return No devuelve nada.
*/

void frontManageError(ErrorCode_t err);

/**
 * @brief TODO: Esta funcion maneja los errores del frontend, se encarga de mostrarlos por
 * pantalla o en consola en caso de no poder cargar los recursos suficientes. 
 * @param err Recibe el código de error
 * @return No devuelve nada.
*/

#endif
 
 