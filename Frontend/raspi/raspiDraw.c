#include <stdio.h>
#include <stdint.h>
#include "disdrv.h"
#include "raspiFrontend.h"
#include "raspiDraw.h"
#include "levels.h"
#include "entities.h"

// Defino arreglo de bitmaps con distintos mensajes
const uint16_t msgs_arr[MSG_MAX_MENUS][MAP_HEIGHT + 1] = {
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
		{//Play option
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1111111111111111, 0b1000101100010101, 0b1010101101010101, 0b1000101100010101,
			0b1011101101011011, 0b1011100101011011, 0b1111111111111111, 0b1111111111111111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//Go to home option
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1111111011111111, 0b1111110001111111, 0b1111100000111111, 0b1111000000111111,
			0b1110000000001111, 0b1111001110011111, 0b1111001110011111, 0b1111001110011111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//Despause option
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1111110011111111, 0b1111110001111111, 0b1111110000111111, 0b1111110000011111,
			0b1111110000111111, 0b1111110001111111, 0b1111110011111111, 0b1111111111111111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//TOP 10 option
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1100010001000111, 0b1110110101010111, 0b1110110101000111, 0b1110110001011111,
			0b1111111111111111, 0b1111101000111111, 0b1111101010111111, 0b1111101000111111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//Go BACK option
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b0001100010001010, 0b0110101010111010, 0b0110101010111010, 0b0001100010111001,
			0b0110101010111010, 0b0110101010111010, 0b0110101010111010, 0b0001101010001010,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//EXIT option
			0b0000000100000000, 0b0000001110000000, 0b0000000000000000, 0b1111111111111111,
			0b1000101010010001, 0b1011101010011011, 0b1011101010011011, 0b1001110110011011,
			0b1011101010011011, 0b1011101010011011, 0b1000101010011011, 0b1111111111111111,
			0b1111111111111111, 0b0000000000000000, 0b0000001110000000, 0b0000000100000000
		},
		{//GAME OVER
			0b0000000000000000, 0b1111011101010111, 0b1000010101110100, 0b1011011101010110,
			0b1001010101010100, 0b1111010101010111, 0b0000000000000000, 0b0000000000000000,
			0b0000000000000000, 0b1111010101110111, 0b1001010101000101, 0b1001010101110111,
			0b1001001001000110, 0b1111001001110101, 0b0000000000000000, 0b0000000000000000
		},
		{ //YOU WIN
			0b0000000000000000, 0b0100101111010010, 0b0100101001010010, 0b0100101001010010,
			0b0011001001010010, 0b0011001001010010, 0b0011001001010010, 0b0011001111011110,
			0b0000000000000000, 0b0100010110100010, 0b0100010110110010, 0b0100010110101010,
			0b0101010110100110, 0b0110110110100010, 0b0100010110100010, 0b0000000000000000
		}
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

static const int digits[10][DIGIT_HEIGHT][DIGIT_WIDTH] = {
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

static int popFromOtherSide(int x) {
    int width = MAP_WIDTH + 1;
    x %= width;
    if (x < 0) {
        x += width;
    }
    return x;
}

static void checkBorders(int x, int y, dlevel_t val) {
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
				checkBorders(c, f, D_ON);
			} else {
				checkBorders(c, f, D_OFF);
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
    int r, c, r_disp, backend_row;

    for (r = 0; r <= MAP_HEIGHT; r++) {
        backend_row = (r < MAP_HEIGHT) ? r : (MAP_HEIGHT - 1);
        r_disp = ROW(r);

        for (c = 0; c <= MAP_WIDTH; c++) {
            int draw_on = 0;

            switch (rows[backend_row].zone) {
                case WATER:
                    draw_on = 1;
                    break;
                case ROAD:
                    draw_on = 0;
                    break;
                case SAFE:
                case START:
                    draw_on = ((c + r_disp) % 2 == 0);
                    break;
                case DEFAULT:
                default:
                    draw_on = 0;
                    break;
            }

            checkBorders(c, r_disp, draw_on ? D_ON : D_OFF);
        }
    }
}


void drawObstacles(const Entity obstacles[]){
	int idxObs, len, r_disp;
	int x_disp, y_disp;

	for (idxObs = 0; idxObs < MAX_OBSTACLES; idxObs++){
		if (obstacles[idxObs].active){ // si existe obstáculo
			r_disp = ROW(obstacles[idxObs].y);
			y_disp = r_disp;
			for (len = 0; len < obstacles[idxObs].length; len++){ // itera por largo
				x_disp = obstacles[idxObs].x + len;
				checkBorders(x_disp, y_disp, D_ON); // obstaculos prendidos
			}
		}
	}
}

void drawFloaters(const Entity floaters[]){
	int idxFlo, len, r_disp;
	int x_disp, y_disp;

	for (idxFlo = 0; idxFlo < MAX_FLOATERS; idxFlo++){
		if (floaters[idxFlo].active){ // si existe floater
			r_disp = ROW(floaters[idxFlo].y);
			y_disp = r_disp;
			for (len = 0; len < floaters[idxFlo].length; len++){ // itera por largo
				x_disp = floaters[idxFlo].x + len;
				checkBorders(x_disp, y_disp, D_OFF); // Floaters apagados sobre agua
			}
		}
	}
}
