#include "sfx.h"

#include <stdlib.h>
#include <raylib.h>

SFX *load_sfx()
{
    SFX *s = (SFX *)malloc(sizeof(SFX));

    InitAudioDevice();

    s->jump = LoadSound("res/sfx/cj.wav");

    return s;
}

void unload_sfx(SFX *sfx)
{
    UnloadSound(sfx->jump);
    CloseAudioDevice();
}
