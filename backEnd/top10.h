

/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

 #ifndef TOP10_H
 #define TOP10_H

 
 /*******************************************************************************
  * INCLUDE HEADER FILES
  ******************************************************************************/
 #include <stdbool.h>
 #include "config.h"
 
 
 
 /*******************************************************************************
  * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
  ******************************************************************************/
 typedef enum {
  TOP10_OK = 0,
  TOP10_FILE_NOT_FOUND,  // no existe el archivo todavia (primera ejecucion, no es un error)
  TOP10_READ_ERROR,      // el archivo existe pero esta corrupto/incompleto
  TOP10_WRITE_ERROR      // no se pudo escribir o guardar el archivo
} Top10Status;

 /*******************************************************************************
  * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
 
 // +ej: extern unsigned int anio_actual;+
 
 
 /*******************************************************************************
  * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
 Top10Status loadTop10(int topScores[TOP10_SIZE]);

/**
 * @brief Carga el top 10 desde TOP10_FILE. Si el archivo no existe o esta
 *        corrupto, rellena las posiciones invalidas con 0. Garantiza que
 *        topScores queda ordenado de mayor a menor al terminar.
 * @param topScores array de salida, tamaño TOP10_SIZE
 * @return TOP10_OK, TOP10_FILE_NOT_FOUND o TOP10_READ_ERROR
 */

bool updateTop10(int topScores[TOP10_SIZE], int newScore);

 /**
 * @brief Inserta newScore en el ranking si corresponde, manteniendo el
 *        array ordenado de mayor a menor.
 * @param topScores array ya ordenado de mayor a menor, tamaño TOP10_SIZE
 * @param newScore puntaje nuevo a intentar insertar
 * @return true si entro al top 10, false si no
 */
 
 Top10Status SaveTop10(const int topScores[TOP10_SIZE]);

 /**
 * @brief Guarda el top 10 en TOP10_FILE de forma atomica (escribe a un
 *        archivo temporal y luego lo renombra), para no dejar el archivo
 *        corrupto si el programa se interrumpe durante el guardado.
 * @param topScores array a guardar, tamaño TOP10_SIZE
 * @return TOP10_OK o TOP10_WRITE_ERROR
 */
 /******************************************************************************/
 
 #endif 
 