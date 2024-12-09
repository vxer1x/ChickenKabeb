#include "enimy.h"

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#include "../gfx/texture.h"
#include "../entity/gun.h"

Enimy *init_enimy(int x, int y,char*name)
{
    Enimy *p = (Enimy *)malloc(sizeof(Enimy));
    p->name = name;
    p->pos.x = x;
    p->pos.y = y;

    p->size.x = 28;
    p->size.y = 32;

    p->velocity.x = 0;
    p->velocity.y = 0;
    p->active = 0;
    p->speed = 20;
    p->terminal_vel = 300;
    p->gravity = 400;
    p->jumpforce = -350;
    p->onground = 0;

    p->health = 100.0f;
    p->taking_damage_timer = 1.1f;
    p->color = WHITE;

    p->anime_clip = 0;
    p->anime_time = 0;
    p->dir = 1;

    p->gun_in_hand = 0;
    p->is_gun_in_hand = 0;

    return p;
}

void update_enimy(Enimy *enim, float dt)
{
    enim->taking_damage_timer += dt;

    if (enim->taking_damage_timer <= 0.3f)
    {
        enim->color = RED;
    }else
    {
        enim->color = WHITE;
    }
    
    
    enim->anime_time += dt*10;

    if (enim->velocity.y <= enim->gravity)
    {
        enim->velocity.y += 500*dt;
    }

    if (enim->anime_time >= 1.0f && enim->ismoving == 1)
    {
        if (enim->anime_clip == 1)
        {
            enim->anime_clip = 0;
        }else if (enim->anime_clip == 0)
        {
            enim->anime_clip = 1;
        }
        enim->anime_time = 0.0;
    }
    
}

void draw_enimy(Enimy *enimy, PreTextures *tex)
{
    if (enimy->active == 1)
    {
        DrawText(enimy->name,enimy->pos.x,enimy->pos.y-30,5, RED);

        if (enimy->onground == 1)
        {
            if (enimy->dir == 1)
            {
                if (enimy->anime_clip == 0)
                {
                    DrawTexture(tex->chicken_2, (int)enimy->pos.x, (int)enimy->pos.y, enimy->color);
                }else if (enimy->anime_clip == 1)
                {
                    DrawTexture(tex->chicken_1, (int)enimy->pos.x, (int)enimy->pos.y, enimy->color);
                }
            }else if (enimy->dir == 0)
            {
                if (enimy->anime_clip == 0)
                {
                    DrawTexture(tex->chicken_2f, (int)enimy->pos.x, (int)enimy->pos.y, enimy->color);
                }else if (enimy->anime_clip == 1)
                {
                    DrawTexture(tex->chicken_1f, (int)enimy->pos.x, (int)enimy->pos.y, enimy->color);
                }
            }
        }else
        {
            if (enimy->dir == 1)
            {
                DrawTexture(tex->chicken_3, (int)enimy->pos.x, (int)enimy->pos.y, enimy->color);
            }else if (enimy->dir == 0)
            {
                DrawTexture(tex->chicken_3f, (int)enimy->pos.x, (int)enimy->pos.y, enimy->color);
            }
            
        }
    }
    

}
