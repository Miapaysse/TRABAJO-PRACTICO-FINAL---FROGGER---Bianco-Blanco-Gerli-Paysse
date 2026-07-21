/***************************************************************************//**
  @file     raspiDraw.h
  @brief    Prototipos de las funciones de dibujo en la pantalla LED
  @author   Bianco-Blanco-Gerli-Paysse
 ******************************************************************************/

#ifndef RASPI_DRAW_H
#define RASPI_DRAW_H

#include <stdint.h>
#include "config.h"
#include "levels.h"

// Lista de mensajes indexados para la pantalla
enum msgs {
	MSG_HOME,       // Titulo principal
	MSG_PAUSE,      // Pantalla de pausa
	MSG_TOP_10,     // Titulo del Top 10
	MSG_PLAY,       // Opcion jugar
	MSG_GO_HOME,    // Opcion volver al menu
	MSG_DESPAUSE,   // Opcion reanudar
	MSG_GO_TOP_10,  // Opcion ir a puntuaciones
	MSG_GO_BACK,    // Flecha para atras
	MSG_EXIT,       // Opcion salir
	MSG_GAME_OVER,  // Pantalla perdiste
	MSG_YOU_WIN,    // Pantalla ganaste
	LIVE_LOSED,     // Animacion de vida perdida
	NEXT_LEVEL,     // Pantalla de cambio de nivel
	MY_RANKING,     // Cartel especial si entraste al top 10
	MSG_ERROR,      // Pantalla de error (?)
	MSG_MAX_MENUS   
};

extern const uint16_t msgsDisp[MSG_MAX_MENUS][MAP_HEIGHT + 1];

/**
 * @brief Dibuja el fondo (rio, calle, veredas) segun el backend.
 * @param rows Puntero a las filas del nivel actual.
 */
void drawZone(const Row_t * rows);

/**
 * @brief Dibuja los autos activos en la calle (prendidos).
 * @param obstacles Arreglo de obstaculos del juego.
 */
void drawObstacles(const Entity_t obstacles[]);

/**
 * @brief Dibuja los troncos en el agua (apagados sobre fondo prendido).
 * @param floaters Arreglo de plataformas flotantes.
 */
void drawFloaters(const Entity_t floaters[]);

/**
 * @brief Dibuja la rana titilando.
 * @param frog Puntero a la rana.
 * @param blink Estado actual del parpadeo (D_ON o D_OFF).
 */
void drawFrog(const Frog_t * frog, int blink);

/**
 * @brief Dibuja una pantalla fija completa (bitmaps 16x16).
 * @param bitmap Arreglo de bits de la imagen a mostrar.
 */
void drawMSG(const uint16_t bitmap[MAP_HEIGHT+1]);

/**
 * @brief Dibuja los tres digitos de una puntuacion en la pantalla.
 * @param idxScore Puesto en el ranking para prender los leds de abajo.
 * @param score El puntaje numerico a mostrar.
 */
void drawScore(int idxScore, uint16_t score);

/**
 * @brief Dibuja los nidos de llegada.
 * @param boxes Arreglo de los casilleros de meta.
 * @param blink Estado de parpadeo para los nidos ocupados.
 */
void drawBoxes (FinishBox_t boxes[], int blink);

/**
 * @brief Frena el juego y muestra el cartel si entraste al ranking.
 * @param status Estado del ranking enviado por el backend.
 */
void showRank(const Top10Status_t status);

/**
 * @brief Muestra el puntaje final de la partida.
 * @param score Puntos acumulados.
 */
void showScore(const uint16_t score);

/**
 * @brief Frena el juego para avisar que pasaste de nivel.
 * @param currentLevel ID del nivel actual.
 * @param lastLevel Puntero al nivel anterior para chequear cambios.
 */
void showLevelNextLevel(const LevelId_t currentLevel, LevelId_t* lastLevel);

/**
 * @brief Frena el juego y muestra animacion si perdiste una vida.
 * @param currentLives Vidas actuales.
 * @param lastLives Puntero a vidas anteriores para chequear cambios.
 */
void showLives(const uint8_t currentLives, uint8_t * lastLives);

#endif