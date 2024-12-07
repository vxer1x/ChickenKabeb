#pragma once

#include <raylib.h>

typedef struct PreTextures
{
    Texture2D dirt_texture;
    Texture2D grass_dirt_texture;
    Texture2D purple_block;
    Texture2D chicken_1;
    Texture2D chicken_2;
    Texture2D chicken_3;
    Texture2D chicken_1f;
    Texture2D chicken_2f;
    Texture2D chicken_3f;
    Texture2D bg;
    Texture2D shotgun;
} PreTextures;


PreTextures* load_textures();
void unload_textures(PreTextures*t);