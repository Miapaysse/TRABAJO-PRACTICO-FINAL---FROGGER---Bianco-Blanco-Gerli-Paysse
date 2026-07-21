/***************************************************************************//**
  @file     +raspiDraw.c+
  @brief    +Funciones y variables para dibujar sobre el display de LEDs+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include "disdrv.h"
#include <unistd.h>
#include "raspiFrontend.h"
#include "raspiDraw.h"
#include "levels.h"
#include "entities.h"
#include "config.h"

// Bitmaps de 16x16 para los carteles y opciones del juego
const uint16_t msgsDisp[MSG_MAX_MENUS][MAP_HEIGHT + 1] = {
		{//Home title
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1111111111111111, 0b1010100010101001, 0b1010101010001011, 0b1000101010101001,
			0b1010101010101011, 0b1010100010101001, 0b1111111111111111, 0b1000000000000001,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//Pause title
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b0010001010100100, 0b0010101010101101, 0b0010001010100100, 0b0110101010110101,
			0b0110101000100100, 0b1111111111111111, 0b1000000000000001, 0b1111111111111111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//Top 10 title
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1100010001000111, 0b1110110101010111, 0b1110110101000111, 0b1110110001011111,
			0b1111111111111111, 0b1111101000111111, 0b1000101010110001, 0b1111101000111111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//Go Play 
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1111111111111111, 0b1000101100010101, 0b1010101101010101, 0b1000101100010101,
			0b1011101101011011, 0b1011100101011011, 0b1111111111111111, 0b1111111111111111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//Go to home 
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1111111011111111, 0b1111110001111111, 0b1111100000111111, 0b1111000000011111,
			0b1110000000001111, 0b1111001110011111, 0b1111001110011111, 0b1111001110011111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//Despause
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1111110011111111, 0b1111110001111111, 0b1111110000111111, 0b1111110000011111,
			0b1111110000111111, 0b1111110001111111, 0b1111110011111111, 0b1111111111111111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//Go TOP 10 
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1100010001000111, 0b1110110101010111, 0b1110110101000111, 0b1110110001011111,
			0b1111111111111111, 0b1111101000111111, 0b1111101010111111, 0b1111101000111111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//Go BACK 
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b0001100010001010, 0b0110101010111010, 0b0110101010111010, 0b0001100010111001,
			0b0110101010111010, 0b0110101010111010, 0b0110101010111010, 0b0001101010001010,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//EXIT 
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1000101010010001, 0b1011101010011011, 0b1011101010011011, 0b1001110110011011,
			0b1011101010011011, 0b1011101010011011, 0b1000101010011011, 0b1111111111111111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//GAME OVER
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1111111111111111, 0b0011000100010011, 0b0101011101010101, 0b0101000100010101,
			0b0101011101010101, 0b0011000101010011, 0b1111111111111111, 0b1000000000000001,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{ //YOU WIN
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1101010001010111, 0b1110110101010111, 0b1110110001000111, 0b1111111111111111,
			0b1101010101101111, 0b1101010100101111, 0b1100010101001111, 0b1101010101101111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{ //-corazon, perdio vida
			0b1111111111111111, 0b1111111111111111, 0b0000000000000000, 0b1111111111111111,
			0b1111111111111111, 0b1111111001001111, 0b1111110000000111, 0b1001111000001111,
			0b1111111100011111, 0b1111111110111111, 0b1111111111111111, 0b1111111111111111,
			0b1111111111111111, 0b0000000000000000, 0b1111111111111111, 0b1111111111111111
		},
		{ //Next level
			0b1111111111111111, 0b1111111111111111, 0b0110100101010001, 0b0010101101011011,
			0b0100100110111011, 0b0110101101011011, 0b1110100101011111, 0b1111111111111111,
			0b0110010101001011, 0b0110110101011011, 0b0110010101001011, 0b0110111011011011,
			0b0010011011001001, 0b1111111111111111, 0b1111111111111111, 0b1111111111111111
		},
		{ //Reached top 10, "IN TOP 10"
			0b1111111111111111, 0b1110001011011111, 0b1111011001011111, 0b1110001010011111,
			0b1111111111111111, 0b1111111111111111, 0b1100010001000111, 0b1110110101010111,
			0b1110110101000111, 0b1110110001011111, 0b1111111111111111, 0b1111111111111111,
			0b1111101000111111, 0b1111101010111111, 0b1111101000111111, 0b1111111111111111
		},
		{ //ERROR "?"
			0b1111111111111111, 0b1111111111111111, 0b1111111111111111, 0b1111000000111111,
			0b1111111110111111, 0b1111111110111111, 0b1111000000111111, 0b1111011111111111,
			0b1111011111111111, 0b1111011111111111, 0b1111111111111111, 0b1111011111111111,
			0b1111111111111111, 0b1111111111111111, 0b1111111111111111, 0b1111111111111111
		}
};

/*******************************************************************************
 * STATIC VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static DISP bufferDisplay; // Buffer para armar el score antes de imprimir

static const DISP menuBackground = { // Fondo decorativo del ranking
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}
};

static const int digits[10][DIGIT_HEIGHT][DIGIT_WIDTH] = { // Dibujos de los numeros 0-9
	{ {0,0,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,0,0} }, 
	{ {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1} }, 
	{ {0,0,0}, {1,1,0}, {0,0,0}, {0,1,1}, {0,0,0} }, 
	{ {0,0,0}, {1,1,0}, {0,0,0}, {1,1,0}, {0,0,0} }, 
	{ {0,1,0}, {0,1,0}, {0,0,0}, {1,1,0}, {1,1,0} }, 
	{ {0,0,0}, {0,1,1}, {0,0,0}, {1,1,0}, {0,0,0} }, 
	{ {0,0,0}, {0,1,1}, {0,0,0}, {0,1,0}, {0,0,0} }, 
	{ {0,0,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0} }, 
	{ {0,0,0}, {0,1,0}, {0,0,0}, {0,1,0}, {0,0,0} }, 
	{ {0,0,0}, {0,1,0}, {0,0,0}, {1,1,0}, {0,0,0} }  
};

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static int popFromOtherSide(int x) { // Logica Pac-Man para envolver coordenadas horizontales
    int width = MAP_WIDTH + 1;
    x %= width;
    if (x < 0) { // Reaparece por la izquierda si es negativo
        x += width;
    }
    return x;
}

static int passDrawing(int x, int y, dlevel_t val) { // Chequea limites y manda el pixel al driver real
    if (y < 0 || y > MAP_HEIGHT) {
        return ERR_OUT_OF_DISPLAY_BOUNDS;
    }
    x = popFromOtherSide(x);

	if (x < 0 || x > MAP_HEIGHT) {
        return ERR_OUT_OF_DISPLAY_BOUNDS;
    }
    disp_write((dcoord_t){ .x = x, .y = y }, val);
	return 0;
}

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void drawMSG(const uint16_t msg[MAP_HEIGHT+1]){ // Muestra una pantalla fija bit a bit
	int f, c, ledState = 0;
	for (f = 0; f <= MAP_HEIGHT; f++) {
		for (c = 0; c <= MAP_WIDTH; c++) {
			ledState = msg[f] >> (MAP_HEIGHT - c) & 1;
			if(ledState){
				passDrawing(c, f, D_ON);
			} else {
				passDrawing(c, f, D_OFF);
			}
		}
	}
}

void drawScore(int idxScore, uint16_t score) { // Descompone el puntaje y lo dibuja en pantalla
	int f, c, d, id;

	for (f = 0; f <= MAP_HEIGHT; f++) { // Carga el fondo decorativo
		for (c = 0; c <= MAP_WIDTH; c++) {
			bufferDisplay[f][c] = menuBackground[f][c];
		}
	}

	int d1 = (score/100), d2 = (score%100)/10, d3 = (score%10); // Centenas, decenas, unidades
	int scoreDigits[DIGITS] = {d1,d2,d3};
	int currentDigit = 0, x_offset = 0, y_offset = 0;

	for (d = 0; d < DIGITS; d++) { // Pega cada numero en el buffer
		currentDigit = scoreDigits[d];
		x_offset = SCORE_XCOORD + d*(DIGIT_WIDTH + SPACE_DIGITS);
		y_offset = SCORE_YCOORD;

		for (f = 0; f < DIGIT_HEIGHT; f++) {
			for (c = 0; c < DIGIT_WIDTH; c++) {
				bufferDisplay[f + y_offset][c + x_offset] = digits[currentDigit][f][c];
			}
		}
	}

	for (f = 0; f <= MAP_HEIGHT; f++) { // Pasa el buffer a la pantalla real
		for (c = 0; c <= MAP_WIDTH; c++) {
			if(bufferDisplay[f][c]){
				disp_write((dcoord_t){.y = f, .x = c}, D_ON);
			} else {
				disp_write((dcoord_t){.y = f, .x = c}, D_OFF);
			}
		}
	}

	for(id = 0; id <= idxScore; id++){ // Puntos inferiores para marcar el puesto en el top 10
		disp_write((dcoord_t){.y = SCORE_ID_YCOOR, .x = SCORE_ID_XCOOR + id}, D_OFF);
	}
}

void drawZone(const Row_t *rows) { // Dibuja el fondo segun la zona de cada fila
    int r, c, rDisp;

    for (r = 0; r <= MAP_HEIGHT; r++) {
        rDisp = ROW(r);

        for (c = 0; c <= MAP_WIDTH; c++) {
            int drawFlag = 0;

            switch (rows[r].zone) {
                case WATER: // Agua prendida
                    drawFlag = 1;
                    break;
                case ROAD: // Calle apagada
                    drawFlag = 0;
                    break;
				case START:
				case SAFE: // Veredas ajedrezadas, meta fija brillante
					if (r == FINISH_LINE || r == FINISH_LINE + 1) {
						drawFlag = 1;
					} else {
						drawFlag = ((c + rDisp) % 2 == 0);
					}
                    break;
                case DEFAULT:
                default:
                    drawFlag = 0;
                    break;
            }

            passDrawing(c, rDisp, drawFlag ? D_ON : D_OFF);
        }
    }
}

void drawObstacles(const Entity_t obstacles[]){ // Pinta los autos (Prendidos)
	int idxObs, len, rDisp;
	int cDisp;

	for (idxObs = 0; idxObs < MAX_OBSTACLES; idxObs++){
		if (obstacles[idxObs].active){
			rDisp = ROW(obstacles[idxObs].y);
			for (len = 0; len < obstacles[idxObs].length; len++){
				cDisp = obstacles[idxObs].x + len;
				passDrawing(cDisp, rDisp, D_ON);
			}
		}
	}
}

void drawFloaters(const Entity_t floaters[]){ // Apaga leds sobre el rio para recortar los troncos
	int idxFlo, len, rDisp;
	int cDisp;

	for (idxFlo = 0; idxFlo < MAX_FLOATERS; idxFlo++){
		if (floaters[idxFlo].active){
			rDisp = ROW(floaters[idxFlo].y);
			for (len = 0; len < floaters[idxFlo].length; len++){
				cDisp = floaters[idxFlo].x + len;
				passDrawing(cDisp, rDisp, D_OFF); 
			}
		}
	}
}

void drawBoxes (FinishBox_t boxes[], int blink){ // Dibuja nidos y los hace titilar si la rana llego
	int x, i = 0;
	for (; i < FINISH_BOX_COUNT; i++){
		x = boxes[i].x;
		if (!boxes[i].occupied){
			passDrawing(x, 1, D_OFF);
		} else {
			passDrawing(x, 1, blink);
		}
	}
}

void drawFrog(const Frog_t * frog, int blink) { // Dibuja la rana prendida o apagada (para el efecto titilante)
	int cDisp = frog->x;
	int y_disp = ROW(frog->y);
	if (blink) {
		passDrawing(cDisp, y_disp, D_ON);
	} else {
		passDrawing(cDisp, y_disp, D_OFF);
	}
}

void showRank(const Top10Status_t status){ // Si entro al ranking muestra festejo, sino pasa de largo
	printf("%d", status);
	if(status == TOP10_CHANGED){ 
		drawMSG(msgsDisp[MY_RANKING]);
		disp_update();
		usleep(DISPLAY_RANK_TIME);
	} 
}

void showScore(const uint16_t score){ // Fuerza la muestra de los puntos totales ganados
	drawScore(-1, score);
	disp_update();
	usleep(DISPLAY_SCORE_TIME);
}

void showLevelNextLevel(const LevelId_t currentLevel, LevelId_t * lastLevel){ // Frena un segundo para avisar cambio de nivel
	if (currentLevel != *lastLevel) {
		*lastLevel = currentLevel;
		drawMSG(msgsDisp[NEXT_LEVEL]);
		disp_update();
		usleep(DISPLAY_DEFAULT_TIME);
	}
}

void showLives(const uint8_t currentLives, uint8_t * lastLives){ // Frena un segundo y muestra corazon roto si moriste
	if (currentLives != *lastLives) {
		*lastLives = currentLives;
		drawMSG(msgsDisp[LIVE_LOSED]);
		disp_update();
		usleep(DISPLAY_DEFAULT_TIME); 
	}
}