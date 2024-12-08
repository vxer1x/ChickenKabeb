#include "entity.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Entity *create_entity(int x, int y)
{
    Entity* e = (Entity*)malloc(sizeof(Entity));

    e->pos.x = x;
    e->pos.y = y;

    e->gravity = 400.0f;
    e->direction = 0.0f;
    e->range = 0;

    e->velocity.x = 0;
    e->velocity.y = 0;

    e->damage = 0;
    return e;
}
