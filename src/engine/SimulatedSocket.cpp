#include "engine/SimulatedSocket.hpp"
#include "engine/EthernetMedium.hpp"
#include "engine/Node.hpp"
#include <iostream>
using namespace std;

SimulatedSocket::SimulatedSocket(EthernetMedium &medium, Node &parentNode) : medium(medium), parentNode(parentNode) {
  medium.addSocket(this);
}

void SimulatedSocket::onReceive(
    std::function<void(const std::vector<uint8_t> &)> cb) {
  receiveCallback = cb;
}

void SimulatedSocket::sendBroadcast(const std::vector<uint8_t> &data) {

  medium.transmitBroadcast(this, data, []() {});
}

void SimulatedSocket::sendMulticast(const std::vector<uint8_t> &data,
                                    const std::vector<SimulatedSocket *> &to) {
  medium.transmitMulticast(this, data, to, []() {});
}

void SimulatedSocket::sendUnicast(const std::vector<uint8_t> &data,
                                  SimulatedSocket *to) {
  medium.transmitUnicast(this, data, to, []() {});
}

void SimulatedSocket::deliver(const std::vector<uint8_t> &data) {
  if (receiveCallback) {
    receiveCallback(data);
  }
  else {
    std::cout << "" << parentNode.getName() << " recebeu " << data.size() << " bytes\n";
  }
}