#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include "../entity/player.h"
#include "../level/level.h"
#include "../gfx/camera.h"
#include "../gfx/texture.h"

Game *init_game(int width, int height)
{
    Game *l = (Game *)malloc(sizeof(Game));

    l->cam = init_camera();
    l->level = load_level();


    l->icon = LoadImage("res/textures/icon.bmp");
    if (l->icon.format != PIXELFORMAT_UNCOMPRESSED_R8G8B8A8) {
        ImageFormat(&l->icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8); // Convert to R8G8B8A8
    }
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width,height,"Chicken Kabeb");
    SetWindowIcon(l->icon);
    SetTargetFPS(90);
    
    l->tex = load_textures();

    l->lastTime = clock();
    l->dt = 0;

    return l;
}

void update_game(Game *game)
{
    while (!WindowShouldClose())
    {
        clock_t currentTime = clock();
        game->dt = (float)(currentTime - game->lastTime) / CLOCKS_PER_SEC;
        game->lastTime = currentTime;

        update_level(game->level, game->cam, game->dt);
        update_camera(game->cam,game->level->player,game->dt);

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(game->cam->cam);

        draw_level(game->level, game->tex);

        EndMode2D();

        DrawText(TextFormat("%d", GetFPS()), 10, 10, 30, RED);
        EndDrawing();
    }
}

void terminate_game(Game *game)
{
    CloseWindow();
    unload_textures(game->tex);
    UnloadImage(game->icon);

    free(game->level);
}
