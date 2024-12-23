using ChickenKabeb.src.util;
using Raylib_cs;

namespace ChickenKabeb.src.entity
{
    public abstract class Entity
    {
        public Vec2 position;
        public Vec2 size;
        public Vec2 velocity;

        public float direction;
        public float terminalVelocity;
        public bool isStatic;
        public string typeName;
        public bool onGround;

        public Entity(int x, int y, int width, int height,string name)
        {
            this.position.x = x;
            this.position.y = y;

            this.size.x = width;
            this.size.y = height;

            this.velocity.x = 0;
            this.velocity.y = 0;

            this.direction = 0;
            this.onGround = false;
            this.isStatic = true;
            this.typeName = name;
            this.terminalVelocity = 200;
        }

        public virtual void Update()
        {

        }
    }
}