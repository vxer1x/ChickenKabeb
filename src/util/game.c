#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include "../entity/player.h"
#include "../level/level.h"
#include "../gfx/camera.h"
#include "../gfx/texture.h"

static void load_menu_ongame(Game*game)
{

}

void draw_ui(Game*game)
{
    DrawText(TextFormat("%f", game->level->player->health), game->w_width- 75, 10, 50, PINK);

    if (game->level->player->is_gun_in_hand == 1)
    {
        DrawText(TextFormat("%d", game->level->player->gun_in_hand->num_bullets), game->w_width- 75, game->w_height-70, 50,WHITE);
        if (game->level->player->gun_in_hand->isreloading == 1)
        {
            DrawText("RELOADING..", game->w_width/3, game->w_height/3, 100,WHITE);
        }
        
    }
    
    
}

static void start_level_ongame(Game*l)
{
    l->cam = init_camera();
    l->level = load_level();

}

Game *init_game()
{
    Game *l = (Game *)malloc(sizeof(Game));
    start_level_ongame(l);

    l->icon = LoadImage("res/textures/icon.bmp");
    if (l->icon.format != PIXELFORMAT_UNCOMPRESSED_R8G8B8A8) {
        ImageFormat(&l->icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8); // Convert to R8G8B8A8
    }

    l->w_width = 1920;
    l->w_height = 1080;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(l->w_width,l->w_height,"Chicken Kabeb");
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
        game->w_width = GetScreenWidth();
        game->w_height = GetScreenHeight();

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
        draw_ui(game);
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

