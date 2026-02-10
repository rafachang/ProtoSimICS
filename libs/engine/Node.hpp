#pragma once
#include "SimulatedSocket.hpp"
#include "EthernetMedium.hpp"
#include "debug/MessageLog.hpp"
#include <string>

class EventQueue;
class SimulationClock;

class Node {
public:
  Node(const std::string &name, EthernetMedium &medium, EventQueue &eventQueue,
       SimulationClock &simulationClock);

  SimulatedSocket &getSocket();

  const std::string &getName() const;

  void sendBroadcast(const std::vector<uint8_t> &data);
  void sendMulticast(const std::vector<uint8_t> &data, const std::vector<SimulatedSocket *> &to);
  void sendUnicast(const std::vector<uint8_t> &data, SimulatedSocket *to);

  void printLogs();

private:
  std::string name;
  SimulatedSocket socket;
  EventQueue &eventQueue;
  SimulationClock &simulationClock;
  std::vector<MessageLog> logs;
};
