#pragma once
#include <vector>
#include <cstdint>
#include <functional>

class SimulatedSocket;
class EventQueue;
class SimulationClock;

class EthernetMedium {
public:
    explicit EthernetMedium(uint64_t latency, EventQueue& eventQueue, SimulationClock& simulationClock);

    void transmit(
        SimulatedSocket* from,
        const std::vector<uint8_t>& data,
        std::function<void()> delivery
    );

private:
    uint64_t latency;
    EventQueue& eventQueue;
    SimulationClock& simulationClock;
};
