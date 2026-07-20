#include <stdio.h>
#include <stdint.h>
#include "disdrv.h"
#include "raspiFrontend.h"
#include "raspiDraw.h"
#include "levels.h"
#include "entities.h"
#include "config.h"

// Defino arreglo de bitmaps con distintos mensajes
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
			0b1111111011111111, 0b1111110001111111, 0b1111100000111111, 0b1111000000111111,
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
			0b0000000100000000, 
			0b0000001110000000, 
			0b0000000000000000,
			0b1111111111111111,
			0b1111111111111111, 
			0b0011000100010011,
			0b0101011101010101, 
			0b0101000100010101,
			0b0101011101010101,
			0b0011000101010011,
			0b1111111111111111, 
			0b1000000000000001,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},
		{ //YOU WIN
			0b0000000100000000, 
			0b0000001110000000, 
			0b0000000000000000,
			0b1111111111111111,
			0b1101010001010111, 
			0b1110110101010111, 
			0b1110110001000111, 
			0b1111111111111111, 
			0b1101010101101111, 
			0b1101010100101111, 
			0b1100010101001111, 
			0b1101010101101111,
			0b1111111111111111,
			0b0000000000000000,
			0b0000001110000000,
			0b0000000100000000
		},
		{ //-corazon, perdio vida
			0b1111111111111111,
			0b1111111111111111,
			0b0000000000000000,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111001001111,
			0b1111110000000111,
			0b1001111000001111,
			0b1111111100011111,
			0b1111111110111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b0000000000000000,
			0b1111111111111111,
			0b1111111111111111
		},
		{ //Next level
			0b1111111111111111,
			0b1111111111111111,
			0b0110100101010001,
			0b0010101101011011,
			0b0100100110111011,
			0b0110101101011011,
			0b1110100101011111,
			0b1111111111111111,
			0b0110010101001011,
			0b0110110101011011,
			0b0110010101001011,
			0b0110111011011011,
			0b0010011011001001,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111
		},
		{ //YOU'RE TOP 10
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111110000111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111,
			0b1111111111111111
		},

};

static DISP bufferDisplay; // buffer para cargar lo que muestra finalmente

static const DISP menuBackground = {
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}
};

static const int digits[10][DIGIT_HEIGHT][DIGIT_WIDTH] = { //Arreglo con todos los dibujos de los dijitos para el display
	{ {0,0,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,0,0} }, // Nro 0
	{ {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,0,1} }, // Nro 1
	{ {0,0,0}, {1,1,0}, {0,0,0}, {0,1,1}, {0,0,0} }, // Nro 2
	{ {0,0,0}, {1,1,0}, {0,0,0}, {1,1,0}, {0,0,0} }, // Nro 3
	{ {0,1,0}, {0,1,0}, {0,0,0}, {1,1,0}, {1,1,0} }, // Nro 4
	{ {0,0,0}, {0,1,1}, {0,0,0}, {1,1,0}, {0,0,0} }, // Nro 5
	{ {0,0,0}, {0,1,1}, {0,0,0}, {0,1,0}, {0,0,0} }, // Nro 6
	{ {0,0,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0} }, // Nro 7
	{ {0,0,0}, {0,1,0}, {0,0,0}, {0,1,0}, {0,0,0} }, // Nro 8
	{ {0,0,0}, {0,1,0}, {0,0,0}, {1,1,0}, {0,0,0} }  // Nro 9
};

static int popFromOtherSide(int x) { //Dibuja la parte de la entitie que debe aparece por el otro lado
    int width = MAP_WIDTH + 1;
    x %= width; //toma su cordenada en x y ve cuanto se fue del mapa
    if (x < 0) { // Si es negativa, es por que debe aparecer por la izquierda
        x += width;
    }
    return x;
}

static void passDrawing(int x, int y, dlevel_t val) {
    if (y < 0 || y > MAP_HEIGHT) {
        return;
    }
    x = popFromOtherSide(x);
    disp_write((dcoord_t){ .x = x, .y = y }, val);
}

