using System.Numerics;
using Raylib_cs;

namespace ChickenKabeb.src.gfx
{
    public class CameraManager
    {
        private Camera2D cam;
        public float alpha;
        public float zoom;

        public CameraManager()
        {
            this.cam.Zoom = 2;
            this.cam.Rotation = 0;
            this.alpha = 5;
        }

        public void Update(float p_x,float p_y,int width,int height,float dt)
        {
            this.cam.Offset = new Vector2(width/2, height/2);
            this.cam.Target.X = p_x;
            this.cam.Target.Y = p_y;
        }

        public Camera2D getCamera()
        {
            return this.cam;
        }
    }
}