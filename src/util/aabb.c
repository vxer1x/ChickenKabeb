#include "aabb.h"

#include <raylib.h>
#include <stdio.h>

#include "../entity/tile.h"
#include "../level/level.h"
#include "../entity/player.h"

int is_colliding(Player *a, Tile *b) {
    int result = (a->pos.x < b->pos.x + b->size.x &&
                  a->pos.x + a->size.x > b->pos.x &&
                  a->pos.y < b->pos.y + b->size.y &&
                  a->pos.y + a->size.y > b->pos.y);

    if (result == 1)
    {
        if (b->type_id == 1)
        {
            result = 0;
        }
    }
    

    return result;
}


void update_aabb(Level *l, Player *player, float dt) {
    // Resolve X-axis first
    player->pos.x += (player->velocity.x * dt);
    for (int i = 0; i < l->num_tiles; i++) {
        Tile *tile = l->tiles[i];
        if (is_colliding(player, tile)) {
            if (player->velocity.x > 0) { // Moving right
                player->pos.x = tile->pos.x - player->size.x;
            } else if (player->velocity.x < 0) { // Moving left
                player->pos.x = tile->pos.x + tile->size.x;
            }
            player->velocity.x = 0; // Stop horizontal movement
        }
    }

    // Resolve Y-axis
    player->pos.y += (player->velocity.y * dt);
    for (int i = 0; i < l->num_tiles; i++) {
        Tile *tile = l->tiles[i];
        if (is_colliding(player, tile)) {
            if (player->velocity.y > 0) { // Moving down
                player->pos.y = tile->pos.y - player->size.y;
                player->onground = 1;
            } else if (player->velocity.y < 0) { // Moving up
                player->pos.y = tile->pos.y + tile->size.y;
            }
            player->velocity.y = 0; // Stop vertical movement
        }
        
    }
}

void update_aabb_ent(Level *l, Entity *player, float dt)
{
    // Resolve X-axis first
    player->pos.x += (player->velocity.x * dt);
    for (int i = 0; i < l->num_tiles; i++) {
        Tile *tile = l->tiles[i];
        if (is_colliding_ent(player, tile)) {
            if (player->velocity.x > 0) { // Moving right
                player->pos.x = tile->pos.x - player->size.x;
            } else if (player->velocity.x < 0) { // Moving left
                player->pos.x = tile->pos.x + tile->size.x;
            }
            player->velocity.x = 0; // Stop horizontal movement
        }
    }

    // Resolve Y-axis
    player->pos.y += (player->velocity.y * dt);
    for (int i = 0; i < l->num_tiles; i++) {
        Tile *tile = l->tiles[i];
        if (is_colliding_ent(player, tile)) {
            if (player->velocity.y > 0) { // Moving down
                player->pos.y = tile->pos.y - player->size.y;
            } else if (player->velocity.y < 0) { // Moving up
                player->pos.y = tile->pos.y + tile->size.y;
            }
            player->velocity.y = 0; // Stop vertical movement
        }
        
    }
}

int is_colliding_ent(Entity *a, Tile *b)
{
    int result = (a->pos.x < b->pos.x + b->size.x &&
                  a->pos.x + a->size.x > b->pos.x &&
                  a->pos.y < b->pos.y + b->size.y &&
                  a->pos.y + a->size.y > b->pos.y);
    return result;
}
