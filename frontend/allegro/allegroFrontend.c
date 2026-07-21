/*
  @file     +allegroFrontend.c+
  @author   +Bianco-Blanco-Gerli-Paysse+
*/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h> 
#include <allegro5/allegro_image.h>   
#include <allegro5/allegro_primitives.h>

#include "allegroFrontend.h"   
#include "game.h"
#include "entities.h"
#include "config.h"
#include "allegroFrontendInternal.h"
#include "errors.h"


/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/

static ALLEGRO_EVENT_QUEUE *queue = NULL;
static ALLEGRO_DISPLAY *display;

ALLEGRO_BITMAP* floater_trunk = NULL;
ALLEGRO_BITMAP* car = NULL;
ALLEGRO_BITMAP* truck = NULL;
ALLEGRO_BITMAP* frog = NULL;
ALLEGRO_BITMAP* pause_img = NULL;
ALLEGRO_BITMAP* skull = NULL;
ALLEGRO_BITMAP* trophy = NULL;
ALLEGRO_BITMAP* heart = NULL;
ALLEGRO_BITMAP* safe_box = NULL;
ALLEGRO_BITMAP* floater_leaf = NULL;
 
ALLEGRO_FONT* very_big_font = NULL;
ALLEGRO_FONT* big_font = NULL;
ALLEGRO_FONT* medium_font = NULL;
ALLEGRO_FONT* small_font = NULL;
 
ALLEGRO_COLOR white;
ALLEGRO_COLOR pink;
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

 static int loadFiles(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int frontendInit(void) {

    //Inicializa el núcleo de Allegro y todos los subsistemas necesarios para el juego. 
    if (al_init() == false) {
        return ERR_ALLEGRO_INIT_FAILED;
    }
    //Inicializa
    if (al_install_keyboard() == false) {
        return ERR_KEYBOARD_INIT_FAILED;
    }

    if (al_init_image_addon() == false) {
        return ERR_IMAGE_ADDON_FAILED;
    }

    if (al_init_primitives_addon() == false) {
        return ERR_PRIMITIVES_ADDON_FAILED;
    }

    if (al_init_font_addon() == false) {
        return ERR_FONT_ADDON_FAILED;
    }

    //Creamos ventana del juego
    al_set_new_display_flags(ALLEGRO_WINDOWED);

    display = al_create_display(MAP_WIDTH*SCALE, (MAP_HEIGHT+1)*SCALE);
    if(display == NULL) {
        return ERR_DISPLAY_INIT_FAILED;
    }

    if (al_init_ttf_addon() == false) {
        return ERR_FONT_ADDON_FAILED;
    }

    //Creamos la cola de eventos para manejar el teclado y la ventana
    queue = al_create_event_queue();
    if(queue == NULL) {
        return ERR_EVENT_QUEUE_FAILED;
    }

    // Registramos teclado y eventos de la ventana en la cola
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    //Inicializa los colores globales del frontend
    white = al_map_rgb(255, 255, 255);
    pink = al_map_rgb(255, 105, 180);

    // Cargamos archivos
    int files_loaded = loadFiles();
    if (files_loaded == -1) {
        return ERR_FILE_LOAD_FAILED;
    }
}

/**
 * @brief Inicializa todo el entorno gráfico, periféricos y recursos de Allegro.
 * @return 
 */


Input_t frontendGetInput(void){
    ALLEGRO_EVENT event;
    
    if (al_get_next_event(queue, &event) == true){
        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:    return UP;   
                case ALLEGRO_KEY_DOWN:  return DOWN;
                case ALLEGRO_KEY_LEFT:  return LEFT;
                case ALLEGRO_KEY_RIGHT: return RIGHT;
                case ALLEGRO_KEY_ENTER: return SELECT;
                //case ALLEGRO_EVENT_DISPLAY_CLOSE: return EXIT;
                default: return NONE;
            }
        }
       else {
        return NONE;
       }
    }

    else {
        return NONE;
    }
}
  

