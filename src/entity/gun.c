#include "gun.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../entity/entity.h"
#include "../gfx/texture.h"

float GetOppositeAngle(float angle) {
    float oppositeAngle = angle + 180.0f;
    if (oppositeAngle > 180.0f) oppositeAngle -= 360.0f;
    return oppositeAngle;
}

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
        e->bullet_force = 1000;
        e->player_force = (Vector2){ 0,0 };

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
        e->bullet_force = 100;
        e->player_force = (Vector2){ 0,0 };

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

            float angleRad = gun->base->direction * (PI / 180.0f);

            gun->player_force.x = -gun->bullet_force * cosf(-angleRad);
            gun->player_force.y = gun->bullet_force * sinf(-angleRad);
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
            DrawTexturePro(
            tex->bullet,
            (Rectangle){ gun->base->pos.x, gun->base->pos.y, tex->bullet.width, tex->bullet.height }, // Source rectangle
            (Rectangle){ gun->bullets[i]->pos.x, gun->bullets[i]->pos.y, tex->bullet.width, tex->bullet.height }, // Destination rectangle
            (Vector2){ 0,0 },                       // Rotation origin (center of the texture)
            gun->bullets[i]->direction,             // Rotation angle in degrees
            WHITE                         // Tint color
        );
        }
    
    }

    
    if (gun->texture_id == 10)
    {
        Rectangle sourceRec = { 
            0.0f, 
            (gun->tflip == -1) ? tex->shotgun.height : 0.0f,
            (float)tex->shotgun.width, 
            (float)tex->shotgun.height * gun->tflip
        };

        Vector2 origin = { 0.0f, 0.0f };

        Rectangle destRec = { 
            gun->base->pos.x, 
            gun->base->pos.y + ((gun->tflip == -1) ? tex->shotgun.height : 0.0f),
            tex->shotgun.width, 
            tex->shotgun.height 
        };

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
    gun->bullets[bullet_index]->direction = gun->base->direction;

    // Move to the next slot (circular indexing)
    bullet_index = (bullet_index + 1) % 30;
}

