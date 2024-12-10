using Raylib_cs;

using ChickenKabeb.src.entity;
using ChickenKabeb.src.entity.tiles;
using ChickenKabeb.src.util;
using ChickenKabeb.src.gfx;
using ChickenKabeb.src.world;


namespace ChickenKabeb.src.util
{
    public class Game
    {
        private int window_width = 1920;
        private int window_height = 1080;

        private bool game_running = true;

        private TextureManager tex_manager;
        private Player player = new(1000,100);

        private List<Entity> Tiles;
        private List<Entity> Entities = new();

        public Game()
        {
            Raylib.SetConfigFlags(ConfigFlags.ResizableWindow);
            Raylib.InitWindow(window_width, window_height, "ChickenKabeb");

            tex_manager = new TextureManager();
            Tiles = World.LoadEntitiesFromFile("res/maps/map.txt");

            Entities.Add(this.player);
        }


        public void Update()
        {
            Time.Update();
            if (Raylib.WindowShouldClose())
            {
                game_running = false;
            }

            this.window_width = Raylib.GetScreenWidth();
            this.window_height = Raylib.GetScreenHeight();

            World.UpdateEntites(Entities);
            AABB.ResolveCollisions(this.Entities,this.Tiles);
        }

        public void Draw()
        {
            Raylib.BeginDrawing();
            Raylib.ClearBackground(Color.SkyBlue);

            World.DrawEntites(this.Tiles,this.tex_manager);
            World.DrawEntites(this.Entities,this.tex_manager);

            Raylib.DrawText(Raylib.GetFPS().ToString(), 10, 10, 20, Color.White);
            Raylib.EndDrawing();
        }

        public void Terminate()
        {
            Raylib.CloseWindow();
            this.tex_manager.UnloadTextures();
        }
        public bool IsRunning() 
        {
            return game_running;
        }
    }
}
