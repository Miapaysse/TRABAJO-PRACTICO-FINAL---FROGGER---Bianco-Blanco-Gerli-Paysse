#include "raspiFrontend.h"
#include "game.h"

int main(void){
    Game game = {0};
    ErrorCode_t err;

    if((err=gameInit(&game))){
        frontManageError(err); //aca el front imprime "errorMessage(err)"
        return err;
    }
    if(frontendInit()){
        frontManageError(err); //aca el front imprime "errorMessage(err)"
        return err;
    }
    
    while(game.state.id != EXIT){
        Input input = frontendGetInput();
        if(updateGame(&game, input)){
            frontManageError(err); //aca el front imprime "errorMessage(err)"
            return err;
        }
        frontendRender(&game);
    }

    frontendDestroy();
    return 0;
}
