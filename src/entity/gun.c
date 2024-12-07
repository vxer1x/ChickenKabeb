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
    e->istaken = 0;
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
    if (gun->base->velocity.y <= gun->base->gravity && gun->istaken == 0)
    {
        gun->base->velocity.y += 500*dt;
    }
}

void draw_gun(Gun *gun, PreTextures *tex)
{
    float flip = 1.0f;
    if (gun->base->direction <= 90 && gun->base->direction >= -90)
    {
        flip = 1.0f;
    }else
    {
        flip = -1.0f;
    }
    
    
    Rectangle sourceRec = { 0.0f, 0.0f, (float)tex->shotgun.width, (float)tex->shotgun.height*flip };
    Vector2 origin = { tex->shotgun.width / 2.0f, tex->shotgun.height / 2.0f };  // Rotate around the center of the gun

    // Use DrawTexturePro to draw the gun rotated towards the mouse
    DrawTexturePro(tex->shotgun, sourceRec, (Rectangle){ gun->base->pos.x, gun->base->pos.y, tex->shotgun.width, tex->shotgun.height },
        origin, gun->base->direction, WHITE);
    }
