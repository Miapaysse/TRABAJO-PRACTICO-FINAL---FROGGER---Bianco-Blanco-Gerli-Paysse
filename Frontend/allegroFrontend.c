/***************************************************************************//**
  @file     +allegroFrontend.c+
  @brief    +Descripcion del archivo+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

 #define ALLEGRO_NO_MAGIC_MAIN //sino se rompe todo 1

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h> 
#include <allegro5/allegro_image.h>       // Para al_init_image_addon
#include <allegro5/allegro_audio.h>       // Para al_install_audio
#include <allegro5/allegro_primitives.h>

#include "frontend.h"   
#include "game.h"   
#include "levels.h"
  
//VAN EN EL .H O EN EL .C??
#define SCALE 120
#define MARGIN 100

//Variables locales
static ALLEGRO_EVENT_QUEUE *queue = NULL;
static ALLEGRO_DISPLAY* display;
static ALLEGRO_BITMAP* floater = NULL;
static ALLEGRO_BITMAP* car = NULL;
static ALLEGRO_BITMAP* truck = NULL;
static ALLEGRO_BITMAP* frog = NULL;
static ALLEGRO_BITMAP* game_over = NULL;
static ALLEGRO_BITMAP* victory = NULL;
static ALLEGRO_BITMAP* main_menu = NULL;
static ALLEGRO_BITMAP* pause = NULL;
static ALLEGRO_BITMAP* skull = NULL;
static ALLEGRO_BITMAP* trophy = NULL;


static ALLEGRO_FONT* very_big_font = NULL;
static ALLEGRO_FONT* big_font = NULL;
static ALLEGRO_FONT* medium_font = NULL;
static ALLEGRO_FONT* small_font = NULL;


//Prototipos funciones internas

static void drawZones(Game * p2game);
static void drawObstacles(Game * p2game);
static void drawFrog(Game * p2game);
static void loadFiles (void);
static void drawMainMenu (Game* p2game);
static void drawGameOver (Game* p2game);
static void drawPaused (Game* p2game);
static void drawVictory(Game* p2game);
static void drawScores (Game* p2game);


void frontendInit(void) {
    // inicialización allegro
    if (al_init() == false) {
        fprintf(stderr, "Error: No se pudo inicializar Allegro.\n");
    }
    //sino se rompe todo 2
    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL);

    display = al_create_display(MAP_WIDTH*SCALE + 2*MARGIN, MAP_HEIGHT*SCALE);

    //MANEJO ERRORES
    if (display == NULL) {
        fprintf(stderr, "Error: No se pudo crear el display.\n");
    }

    if (al_install_keyboard() == false){
        fprintf(stderr, "Error: no se pudo inicializar el teclado.");
    }

    if (al_init_image_addon() == false) {
        fprintf(stderr, "Error: No se pudo cargar el módulo de imágenes.\n");
    }

    if (al_install_audio() == false) {
        fprintf(stderr, "Error: No se pudo cargar el módulo de audio.\n");
    }
    
    //MAL MENSAJE
    if (al_init_font_addon() == false) {
        fprintf(stderr, "Error: No se pudo cargar el addon.\n");
    }

    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_primitives_addon();

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    //cargamos archivos
    loadFiles();
}



Input frontendGetInput(void){
    ALLEGRO_EVENT event;
    
    if (al_get_next_event(queue, &event) == true){
        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:    return UP;   
                case ALLEGRO_KEY_DOWN:  return DOWN;
                case ALLEGRO_KEY_LEFT:  return LEFT;
                case ALLEGRO_KEY_RIGHT: return RIGHT;
                case ALLEGRO_KEY_ENTER: return SELECT;
                default: return NONE;
            }
        }
        /*else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            al_destroy_event_queue(queue);
            al_destroy_display(display);
            return ...; //OJO QUE NO EXISTE EN LA STRUCT ESTE CASO
        } */
       else {
        return NONE;
       }
    }

    else {
        return NONE;
    }
}
  

