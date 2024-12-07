#pragma once

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Entity
{
    Vector2 pos;
    Vector2 size;
    Vector2 velocity;

    float gravity;
    float direction;
} Entity;

Entity *create_entity(int x, int y);