/***************************************************************************//**
  @file     raspiFrontend.c
  @brief    Implementacion del loop de renderizado e inputs de hardware
  @author   Bianco-Blanco-Gerli-Paysse
 ******************************************************************************/

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
static Input_t ultimo_input = NONE; // Evita que se disparen comandos seguidos al mantener apretado
static uint8_t showPlayer = 1;      // Controla que las pantallas finales se muestren una sola vez
static uint8_t lastLive = MAX_LIVES;   // Cache para chequear si bajaron las vidas
static LevelId_t lastLevel = LEVEL_1; // Cache para chequear si cambio el nivel

int frontendInit(void) { // Arranca perifericos y resetea las banderas del frontend
    joy_init();
    disp_init();
    disp_clear();
    disp_update();

	showPlayer = 1;
	lastLive = MAX_LIVES;
	lastLevel = LEVEL_1;
	return 0;
}

void frontendDestroy(void) { // Apaga la pantalla al cerrar
    disp_clear();
    disp_update();
}

Input_t frontendGetInput(void) { // Lee el joystick y bloquea rebotes
    Input_t input_actual = NONE;
    joy = joy_read();

    if (joy.sw == J_PRESS) {
        input_actual = SELECT;
    } else if (joy.y > JOY_LIM && joy.x < JOY_LIM && joy.x > -JOY_LIM) { 
        input_actual = UP;
    } else if (joy.y < -JOY_LIM && joy.x < JOY_LIM && joy.x > -JOY_LIM) { 
        input_actual = DOWN;
    } else if (joy.x > JOY_LIM && joy.y < JOY_LIM && joy.y > -JOY_LIM) { 
        input_actual = RIGHT;
    } else if (joy.x < -JOY_LIM && joy.y < JOY_LIM && joy.y > -JOY_LIM) { 
        input_actual = LEFT;
    } else {
        input_actual = NONE;
    }

    if (input_actual != ultimo_input) { // Obliga a soltar el joystick para marcar otro movimiento
        ultimo_input = input_actual;
        return input_actual;
    } else {
        return NONE; 
    }
}

void frontendRender(Game_t * game) { // Escanea el estado del backend y decide que dibujar
    int option = 0;
	disp_clear();

	switch((game->state).id) {
		case MENU: // Resetea variables locales y dibuja items del menu principal
			showPlayer = 1;
			lastLive = MAX_LIVES;
			lastLevel = LEVEL_1;

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

		case POINTS: // Dibuja la lista de puntuaciones records obtenidas del backend
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

		case PAUSED: // Pantalla fija de pausa
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
		
		case PLAYING: // Dibuja la accion del juego en tiempo real
			option = (game->state).id;
			if(option == PAUSED){
				drawMSG(msgsDisp[MSG_PAUSE]);
			} else {
				showLives(game->lives, &lastLive); // Chequea muerte
				showLevelNextLevel(game->level.id, &lastLevel); // Chequea cambio de nivel
				
				drawZone((game->level).rows); // Dibuja terreno base
				drawBoxes (game->level.finishBoxes, game->timeNow % (TIME_BLINK_BOX*2) < TIME_BLINK_BOX? D_ON : D_OFF); // Nidos

				drawObstacles((game->entities).obstacles); // Dibuja autos
				drawFloaters((game->entities).floaters); // Dibuja troncos
				
				drawFrog(&(game->frog), game->timeNow % (TIME_BLINK_FROG*2) < TIME_BLINK_FROG? D_ON : D_OFF); // Dibuja la rana
			}
		break;
		
		case GAME_OVER: // Secuencia final si perdiste todas las vidas
			option = (game->state).gameOver.selected;
			if(option == GAME_OVER_TITLE){
				drawMSG(msgsDisp[MSG_GAME_OVER]);
				if (showPlayer){
					showPlayer = 0;
					disp_update();
					usleep(DISPLAY_DEFAULT_TIME);
					
					showRank(game->top10.status); // Te avisa si entraste al ranking leaderboard
					
					showScore(game->score); // Muestra tus puntos logrados
				}
			} else if(option == GAME_OVER_MENU){
				drawMSG(msgsDisp[MSG_GO_HOME]);
			} else if(option == GAME_OVER_EXIT){
				drawMSG(msgsDisp[MSG_EXIT]);
			} else {
				printf("Error");
			}
		break;

		case VICTORY: // Secuencia final si completaste exitosamente el juego
			option = (game->state).victory.selected;
			if(option == VICTORY_TITLE){
				drawMSG(msgsDisp[MSG_YOU_WIN]);
				if (showPlayer){
					showPlayer = 0;
					disp_update();
					usleep(DISPLAY_DEFAULT_TIME);
					
					showRank(game->top10.status); // Chequea si entraste a la tabla de records
					
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
	
	disp_update(); // Dibuja el buffer completo definitivo
}

void frontManageError(ErrorCode_t err){ // Despliega cartel con "?" si explota algo internamente
	drawMSG(msgsDisp[MSG_ERROR]);
	disp_update();
	usleep(2000000);
}