void drawMSG(const uint16_t msg[MAP_HEIGHT+1]){
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

void drawScore(int idxScore, int score) {
	int f, c, d, id;

	for (f = 0; f <= MAP_HEIGHT; f++) {
		for (c = 0; c <= MAP_WIDTH; c++) {
			bufferDisplay[f][c] = menuBackground[f][c];
		}
	}

	int d1 = (score/100), d2 = (score%100)/10, d3 = (score%10);
	int scoreDigits[DIGITS] = {d1,d2,d3};
	int currentDigit = 0, x_offset = 0, y_offset = 0;

	for (d = 0; d < DIGITS; d++) {
		currentDigit = scoreDigits[d];
		x_offset = SCORE_XCOORD + d*(DIGIT_WIDTH + SPACE_DIGITS);
		y_offset = SCORE_YCOORD;

		for (f = 0; f < DIGIT_HEIGHT; f++) {
			for (c = 0; c < DIGIT_WIDTH; c++) {
				bufferDisplay[f + y_offset][c + x_offset] = digits[currentDigit][f][c];
			}
		}
	}

	for (f = 0; f <= MAP_HEIGHT; f++) {
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
}


void drawZone(const Row *rows) {
    int r, c, rDisp;

    for (r = 0; r <= MAP_HEIGHT; r++) {
        rDisp = ROW(r);

        for (c = 0; c <= MAP_WIDTH; c++) {
            int drawFlag = 0;

            switch (rows[r].zone) {
                case WATER:
                    drawFlag = 1;
                    break;
                case ROAD:
                    drawFlag = 0;
                    break;
				case START:
				case SAFE:
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


void drawObstacles(const Entity obstacles[]){
	int idxObs, len, rDisp;
	int x_disp, y_disp;

	for (idxObs = 0; idxObs < MAX_OBSTACLES; idxObs++){
		if (obstacles[idxObs].active){ // si existe obstáculo
			rDisp = ROW(obstacles[idxObs].y);
			y_disp = rDisp;
			for (len = 0; len < obstacles[idxObs].length; len++){ // itera por largo
				x_disp = obstacles[idxObs].x + len;
				passDrawing(x_disp, y_disp, D_ON); // obstaculos prendidos
			}
		}
	}
}

void drawFloaters(const Entity floaters[]){
	int idxFlo, len, rDisp;
	int x_disp, y_disp;

	for (idxFlo = 0; idxFlo < MAX_FLOATERS; idxFlo++){
		if (floaters[idxFlo].active){ // si existe floater
			rDisp = ROW(floaters[idxFlo].y);
			y_disp = rDisp;
			for (len = 0; len < floaters[idxFlo].length; len++){ // itera por largo
				x_disp = floaters[idxFlo].x + len;
				passDrawing(x_disp, y_disp, D_OFF); // Floaters apagados sobre agua
			}
		}
	}
}

void drawBoxes (FinishBox boxes[], int blink){
	int x, i = 0;
	for (; i < FINISH_BOX_COUNT; i++){
		x = boxes[i].x;
		if (!boxes[i].occupied){
			passDrawing(x, 1, D_OFF);
		} else {
			passDrawing(x, 1, blink);
		}
	}
	//printf("\nListo\n");
}

void drawFrog(const Frog * frog, int blink) {
	int x_disp = frog->x;
	int y_disp = ROW(frog->y);
	if (blink) {
		passDrawing(x_disp, y_disp, D_ON);
	} else {
		passDrawing(x_disp, y_disp, D_OFF);
	}
}


void showRank(const Top10Status  status){
	printf("%d", status);
	if(status == TOP10_CHANGED){
		drawMSG(msgsDisp[MY_RANKING]);
		disp_update();
		usleep(DISPLAY_INFO_TIME);
	} 
}

void showScore(const uint16_t score){
	drawScore(-1, score);
	disp_update();
	usleep(DISPLAY_INFO_TIME);
}
