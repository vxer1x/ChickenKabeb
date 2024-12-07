#include "level.h"

#include "../entity/tile.h"
#include "../gfx/texture.h"
#include "../gfx//camera.h"
#include "../util/aabb.h"
#include "../entity/player.h"
#include "../entity/entity.h"
#include "../entity/gun.h"

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>




void load_tile(Level *l)
{
    FILE *file = fopen("res/maps/map.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    int x, y, type;
    int index = 0;

    // Read the file line by line
    while (fscanf(file, "%d,%d,%d", &x, &y, &type) == 3) {
        if (index >= l->num_tiles) {
            printf("Warning: Maximum tiles allowed. Ignoring extra entries.\n");
            break;
        }

        // Create a tile and assign it to the array
        l->tiles[index] = create_tile(x, y, 0, type);
        index++;
    }

    fclose(file);

}

Level *load_level()
{
    Level *l = (Level *)malloc(sizeof(Level));

    l->guns[0] = create_gun(150,-200, 10);
    l->guns[1] = create_gun(250,-200, 10);

    l->num_tiles = 50;
    load_tile(l);

    return l;
}

void update_level(Level *l, Player*player,Cam*cam, float dt)
{

    update_aabb(l,player,dt);

    for (int i = 0; i < 2; i++)
    {
        update_gun(l->guns[i], dt);
        update_aabb_ent(l, l->guns[i]->base,dt);
    }
    

}

void draw_level(Level *l, PreTextures*tex)
{
    for (int i = 0; i < l->num_tiles; i++)
    {
        draw_tile(l->tiles[i], tex);
    }
    
    for (int i = 0; i < 2; i++)
    {
        draw_gun(l->guns[i], tex);
    }
    
}
