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
    e->istaken = 0;
    e->tflip = 1.0f;
    if (type == 10)
    {
        e->num_bullets = 9;
        e->max_bullets = 9;
        e->texture_id = type;
        e->base->size.x = 26;
        e->base->size.y = 9;
        e->bullet_speed = 800;
        e->fire_rate = 0.5f;

        e->reload_time = 3;
        e->reload_timer = 0;
    }else if (type == 11)
    {
        e->num_bullets = 30;
        e->max_bullets = 30;
        e->texture_id = type;
        e->base->size.x = 21;
        e->base->size.y = 12;
        e->bullet_speed = 800;
        e->fire_rate = 0.07f;

        e->reload_time = 3;
        e->reload_timer = 0;
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

    if (gun->num_bullets <= 0)
    {
        if (gun->reload_timer >= gun->reload_time)
        {
            gun->num_bullets = gun->max_bullets;
            gun->reload_timer = 0;
            
        }
        gun->reload_timer += dt;
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

    
    if (gun->texture_id == 10)
    {
        Rectangle sourceRec = { 
            0.0f, 
            (gun->tflip == -1) ? tex->shotgun.height : 0.0f, // Adjust for vertical flipping
            (float)tex->shotgun.width, 
            (float)tex->shotgun.height * gun->tflip // Flip vertically if tflip is -1
        };

        Vector2 origin = { 0.0f, 0.0f }; // Keep origin at the top-left corner

        // Adjust destination rectangle to compensate for vertical flip
        Rectangle destRec = { 
            gun->base->pos.x, 
            gun->base->pos.y + ((gun->tflip == -1) ? tex->shotgun.height : 0.0f), // Offset by height when flipping
            tex->shotgun.width, 
            tex->shotgun.height 
        };

        // Draw the texture
        DrawTexturePro(tex->shotgun, sourceRec, destRec, origin, gun->base->direction, WHITE);

    }else if (gun->texture_id == 11)
    {
        Rectangle sourceRec = { 0.0f, (gun->tflip == -1) ? tex->uzi.height : 0.0f, 
                        (float)tex->uzi.width, (float)tex->uzi.height * gun->tflip };
        Vector2 origin = { 0,0 };
        Rectangle destRec = { gun->base->pos.x, 
                      gun->base->pos.y + ((gun->tflip == -1) ? tex->uzi.height : 0), 
                      tex->uzi.width, tex->uzi.height };

        DrawTexturePro(tex->uzi, sourceRec, destRec, origin, gun->base->direction, WHITE);
    }
    


    
    
}


void shoot_gun(Gun *gun)
{
    float radians = gun->base->direction * (3.14159f / 180.0f);
    float velocityx = gun->bullet_speed * cos(radians);
    float velocityy = gun->bullet_speed * sin(radians);

    // Find the first available slot or the oldest bullet (to overwrite)
    static int bullet_index = 0; // Keeps track of the oldest bullet (circular array behavior)

    // Free the memory of the oldest bullet if it's being overwritten
    if (gun->bullets[bullet_index] != NULL) {
        free(gun->bullets[bullet_index]); // Free memory of the oldest bullet
        gun->bullets[bullet_index] = NULL; // Set the slot to NULL (not necessary but clean)
    }

    // Allocate memory for the new bullet
    gun->bullets[bullet_index] = (Entity *)malloc(sizeof(Entity));

    // Initialize the new bullet's position and velocity
    gun->bullets[bullet_index]->pos.x = gun->base->pos.x;
    gun->bullets[bullet_index]->pos.y = gun->base->pos.y;
    gun->bullets[bullet_index]->velocity.x = velocityx;
    gun->bullets[bullet_index]->velocity.y = velocityy;
    gun->bullets[bullet_index]->size.x = 1;
    gun->bullets[bullet_index]->size.y = 1;

    // Move to the next slot (circular indexing)
    bullet_index = (bullet_index + 1) % 30;
}

