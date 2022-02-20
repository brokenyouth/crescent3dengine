#include "Timer.h"

Timer::Timer()
{
    Reset();
}


void Timer::Reset()
{
    StartTime = std::chrono::high_resolution_clock::now();
    FrameTime = StartTime;
}

float Timer::GetDeltaTime() const
{
    std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - FrameTime);
    return (float)time.count();
}

float Timer::GetElapsedTime() const
{
    std::chrono::duration<double> Time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - StartTime);
    return (float)Time.count();
}

