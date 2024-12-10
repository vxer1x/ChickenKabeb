using System;
using System.Diagnostics;

namespace ChickenKabeb.src.util
{
    static public class Time
    {
        static public float DeltaTime { get; private set; } = 0.0f;
        static private Stopwatch stopwatch = new();

        // Initialize the stopwatch
        static Time()
        {
            stopwatch.Start();
        }

        static public void Update()
        {
            DeltaTime = (float)stopwatch.Elapsed.TotalSeconds;
            stopwatch.Restart();
        }
    }
}
