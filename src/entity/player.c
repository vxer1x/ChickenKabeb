#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#include "../gfx/texture.h"
#include "../entity/gun.h"


Player* init_player(int x, int y)
{
    Player *p = (Player *)malloc(sizeof(Player));
    p->pos.x = x;
    p->pos.y = y;

    p->size.x = 28;
    p->size.y = 32;

    p->velocity.x = 0;
    p->velocity.y = 0;

    p->speed = 20;
    p->terminal_vel = 300;
    p->gravity = 400;
    p->jumpforce = -350;
    p->onground = 0;

    p->health = 100.0f;
    p->taking_damage_timer = 1.1f;

    p->anime_clip = 0;
    p->anime_time = 0;
    p->dir = 1;

    p->gun_in_hand = 0;
    p->is_gun_in_hand = 0;

    return p;
}

void update_player(Player *player,  float dt)
{
    player->taking_damage_timer += dt;

    if (player->pos.y > 1000)
    {
        player->pos = (Vector2){ 200,-200 };
    }



    if (IsKeyDown(KEY_A))
    {
        player->velocity.x += -player->speed;
        player->ismoving = 1;
        player->dir = 0;
    }else if (IsKeyDown(KEY_D))
    {
        player->velocity.x += player->speed;
        player->ismoving = 1;
        player->dir = 1;
    }else
    {
        player->ismoving = 0;
    }

    if (IsKeyPressed(KEY_SPACE) && player->onground == 1) // Use IsKeyPressed for a single jump per key press
    {
        player->velocity.y += player->jumpforce;
        // PlaySound(sfx->jump);
    }
    
    

    if (player->velocity.y <= player->gravity)
    {
        player->velocity.y += 500*dt;
    }
    
    player->anime_time += dt*10;

    if (player->anime_time >= 1.0f && player->ismoving == 1)
    {
        if (player->anime_clip == 1)
        {
            player->anime_clip = 0;
        }else if (player->anime_clip == 0)
        {
            player->anime_clip = 1;
        }
        player->anime_time = 0.0;
    }
    
    
    if (player->is_gun_in_hand == 1)
    {
        player->gun_in_hand->base->pos.x = player->pos.x+16;
        player->gun_in_hand->base->pos.y = player->pos.y+16;

        player->velocity.x += player->gun_in_hand->player_force.x;
        player->velocity.y += player->gun_in_hand->player_force.y;
        player->gun_in_hand->player_force = (Vector2){ 0, 0 };
    }

}

void draw_player(Player *player, PreTextures*tex)
{
    if (player->onground == 1)
    {
        if (player->dir == 1)
        {
            if (player->anime_clip == 0)
            {
                DrawTexture(tex->chicken_2, (int)player->pos.x, (int)player->pos.y, WHITE);
            }else if (player->anime_clip == 1)
            {
                DrawTexture(tex->chicken_1, (int)player->pos.x, (int)player->pos.y, WHITE);
            }
        }else if (player->dir == 0)
        {
            if (player->anime_clip == 0)
            {
                DrawTexture(tex->chicken_2f, (int)player->pos.x, (int)player->pos.y, WHITE);
            }else if (player->anime_clip == 1)
            {
                DrawTexture(tex->chicken_1f, (int)player->pos.x, (int)player->pos.y, WHITE);
            }
        }
    }else
    {
        if (player->dir == 1)
        {
            DrawTexture(tex->chicken_3, (int)player->pos.x, (int)player->pos.y, WHITE);
        }else if (player->dir == 0)
        {
            DrawTexture(tex->chicken_3f, (int)player->pos.x, (int)player->pos.y, WHITE);
        }
        
    }
}

