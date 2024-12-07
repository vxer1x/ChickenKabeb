#pragma once

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "../entity/entity.h"
#include "../gfx/texture.h"

typedef struct Gun
{
    Entity*base;

    int num_bullets;
    float fire_time;
    Entity*bullets[30];
    int texture_id;
    int istaken;
} Gun;

Gun* create_gun(int x,int y,int type);
void update_gun(Gun*gun, float dt);
void draw_gun(Gun*gun, PreTextures*tex);