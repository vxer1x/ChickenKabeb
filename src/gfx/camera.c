#include "camera.h"

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#include "../entity/player.h"

Cam *init_camera()
{
    Cam *camera = (Cam *)malloc(sizeof(Cam));
    camera->cam.rotation = 0.0f;
    camera->cam.zoom = 3.0f;
    camera->cam.offset = (Vector2){ 900, 450 };
    camera->cam.target = (Vector2){ 500, 400 };

    camera->alpha = 5;
    camera->zoom = 3.0f;

    return camera;
}

void update_camera(Cam*cam, Player* player, float dt)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    cam->cam.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };

    float aspectRatio = (float)screenWidth / 1080;
    if (screenWidth / (float)screenHeight > aspectRatio) {
        cam->cam.zoom = ((float)screenHeight / 1080)*cam->zoom;
    } else {
        cam->cam.zoom = ((float)screenWidth / 1920)*cam->zoom;
    }


    cam->cam.target.x += ((-cam->cam.target.x + player->pos.x)*dt*cam->alpha);
    cam->cam.target.y += ((-cam->cam.target.y + player->pos.y)*dt*cam->alpha);

}
