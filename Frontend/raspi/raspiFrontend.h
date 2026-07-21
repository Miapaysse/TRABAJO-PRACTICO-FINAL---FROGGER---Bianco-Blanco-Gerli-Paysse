/***************************************************************************//**
  @file     raspiFrontend.h
  @brief    Constantes y tipos de datos para el frontend de la Raspi
  @author   Bianco-Blanco-Gerli-Paysse
 ******************************************************************************/

#ifndef RASPI_H
#define RASPI_H

#include <stdint.h>
#include "game.h"
#include "config.h"

#define JOY_LIM 50 // Limite para detectar movimiento del joystick
typedef int DISP[MAP_WIDTH + 1][MAP_HEIGHT + 1]; // Matriz que simula la pantalla
#define ROW(r) ((MAP_HEIGHT) - r) // Invierte el eje Y para la pantalla fisica

// ------ Coordenadas y espaciado para dibujar el score ------
#define SCORE_YCOORD 4
#define SCORE_XCOORD 2
#define SPACE_DIGITS 1
#define DIGITS 3
#define DIGIT_WIDTH 3
#define DIGIT_HEIGHT 5

#define SCORE_ID_YCOOR 11
#define SCORE_ID_XCOOR 3

// ------ Tiempos para los parpadeos (en ms) ------
#define TIME_BLINK_FROG 750 // Cada cuanto parpadea la rana
#define TIME_BLINK_BOX 900  // Cada cuanto parpadean los nidos ocupados

// ------ Tiempos de espera para las pantallas fijas ------
#define DISPLAY_DEFAULT_TIME 1000000 
#define DISPLAY_RANK_TIME 4000000    
#define DISPLAY_SCORE_TIME 1000000   

/**
 * @brief Inicializa los drivers y limpia la pantalla.
 * @return Entero para manejo de errores.
 */
int frontendInit(void);

/**
 * @brief Lee el joystick y devuelve el movimiento actual.
 * @return El input detectado (UP, DOWN, LEFT, RIGHT, SELECT, NONE).
 */
Input_t frontendGetInput(void);

/**
 * @brief Dibuja todo segun el estado actual del juego.
 * @param game Puntero a la estructura principal del juego.
 */
void frontendRender(Game_t * game);

/**
 * @brief Apaga y limpia la pantalla al cerrar el programa.
 */
void frontendDestroy(void);

/**
 * @brief Muestra la pantalla de error si algo falla en el backend.
 * @param err Codigo de error detectado.
 */
void frontManageError(ErrorCode_t err);

#endif