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

#include "raspiFrontend.h"
#include "entities.h"
#include "levels.h"
#include "config.h"
#include "game.h"


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static dcoord_t frog_pos = {(MAP_WIDTH + 1)  >> 1, MAP_HEIGHT + 1}; //Sse queda del lado izquierdo de la mitad vertical, abajo de todo
static dcoord_t entity_pos;


static enum msgs { //Enum apara signarle indice a las opciones de mensajes
	HOME,
	PAUSE,
	TOP_10,
	PLAY,
	GO_HOME,
	DESPAUSE,
	GO_TOP_10,
	GO_BACK,
	EXIT,
	GAME_OVER,
	YOU_WIN,
	MAX_MENUS
};

// Defino arreglo de bitmaps con distintos mensajes
static uint16_t msgs[MAX_MENUS][MAP_HEIGHT + 1] = {
		{//Home title
			0b0000000100000000,
			0b0000001110000000,
			0b0000000000000000,
			0b1111111111111111,
			0b1111111111111111,
			0b1010100010101001,
			0b1010101010001011,
			0b1000101010101001,
			0b1010101010101011,
			0b1010100010101001,
			0b1111111111111111,
			0b1000000000000001,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},

		{//Pause title
			0b0000000100000000,
			0b0000001110000000,
			0b0000000000000000,
			0b1111111111111111,
			0b0010001010100100,
			0b0010101010101101,
			0b0010001010100100,
			0b0110101010110101,
			0b0110101000100100,
			0b1111111111111111,
			0b1000000000000001,
			0b1111111111111111,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},
		
		{//Top 10 title
			0b0000000100000000,
			0b0000001110000000,
			0b0000000000000000,
			0b1111111111111111,
			0b1100010001000111,
			0b1110110101010111,
			0b1110110101000111,
			0b1110110001011111,
			0b1111111111111111,
			0b1111101000111111,
			0b1000101010110001,
			0b1111101000111111,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},
		
		{//Play option
			0b0000000100000000,
			0b0000001110000000,
			0b0000000000000000,
			0b1111111111111111,
			0b1111111111111111,
			0b1000101100010101,
			0b1010101101010101,
			0b1000101100010101,
			0b1011101101011011,
			0b1011100101011011,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},
		
		{//Go to home option
			0b0000000100000000,
			0b0000001110000000,
			0b0000000000000000,
			0b1111111111111111,
			0b1111111011111111,
			0b1111110001111111,
			0b1111100000111111,
			0b11110000000111111,
			0b1110000000001111,
			0b1111001110011111,
			0b1111001110011111,
			0b1111001110011111,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},
		
		{//Despause option
			0b0000000100000000,
			0b0000001110000000,
			0b0000000000000000,
			0b1111111111111111,
			0b1111110011111111,
			0b1111110001111111,
			0b1111110000111111,
			0b1111110000011111,
			0b1111110000111111,
			0b1111110001111111,
			0b1111110011111111,
			0b1111111111111111,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},
		
		{//TOP 10 option
			0b0000000100000000,
			0b0000001110000000,
			0b0000000000000000,
			0b1111111111111111,
			0b1100010001000111,
			0b1110110101010111,
			0b1110110101000111,
			0b1110110001011111,
			0b1111111111111111,
			0b1111101000111111,
			0b1111101010111111,
			0b1111101000111111,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},
		
		{//Go BACK option
			0b0000000100000000,
			0b0000001110000000,
			0b0000000000000000,
			0b1111111111111111,
			0b0001100010001010,
			0b0110101010111010,
			0b0110101010111010,
			0b0001100010111001,
			0b0110101010111010,
			0b0110101010111010,
			0b0110101010111010,
			0b0001101010001010,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},
		
		{//EXIT option
			0b0000000100000000,
			0b0000001110000000,
			0b0000000000000000,
			0b1111111111111111,
			0b1000101010010001,
			0b1011101010011011,
			0b1011101010011011,
			0b1001110110011011,
			0b1011101010011011,
			0b1011101010011011,
			0b1000101010011011,
			0b1111111111111111,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},

		{//GAME OVER
			0b0000000000000000,
			0b1111011101010111,
			0b1000010101110100,
			0b1011011101010110,
			0b1001010101010100,
			0b1111010101010111,
			0b0000000000000000,
			0b0000000000000000,
			0b0000000000000000,
			0b1111010101110111,
			0b1001010101000101,
			0b1001010101110111,
			0b1001001001000110,
			0b1111001001110101,
			0b0000000000000000,
			0b0000000000000000
		},

		{ //YOU WIN
			0b0000000000000000,
			0b0100101111010010,
			0b0100101001010010,
			0b0100101001010010,
			0b0011001001010010,
			0b0011001001010010,
			0b0011001001010010,
			0b0011001111011110,
			0b0000000000000000,
			0b0100010110100010,
			0b0100010110110010,
			0b0100010110101010,
			0b0101010110100110,
			0b0110110110100010,
			0b0100010110100010,
			0b0000000000000000
		}
};

//--------- Variables para mostrar los scores en TOP 10 ------------
static int idxScore = 0;

DISP bufferDisplay; // buffer para cargar lo que muestra finalmente

const DISP menuBackground = {
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

// Defino digitos para display score. 10 valores, c/u ocupa 5 filas y 3 columnas
static const int digits[10][DIGIT_HEIGHT][DIGIT_WIDTH] = {
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

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

// Todas las q intervienen con el display no pueden usarse por otros archivos
static void drawScore(int idxScore, int score);
static void drawObstacles(Entity obstacles[]);
static void drawFloaters(Entity floaters[]);
static void drawZone(const Zone * zone);
static void drawMSG(const uint16_t bitmap[MAP_HEIGHT+1]);

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
    } else { // Esta normal
    	return NONE;
    }
}

void frontendRender(Game * game){
	int f = 0, c = 0, idxZones = 0;

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

			drawMSG(msgs[GAME_OVER]);

			break;

		case VICTORY:

			
			break;

		default:
			break;
	}

	disp_update();
}


static void drawObstacles(Entity obstacles[]){
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

static void drawFloaters(Entity floaters[]){
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

static void drawZone(const Zone * zone){
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
				for (c = 0 ; c <= MAP_WIDTH; c++) {
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


static void drawScore(int idxScore, int score) {
	int f, c, d, id;

	for (f = 0; f <= MAP_HEIGHT; f++) { // Copia base a buffer
		for (c = 0; c <= MAP_WIDTH; c++) {
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

	for (f = 0; f <= MAP_HEIGHT; f++) { //Paso buffer display
		for (c = 0; c <= MAP_WIDTH; c++) {
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

static void drawMSG(const uint16_t bitmap[MAP_HEIGHT+1]){
	int f, c, ledState = 0;
	for (f = 0; f <= MAP_HEIGHT; f++) {
		for (c = 0; c <= MAP_WIDTH; c++) {
			ledState = bitmap[f] >> (MAP_HEIGHT - c) & 1; // Obtengo bit a bit
			if(ledState){
				disp_write((dcoord_t){.y = f, .x = c}, D_ON);
			} else {
				disp_write((dcoord_t){.y = f, .x = c}, D_OFF);
			}
		}
	}
}