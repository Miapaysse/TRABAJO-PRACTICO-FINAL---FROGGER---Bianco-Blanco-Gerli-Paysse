#define ALLEGRO_NO_MAGIC_MAIN //sino se rompe todo 1
#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdbool.h> 
#include "frontend.h"   
#include "game.h"   
#include "levels.h"
  
//VAN EN EL .H O EN EL .C??
#define SCALE 120
#define MARGIN 100

//Variables locales
static ALLEGRO_EVENT_QUEUE *queue = NULL;
static ALLEGRO_DISPLAY* display;


//Prototipos funciones internas

void drawZones(Game * p2game);
void drawCars(Game * p2game);
void drawFloaters(Game * p2game);
void drawFrog(Game * p2game);


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
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    //void al_register_event_source(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT_SOURCE *source);
    //void al_register_event_source(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT_SOURCE *source);
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
}


//mal el if
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
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            al_destroy_event_queue(queue);
            al_destroy_display(display);
            return NONE; //OJO QUE NO EXISTE EN LA STRUCT ESTE CASO
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
    case PLAYING:
    drawZones(game);

    case GAME_OVER:
    case VICTORY:
    case POINTS:
    case EXIT:
    default:
        break;
   }
}

void frontendDestroy(void){

}

//Definiciones de funciones locales

void drawZone(Game * p2game){ //FALTA UN CASO DEFAULT?
    
    int i, y1, y2;
    int x1 = MARGIN;
    int x2 = MARGIN + MAP_WIDTH*SCALE;

    for (i=0 ; i<MAP_HEIGHT ; i++){

        y1 = i*SCALE;
        y2 = y1 + SCALE;

        switch (p2game->level.rows[i].zone){
            case ROAD:
            ALLEGRO_COLOR road_colour = al_map_rgb(45, 45, 48);
            al_draw_filled_rectangle(x1, y1, x2, y2, road_colour);
            break;

            case WATER:
            ALLEGRO_COLOR water_colour = al_map_rgb(0, 119, 190);
            al_draw_filled_rectangle(x1, y1, x2, y2, water_colour);
            break;

            case START:
            case SAFE:
            ALLEGRO_COLOR safe_colour = al_map_rgb(46, 139, 87);
            al_draw_filled_rectangle(x1, y1, x2, y2, safe_colour);
            break;

            default: break;

        }
    }

}

//en los png los vehículos apuntan para la izquierda
void drawVehicles( Game* p2game){

    int i, x, y;

    //Bucle generador de vehículos
    for (i=0 ; i<MAX_OBSTACLES ; i++){
        //si la entidad está activa
        if (p2game -> entities.obstacles[i].active){
            x = (p2game -> entities.obstacles[i].x)*SCALE + MARGIN;
            y = (p2game -> entities.obstacles[i].y)*SCALE;

            //if (p2game -> entities.obstacles[i].length == )
                //al_draw_bitmap(png_correspondiente, x, y, 0);

                // Mostramos los cambios en el monitor
                al_flip_display();

        }

    }

    //Bucle generador de flotadores
    for (i=0 ; i<MAX_FLOATERS ; i++){
        //si la entidad está activa
        if (p2game -> entities.floaters[i].active){
            x = (p2game -> entities.floaters[i].x)*SCALE + MARGIN;
            y = (p2game -> entities.floaters[i].y)*SCALE;

            if ((p2game -> entities.floaters[i].length) == 2){

                //al_draw_scaled_bitmap(car, 0, 0, ...);
                al_flip_display();
            }

        }

    }
}