void frontendRender(Game * game){

    //pintamos todo el fondo de negro para borrar el fotograma anterior
   al_clear_to_color(al_map_rgb(0, 0, 0)); 

   int game_state = (game -> state.id);

   switch (game_state){
    case MENU:
    drawMainMenu(game);
    break;

    case PLAYING:
    drawZones(game);
    drawObstacles(game);
    drawFrog(game);
    break;

    case GAME_OVER:
    drawGameOver(game);
    break;

    case VICTORY:
    drawVictory(game);
    break;

    case POINTS:
    //drawScores(game);
    break;

    case PAUSED:
    drawPaused(game);
    break;

    case EXIT:
    frontendDestroy();
    break;

    default:
    break;
   }

   al_flip_display();
}


void frontendDestroy(void){

    if (car) al_destroy_bitmap(car);
    if (truck) al_destroy_bitmap(truck);
    if (trophy) al_destroy_bitmap(trophy);
    if (skull) al_destroy_bitmap(skull);
    if (frog) al_destroy_bitmap(frog);
    if (floater) al_destroy_bitmap(floater);
    if (pause) al_destroy_bitmap(pause);

    
    if (very_big_font) al_destroy_font(very_big_font);
    if (medium_font) al_destroy_font(medium_font);
    if (big_font) al_destroy_font(big_font);
    if (small_font) al_destroy_font(small_font);

    if (queue) al_destroy_event_queue(queue);
    if (display) al_destroy_display(display);
}


//Definiciones de funciones locales

static void drawZones(Game * p2game){ //FALTA UN CASO DEFAULT?
    
    int i, y1, y2;
    int x1 = MARGIN;
    int x2 = MARGIN + MAP_WIDTH*SCALE;
    ALLEGRO_COLOR road_colour = al_map_rgb(45, 45, 48);
    ALLEGRO_COLOR water_colour = al_map_rgb(0, 119, 190);
    ALLEGRO_COLOR safe_colour = al_map_rgb(46, 139, 87);

    for (i=0 ; i<MAP_HEIGHT ; i++){

        y1 = i*SCALE;
        y2 = y1 + SCALE;

        switch (p2game->level.rows[i].zone){
            case ROAD:
            al_draw_filled_rectangle(x1, y1, x2, y2, road_colour);
            break;

            case WATER:
            al_draw_filled_rectangle(x1, y1, x2, y2, water_colour);
            break;

            case START:
            case SAFE:
            al_draw_filled_rectangle(x1, y1, x2, y2, safe_colour);
            break;

            default: break;

        }
    }

}


static void drawObstacles( Game* p2game){

    int i, x, y, new_lenght, new_height;
    int flag_direction = 0; //flag para rotar el dibujo

    //Bucle generador de vehículos
    for (i=0 ; i<MAX_OBSTACLES ; i++){
        //si la entidad está activa
        if (p2game -> entities.obstacles[i].active){
            x = (p2game -> entities.obstacles[i].x)*SCALE + MARGIN;
            y = (p2game -> entities.obstacles[i].y)*SCALE;

            //en los png los vehículos apuntan para la izquierda
            if ((p2game -> entities.obstacles[i].direction) == DIR_LEFT){
                flag_direction = 0;
            }
            else {
                flag_direction = ALLEGRO_FLIP_HORIZONTAL;
            }

            if (p2game -> entities.obstacles[i].length == CAR_LENGTH){
                al_draw_bitmap(car, x, y, flag_direction);
            }
            else { //es camión
                al_draw_bitmap(truck, x, y, flag_direction);
            }
        }

    }

    //Bucle generador de flotadores
    for (i=0 ; i<MAX_FLOATERS ; i++){
        //si la entidad está activa
        if (p2game -> entities.floaters[i].active){
            x = (p2game -> entities.floaters[i].x)*SCALE + MARGIN;
            y = (p2game -> entities.floaters[i].y)*SCALE;
            new_lenght = (p2game -> entities.floaters[i].length)*SCALE;
            new_height = SCALE;
          
            //Dibujamos el tronco con el largo correspondiente
            al_draw_scaled_bitmap(floater, 0, 0, al_get_bitmap_width(floater),
                al_get_bitmap_height(floater), x, y, new_lenght, new_height, 0);
        }

    }
}


