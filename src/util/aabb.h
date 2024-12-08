#pragma once

#include <raylib.h>

#include "../entity/tile.h"
#include "../entity/player.h"
#include "../entity/entity.h"
#include "../entity/enimy.h"
#include "../level/level.h"

int is_colliding(Player* a, Tile* b);
void update_aabb(Level*l, Player*player, float dt);

int is_colliding_enimy(Enimy* a, Tile* b);
void update_aabb_enimy(Level*l, Enimy*player, float dt);
int is_colliding_ent_enimy(Entity* b, Enimy* a);

void update_aabb_ent(Level*l, Entity*player, float dt);
int is_colliding_ent(Entity* a, Tile* b);
int is_colliding_ent_player(Entity* a, Player* b);
