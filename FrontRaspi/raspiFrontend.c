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
    	return NULL; //Caso no se movio joystick, siempre tiene que devolver algo la funcion
    }
}


void frontendRender(Game * game, GameEntities * gameEntities){
	disp_clear();

	switch(game->state.id) {
		case MENU:
			break;

		case PLAYING:
			// Dibuja rana
			frog_pos = {x, y};
			disp_write(frog_pos, D_ON);


			// Dibuja obstaculos
			int cont_obs = 0, cont_flo = 0, length = 0;
			for ( ; cont_obs <= MAX_OBSTACLES; cont_obs++){
				if (gameEntities->obstacles)[i].active){ //si existe obstaculo
					for ( ; height <= (game->entities.obstacles[i].height), height++){ //itera por altura
						for ( ; length<= (game->entities.obstacles[i].length), length++){ //itera por largo
							entity_pos = {game->entities.obstacles[i].x + length,(game->entities.obstacles[i].y + height};
							disp_write(entity_pos, D_ON);
						}
					}
				}
			}

			for ( ; cont_obs <= MAX_FLOATERS; cont_obs++){
				if (gameEntities->floaters)[i].active){ //si existe obstaculo
					for ( ; height <= (game->entities.floaters[i].height), height++){ //itera por altura
						for ( ; length<= (game->entities.floaters[i].length), length++){ //itera por largo
							entity_pos = {game->entities.floaters[i].x + length,(game->entities.floaters[i].y + height};
							disp_write(entity_pos, D_ON);
						}
					}
				}
			}

			break;

		case GAME_OVER:
			break;

		case VICTORY:
			break;

		default:
			break;
	}

	disp_update();
}
