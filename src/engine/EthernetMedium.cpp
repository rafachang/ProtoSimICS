#include "EthernetMedium.hpp"
#include <stdio.h>

EthernetMedium::EthernetMedium(uint64_t latency) : latency(latency) {}
// void EthernetMedium::transmit(SimulatedSocket *from,
//                               const std::vector<uint8_t> &data,
//                               std::function<void()> delivery) {
//   // Transmission logic would go here.
//   // For now, we just call the delivery callback immediately.
//   //delivery();
//   printf("EthernetMedium::transmit called with data size: %zu\n", data.size());
// }