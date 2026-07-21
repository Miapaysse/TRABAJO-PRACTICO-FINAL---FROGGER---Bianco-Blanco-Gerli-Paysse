/***************************************************************************//**
  @file     +top10.c+
  @brief    +Manejo del ranking de los 10 mejores puntajes+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/
 
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
 #include "stdio.h"
 #include "stdbool.h"
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

Top10Status_t loadTop10(int topScores[TOP10_SIZE]);

/**
 * @brief Carga el top 10 desde TOP10_FILE. Si el archivo no existe o esta
 *        corrupto, rellena las posiciones invalidas con 0. Garantiza que
 *        topScores queda ordenado de mayor a menor al terminar.
 * @param topScores array de salida, tamaño TOP10_SIZE
 * @return TOP10_OK, TOP10_FILE_NOT_FOUND o TOP10_READ_ERROR
 */

static Top10Status_t UpdateTop10(int topScores[TOP10_SIZE], int newScore);

 /**
 * @brief Inserta newScore en el ranking si corresponde, manteniendo el
 *        array ordenado de mayor a menor.
 * @param topScores array ya ordenado de mayor a menor, tamaño TOP10_SIZE
 * @param newScore puntaje nuevo a intentar insertar
 * @return true si entro al top 10, false si no
 */
 
 static Top10Status_t SaveTop10(const int topScores[TOP10_SIZE]);

 /**
 * @brief Guarda el top 10 en TOP10_FILE de forma atomica (escribe a un
 *        archivo temporal y luego lo renombra), para no dejar el archivo
 *        corrupto si el programa se interrumpe durante el guardado.
 * @param topScores array a guardar, tamaño TOP10_SIZE
 * @return TOP10_OK o TOP10_WRITE_ERROR
 */
 /******************************************************************************/
 

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

Top10Status_t getTop10Status(int topScores[TOP10_SIZE], int newScore){
    Top10Status_t status = loadTop10(topScores); //Carga archivo
    if (status == TOP10_OK || status == TOP10_FILE_NOT_FOUND){ // Con cualquiera de estos status se puede devolver algo
        Top10Status_t rankingChanged = UpdateTop10(topScores, newScore); //Todo OK, analiza si jugador ingreso a top 10
        status = SaveTop10(topScores); // Vemos si se puede guardar el archivo
        if (status != TOP10_OK) { //Si no es asi
            return TOP10_WRITE_ERROR; // Avisamos que no se pudo guardar
        } else {
            //Esta todo bien entonces devuelve estado de ranking
            return rankingChanged;
        }
    }
    return status; // Hubo un error irreparable al intentar habrir el archivo
}

Top10Status_t loadTop10(int topScores[TOP10_SIZE]){
   
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

    Top10Status_t status = TOP10_OK;

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
    fclose(file);
    sortDescending(topScores);

    return status;
}


static Top10Status_t UpdateTop10(int topScores[TOP10_SIZE], int newScore){
    if(topScores == NULL){
        return TOP10_WRITE_ERROR; // Avisa que hubo un error al acceder a los puntajes
    }
    int position = TOP10_SIZE - 1;

    if(newScore <= topScores[position]){ //Si no supera el ultimo lugar no entra
        return TOP10_NO_CHANGE;
    }

    for (; position > 0 && topScores[position - 1] < newScore ; position--){ 
        topScores[position] = topScores[position - 1]; // Corregido comentario
    }
    topScores[position] = newScore;
    return TOP10_CHANGED;
}

static Top10Status_t SaveTop10(const int topScores[TOP10_SIZE]){

    if(topScores == NULL){ // No se pudo acceder al rankin
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
        for (; j >= 0 && topScores[j] < key; j--){
            topScores[j + 1] = topScores[j];
        }
        topScores[j + 1] = key;
    }
}
 
/******************************************************************************/


