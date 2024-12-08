#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include "../entity/player.h"
#include "../level/level.h"
#include "../gfx/camera.h"
#include "../gfx/texture.h"

typedef struct Game
{
    Cam*cam;
    PreTextures* tex;
    Level* level;
    clock_t lastTime;
    Image icon;
    float dt;
} Game;

Game* init_game(int width, int height);
void update_game(Game*game);
void terminate_game(Game*game);