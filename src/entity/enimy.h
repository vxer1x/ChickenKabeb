#pragma once

#include <raylib.h>

#include "../gfx/texture.h"
#include "../entity/entity.h"
#include "../entity/gun.h"

typedef struct Enimy
{
    char*name;

    Vector2 pos;
    Vector2 size;
    Vector2 velocity;

    int onground;
    int ismoving;
    int dir;
    int active;

    float health;
    float taking_damage_timer;
    Color color;

    float speed;
    float terminal_vel;
    float jumpforce;
    float gravity;

    int anime_clip;
    float anime_time;

    Gun*gun_in_hand;
    int is_gun_in_hand;

} Enimy;

Enimy* init_enimy(int x, int y,char*name);
void update_enimy(Enimy* enimy, float dt);

void draw_enimy(Enimy* enimy, PreTextures*tex);