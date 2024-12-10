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
            this.speed = 500;
            this.isStatic = false;
        }

        public override void Update()
        {
            UserInput();
        }

        // Manges the user input of player
        private void UserInput()
        {
            if (Raylib.IsKeyDown(KeyboardKey.D))
            {
                this.velocity.x += this.speed*Time.DeltaTime;
            }else if (Raylib.IsKeyDown(KeyboardKey.A))
            {
                this.velocity.x -= this.speed*Time.DeltaTime;
            }

            if (Raylib.IsKeyDown(KeyboardKey.W))
            {
                this.velocity.y -= this.speed*Time.DeltaTime;
            }else if (Raylib.IsKeyDown(KeyboardKey.S))
            {
                this.velocity.y += this.speed*Time.DeltaTime;
            }
        }
    }
    
}