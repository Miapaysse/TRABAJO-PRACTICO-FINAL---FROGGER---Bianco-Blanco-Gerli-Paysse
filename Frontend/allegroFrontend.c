#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdbool.h> 
#include "frontend.h"   
#include "game.h"   
  

/*despues lo saco:
ALLEGRO_DISPLAY* al_create_display(int w, int h);
si hay error devuelve null
*/

void frontendInit(void) {
    // inicialización allegro
    if (al_init() == false) {
        fprintf(stderr, "Error: No se pudo inicializar Allegro.\n");
    }
    else {

    }
}