#pragma once

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "../entity/entity.h"
#include "../entity/gun.h"
#include "../gfx/texture.h"

typedef struct Gun
{
    Entity*base;

    int bullet_damage;
    int num_bullets;
    int max_bullets;
    float reload_time;   
    float reload_timer;   
    float fire_time;
    float fire_rate;
    int bullet_speed;
    float bullet_force;
    Vector2 player_force;
    Entity*bullets[30];
    int isreloading;

    int texture_id;
    int istaken;
    float tflip;
} Gun;

Gun* create_gun(int x,int y,int type);
void update_gun(Gun*gun, float dt);
void draw_gun(Gun*gun, PreTextures*tex);
void shoot_gun(Gun*gun);