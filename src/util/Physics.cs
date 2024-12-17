using System;
using System.Collections.Generic;
using ChickenKabeb.src.entity;

namespace ChickenKabeb.src.util
{
    public static class AABB
    {
        public static bool CheckCollision(Entity a, Entity b)
        {
            return a.position.x < b.position.x + b.size.x &&
                   a.position.x + a.size.x > b.position.x &&
                   a.position.y < b.position.y + b.size.y &&
                   a.position.y + a.size.y > b.position.y;
        }

        public static void ResolveCollisions(List<Entity> entities, List<Entity> tiles)
        {
            foreach (var entity in entities)
            {
                entity.onGround = false;

                // Apply velocity
                Vec2 originalPosition = entity.position;

                // Horizontal movement
                entity.position.x += entity.velocity.x * Time.DeltaTime;

                foreach (var tile in tiles)
                {
                    if (CheckCollision(entity, tile))
                    {
                        if (entity.velocity.x > 0) // Moving right
                        {
                            entity.position.x = tile.position.x - entity.size.x;
                        }
                        else if (entity.velocity.x < 0) // Moving left
                        {
                            entity.position.x = tile.position.x + tile.size.x;
                        }
                        entity.velocity.x = 0;
                    }
                }

                // Vertical movement
                entity.position.y += entity.velocity.y * Time.DeltaTime;

                foreach (var tile in tiles)
                {
                    if (CheckCollision(entity, tile))
                    {
                        if (entity.velocity.y > 0) // Moving down
                        {
                            entity.position.y = tile.position.y - entity.size.y;
                            entity.onGround = true; // Player landed on a tile
                        }
                        else if (entity.velocity.y < 0) // Moving up
                        {
                            entity.position.y = tile.position.y + tile.size.y;
                        }
                        entity.velocity.y = 0;
                    }
                }
            }
        }
    }
}
