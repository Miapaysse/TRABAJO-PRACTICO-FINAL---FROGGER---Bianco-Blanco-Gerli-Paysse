#include <stdio.h>
#include <stdint.h>
#include "unistd.h"
#include "disdrv.h"
#include "joydrv.h"

#include "config.h"
#include "game.h"
#include "entities.h"
#include "levels.h"
#include "top10.h"
#include "raspiFrontend.h"
#include "raspiDraw.h"

joyinfo_t joy;
//static int scores[10]; 
static Input ultimo_input = NONE;
int lastLive, showPlayer;
LevelId lastLevel;

void frontendInit(void) {
    joy_init();
    disp_init();
    disp_clear();
    disp_update();
	showPlayer = 1;
	lastLive = MAX_LIVES;
	lastLevel = LEVEL_1;
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
			showPlayer = 1;
			// si estas en menu signica que volviste a empezar el juego, por lo tanto se resetea el showPlayer
			lastLive = MAX_LIVES;

			option = (game->state).menu.selected;
			if(option == MENU_TITLE){
				drawMSG(msgsDisp[MSG_HOME]);
			} else if(option == MENU_PLAY){
				drawMSG(msgsDisp[MSG_PLAY]);
			} else if(option == MENU_POINTS){
				drawMSG(msgsDisp[MSG_GO_TOP_10]);
			} else if(option == MENU_EXIT){
				drawMSG(msgsDisp[MSG_EXIT]);
			} else {
				printf("Error en Menu");
			}
			break;

		case POINTS:
			option = (game->state).points.selected;			
            switch (option) {	
				case POINTS_TITLE:
				    drawMSG(msgsDisp[MSG_TOP_10]);
				break;
				
				case POINT_1: case POINT_2: case POINT_3: case POINT_4: case POINT_5:
				case POINT_6: case POINT_7: case POINT_8: case POINT_9: case POINT_10:
				    drawScore(option-POINT_1, (game->top10.topScores)[option-POINT_1]);
				break;
				
				case POINTS_MENU:
					drawMSG(msgsDisp[MSG_GO_HOME]);
				break;
				
				case POINTS_EXIT:
				    drawMSG(msgsDisp[MSG_EXIT]);
				break;
            }
			break;

		case PAUSED:
			option = (game->state).paused.selected;
			if(option == PAUSED_TITLE){
				drawMSG(msgsDisp[MSG_PAUSE]);
			} else if(option == PAUSED_MENU){
				drawMSG(msgsDisp[MSG_GO_HOME]);
			} else if(option == PAUSED_PLAY){
				drawMSG(msgsDisp[MSG_DESPAUSE]);
			} else if(option == PAUSED_EXIT){
				drawMSG(msgsDisp[MSG_EXIT]);
			} else {
				printf("Error");
			}
		break;
		
		case PLAYING:
			option = (game->state).id;
			if(option == PAUSED){
				drawMSG(msgsDisp[MSG_PAUSE]);
			} else {
				if (game->lives != lastLive) {
					lastLive = game->lives;
					drawMSG(msgsDisp[LIVE_LOSED]);
					disp_update();
					usleep(1000000); //pauso todo el programa por 1 seg
				}

				if (game->level.id != lastLevel) {
					lastLevel = game->level.id;
					drawMSG(msgsDisp[NEXT_LEVEL]);
					disp_update();
					usleep(1500000);
				}
				// Dibuja zonas
				drawZone((game->level).rows);
				drawBoxes (game->level.finishBoxes, game->timeNow % (TIME_BLINK_BOX*2) < TIME_BLINK_BOX? D_ON : D_OFF);

				//Dibuja obstaculos y floaters
				drawObstacles((game->entities).obstacles);
				drawFloaters((game->entities).floaters);
				
				//Dibuja rana (titila)
				drawFrog(&(game->frog), game->timeNow % (TIME_BLINK_FROG*2) < TIME_BLINK_FROG? D_ON : D_OFF);

			}
		break;
		
		case GAME_OVER:
			option = (game->state).gameOver.selected;
			if(option == GAME_OVER_TITLE){
				drawMSG(msgsDisp[MSG_GAME_OVER]);
				if (showPlayer){
					showPlayer = 0;
					disp_update();
					usleep(DISPLAY_MENU_TIME);
					
					showRank(game->top10.status);
					
					showScore(game->score);
				}
			} else if(option == GAME_OVER_MENU){
				drawMSG(msgsDisp[MSG_GO_HOME]);
			} else if(option == GAME_OVER_EXIT){
				drawMSG(msgsDisp[MSG_EXIT]);
			} else {
				printf("Error");
			}
		break;

		case VICTORY:
			option = (game->state).victory.selected;
			if(option == VICTORY_TITLE){
				drawMSG(msgsDisp[MSG_YOU_WIN]);
				if (showPlayer){
					showPlayer = 0;
					disp_update();
					usleep(DISPLAY_MENU_TIME); 
					
					showRank(game->top10.status);
					
					showScore(game->score);
				}
			} else if(option == VICTORY_MENU){
				drawMSG(msgsDisp[MSG_GO_HOME]);
			} else if(option == VICTORY_EXIT){
				drawMSG(msgsDisp[MSG_EXIT]);
			} else {
				printf("Error");
			}
			break;

		default:
			break;
	}

	disp_update();
}

