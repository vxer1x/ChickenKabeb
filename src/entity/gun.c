#include "gun.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../entity/entity.h"
#include "../gfx/texture.h"

Gun *create_gun(int x, int y, int type)
{
    Gun* e = (Gun*)malloc(sizeof(Gun));

    e->base = create_entity(x, y);

    e->fire_time = 0;
    e->num_bullets = 30;
    e->istaken = 0;
    e->tflip = 1.0f;
    if (type == 10)
    {
        e->texture_id = type;
        e->base->size.x = 26;
        e->base->size.y = 9;
        e->bullet_speed = 800;
        e->fire_rate = 0.06f;
    }
    
    for (int i = 0; i < 30; ++i) {
        e->bullets[i] = NULL; // Set each bullet to NULL
    }

    return e;
}

void update_gun(Gun *gun, float dt)
{
    gun->fire_time += dt;

    for (int i = 0; i < 30; i++)
    {
        if (gun->bullets[i] != NULL)
        {
            gun->bullets[i]->pos.x += gun->bullets[i]->velocity.x*dt;
            gun->bullets[i]->pos.y += gun->bullets[i]->velocity.y*dt;
        }
        

    }
    

    if (gun->base->velocity.y <= gun->base->gravity && gun->istaken == 0)
    {
        gun->base->velocity.y += 500*dt;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && gun->istaken == 1)
    {
        if (gun->num_bullets > 0 && gun->fire_time > gun->fire_rate)
        {
            shoot_gun(gun);
            gun->num_bullets -= 1;
            gun->fire_time = 0;
        }
    }

    if (gun->base->direction <= 90 && gun->base->direction >= -90)
    {
        gun->tflip = 1.0f;
    }else
    {
        gun->tflip = -1.0f;
    }

    
}

void draw_gun(Gun *gun, PreTextures *tex)
{
    for (int i = 0; i < 30; i++)
    {
        if (gun->bullets[i] != NULL)
        {
            DrawCircle(gun->bullets[i]->pos.x,gun->bullets[i]->pos.y,2,YELLOW);
        }
    
    }

    
    Rectangle sourceRec = { 0.0f, 0.0f, (float)tex->shotgun.width, (float)tex->shotgun.height*gun->tflip };
    Vector2 origin = { tex->shotgun.width / 2.0f, tex->shotgun.height / 2.0f };  // Rotate around the center of the gun

    // Use DrawTexturePro to draw the gun rotated towards the mouse
    DrawTexturePro(tex->shotgun, sourceRec, (Rectangle){ gun->base->pos.x, gun->base->pos.y, tex->shotgun.width, tex->shotgun.height },
        origin, gun->base->direction, WHITE);

    
    
}


void shoot_gun(Gun *gun)
{
    float radians = gun->base->direction * (3.14159f / 180.0f);
    float velocityx = gun->bullet_speed * cos(radians);
    float velocityy = gun->bullet_speed * sin(radians);

    for (int i = 0; i < 30; ++i) {
        if (gun->bullets[i] == NULL) {
            if (gun->bullets[i] == NULL) {
                gun->bullets[i] = (Entity*)malloc(sizeof(Entity)); // Allocate memory for new bullet
            }

            // Initialize bullet position and velocity
            gun->bullets[i]->pos.x = gun->base->pos.x;
            gun->bullets[i]->pos.y = gun->base->pos.y;
            gun->bullets[i]->velocity.x = velocityx;
            gun->bullets[i]->velocity.y = velocityy;
            break;
        }
    }
}
