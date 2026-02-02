#include "engine/SimulatedSocket.hpp"
#include "engine/EthernetMedium.hpp"

SimulatedSocket::SimulatedSocket(EthernetMedium &medium) : medium(medium) {
  medium.addSocket(this);
}

void SimulatedSocket::onReceive(
    std::function<void(const std::vector<uint8_t> &)> cb) {
  receiveCallback = cb;
}

void SimulatedSocket::send(const std::vector<uint8_t>& data) {
    medium.transmit(this, data, []() {});
}

void SimulatedSocket::deliver(const std::vector<uint8_t> &data) {
  if (receiveCallback)
    receiveCallback(data);
}