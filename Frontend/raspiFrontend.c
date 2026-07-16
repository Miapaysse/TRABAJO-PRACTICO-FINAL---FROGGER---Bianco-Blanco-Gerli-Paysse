/***************************************************************************//**
  @file     +top10.c+
  @brief    +Manejo del ranking de los 10 mejores puntajes+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "disdrv.h"
#include "joydrv.h"

#include "game.h"
#include "config.h"
#include "levels.h"
#include "entities.h"
#include "raspiFrontend.h"



#define JOY_LIM 10 //Limite para detectar movimiento del joystic
#define DIGITS 3

static dcoord_t frog_pos = {MAP_WIDTH  >> 1, MAP_HEIGHT}; //Sse queda del lado izquierdo de la mitad vertical, abajo de todo
static dcoord_t entity_pos;
DISP msg; //Global para que inicialice en cero

//Macros para definir coordenadas score y espacio entre digitos del score
#define SCORE_YCOORD 4
#define SCORE_XCOORD 2
#define SPACE_DIGITS 1
#define SCORE_ID_YCOOR 11
#define SCORE_ID_XCOOR 3
int idxScore = 0;


DISP menuBackground = {
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}
};
//Defino digitos para display. 10 valores, c/u ocupa 5 filas y 3 columnas
const int digits[10][DIGIT_HEIGHT][DIGIT_WIDTH] = {
	// Nro 0
	{ {0,0,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,0,0} },
	// Nro 1
	{ {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1} },
	// Nro 2
	{ {0,0,0}, {1,1,0}, {0,0,0}, {0,1,1}, {0,0,0} },
	// Nro 3
	{ {0,0,0}, {1,1,0}, {0,0,0}, {1,1,0}, {0,0,0} },
	// Nro 4
	{ {0,1,0}, {0,1,0}, {0,0,0}, {1,1,0}, {1,1,0} },
	// Nro 5
	{ {0,0,0}, {0,1,1}, {0,0,0}, {1,1,0}, {0,0,0} },
	// Nro 6
	{ {0,0,0}, {0,1,1}, {0,0,0}, {0,1,0}, {0,0,0} },
	// Nro 7
	{ {0,0,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0} },
	// Nro 8
	{ {0,0,0}, {0,1,0}, {0,0,0}, {0,1,0}, {0,0,0} },
	// Nro 9
	{ {0,0,0}, {0,1,0}, {0,0,0}, {1,1,0}, {0,0,0} }
};

static DISP bufferDisplay; // buffer para cargar lo que muestra finalmente

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// Todas las q intervienen con el display no pueden usarse por otros archivos
static void drawScore(int idxScore, int score);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


void frontendInit(void) {
    joy_init();
    disp_init();
    disp_clear();
    disp_update();
}

void frontendDestroy(void) {
    disp_clear();
    disp_update();
}



Input frontendGetInput(void) {
    joyinfo_t joy = joy_read();
    if (joy.sw == J_PRESS) {
		return SELECT;
    } else if (joy.y > JOY_LIM){
    	return UP;
    }  else if joy.y < -JOY_LIM){
    	return DOWN;
    }  else if (joy.x > JOY_LIM){
    	return RIGTH;
    }  else if (joy.x < JOY_LIM){
    	return LEFT;
    } else {
    	return NONE; //Caso no se movio joystick, siempre tiene que devolver algo la funcion
    }
}


void frontendRender(Game * game){
	int f = 0, c = 0, idxZones = 0, idxScore = 0;

	switch(game->state.id) {
	disp_clear(); //Para cada case empiezan todos los leds apagadas
		case MENU:
			//...
			break;

		case POINTS:
			joy = joy_read(); //lee continuamente joystick

			if (joy.y > JOY_LIM && idxScore > 0){ //Si joy arriba y no llego al primer puntaje, sube
				usleep(100000); //ANTIREBOTE BLOQUEANTE
				while(joy_read().y > JOY_LIM);
				idxScore--;
				drawScore(idxScore, scores[idxScore]);

			}  else if (joy.y < -JOY_LIM && idxScore < TOP10_SIZE-1){ //Si joy abajo y no llego a ultimo puntaje, baja
				usleep(100000); //ANTIREBOTE BLOQUEANTE
				while(joy_read().y < -JOY_LIM);
				idxScore++;
				drawScore(idxScore, scores[idxScore]);
			}

			break;

		case PAUSED:
			//...

			break;

		case PLAYING:

			// Dibuja zonas
			for ( f = 0; f < MAX_ZONES; f++) {
				drawZone(&(game->level).zones[idxZones]);
			}

			//Dibuja obstaculos y floaters
			drawObstacles(&(game->entities).obstacles));
			drawFloaters(&(game->entities).floaters));

			//Dibuja rana (titila)
			drawFrog(&(game->frog));

			break;

		case GAME_OVER:

			msg = { //configura msg display para "GAME OVER"
			        {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
			        {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
			        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1},
			        {1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,1},
			        {1,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1},
					{1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,1},
					{1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1},
					{1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			        {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
			        {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}
			};


			for ( f = 0; f <  + 1; f++) {
				for (int c = 0; c < MAP_WIDTH; c++) {
					disp_write((dcoord_t){.y = f, .x = c}, msg[f][c]);
				}
			}
			break;

		case VICTORY:

			msg = { //configura msg display para victory "YOU WIN"
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0},
				{0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0},
				{0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0},
				{0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0},
				{0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0},
				{0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0},
				{0,0,1,1,0,0,1,1,1,1,0,1,1,1,1,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,1,0,0,0,1,0,1,1,0,1,0,0,0,1,0},
				{0,1,0,0,0,1,0,1,1,0,1,1,0,0,1,0},
				{0,1,0,0,0,1,0,1,1,0,1,0,1,0,1,0},
				{0,1,0,1,0,1,0,1,1,0,1,0,0,1,1,0},
				{0,1,1,0,1,1,0,1,1,0,1,0,0,0,1,0},
				{0,1,0,0,0,1,0,1,1,0,1,0,0,0,1,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
			};

			for ( f = 0; f <  + 1; f++) {
				for (int c = 0; c < MAP_WIDTH; c++) {
					disp_write((dcoord_t){.y = f, .x = c}, msg[f][c]);
				}
			}
			break;

		default:
			break;
	}

	disp_update();
}


void drawObstacles(Entity obstacles[]){
	int idxObs = 0, len = 0;
	for ( ; idxObs <= MAX_OBSTACLES; idxObs ++){
		if (obstacles[idxObs].active){ //si existe obstaculo
			for ( ;ht < (obstacles[idxObs].height), ht++){ //itera por altura
				for ( ; len < (obstacles[idxObs].length), len++){ //itera por largo
					entity_pos = {obstacles[idxObs].x + len,(obstacles[idxObs].y +ht};
					disp_write(entity_pos, D_ON); //Obstaculos prendidos. Calle apagada.
				}
			}
		}
	}
}


void drawFloaters(Entity floaters[]){
	int idxFlo = 0, len = 0;
	for ( ; idxFlo  <= MAX_FLOATERS; idxFlo ++){
		if (floaters[idxFlo ].active){ //si existe obstaculo
			for ( ; ht < (floaters[idxFlo ].height), ht++){ //itera por altura
				for ( ; len < (floaters[idxFlo ].length), len++){ //itera por largo
					entity_pos = {floaters[idxFlo ].x + len),(floaters[idxFlo ].y +ht};
					disp_write(entity_pos, D_OFF); //Floaters apagados. Agua prendida.
				}
			}
		}
	}
}

void drawZone(const Zone * zone){
	int f = 0, c = 0;

	switch (zone->type){

		case WATER: // Dibuja agua (LEDs prendidos)
			for (f = 0; f < zone->height; f++) {
				for (c = 0; c <= MAP_WIDTH; c++) {
					disp_write((dcoord_t){.y = f + (zone->y0), .x = c},D_ON);
				}
			}
		break;

		case ROAD: // Dibuja calle (LEDs apagados)
			for (f = 0 ; f < zone->height ; f++) {
				for (c = 0 ; c <= MAP_WIDTH ; c++) {
					disp_write((dcoord_t){.y = f + (zone->y0), .x = c}, D_OFF);
				}
			}
		break;

		case SAFE: // Dibuja safe zone (LEDs diagonales apuntando a izquierda)

			 //height de safe es siempre 2 unidades

			//Dibuja fila de abajo
			for (f = 0 ; f < (zone->height) - 1 ; f++) {
				for (c = 0 ; c <= MAP_WIDTH ; c++) {
					disp_write((dcoord_t){.y = f + (zone->y0) , .x = c}, D_OFF);
					c++; //Saltea un led, lo deja apagado por clear_disp
				}
			}

			//Dibuja fila de arriba
			for (f = 1 ; f < (zone->height) ; f++) {
				for (c = 1 ; c <= MAP_WIDTH ; c++) { //Emppieza con columna defasada a la derecha.
					disp_write((dcoord_t){.y = f + (zone->y0), .x = c}, D_OFF);
					c++; //Saltea un led, lo deja apagado por clear_disp
				}
			}
		break;

		case START: // Dibuja safe zone (LEDs diagonales apuntando a derecha)

			//height de safe es siempre 2 unidades

			//Dibuja fila de abajo
			for (f = 0 ; f < (zone->height) - 1 ; f++) {
				for (c = 1 ; c <= MAP_WIDTH ; c++) {  //Empieza con columna defasada a la derecha.
					disp_write((dcoord_t){.y = f + (zone->y0), .x = c}, D_OFF);
					c++; //Saltea un led, lo deja apagado por clear_disp
				}
			}

			//Dibuja fila de arriba
			for (f = 1; f < (zone->height); f++) {
				for (c = 0; c <= MAP_WIDTH; c++) {
					disp_write((dcoord_t){.y = f + (zone->y0), .x = c},D_OFF);
					c++; //Saltea un led, lo deja apagado por clear_disp
				}
			}
		break;

	}
}


void drawScore(int idxScore, int score) {
	int f, c, d, id;

	for (f = 0; f < MAP_HEIGHT; f++) { // Copia base a buffer
		for (c = 0; c < MAP_WIDTH; c++) {
			bufferDisplay[f][c] = menuBackground[f][c];
		}
	}

	int d1 = (score/100), d2 = (score%100)/10, d3 = (score%10);
	int scoreDigits[DIGITS] = {d1,d2,d3};
	int currentDigit = 0, x_offset = 0, y_offset = 0;

	for (d = 0; d < DIGITS; d++) { // Recorremos digito por digito el score actual
		currentDigit = scoreDigits[d];
		// Establecemos cursor en x
		x_offset = SCORE_XCOORD + d*(DIGIT_WIDTH + SPACE_DIGITS);
		// si d es cero, cursor queda en el x init
		// si d es uno, dezplaza 1 space + 3 ancho de digito desde x init
		// si d es dos, dezplaza 2*1 space + 2*3 ancho de digito desde x init
		y_offset = SCORE_YCOORD; // Cursor en y está arriba siempre

		for (f = 0; f < DIGIT_HEIGHT; f++) { // Copia digito actual a buffer
			for (c = 0; c < DIGIT_WIDTH; c++) {
				// Usamos offsets en x e y para el lugar de copiado en el display
				bufferDisplay[f + y_offset][c + x_offset] = digits[currentDigit][f][c];
			}
		}

	}

	for (f = 0; f < MAP_HEIGHT; f++) { //Paso buffer display
		for (c = 0; c < MAP_WIDTH; c++) {
			if(bufferDisplay[f][c]){
				disp_write((dcoord_t){.y = f, .x = c}, D_ON);
			} else {
				disp_write((dcoord_t){.y = f, .x = c}, D_OFF);
			}
		}
	}

	for(id = 0; id <= idxScore; id++){
		disp_write((dcoord_t){.y = SCORE_ID_YCOOR, .x = SCORE_ID_XCOOR + id}, D_OFF);
	}

	disp_update();
}
