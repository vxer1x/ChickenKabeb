using Raylib_cs;
using ChickenKabeb.src.entity;
using ChickenKabeb.src.util;
using ChickenKabeb.src.gfx;


namespace ChickenKabeb.src.entity
{
    public class Player : Entity
    {
        public float speed;
        public Player(int x, int y)
            : base(x, y, 32, 32, "player")
        {
            this.speed = 300;
        }

        public void Update(float dt)
        {
            UserInput(dt);
        }

        public void Draw(TextureManager tm)
        {
            Raylib.DrawTexture(tm.GetTexture("player"), (int)this.position.x, (int)this.position.y, Color.White);
        }


        // Manges the user input of player
        private void UserInput(float dt)
        {
            if (Raylib.IsKeyDown(KeyboardKey.D))
            {
                this.position.x += this.speed*dt;
            }else if (Raylib.IsKeyDown(KeyboardKey.A))
            {
                this.position.x -= this.speed*dt;
            }

            if (Raylib.IsKeyDown(KeyboardKey.W))
            {
                this.position.y -= this.speed*dt;
            }else if (Raylib.IsKeyDown(KeyboardKey.S))
            {
                this.position.y += this.speed*dt;
            }
        }
    }
    
}