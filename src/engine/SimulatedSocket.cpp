#include "SimulatedSocket.hpp"

SimulatedSocket::SimulatedSocket(EthernetMedium &medium) : medium(medium) {}

// SimulatedSocket::send(const std::vector<uint8_t>& data) {
//     medium.transmit(data);
// }

void SimulatedSocket::onReceive(
    std::function<void(const std::vector<uint8_t> &)> cb) {
  receiveCallback = cb;
}

void SimulatedSocket::deliver(const std::vector<uint8_t> &data) {
  if (receiveCallback)
    receiveCallback(data);
}