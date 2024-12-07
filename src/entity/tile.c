#include "tile.h"

#include <stdlib.h>
#include <raylib.h>

#include "../gfx/texture.h"

Tile *create_tile(int x, int y, int type_id, int texture_id)
{
    Tile *t = (Tile *)malloc(sizeof(Tile));
    
    t->pos.x = x;
    t->pos.y = y;

    t->size.x = 32;
    t->size.y = 32;

    t->type_id = type_id;
    t->texture_id = texture_id;

    return t;
}

void draw_tile(Tile *tile, PreTextures *t)
{
    if (tile->texture_id == 1)
    {
        DrawTexture(t->grass_dirt_texture, (int)tile->pos.x, (int)tile->pos.y, WHITE);
    }else if (tile->texture_id == 2)
    {
        DrawTexture(t->dirt_texture, (int)tile->pos.x, (int)tile->pos.y, WHITE);
    }
    
}

