/***************************************************************************//**
  @file     +top10.c+
  @brief    +Manejo del ranking de los 10 mejores puntajes+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/
 
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
 #include <stdio.h>
 #include "top10.h"

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

// Archivo temporal usado para guardar de forma atomica
#define TOP10_TMP_FILE TOP10_FILE ".tmp"

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void sortDescending(int topScores[TOP10_SIZE]);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


Top10Status LoadTop10(int topScores[TOP10_SIZE]){
   
    if (topScores == NULL){
        return TOP10_READ_ERROR;
    }

FILE *file = fopen(TOP10_FILE, "r");
int i;
if (file == NULL){
    // Probablemente es la primera vez que corre el juego
    for (i = 0; i < TOP10_SIZE; i++){
        topScores[i] = 0;
    }
    return TOP10_FILE_NOT_FOUND;
}

Top10Status status = TOP10_OK;

 for(i=0; i < TOP10_SIZE; i++){
    int value;
    int result = fscanf(file, "%d", &value);
        if(result == EOF){
            break;//no se jugaron diez partidas todavia
        }
    if(result != 1){
        status = TOP10_READ_ERROR;
        break;
    }
    if(value < 0){
        status = TOP10_READ_ERROR;
        topScores[i] = 0;//hubo un error
        continue;
    }
    topScores[i] =value;
 }
 fcloes(file);
 sortdescending(topScores);

 return status;
}


bool UpdateTop10(int topScores[TOP10_SIZE], int newScore){

    if(topScores == NULL){

        return TOP10_WRITE_ERROR;
    }
    int position = TOP10_SIZE - 1; 
    if(newScore <= topScores[position]){ //Si no supera el ultimo lugar no entra
        return false;
    }

    while (position > 0 && topScores[position - 1] < newScore){
        topScores[position] = topScores[position - 1]; //Si el score supera al de una posicion "baja" de ranking esa posicion por el anterior, y luego reemplaza 
        position--;
    }
    topScores[position] = newScore;
    return true;
}

Top10Status SaveTop10(const int topScores[TOP10_SIZE]){

    if(topScores == NULL){
        return TOP10_WRITE_ERROR;
    }

    FILE *file = fopen(TOP10_TMP_FILE, "w"); //Usamos un archivo temporal para que en caso de un fallo, como corte de luz no nos quede el archivo original corrupto
    
          if (file == NULL){
            return TOP10_WRITE_ERROR;
        }
    
        for (int i = 0; i < TOP10_SIZE; i++){
            if (fprintf(file, "%d\n", topScores[i]) < 0){// Escribimos y validamos
                fclose(file);
            remove(TOP10_TMP_FILE);// Limpieza del archivo temporal si hay fallos
            return TOP10_WRITE_ERROR;
            }
        }
        if (fclose(file) != 0){//cerramos el archivo asegurandonos que los datos
            remove(TOP10_TMP_FILE);
            return TOP10_WRITE_ERROR;
        }
        if (rename(TOP10_TMP_FILE, TOP10_FILE) != 0){//si todo salio bien reemplazamos el archivo temporal por el original
            remove(TOP10_TMP_FILE);
            return TOP10_WRITE_ERROR;
        }
     
        return TOP10_OK;
    }
        
/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
 
// TOP10_SIZE es chico (10), asi que el costo de reordenar despues de cada carga es despreciable.

static void sortDescending(int topScores[TOP10_SIZE]){
    for (int i = 1; i < TOP10_SIZE; i++){
        int key = topScores[i];
        int j = i - 1;
        while (j >= 0 && topScores[j] < key){
            topScores[j + 1] = topScores[j];
            j--;
        }
        topScores[j + 1] = key;
    }
}
 
/******************************************************************************/



