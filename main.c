#include "raspiFrontend.h"
#include "game.h"

int main(void){
    Game_t game = {0};
    ErrorCode_t err;

    if((err=gameInit(&game))){
        frontManageError(err); //aca el front imprime el mensaje de error correspondiente
        return err;
    }
    if(frontendInit()){
        frontManageError(err); //aca el front imprime el mensaje de error correspondiente
        return err;
    }
    
    while(game.state.id != EXIT){
        Input_t input = frontendGetInput();
        if(updateGame(&game, input)){
            frontManageError(err); //aca el front imprime el mensaje de error correspondiente
            return err;
        }
        frontendRender(&game);
    }

    frontendDestroy();
    return 0;
}
