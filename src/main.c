#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include "entity/player.h"
#include "level/level.h"
#include "gfx/camera.h"
#include "gfx/texture.h"
#include "util/sfx.h"


int main(void)
{
    Image icon = LoadImage("res/textures/icon.bmp");
    if (icon.format != PIXELFORMAT_UNCOMPRESSED_R8G8B8A8) {
        ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8); // Convert to R8G8B8A8
    }
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1920,1080,"Chicken Kabeb");
    SetWindowIcon(icon);


    Player *player = init_player(200,-200);
    Level* level = load_level();
    Cam* cam = init_camera();
    PreTextures* tex = load_textures();
    SFX* sfx = load_sfx();
    SetTargetFPS(240);

    SetTraceLogLevel(LOG_DEBUG);
    

    clock_t lastTime = clock();
    float dt;

    while (!WindowShouldClose())
    {
        clock_t currentTime = clock();
        dt = (float)(currentTime - lastTime) / CLOCKS_PER_SEC;
        lastTime = currentTime;

        update_player(player,sfx,dt);
        update_level(level, player, cam, dt);
        update_camera(cam,player,dt);

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(cam->cam);

        draw_player(player, tex);
        draw_level(level, tex);

        EndMode2D();

        DrawText(TextFormat("%d", GetFPS()), 10, 10, 30, RED);
        EndDrawing();
    }

    CloseWindow();
    unload_sfx(sfx);
    unload_textures(tex);
    UnloadImage(icon);

    free(player);
    free(level);\
    return 0;
}