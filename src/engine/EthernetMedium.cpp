#include "engine/EthernetMedium.hpp"
#include "engine/Event.hpp"
#include "engine/EventQueue.hpp"
#include "engine/SimulatedSocket.hpp"
#include "engine/SimulationClock.hpp"
#include <stdio.h>

EthernetMedium::EthernetMedium(uint64_t latency, EventQueue &eventQueue,
                               SimulationClock &simulationClock)
    : latency(latency), eventQueue(eventQueue),
      simulationClock(simulationClock) {}

void EthernetMedium::addSocket(SimulatedSocket *socket) {
  sockets.push_back(socket);
}

const std::vector<SimulatedSocket *> &EthernetMedium::getSockets() const {
  return sockets;
}

void EthernetMedium::transmitBroadcast(SimulatedSocket *from,
                                       const std::vector<uint8_t> &data,
                                       std::function<void()>) {
  for (auto *sock : sockets) {
    if (sock == from)
      continue;
    eventQueue.push(Event(simulationClock.now() + latency,
                          [sock, data]() { sock->deliver(data); }));
  }
}

void EthernetMedium::transmitMulticast(SimulatedSocket *from,
                                       const std::vector<uint8_t> &data,
                                       std::vector<SimulatedSocket *> to,
                                       std::function<void()>) {
  for (auto *sock : sockets) {
    if (sock == from)
      continue;
    for (auto *target : to) {
      if (sock == target) {
        eventQueue.push(Event(simulationClock.now() + latency,
                              [sock, data]() { sock->deliver(data); }));
        break;
      }
    }
  }
}

void EthernetMedium::transmitUnicast(SimulatedSocket *from,
                                     const std::vector<uint8_t> &data,
                                     SimulatedSocket *to,
                                     std::function<void()>) {
  for (auto *sock : sockets) {
    if (sock == to) {
      eventQueue.push(Event(simulationClock.now() + latency,
                            [sock, data]() { sock->deliver(data); }));
      break;
    }
  }
}