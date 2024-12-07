#pragma once

#include <raylib.h>

#include "../gfx/texture.h"

typedef struct Tile
{
    Vector2 pos;
    Vector2 size;

    int type_id; // 0 = solid, 1 = free
    int texture_id;
} Tile;


Tile* create_tile(int x, int y, int type_id, int texture_id);
void draw_tile(Tile*tile, PreTextures*t);