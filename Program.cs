using ChickenKabeb.src.util;

namespace ChickenKabeb
{
    class Program
    {
        static void Main()
        {
            var game = new Game();

            // Game loop
            while (game.IsRunning())  // Loop as long as game_running is true
            {
                game.Update();
                game.Draw();
            }

            game.Terminate();  // Close the window and clean up
        }
    }
}
