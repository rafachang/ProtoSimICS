#include "engine/EthernetMedium.hpp"
#include "engine/Event.hpp"
#include "engine/EventQueue.hpp"
#include "engine/Node.hpp"
#include "engine/SimulatedSocket.hpp"
#include "engine/SimulationClock.hpp"
#include <iostream>
#include <random>
#include <stdio.h>

using namespace std;

#pragma region Simulate random packet loss

static std::mt19937 rng{std::random_device{}()};
static std::uniform_real_distribution<double> dist(0.0, 1.0);

// Ajuste aqui a probabilidade de perda (ex: 0.1 = 10%)
static constexpr double LOSS_PROBABILITY = 0.01;
#pragma endregion

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

#pragma region Transmit

void EthernetMedium::transmitBroadcast(SimulatedSocket *from,
                                       const std::vector<uint8_t> &data,
                                       std::function<void()>) {
  for (auto *sock : sockets) {
    if (sock == from)
      continue;
    if (shouldDrop()) {
      std::cout << "Packet lost in broadcast from "
                << from->getParentNode().getName() << "\n";
      return;
    }
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
    if (shouldDrop()) {
      std::cout << "Packet lost in multicast from "
                << from->getParentNode().getName() << " to ";
      for (size_t i = 0; i < to.size(); ++i) {
        std::cout << to[i]->getParentNode().getName();
        if (i + 1 < to.size())
          std::cout << ", ";
      }
      std::cout << "\n";
      return;
    }
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
      if (shouldDrop()) {
        std::cout << "Packet lost in unicast from "
                  << from->getParentNode().getName() << " to "
                  << sock->getParentNode().getName() << "\n";
        return;
      }
      eventQueue.push(Event(simulationClock.now() + latency,
                            [sock, data]() { sock->deliver(data); }));
      break;
    }
  }
}

#pragma endregion

bool EthernetMedium::shouldDrop() { return dist(rng) < LOSS_PROBABILITY; }