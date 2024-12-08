#include "util/game.h"

int main(void)
{
    Game *game = init_game(1920,1080);

    update_game(game);
    terminate_game(game);
}