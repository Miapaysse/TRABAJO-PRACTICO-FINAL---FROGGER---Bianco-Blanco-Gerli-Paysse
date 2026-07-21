/***************************************************************************//**
  @file     +game.c+
  @brief    +funciones del juego+
  @author   +Bianco-Blanco-Gerli-Paysse+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "game.h"
#include "interactions.h"
#include "top10.h"

/*******************************************************************************
 * CONSTANTS, MACROS, ENUMERATIONS, STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void processInputPlaying(GameState_t * state, Input_t input, Frog_t * frog);
static void processInputPaused(Game_t * game, Input_t input);
static void processInputGameOver(Game_t * game, Input_t input);
static void processInputVictory(Game_t * game, Input_t input);
static void processInputPoints(Game_t * game, Input_t input);
static int processInputMenu(Game_t * game, Input_t input);
static int checkTop10Status(Top10Status_t status);

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static const int temperaturas_medias[4] = {23, 26, 24, 29};+


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

// +ej: static int temperaturas_actuales[4];+


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


int updateGame(Game_t * game, Input_t input){
    game->timeNow = clock();
    switch ((game->state).id){
        case MENU: 
            TRY(processInputMenu(game, input));
        break;
        case PLAYING:
            processInputPlaying(&(game->state),input, &(game->frog));

            TRY(updateEntities(game));

            TRY(manageInteractions(game));

            TRY(checkLevel(game));

            //Si estaba jugando y gano o perdio
            if (game->state.id == GAME_OVER || game->state.id == VICTORY) {
                game->top10.status = getTop10Status(game->top10.topScores, game->score);
                checkTop10Status(game->top10.status);
            }
            
        break;
        case PAUSED:
            processInputPaused(game, input);
        break;
        case VICTORY:
            resetFrog(&(game->frog));
            processInputVictory(game, input);
        break;
        case GAME_OVER:
            resetFrog(&(game->frog));
            processInputGameOver(game, input);
        break;
        case POINTS:
            processInputPoints(game, input);
        break;

        case EXIT:
            //no hace nada, main lo lee y termina programa
        break;
    }
    return 0;
 }

 int gameInit(Game_t* game){
    if(game != NULL){
        game->timeNow = clock();
        
        initLevel(game);
        initFrog(&(game->frog));

        game->score=MIN_SCORE;

        game->lives=MAX_LIVES;
        game->lastEntityUpdate = clock();
        
        // Al iniciar solo cargamos el ranking existente; no guardamos un puntaje 0.
        game->top10.status = loadTop10(game->top10.topScores);
        checkTop10Status(game->top10.status);

        game->state.id = MENU;
        game->state.menu.selected = MENU_TITLE;
        game->state.menu.optionCount = MENU_COUNT;

        game->state.menu = (MenuState_t){ MENU_TITLE, MENU_COUNT };
        game->state.paused = (MenuState_t){ PAUSED_TITLE, PAUSED_COUNT };
        game->state.gameOver = (MenuState_t){ GAME_OVER_TITLE, GAME_OVER_COUNT };
        game->state.victory = (MenuState_t){ VICTORY_TITLE, VICTORY_COUNT };
        game->state.points = (MenuState_t){ POINTS_TITLE, POINTS_COUNT };

        return 0;
    }
    else{
        return ERR_INVALID_GAME_POINTER;
    }
}

///////////////////////////////////////////MENUS///////////////
static void menuPrevious(MenuState_t *menu){
    if(menu->selected == 0)
        menu->selected = menu->optionCount - 1;
    else
        menu->selected--;
}

static void menuNext(MenuState_t *menu){
    menu->selected++;

    if(menu->selected >= menu->optionCount)
        menu->selected = 0;
}

/////////////////////////////////////////////////////////////////MENU
static int processInputMenu(Game_t * game, Input_t input){ //aca se procesa el input del menu y se cambia el estado del juego segun corresponda
    MenuState_t *menu = &game->state.menu;
    switch(input){
        case SELECT:
            switch(menu->selected){
                case MENU_PLAY: //aca se inicializa el juego y se cambia el estado a PLAYING
                    gameInit(game);
                    game->state.id = PLAYING;
                break;
                case MENU_POINTS: //aca se carga el top10 y se cambia el estado a POINTS
                    game->top10.status = loadTop10(game->top10.topScores);
                    checkTop10Status(game->top10.status);
                    game->state.id = POINTS;
                break;
                case MENU_EXIT:
                    game->state.id = EXIT;
                break;
                default:
                break;
            }
            menu->selected = MENU_TITLE;
        break;
        case UP:
            menuPrevious(menu);
        break;
        case DOWN:
            menuNext(menu);
        break;
        case NONE: case RIGHT: case LEFT: default:
        break;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////PAUSED
void processInputPaused(Game_t *game, Input_t input){
    switch(input){
        case SELECT:
            switch ( (game->state.paused).selected ){
                case PAUSED_MENU: 
                    game->state.id = MENU;
                break;
                case PAUSED_PLAY:
                    game->state.id = PLAYING; //////////////ANALIZAR TEMA VIDAS REPLAY
                break;
                case PAUSED_EXIT:
                    game->state.id = EXIT;
                break;
            }
            (game->state.paused).selected = PAUSED_TITLE; //resteo menu
        break;
        case UP:
            menuPrevious(&(game->state.paused));
        break;

        case DOWN:
            menuNext(&(game->state.paused));
        break;

        case NONE: case RIGHT: case LEFT: default:
            //se queda en el mismo menu, no hace nada
            break;
    }
}

///////////////////////////////////////////////////////////GAME OVER
void processInputGameOver(Game_t *game, Input_t input){
        switch(input){
            case SELECT:
                switch ( game->state.gameOver.selected ){
                    case GAME_OVER_MENU: 
                        game->state.id = MENU;
                    break;
                    case GAME_OVER_EXIT:
                        game->state.id = EXIT;
                    break;
                }
                (game->state.gameOver).selected = GAME_OVER_TITLE; //reset menu
            break;
            case UP:
                menuPrevious(&(game->state.gameOver));
            break;

            case DOWN:
                menuNext(&(game->state.gameOver));
            break;

            case NONE: case RIGHT: case LEFT: default:
            //se queda en el mismo menu, no hace nada
            break;
    }
}

///////////////////////////////////////////////////////////VICTORY
void processInputVictory(Game_t *game, Input_t input){
        switch(input){
            case SELECT:
                switch ( (game->state.victory).selected ){
                    case VICTORY_MENU: 
                        game->state.id = MENU;
                    break;
                    case VICTORY_EXIT:
                        game->state.id = EXIT;
                    break;
                }
                (game->state.victory).selected = VICTORY_TITLE; //reset menu
            break;
            case UP:
                menuPrevious(&(game->state.victory));
            break;

            case DOWN:
                menuNext(&(game->state.victory));
            break;

            case NONE: case RIGHT: case LEFT: default:
            //se queda en el mismo menu, no hace nada
            break;
    }
}
//////////////////////////////////////////////////////////POINTS
void processInputPoints(Game_t * game, Input_t input){
        switch(input){
            case SELECT:
                switch ( (game->state.points).selected ){
                    case POINTS_MENU: 
                        game->state.id = MENU;
                    break;

                    case POINT_1: case POINT_2: case POINT_3: case POINT_4: case POINT_5:
                    case POINT_6: case POINT_7: case POINT_8: case POINT_9: case POINT_10:
                        //todavia nada 
                    break;

                    case POINTS_EXIT:
                        game->state.id = EXIT;
                    break;
                }
                (game->state.points).selected = POINTS_TITLE; //para que no se pueda seleccionar nada mas
            break;
            case UP:
                menuPrevious(&(game->state.points));
            break;

            case DOWN:
                menuNext(&(game->state.points));
            break;

            case NONE: case RIGHT: case LEFT: default:
            //se queda en el mismo menu, no hace nada
            break;
    }
}
/////////////////////////////GAME LOGIC///////////////////////
void processInputPlaying(GameState_t * state, Input_t input, Frog_t * frog){
    switch(input){
                case SELECT:
                    state->id = PAUSED;
                break;

                case UP:
                    moveFrog(frog,UP);
                break;

                case DOWN:
                    moveFrog(frog,DOWN);
                break;

                case RIGHT:
                    moveFrog(frog,RIGHT);
                break;

                case LEFT:
                    moveFrog(frog,LEFT);
                break;

                case NONE: default:
                //se queda en el mismo menu, no hace nada
                break;
    }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static int checkTop10Status(Top10Status_t status) {
    switch (status) {
        case TOP10_FILE_NOT_FOUND:
        case TOP10_READ_ERROR:
        case TOP10_WRITE_ERROR:
            return ERR_FILE_TOP10_FAILED;
            
        case TOP10_OK:
        case TOP10_NO_CHANGE:
        case TOP10_CHANGED:
        default:
            return 0; // O el macro/valor que uses en tu frontend para indicar "sin errores"
    }
}
/******************************************************************************/
 
