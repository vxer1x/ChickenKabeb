#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>

#include "../entity/player.h"
#include "../level/level.h"
#include "../gfx/camera.h"
#include "../gfx/texture.h"

typedef struct Game
{
    int w_width;
    int w_height;

    Cam*cam;
    PreTextures* tex;
    Level* level;
    clock_t lastTime;
    Image icon;
    float dt;

} Game;

Game* init_game();
void update_game(Game*game);
void terminate_game(Game*game);