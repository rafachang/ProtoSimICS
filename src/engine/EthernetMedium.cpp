#include "engine/EthernetMedium.hpp"
#include "engine/Event.hpp"
#include "engine/EventQueue.hpp"
#include "engine/SimulationClock.hpp"
#include <stdio.h>


EthernetMedium::EthernetMedium(uint64_t latency, EventQueue &eventQueue,
                               SimulationClock &simulationClock)
    : latency(latency), eventQueue(eventQueue),
      simulationClock(simulationClock) {}

void EthernetMedium::transmit(SimulatedSocket *from,
                              const std::vector<uint8_t> &data,
                              std::function<void()> delivery) {
  eventQueue.push(Event{simulationClock.now() + latency, delivery});
}