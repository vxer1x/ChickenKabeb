using System;
using System.Collections.Generic;
using ChickenKabeb.src.entity;

namespace ChickenKabeb.src.util
{
    static public class AABB
    {
        // Check if two entities' AABBs are colliding
        static public bool CheckCollision(Entity a, Entity b)
        {
            return a.position.x < b.position.x + b.size.x &&
                   a.position.x + a.size.x > b.position.x &&
                   a.position.y < b.position.y + b.size.y &&
                   a.position.y + a.size.y > b.position.y;
        }

        // Resolve collisions for both entities and tiles
        static public void ResolveCollisions(List<Entity> entities, List<Entity> tiles)
        {
            foreach (var entity in entities)
            {
                entity.onGround = false;

                // First, apply the velocity and move the entity
                Vec2 originalPosition = entity.position;
                float originalVelocityX = entity.velocity.x;
                float originalVelocityY = entity.velocity.y;

                // Handle horizontal (X) collisions first
                entity.position.x += entity.velocity.x * Time.DeltaTime;

                foreach (var tile in tiles)
                {
                    // Resolve X collisions with tiles
                    if (CheckCollision(entity, tile))
                    {
                        if (entity.velocity.x > 0) // Moving right
                        {
                            entity.position.x = tile.position.x - entity.size.x; // Place entity left of the tile
                        }
                        else if (entity.velocity.x < 0) // Moving left
                        {
                            entity.position.x = tile.position.x + tile.size.x; // Place entity right of the tile
                        }
                        entity.velocity.x = 0; // Stop horizontal movement
                    }
                }

                foreach (var otherEntity in entities)
                {
                    // Skip checking collision with itself
                    if (entity == otherEntity) continue;

                    // Resolve X collisions with other entities
                    if (CheckCollision(entity, otherEntity))
                    {
                        if (entity.velocity.x > 0) // Moving right
                        {
                            entity.position.x = otherEntity.position.x - entity.size.x; // Place entity left of the other entity
                        }
                        else if (entity.velocity.x < 0) // Moving left
                        {
                            entity.position.x = otherEntity.position.x + otherEntity.size.x; // Place entity right of the other entity
                        }
                        entity.velocity.x = 0; // Stop horizontal movement
                    }
                }

                // Now handle vertical (Y) collisions
                entity.position.y += entity.velocity.y * Time.DeltaTime;

                foreach (var tile in tiles)
                {
                    // Resolve Y collisions with tiles
                    if (CheckCollision(entity, tile))
                    {
                        if (entity.velocity.y > 0) // Moving down
                        {
                            entity.position.y = tile.position.y - entity.size.y; // Place entity above the tile
                            entity.onGround = true; // Entity is on the ground
                        }
                        else if (entity.velocity.y < 0) // Moving up
                        {
                            entity.position.y = tile.position.y + tile.size.y; // Place entity below the tile
                        }
                        entity.velocity.y = 0; // Stop vertical movement
                    }
                }

                foreach (var otherEntity in entities)
                {
                    // Skip checking collision with itself
                    if (entity == otherEntity) continue;

                    // Resolve Y collisions with other entities
                    if (CheckCollision(entity, otherEntity))
                    {
                        if (entity.velocity.y > 0) // Moving down
                        {
                            entity.position.y = otherEntity.position.y - entity.size.y; // Place entity above the other entity
                            entity.onGround = true; // Entity is on the ground
                        }
                        else if (entity.velocity.y < 0) // Moving up
                        {
                            entity.position.y = otherEntity.position.y + otherEntity.size.y; // Place entity below the other entity
                        }
                        entity.velocity.y = 0; // Stop vertical movement
                    }
                }

                // If the entity moved downward, check if it's on the ground again
                if (entity.position.y > originalPosition.y)
                {
                    entity.onGround = true;
                }
            }
        }
    }
}
