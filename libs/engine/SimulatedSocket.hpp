#pragma once
#include <cstdint>
#include <functional>
#include <vector>

class EthernetMedium;

class SimulatedSocket {
public:
  SimulatedSocket(EthernetMedium &medium);

  void sendBroadcast(const std::vector<uint8_t> &data);
  void sendMulticast(const std::vector<uint8_t> &data, const std::vector<SimulatedSocket *> &to);
  void sendUnicast(const std::vector<uint8_t> &data, SimulatedSocket *to);
  void onReceive(std::function<void(const std::vector<uint8_t> &)> cb);
  void deliver(const std::vector<uint8_t> &data);

private:
  EthernetMedium &medium;
  std::function<void(const std::vector<uint8_t> &)> receiveCallback;
};
