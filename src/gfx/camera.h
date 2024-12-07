#pragma once

#include <raylib.h>
#include <stdlib.h>

#include "../entity/player.h"

typedef struct Cam
{
    Camera2D cam;
    float speed;
    float alpha;
    float zoom;
} Cam;

Cam* init_camera();
void update_camera(Cam*cam, Player* player, float dt);