#include "gun.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "../entity/entity.h"
#include "../gfx/texture.h"

Gun *create_gun(int x, int y, int type)
{
    Gun* e = (Gun*)malloc(sizeof(Gun));

    e->base = create_entity(x, y);

    e->fire_time = 0;
    e->num_bullets = 30;
    if (type == 10)
    {
        e->texture_id = type;
        e->base->size.x = 26;
        e->base->size.y = 9;
    }
    

    return e;
}

void update_gun(Gun *gun, float dt)
{
    if (gun->base->velocity.y <= gun->base->gravity)
    {
        gun->base->velocity.y += 500*dt;
    }
}

void draw_gun(Gun *gun, PreTextures *tex)
{
    DrawTexture(tex->shotgun, gun->base->pos.x, gun->base->pos.y, WHITE);
}