static void drawFrog(Game * p2game){
    int x = (p2game -> frog.x)*SCALE + MARGIN;
    int y = (p2game -> frog.y)*SCALE;
    al_draw_bitmap (frog, x, y, 0);
}


static void loadFiles (void){
    floater = al_load_bitmap("floater.png");
    car = al_load_bitmap("car.png");
    truck = al_load_bitmap("truck.png");
    frog = al_load_bitmap("frog.png");
    skull = al_load_bitmap("skull.png");
    trophy = al_load_bitmap("trophy.png");
    pause =al_load_bitmap("pause.png");

    very_big_font = al_load_ttf_font("Tiny5-Regular.ttf", 200, 0);
    big_font = al_load_ttf_font("Tiny5-Regular.ttf", 110, 0);
    medium_font = al_load_ttf_font("Tiny5-Regular.ttf", 60, 0);
    small_font = al_load_ttf_font("Tiny5-Regular.ttf", 40, 0);
}


static void drawMainMenu (Game* p2game){

    int spacing1 = 140;
    int spacing2 = 100;
    int y_menu = 430;
    int y_option1 = y_menu + spacing1;
    int x_menu;
    int x_center =MARGIN + (SCALE*MAP_WIDTH)/2; //el medio de la pantalla

    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR green = al_map_rgb(86, 176, 0);
    ALLEGRO_COLOR color;

    int option_selected = (p2game -> state.menu.selected);

    int title_width = al_get_text_width(very_big_font, "FROGGER");

    x_menu = x_center - title_width/2;

    al_draw_text(very_big_font, white, x_center, 150, ALLEGRO_ALIGN_CENTER, "FROGGER");

    color = (option_selected == MENU_TITLE)? green : white;
    al_draw_text(big_font, color, x_menu, y_menu, ALLEGRO_ALIGN_LEFT, "MENU");

    color = (option_selected == MENU_PLAY)? green : white;
    al_draw_text(medium_font, color, x_menu, y_option1, ALLEGRO_ALIGN_LEFT, "Play");

    color = (option_selected == MENU_POINTS)? green : white;
    al_draw_text(medium_font, color, x_menu, y_option1 + spacing2, ALLEGRO_ALIGN_LEFT, "Best scores");

    color = (option_selected == MENU_EXIT)? green : white;
    al_draw_text(medium_font, color, x_menu, y_option1 + 2*spacing2, ALLEGRO_ALIGN_LEFT, "Exit");
}


static void drawGameOver (Game* p2game){
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR green = al_map_rgb(86, 176, 0);
    ALLEGRO_COLOR color;

    int option_selected = (p2game -> state.gameOver.selected);
    int spacing1 = 250;
    int spacing2 = 100;
    int y_title = 400;
    int y_options = y_title + spacing1;
    int x_options;
    int x_center =MARGIN + (SCALE*MAP_WIDTH)/2; //el medio de la pantalla
    int y_skull = y_title/2;

    int title_width = al_get_text_width(very_big_font, "GAME OVER");
    int skull_width = al_get_bitmap_width(skull);
    x_options = x_center - title_width/2;

    al_draw_bitmap(skull, x_center- skull_width/2, y_skull, 0);

    al_draw_text(very_big_font, white, x_center, y_title, ALLEGRO_ALIGN_CENTER, "GAME OVER");

    color = (option_selected == GAME_OVER_MENU)? green : white;
    al_draw_text(medium_font, color, x_options, y_options, ALLEGRO_ALIGN_LEFT, "Back to menu");

    color = (option_selected == GAME_OVER_EXIT)? green : white;
    al_draw_text(medium_font, color, x_options, y_options + spacing2, ALLEGRO_ALIGN_LEFT, "Exit");
}


