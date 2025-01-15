#include "Timing.h"

#include <SDL2/SDL.h>

FpsLimiter::FpsLimiter() = default;

void FpsLimiter::init(const uint32_t maxFPS)
{
    setMaxFPS(maxFPS);
}

void FpsLimiter::setMaxFPS(const uint32_t maxFPS)
{
    _maxFPS = maxFPS;
}

void FpsLimiter::begin()
{
    _startTics = SDL_GetTicks();
}

void FpsLimiter::_calculateFPS()
{
    static constexpr int NUM_SAMPLES = 10;
    static int currentFrame = 0;
    static Uint32 frameTimes[NUM_SAMPLES];
    static Uint32 prevTics = SDL_GetTicks();
    const Uint32 currentTics = SDL_GetTicks();

    _frameTime = currentTics - prevTics;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

    prevTics = currentTics;

    int count;

    currentFrame++;
    if (currentFrame < NUM_SAMPLES)
    {
        count = currentFrame;
    }
    else {
        count = NUM_SAMPLES;
    }

    Uint32 frameTimeAverage = 0;

    for (int i = 0; i < count; i++)
    {
        frameTimeAverage += frameTimes[i];
    }

    frameTimeAverage /= count;

    if (frameTimeAverage > 0)
    {
        _fps = 1000 / frameTimeAverage;
    }
    else {
        _fps = 60;
    }
}

uint32_t FpsLimiter::end()
{
    _calculateFPS();

    if (const uint32_t frameTicks = SDL_GetTicks() - _startTics; 1000 / _maxFPS > frameTicks)
    {
        SDL_Delay(1000 / _maxFPS - frameTicks);
    }

    return _fps;
}
