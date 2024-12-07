#include "texture.h"

#include <stdlib.h>

PreTextures *load_textures()
{
    PreTextures *t = (PreTextures *)malloc(sizeof(PreTextures));

    t->dirt_texture = LoadTexture("res/textures/dirt.png");
    t->grass_dirt_texture = LoadTexture("res/textures/grass_dirt.png");
    t->purple_block = LoadTexture("res/textures/purple.png");
    t->chicken_1 = LoadTexture("res/textures/chicken_1.png");
    t->chicken_2 = LoadTexture("res/textures/chicken_2.png");
    t->chicken_3 = LoadTexture("res/textures/chicken_3.png");
    t->chicken_1f = LoadTexture("res/textures/chicken_1f1.png");
    t->chicken_2f = LoadTexture("res/textures/chicken_2f1.png");
    t->chicken_3f = LoadTexture("res/textures/chicken_3f.png");
    t->bg = LoadTexture("res/textures/purple.png");
    t->shotgun = LoadTexture("res/textures/shotgun.png");  // tid 10
    t->uzi = LoadTexture("res/textures/uzi.png");  // tid 11

    return t;
}

void unload_textures(PreTextures *t)
{
    UnloadTexture(t->chicken_1);
    UnloadTexture(t->chicken_2);
    UnloadTexture(t->chicken_3);
    UnloadTexture(t->chicken_1f);
    UnloadTexture(t->chicken_2f);
    UnloadTexture(t->chicken_3f);
    UnloadTexture(t->dirt_texture);
    UnloadTexture(t->grass_dirt_texture);
    UnloadTexture(t->purple_block);
    UnloadTexture(t->bg);
    UnloadTexture(t->shotgun);
    UnloadTexture(t->uzi);
}
