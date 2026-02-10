#pragma once
#include <cstdint>
#include <functional>
#include <vector>


class SimulatedSocket;
class EventQueue;
class SimulationClock;

class EthernetMedium {
public:
  explicit EthernetMedium(uint64_t latency, EventQueue &eventQueue,
                          SimulationClock &simulationClock);

  void addSocket(SimulatedSocket *socket);
  const std::vector<SimulatedSocket *> &getSockets() const;
  
  void transmitBroadcast(SimulatedSocket *from,
                         const std::vector<uint8_t> &data,
                         std::function<void()> delivery);
  void transmitMulticast(SimulatedSocket *from,
                         const std::vector<uint8_t> &data,
                         std::vector<SimulatedSocket *> to,
                         std::function<void()> delivery);
  void transmitUnicast(SimulatedSocket *from,
                         const std::vector<uint8_t> &data,
                         SimulatedSocket *to,
                         std::function<void()> delivery);

  // Simulate loss of packets
  bool shouldDrop();

private:
  uint64_t latency;
  EventQueue &eventQueue;
  SimulationClock &simulationClock;
  std::vector<SimulatedSocket *> sockets;
};
