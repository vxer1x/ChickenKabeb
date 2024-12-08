#include "util/game.h"

int main(void)
{
    Game *game = init_game();

    update_game(game);
    terminate_game(game);
}