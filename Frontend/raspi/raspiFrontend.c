#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <unistd.h>
#include "disdrv.h"
#include "joydrv.h"

#include "config.h"
#include "game.h"
#include "entities.h"
#include "levels.h"
#include "raspiFrontend.h"
#include "raspiDraw.h"

joyinfo_t joy;
static int scores[10]; 
static Input ultimo_input = NONE;
int lastLive, showScore;

void frontendInit(void) {
    joy_init();
    disp_init();
    disp_clear();
    disp_update();
	showScore = 1;
	lastLive = MAX_LIVES;
	//scores[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
}

void frontendDestroy(void) {
    disp_clear();
    disp_update();
}

Input frontendGetInput(void) {
    Input input_actual = NONE;
    joy = joy_read();

    if (joy.sw == J_PRESS) {
        input_actual = SELECT;
    } else if (joy.y > JOY_LIM && joy.x < JOY_LIM && joy.x > -JOY_LIM) { //solamente arriba
        input_actual = UP;
    } else if (joy.y < -JOY_LIM && joy.x < JOY_LIM && joy.x > -JOY_LIM) { //solamente abajo
        input_actual = DOWN;
    } else if (joy.x > JOY_LIM && joy.y < JOY_LIM && joy.y > -JOY_LIM) { // solo a la derecha
        input_actual = RIGHT;
    } else if (joy.x < -JOY_LIM && joy.y < JOY_LIM && joy.y > -JOY_LIM) { //solo a la izquierda
        input_actual = LEFT;
    } else {
        input_actual = NONE;
    }

    if (input_actual != ultimo_input) {
        ultimo_input = input_actual;
        return input_actual;
    } else {
        return NONE; 
    }
}

void frontendRender(Game * game) {
    int option = 0;
	disp_clear();

	switch((game->state).id) {
		case MENU:

			//Inicializo aca variables para mostras mensajes temporales en display
			showScore = 1;
			// si estas en menu signica que volviste a empezar el juego, por lo tanto se resetea el showScore
			lastLive = MAX_LIVES;

			option = (game->state).menu.selected;
			if(option == MENU_TITLE){
				drawMSG(msgs_arr[MSG_HOME]);
			} else if(option == MENU_PLAY){
				drawMSG(msgs_arr[MSG_PLAY]);
			} else if(option == MENU_POINTS){
				drawMSG(msgs_arr[MSG_GO_TOP_10]);
			} else if(option == MENU_EXIT){
				drawMSG(msgs_arr[MSG_EXIT]);
			} else {
				printf("Error en Menu");
			}
			break;

		case POINTS:
			option = (game->state).points.selected;			
            switch (option) {	
				case POINTS_TITLE:
				    drawMSG(msgs_arr[MSG_TOP_10]);
				break;
				
				case POINT_1: case POINT_2: case POINT_3: case POINT_4: case POINT_5:
				case POINT_6: case POINT_7: case POINT_8: case POINT_9: case POINT_10:
				    drawScore(option-POINT_1, scores[option-POINT_1]);
				break;
				
				case POINTS_MENU:
					drawMSG(msgs_arr[MSG_GO_HOME]);
				break;
				
				case POINTS_EXIT:
				    drawMSG(msgs_arr[MSG_EXIT]);
				break;
            }
			break;

		case PAUSED:
			option = (game->state).paused.selected;
			if(option == PAUSED_TITLE){
				drawMSG(msgs_arr[MSG_PAUSE]);
			} else if(option == PAUSED_MENU){
				drawMSG(msgs_arr[MSG_GO_HOME]);
			} else if(option == PAUSED_PLAY){
				drawMSG(msgs_arr[MSG_DESPAUSE]);
			} else if(option == PAUSED_EXIT){
				drawMSG(msgs_arr[MSG_EXIT]);
			} else {
				printf("Error");
			}
			break;
			
			case PLAYING:
				option = (game->state).id;
				if(option == PAUSED){
					drawMSG(msgs_arr[MSG_PAUSE]);
				} else {
					if (game->lives != lastLive) {
						lastLive = game->lives;
						drawMSG(msgs_arr[LIVE_LOSED]);
						disp_update();
						usleep(1000000); //pauso todo el programa por 1 seg
					}
					// Dibuja zonas
					drawZone((game->level).rows);
					
					//Dibuja obstaculos y floaters
					drawObstacles((game->entities).obstacles);
					drawFloaters((game->entities).floaters);
					
					//Dibuja rana (titila)
					drawFrog(&(game->frog), (game->timeNow % 1000) < 300);

				}
			break;
			
			case GAME_OVER:
				option = (game->state).gameOver.selected;
				if(option == GAME_OVER_TITLE){
					drawMSG(msgs_arr[MSG_GAME_OVER]);
					if (showScore){
						showScore = 0;
						disp_update();
						usleep(500000); //pauso todo el programa por 1 seg
						drawScore(-1, game->score);
						disp_update();
						usleep(1000000); //pauso todo el programa por 1 seg
					}
				} else if(option == GAME_OVER_MENU){
					drawMSG(msgs_arr[MSG_GO_HOME]);
				} else if(option == GAME_OVER_EXIT){
					drawMSG(msgs_arr[MSG_EXIT]);
				} else {
					printf("Error");
				}
			break;

		case VICTORY:
			option = (game->state).victory.selected;
			if(option == VICTORY_TITLE){
				drawMSG(msgs_arr[MSG_YOU_WIN]);
				if (showScore){
					showScore = 0;
					disp_update();
					usleep(1000000); //pauso todo el programa por 1 seg
					drawScore(-1, game->score);
					disp_update();
					usleep(2000000); //pauso todo el programa por 1 seg
				}
			} else if(option == VICTORY_MENU){
				drawMSG(msgs_arr[MSG_GO_HOME]);
				showScore = 1;
			} else if(option == VICTORY_EXIT){
				drawMSG(msgs_arr[MSG_EXIT]);
			} else {
				printf("Error");
			}
			break;

		default:
			break;
	}

	disp_update();
}
