#include "level.h"

#include "../entity/tile.h"
#include "../gfx/texture.h"
#include "../gfx//camera.h"
#include "../util/aabb.h"
#include "../entity/player.h"
#include "../entity/entity.h"
#include "../entity/gun.h"

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>



void load_tile(Level *l)
{
    FILE *file = fopen("res/maps/map.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    int x, y, type;
    int index = 0;

    // Read the file line by line
    while (fscanf(file, "%d,%d,%d", &x, &y, &type) == 3) {
        if (index >= l->num_tiles) {
            printf("Warning: Maximum tiles allowed. Ignoring extra entries.\n");
            break;
        }

        // Create a tile and assign it to the array
        l->tiles[index] = create_tile(x, y, 0, type);
        index++;
    }

    fclose(file);

}

Level *load_level()
{
    Level *l = (Level *)malloc(sizeof(Level));

    l->guns[0] = create_gun(150,-200, 10);
    l->guns[1] = create_gun(250,-200, 11);

    l->num_tiles = 50;
    l->player = init_player(200,-200);
    load_tile(l);

    return l;
}

void update_level(Level *l,Cam*cam, float dt)
{

    for (int i = 0; i < 2; i++)
    {
        update_aabb_ent(l, l->guns[i]->base,dt);

        if (is_colliding_ent_player(l->guns[i]->base, l->player))
        {
            if (l->guns[i]->istaken == 0 && l->player->is_gun_in_hand == 0)
            {
                if (IsKeyPressed(KEY_E))
                {
                    l->player->gun_in_hand = l->guns[i];
                    l->player->is_gun_in_hand = 1;
                    l->guns[i]->istaken = 1;
                }
            }
        }

        if (l->guns[i]->istaken == 1)
        {
            Vector2 worldMousePos = GetScreenToWorld2D(GetMousePosition(), cam->cam);
            Vector2 direction = (Vector2){ worldMousePos.x - l->guns[i]->base->pos.x, worldMousePos.y - l->guns[i]->base->pos.y };
            l->guns[i]->base->direction = atan2(direction.y, direction.x)* (180.0f / PI);

            if (IsKeyPressed(KEY_Q))
            {
                l->player->gun_in_hand = NULL;
                l->player->is_gun_in_hand = 0;
                l->guns[i]->istaken = 0;
            }
            
        }else
        {
            l->guns[i]->base->direction = 0.0f;
        }      
        
        for (size_t j = 0; j < l->num_tiles; j++) {
            for (size_t k = 0; k < l->guns[i]->max_bullets; k++) {
                // Skip null bullets
                if (l->guns[i]->bullets[k] == NULL) {
                    continue;
                }

                // Check collision
                if (is_colliding_ent(l->guns[i]->bullets[k], l->tiles[j])) {
                    l->guns[i]->bullets[k] = NULL;

                    // Optional: Break early if one collision per tile is enough
                    break;
                }
            }
        }
    }

    update_gun(l->guns[0], dt);
    update_gun(l->guns[1], dt);
    update_player(l->player, dt);
    update_aabb(l,l->player,dt);

    if (l->player->velocity.x != 0)
    {
        l->player->velocity.x += -l->player->velocity.x*dt*5;
    }
}

void draw_level(Level *l, PreTextures*tex)
{
    draw_player(l->player, tex);

    for (int i = 0; i < l->num_tiles; i++)
    {
        draw_tile(l->tiles[i], tex);
    }
    
    for (int i = 0; i < 2; i++)
    {
        draw_gun(l->guns[i], tex);
    }
    
}
