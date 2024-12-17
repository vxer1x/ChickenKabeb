using Raylib_cs;
using ChickenKabeb.src.entity;
using ChickenKabeb.src.util;

namespace ChickenKabeb.src.entity
{
    public class Player : Entity
    {
        public float speed;
        public float jumpForce;

        public Player(int x, int y)
            : base(x, y, 32, 32, "player")
        {
            this.speed = 200f;
            this.jumpForce = 20000f;
            this.isStatic = false;
        }

        public override void Update()
        {
            this.velocity.y += 400f * Time.DeltaTime; // Apply gravity
            UserInput();
        }

        private void UserInput()
        {
            float acceleration = 10f;  // Acceleration speed
            float deceleration = 15f;  // Deceleration speed
            float maxSpeed = this.speed;

            // Horizontal movement with acceleration/deceleration
            if (Raylib.IsKeyDown(KeyboardKey.D))
            {
                this.velocity.x = MathF.Min(this.velocity.x + acceleration, maxSpeed);
            }
            else if (Raylib.IsKeyDown(KeyboardKey.A))
            {
                this.velocity.x = MathF.Max(this.velocity.x - acceleration, -maxSpeed);
            }
            else
            {
                // Deceleration when no input
                if (this.velocity.x > 0)
                {
                    this.velocity.x = MathF.Max(this.velocity.x - deceleration, 0);
                }
                else if (this.velocity.x < 0)
                {
                    this.velocity.x = MathF.Min(this.velocity.x + deceleration, 0);
                }
            }

            // Jumping
            if (Raylib.IsKeyPressed(KeyboardKey.W) && this.onGround)
            {
                this.velocity.y = -jumpForce * Time.DeltaTime;
                this.onGround = false; // Ensure jumping is only from the ground
            }
        }
    }
}
