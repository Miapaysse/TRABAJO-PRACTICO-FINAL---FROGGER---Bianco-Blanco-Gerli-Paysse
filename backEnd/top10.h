

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

 
 
 
 /*******************************************************************************
  * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
  ******************************************************************************/
  #define TOP10_SIZE 10

  #define TOP10_FILE "top10.txt"
 
 
  typedef enum {
  TOP10_OK = 0,
  TOP10_NO_CHANGE,        // Usuario NO ingreso al ranking
  TOP10_CHANGED,          // Usuario ingreso al ranking
  TOP10_FILE_NOT_FOUND,  // no existe el archivo todavia (primera ejecucion, no es un error)
  TOP10_READ_ERROR,      // el archivo existe pero esta corrupto/incompleto
  TOP10_WRITE_ERROR      // no se pudo escribir o guardar el archivo
} Top10Status;

 /*******************************************************************************
  * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
 
 // +ej: extern unsigned int anio_actual;+
 
 typedef struct {
  Top10Status status;
  int topScores[TOP10_SIZE];
 } Top10_t;
 
 /*******************************************************************************
  * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
  ******************************************************************************/
Top10Status getTop10Status(int topScores[TOP10_SIZE], int newScore);
Top10Status loadTop10(int topScores[TOP10_SIZE]);
 #endif 
 
