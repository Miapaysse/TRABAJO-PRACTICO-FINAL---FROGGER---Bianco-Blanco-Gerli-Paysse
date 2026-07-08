
int main(void)
{
   startGame();

   while(game.state!=OFF){
        updateGame();
   }

   finalizarJuego();
}
