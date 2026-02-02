#include "SimulationClock.hpp"

SimulationClock::SimulationClock() : currentTime(0) {}

void SimulationClock::advance(uint64_t newTime) { currentTime = newTime; }

uint64_t SimulationClock::now() const { return currentTime; }
