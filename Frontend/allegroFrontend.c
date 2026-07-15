#define ALLEGRO_NO_MAGIC_MAIN //sino se rompe todo 1
#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdbool.h> 
#include "frontend.h"   
#include "game.h"   
  
//VAN EN EL .H O EN EL .C??
#define SCALE 120
#define MARGIN 100

//Variables locales
static ALLEGRO_EVENT_QUEUE *queue = NULL;
static ALLEGRO_DISPLAY* display;

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
        fprintf(stderr, "Error: No se pudo cargar el módulo de audio.\n");
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

    //bool al_get_next_event(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_EVENT *ret_event);
    if (al_get_next_event(queue, &event) == true){
        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:    return UP;   
                case ALLEGRO_KEY_DOWN:  return DOWN;
                case ALLEGRO_KEY_LEFT:  return LEFT;
                case ALLEGRO_KEY_RIGHT: return RIGHT;
                case ALLEGRO_KEY_ENTER: return SELECT;
            }
    }

    else {
        return NONE;
    }
}   

void frontendRender(Game * game){

    //pintamos todo el fondo de negro para borrar el fotograma anterior
    al_clear_to_color(al_map_rgb(0, 0, 0)); 

}