#pragma once
#include <cstdint>

class SimulationClock {
public:
    SimulationClock();
    void advance(uint64_t newTime);
    uint64_t now() const;

private:
    uint64_t currentTime = 0;
};
