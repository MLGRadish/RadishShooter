#pragma once
#include <cstdint>

class FpsLimiter {
public:
    FpsLimiter();

    void init(uint32_t maxFPS);
    void setMaxFPS(uint32_t maxFPS);
    void begin();

    uint32_t end();

private:
    uint32_t _fps;
    uint32_t _maxFPS;
    uint32_t _frameTime;

    void _calculateFPS();

    unsigned int _startTics;
};
