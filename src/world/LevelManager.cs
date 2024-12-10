using Raylib_cs;
using ChickenKabeb.src.entity;
using ChickenKabeb.src.gfx;
using ChickenKabeb.src.entity.tiles;

namespace ChickenKabeb.src.world
{
    public static class World
    {
        public static List<Entity> LoadEntitiesFromFile(string filePath)
        {
            List<Entity> entities = new List<Entity>();

            try
            {
                // Read all lines from the file
                string[] lines = File.ReadAllLines(filePath);

                foreach (string line in lines)
                {
                    // Skip empty lines or invalid data
                    if (string.IsNullOrWhiteSpace(line)) continue;

                    // Split the line by commas
                    string[] parts = line.Split(',');

                    if (parts.Length == 3 &&
                        int.TryParse(parts[0], out int posX) &&
                        int.TryParse(parts[1], out int posY) &&
                        int.TryParse(parts[2], out int typeBlock))
                    {
                        // Create entities based on typeBlock
                        Entity entity = typeBlock switch
                        {
                            2 => new Dirt(posX, posY),
                            1 => new Grass(posX, posY),
                            _ => throw new NotImplementedException(),
                        };

                        if (entity != null)
                        {
                            entities.Add(entity);
                        }
                        else
                        {
                            Console.WriteLine($"Unknown typeBlock: {typeBlock} in line: {line}");
                        }
                    }
                    else
                    {
                        Console.WriteLine($"Skipping invalid line: {line}");
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error reading file: {ex.Message}");
            }

            return entities;
        }

        public static void DrawEntites(List<Entity> entities,TextureManager texm)
        {
            foreach (Entity entity in entities)
            {
                Raylib.DrawTexture(texm.GetTexture(entity.typeName), (int)entity.position.x, (int)entity.position.y, Color.White);
            }
        }
    }
}
