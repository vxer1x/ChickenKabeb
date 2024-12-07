#pragma once

#include <raylib.h>

typedef struct SFX
{
    Sound jump;
} SFX;

SFX* load_sfx();
void unload_sfx(SFX*sfx);