#include <iostream>
#include "engine/SimulationClock.hpp"
#include "engine/EventQueue.hpp"
#include "engine/EthernetMedium.hpp"
#include "engine/Node.hpp"

SimulationClock simulationClock;
EventQueue eventQueue;

int main() {
    EthernetMedium eth(10, eventQueue, simulationClock);

    Node plc("PLC", eth);

    plc.getSocket().onReceive([](const std::vector<uint8_t>& data) {
        std::cout << "PLC recebeu " << data.size() << " bytes\n";
    });

    plc.getSocket().send({0x01, 0x02, 0x03});

    while (!eventQueue.empty()) {
        auto e = eventQueue.pop();
        simulationClock.advance(e.time);
        e.action();
    }

    return 0;
}
