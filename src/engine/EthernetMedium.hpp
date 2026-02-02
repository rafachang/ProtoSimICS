#pragma once
#include <vector>
#include <cstdint>
#include <functional>

class SimulatedSocket;

class EthernetMedium {
public:
    explicit EthernetMedium(uint64_t latency);

    void transmit(
        SimulatedSocket* from,
        const std::vector<uint8_t>& data,
        std::function<void()> delivery
    );

private:
    uint64_t latency;
};
