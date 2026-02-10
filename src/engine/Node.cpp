#include "engine/Node.hpp"
#include "debug/MessageLog.hpp"
#include "engine/EventQueue.hpp"
#include "engine/SimulationClock.hpp"

#include <iostream>

using namespace std;

Node::Node(const std::string &name, EthernetMedium &medium,
           EventQueue &eventQueue, SimulationClock &simulationClock)
    : name(name), medium(medium), socket(medium, *this), eventQueue(eventQueue),
      simulationClock(simulationClock) {}

SimulatedSocket &Node::getSocket() { return socket; }
const std::string &Node::getName() const { return name; }

void Node::printLogs() {
    for (const auto& log : logs) {
        std::cout << log.timestamp << " | "
                  << log.type << " | "
                  << log.sender << " -> ";

        std::cout << "[";
        for (size_t i = 0; i < log.receiver.size(); ++i) {
            std::cout << log.receiver[i];
            if (i + 1 < log.receiver.size())
                std::cout << ", ";
        }
        std::cout << "]";

        std::cout << " | " << log.size << " bytes | "
                  << log.deliveryTime << " ms\n";
    }
}


void Node::sendBroadcast(const std::vector<uint8_t> &data) {
  MessageLog log;
  log.timestamp = simulationClock.now();
  log.type = "sent broadcast";
  log.sender = &socket;
  log.receiver = medium.getSockets(); // Placeholder, to be updated with actual receivers
  log.size = data.size();
  log.deliveryTime = 0; // To be updated upon delivery
  logs.push_back(log);
  socket.sendBroadcast(data);
}

void Node::sendMulticast(const std::vector<uint8_t> &data,
                         const std::vector<SimulatedSocket *> &to) {
  MessageLog log;
  log.timestamp = simulationClock.now();
  log.type = "sent multicast";
  log.sender = &socket;
  log.receiver = to; // Placeholder, to be updated with actual receivers
  log.size = data.size();
  log.deliveryTime = 0; // To be updated upon delivery
  logs.push_back(log);
  socket.sendMulticast(data, to);
}

void Node::sendUnicast(const std::vector<uint8_t> &data, SimulatedSocket *to) {
  MessageLog log;
  log.timestamp = simulationClock.now();
  log.type = "sent unicast";
  log.sender = &socket;
  log.receiver = {to}; // Placeholder, to be updated with actual receivers
  log.size = data.size();
  log.deliveryTime = 0; // To be updated upon delivery
  logs.push_back(log);
  socket.sendUnicast(data, to);
}