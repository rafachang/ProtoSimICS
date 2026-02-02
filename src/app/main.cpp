#include "engine/EthernetMedium.hpp"
#include "engine/EventQueue.hpp"
#include "engine/Node.hpp"
#include "engine/SimulationClock.hpp"
#include <iostream>
#include <windows.h>

SimulationClock simulationClock;
EventQueue eventQueue;

int main() {
  SetConsoleOutputCP(CP_UTF8); // Define a saída do console para UTF-8
  SetConsoleCP(CP_UTF8);       // Define a entrada do console para UTF-8

  EthernetMedium eth(10, eventQueue, simulationClock);

  Node plc("PLC", eth);
  Node rtu("RTU", eth);

  plc.getSocket().onReceive([](const std::vector<uint8_t> &data) {
    std::cout << "PLC recebeu " << data.size() << " bytes\n";
  });

  rtu.getSocket().onReceive([](const std::vector<uint8_t> &data) {
    std::cout << "RTU recebeu " << data.size() << " bytes\n";
  });

  std::cout << "Iniciando simulação...\n";

  plc.getSocket().send({0x10, 0x20, 0x30, 0x40});
  rtu.getSocket().send({0x10, 0x20});
  // plc.getSocket().send({0x01, 0x02, 0x03, 0x21});

  while (!eventQueue.empty()) {
    auto e = eventQueue.pop();
    simulationClock.advance(e.time);
    e.action();
  }

  return 0;
}
