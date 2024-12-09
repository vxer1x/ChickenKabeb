#pragma once

#include <raylib.h>

#include "../entity/tile.h"
#include "../gfx/texture.h"
#include "../entity/player.h"
#include "../entity/gun.h"
#include "../entity/entity.h"
#include "../entity/enimy.h"
#include "../gfx/camera.h"

typedef struct Level
{
    int num_tiles;
    Tile* tiles[119];
    Gun*guns[2];
    Player*player;

    Entity*Enimy_bullets[120];
    Enimy*enimes[10];
}Level;

void load_tile(Level*l);

Level* load_level();
void update_level(Level* l, Cam*cam, float dt);
void draw_level(Level* l, PreTextures*tex);