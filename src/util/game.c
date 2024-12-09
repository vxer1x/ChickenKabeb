#define SDL_MAIN_HANDLED
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include <SDL2/SDL_net.h>
#include <string.h>

#include "../entity/player.h"
#include "../level/level.h"
#include "../gfx/camera.h"
#include "../gfx/texture.h"

#define BUFFER_SIZE 512
#define MAX_CLIENTS 10

static void load_menu_ongame(Game *game)
{
    // Add functionality if necessary
}

void draw_ui(Game *game)
{
    DrawText(TextFormat("%f", game->level->player->health), game->w_width - 75, 10, 50, PINK);

    if (game->level->player->is_gun_in_hand == 1)
    {
        DrawText(TextFormat("%d", game->level->player->gun_in_hand->num_bullets), game->w_width - 75, game->w_height - 70, 50, WHITE);
        if (game->level->player->gun_in_hand->isreloading == 1)
        {
            DrawText("RELOADING..", game->w_width / 3, game->w_height / 3, 100, WHITE);
        }
    }
}

static void start_level_ongame(Game *l)
{
    l->cam = init_camera();
    l->level = load_level();
}

Game *init_game()
{
    Game *l = (Game *)malloc(sizeof(Game));
    start_level_ongame(l);

    l->icon = LoadImage("res/textures/icon.bmp");
    if (l->icon.format != PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
    {
        ImageFormat(&l->icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8); // Convert to R8G8B8A8
    }

    l->w_width = 1920;
    l->w_height = 1080;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(l->w_width, l->w_height, "Chicken Kabeb");
    SetWindowIcon(l->icon);
    SetTargetFPS(90);

    l->tex = load_textures();

    l->lastTime = clock();
    l->dt = 0;

    return l;
}

void update_game(Game *game)
{
    if (SDLNet_Init() < 0)
    {
        fprintf(stderr, "SDLNet_Init failed: %s\n", SDLNet_GetError());
        return; // Exit early if SDLNet fails to initialize
    }

    TCPsocket socket;
    IPaddress ip;

    if (SDLNet_ResolveHost(&ip, "127.0.0.1", 1234) < 0)
    {
        fprintf(stderr, "SDLNet_ResolveHost failed: %s\n", SDLNet_GetError());
        SDLNet_Quit();
        return; // Exit early if resolve fails
    }

    socket = SDLNet_TCP_Open(&ip);
    if (!socket)
    {
        fprintf(stderr, "SDLNet_TCP_Open failed: %s\n", SDLNet_GetError());
        SDLNet_Quit();
        return; // Exit early if socket cannot be opened
    }

    while (!WindowShouldClose())
    {
        game->w_width = GetScreenWidth();
        game->w_height = GetScreenHeight();

        clock_t currentTime = clock();
        game->dt = (float)(currentTime - game->lastTime) / CLOCKS_PER_SEC;
        game->lastTime = currentTime;

        update_level(game->level, game->cam, game->dt);
        update_camera(game->cam, game->level->player, game->dt);

        // Send player position to the server
        char buffer[BUFFER_SIZE];
        snprintf(buffer, BUFFER_SIZE, "%d %d", (int)game->level->player->pos.x, (int)game->level->player->pos.y);
        if (SDLNet_TCP_Send(socket, buffer, strlen(buffer) + 1) < strlen(buffer) + 1)
        {
            fprintf(stderr, "Error sending data: %s\n", SDLNet_GetError());
        }

        // Receive updates from the server
        int len = SDLNet_TCP_Recv(socket, buffer, BUFFER_SIZE);
        if (len > 0)
        {
            buffer[len] = '\0'; // Null-terminate the received data
            if (strncmp(buffer, "UPDATES", 7) == 0)
            {
                char *data = buffer + 8; // Skip "UPDATES "
                int id, px, py, act;
                while (sscanf(data, "%d %d %d %d", &id, &px, &py, &act) == 4)
                {
                    if (id >= 0 && id < 10) // Ensure id is within range
                    {
                        game->level->enimes[id]->active = act;
                        game->level->enimes[id]->pos.x = px;
                        game->level->enimes[id]->pos.y = py;
                    }
                    data = strchr(data, ' ');
                    if (data)
                        data++; // Skip past the space
                }
            }
        }
        else if (len == 0)
        {
            printf("No data received.\n");
        }
        else
        {
            printf("Error receiving data: %s\n", SDLNet_GetError());
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(game->cam->cam);
        draw_level(game->level, game->tex);
        EndMode2D();

        DrawText(TextFormat("%d", GetFPS()), 10, 10, 30, RED);
        draw_ui(game);
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    SDLNet_TCP_Close(socket);
    SDLNet_Quit();
}

void terminate_game(Game *game)
{
    CloseWindow();
    unload_textures(game->tex);
    UnloadImage(game->icon);
    free(game->level);
}
