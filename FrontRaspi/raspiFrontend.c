#include <stdio.h>
#include <stdint.h>


#include <time.h>
#include <unistd.h>

#include "disdrv.h"
#include "joydrv.h"

#include "game.h"
#include "config.h"

#define JOY_LIM 10 //Limite para detectar movimiento del joystic

static dcoord_t frog_pos = {MAP_WIDTH  >> 1, MAP_HEIGHT}; //Sse queda del lado izquierdo de la mitad vertical, abajo de todo
static dcoord_t entity_pos;
MSG msg; //Global para que inicialice en cero

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
	disp_clear();

	switch(game->state.id) {
		case MENU:
			break;

		case PLAYING:
			// Dibuja rana
			frog_pos = {x, y};
			disp_write(frog_pos, D_ON);


			// Dibuja obstaculos
			drawObstacles((game->entities).obstacles));
			drawFloaters((game->entities).floaters));


			break;

		case GAME_OVER:

			msg = { //configura msg display para "GAME OVER"
			        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			        {1,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1},
			        {1,0,0,0,0,1,0,1,0,1,1,1,0,1,0,0},
			        {1,0,1,1,0,1,1,1,0,1,0,1,0,1,1,0},
			        {1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0},
			        {1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1},
			        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			        {1,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1},
			        {1,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1},
			        {1,0,0,1,0,1,0,1,0,1,1,1,0,1,1,1},
			        {1,0,0,1,0,0,1,0,0,1,0,0,0,1,1,0},
			        {1,1,1,1,0,0,1,0,0,1,1,1,0,1,0,1},
			        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
			};

			for (int f = 0; f < 16; f++) {
				for (int c = 0; c < 16; c++) {
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

			for (int f = 0; f < 16; f++) {
				for (int c = 0; c < 16; c++) {
					disp_write((dcoord_t){.y = f, .x = c}, gameOver[f][c]);
				}
			}
			break;

		default:
			break;
	}

	disp_update();
}


void drawObstacles(Entity obstacles[]){
	int idx_obs = 0, len = 0;
	for ( ; idx_obs <= MAX_OBSTACLES; idx_obs++){
		if (obstacles[idx_obs].active){ //si existe obstaculo
			for ( ;ht < (obstacles[idx_obs].height),ht++){ //itera por altura
				for ( ; len < (obstacles[idx_obs].length), len++){ //itera por largo
					entity_pos = {obstacles[idx_obs].x + len,(obstacles[idx_obs].y +ht};
					disp_write(entity_pos, D_ON); //Obstaculos prendidos. Calle apagada.
				}
			}
		}
	}
}


void drawFloaters(Entity floaters[]){

	int idx_flo = 0, len = 0;
	for ( ; idx_flo <= MAX_FLOATERS; idx_flo++){
		if (floaters[flo].active){ //si existe obstaculo
			for ( ; ht < (floaters[idx_flo].height), ht++){ //itera por altura
				for ( ; len < (floaters[idx_flo].length), len++){ //itera por largo
					entity_pos = {floaters[idx_flo].x + len),(floaters[idx_flo].y +ht};
					disp_write(entity_pos, D_OFF); //Floaters apagados. Agua prendida.
				}
			}
		}
	}
}