static void drawVictory(Game* p2game){
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR green = al_map_rgb(86, 176, 0);
    ALLEGRO_COLOR color;

    int option_selected = (p2game -> state.victory.selected);
    int spacing1 = 250;
    int spacing2 = 100;
    int y_title = 400;
    int y_options = y_title + spacing1;
    int x_options;
    int x_center =MARGIN + (SCALE*MAP_WIDTH)/2; //el medio de la pantalla
    int y_trophy = y_title/2;

    int title_width = al_get_text_width(very_big_font, "YOU WIN");
    int trophy_width = al_get_bitmap_width(trophy);
    x_options = x_center - title_width/2;

    al_draw_bitmap(trophy, x_center- trophy_width/2, y_trophy, 0);

    al_draw_text(very_big_font, white, x_center, y_title, ALLEGRO_ALIGN_CENTER, "YOU WIN");

    color = (option_selected == VICTORY_MENU)? green : white;
    al_draw_text(medium_font, color, x_options, y_options, ALLEGRO_ALIGN_LEFT, "Back to menu");

    color = (option_selected == VICTORY_EXIT)? green : white;
    al_draw_text(medium_font, color, x_options, y_options + spacing2, ALLEGRO_ALIGN_LEFT, "Exit");
}


static void drawPaused (Game* p2game){
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR green = al_map_rgb(86, 176, 0);
    ALLEGRO_COLOR color;

    int option_selected = (p2game -> state.paused.selected);
    int spacing1 = 180;
    int spacing2 = 100;
    int y_title = 400;
    int y_options = y_title + spacing1;
    int x_options;
    int x_center =MARGIN + (SCALE*MAP_WIDTH)/2; //el medio de la pantalla
    int y_image = y_title/3;

    int title_width = al_get_text_width(big_font, "GAME PAUSED");
    int image_width = al_get_bitmap_width(pause);
    x_options = x_center - title_width/2;

    al_draw_bitmap(pause, x_center- image_width/2, y_image, 0);

    al_draw_text(big_font, white, x_center, y_title, ALLEGRO_ALIGN_CENTER, "GAME PAUSED");

    color = (option_selected == PAUSED_MENU)? green : white;
    al_draw_text(medium_font, color, x_options, y_options, ALLEGRO_ALIGN_LEFT, "Back to menu");

    color = (option_selected == PAUSED_PLAY)? green : white;
    al_draw_text(medium_font, color, x_options, y_options + spacing2, ALLEGRO_ALIGN_LEFT, "Continue");

    color = (option_selected == PAUSED_EXIT)? green : white;
    al_draw_text(medium_font, color, x_options, y_options + 2*spacing2, ALLEGRO_ALIGN_LEFT, "Exit");
}

//INCOMPLETA LA PARTE DE OBTENER LOS PUNTAJES Y LAS COORDENADAS
/*static void drawScores(Game* p2game){
    char* scores[10];

    //agregamos el #1, 2 3,... antes del score

    //OJO DEFINICION DE X E Y PROVISORIA
    int i, x= 1, y =1;
    int option_selected = (p2game -> state.points.selected);
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR green = al_map_rgb(86, 176, 0);
    ALLEGRO_COLOR color = white;

    al_draw_text(big_font, white, x, y, ALLEGRO_ALIGN_CENTER, "TOP 10");

    for (i=0 ; i<10 ; i++){
        int x;
        int y;
        al_draw_text(medium_font, color, x, y, ALLEGRO_ALIGN_LEFT, scores[i]);
    }

    color = (option_selected == POINTS_MENU)? green : white;
    al_draw_text(medium_font, color, x, y, ALLEGRO_ALIGN_LEFT, "Back to menu");

    color = (option_selected == POINTS_EXIT)? green : white;
    al_draw_text(medium_font, color, x, y, ALLEGRO_ALIGN_LEFT, "Exit");

}*/