void frontendRender(Game_t * game){

    //pintamos todo el fondo de negro para borrar el fotograma anterior
   al_clear_to_color(al_map_rgb(0, 0, 0));

   int game_state = (game -> state.id);
   //int game_state = PAUSED;

   switch (game_state){
    case MENU:
    drawMainMenu(game);
    break;

    case PLAYING:
    drawZones(game);
    drawEntities(game);
    drawFrog(game);
    drawScore(game);
    drawLevel(game);
    drawLives(game);
    drawFinishBoxes(game);
    cloneFrog(game);
    break;

    case GAME_OVER:
    drawGameOver(game);
    break;

    case VICTORY:
    drawVictory(game);
    break;

    case POINTS:
    drawTop10(game);
    break;

    case PAUSED:
    drawPaused(game);
    break;

    case EXIT:
    break;

    default:
    break;
   }

   al_flip_display();
}
 

void frontendDestroy(void){

    //Liberamos memoria al finalizar el programa
    if (car) al_destroy_bitmap(car);
    if (truck) al_destroy_bitmap(truck);
    if (trophy) al_destroy_bitmap(trophy);
    if (skull) al_destroy_bitmap(skull);
    if (frog) al_destroy_bitmap(frog);
    if (floater_trunk) al_destroy_bitmap(floater_trunk);
    if (pause_img) al_destroy_bitmap(pause_img);
    if (heart) al_destroy_bitmap(heart);
    if (safe_box) al_destroy_bitmap(safe_box);
    if (floater_leaf) al_destroy_bitmap(floater_leaf);

    if (very_big_font) al_destroy_font(very_big_font);
    if (medium_font) al_destroy_font(medium_font);
    if (big_font) al_destroy_font(big_font);
    if (small_font) al_destroy_font(small_font);

    
    if (queue) al_destroy_event_queue(queue);
    if (display) al_destroy_display(display);
}

void frontManageError(ErrorCode_t err){
    //si el error es de inicializacion de allegro o de carga de fuentes, no se 
    //puede mostrar el mensaje en pantalla, por lo que se imprime en consola
    if (err == ERR_ALLEGRO_INIT_FAILED || err == ERR_FONT_ADDON_FAILED ||  err == ERR_INIT_TTF_FAILED
         || err == ERR_DISPLAY_INIT_FAILED || err == ERR_LOAD_FONTS_FAILED){
        printf("Unable to load resources to show display\n");
        return;
    }
    else {
        al_draw_text(medium_font, al_map_rgb(255, 0, 0), MAP_WIDTH*SCALE/2, (MAP_HEIGHT+1)*SCALE/2, ALLEGRO_ALIGN_CENTRE, errorMessage(err));
        return;
    }
}


 /*******************************************************************************
  *******************************************************************************
                         LOCAL FUNCTION DEFINITIONS
  *******************************************************************************
  ******************************************************************************/


static int loadFiles (void){
    floater_trunk = al_load_bitmap(ALLEGRO_DIR"floater_trunk.png");
    car = al_load_bitmap(ALLEGRO_DIR"car.png");
    truck = al_load_bitmap(ALLEGRO_DIR"truck.png");
    frog = al_load_bitmap(ALLEGRO_DIR"frog.png");
    skull = al_load_bitmap(ALLEGRO_DIR"skull.png");
    trophy = al_load_bitmap(ALLEGRO_DIR"trophy.png");
    pause_img =al_load_bitmap(ALLEGRO_DIR"pause.png");
    heart = al_load_bitmap(ALLEGRO_DIR"heart.png");
    safe_box = al_load_bitmap(ALLEGRO_DIR"safe_box.png");
    floater_leaf = al_load_bitmap(ALLEGRO_DIR"floater_leaf.png");

    very_big_font = al_load_ttf_font(ALLEGRO_DIR"Tiny5-Regular.ttf", 200, 0);
    big_font = al_load_ttf_font(ALLEGRO_DIR"Tiny5-Regular.ttf", 110, 0);
    medium_font = al_load_ttf_font(ALLEGRO_DIR"Tiny5-Regular.ttf", 60, 0);
    small_font = al_load_ttf_font(ALLEGRO_DIR"Tiny5-Regular.ttf", 40, 0);
    
    if (!floater_trunk || !car || !truck || !frog || !skull || !trophy || !pause_img ||
        !heart || !safe_box || !floater_leaf) {
        return -1;
    }
    else if (!very_big_font || !big_font || !medium_font || !small_font) {
        return -2;
    }
    else {
        return 0;
    }
}

/**
 * @brief Carga todos los archivos necesarios para el juego
 * @return 0 si se cargaron correctamente, -1 si hubo un error de carga de imágenes, -2
 * si hubo un error de carga de fuentes
 */

