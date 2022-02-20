#pragma once
#include <chrono>

class Timer
{
public:
    Timer();
    virtual ~Timer() {}

    void		Reset();
    float		GetDeltaTime() const;
    float		GetElapsedTime() const;

protected:
    std::chrono::high_resolution_clock::time_point StartTime;
    std::chrono::high_resolution_clock::time_point FrameTime;
};
