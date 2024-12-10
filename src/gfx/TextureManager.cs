using Raylib_cs;

namespace ChickenKabeb.src.gfx
{
    public class TextureManager
    {
        private Texture2D player;
        private Texture2D dirt;
        private Texture2D grass;
        private Texture2D purple;

        public TextureManager()
        {
            this.dirt = Raylib.LoadTexture("res/textures/dirt.png");
            this.grass = Raylib.LoadTexture("res/textures/grass_dirt.png");
            this.player = Raylib.LoadTexture("res/textures/chicken_1.png");
            this.purple = Raylib.LoadTexture("res/textures/purple.png");
        }

        public Texture2D GetTexture(string name)
        {
            if (name == "player")
            {
                return this.player;
            }else if (name == "dirt")
            {
                return this.dirt;
            }else if (name == "grass")
            {
                return this.grass;
            }else
            {
                return this.purple;
            }
        }

        public void UnloadTextures()
        {
            Raylib.UnloadTexture(this.dirt);
            Raylib.UnloadTexture(this.grass);
            Raylib.UnloadTexture(this.purple);
            Raylib.UnloadTexture(this.player);
        }
    }
}