#pragma once

#include <raylib.h>

#include "../gfx/texture.h"
#include "../entity/entity.h"
#include "../entity/gun.h"

typedef struct Player
{
    Vector2 pos;
    Vector2 size;
    Vector2 velocity;

    int onground;
    int ismoving;
    int dir;

    float speed;
    float terminal_vel;
    float jumpforce;
    float gravity;

    int anime_clip;
    float anime_time;

    Gun*gun_in_hand;
    int is_gun_in_hand;

} Player;

Player* init_player(int x, int y);
void update_player(Player* player, float dt);

void draw_player(Player* player, PreTextures*tex);