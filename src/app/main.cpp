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

  Node plc("PLC", eth, eventQueue, simulationClock);
  Node rtu1("RTU1", eth, eventQueue, simulationClock);
  Node rtu2("RTU2", eth, eventQueue, simulationClock);
  Node rtu3("RTU3", eth, eventQueue, simulationClock);
  Node rtu4("RTU4", eth, eventQueue, simulationClock);

  plc.getSocket().onReceive([](const std::vector<uint8_t> &data) {
    std::cout << "PLC recebeu " << data.size() << " bytes\n";
  });

  rtu1.getSocket().onReceive([](const std::vector<uint8_t> &data) {
    std::cout << "RTU1 recebeu " << data.size() << " bytes\n";
  });

  rtu2.getSocket().onReceive([](const std::vector<uint8_t> &data) {
    std::cout << "RTU2 recebeu " << data.size() << " bytes\n";
  });

  rtu3.getSocket().onReceive([](const std::vector<uint8_t> &data) {
    std::cout << "RTU3 recebeu " << data.size() << " bytes\n";
  });

  rtu4.getSocket().onReceive([](const std::vector<uint8_t> &data) {
    std::cout << "RTU4 recebeu " << data.size() << " bytes\n";
  });

  std::cout << "Iniciando simulação...\n";

  plc.sendBroadcast({0x10});
  rtu1.sendUnicast({0x20, 0x21}, &plc.getSocket());
  rtu2.sendMulticast({0x30, 0x31, 0x32}, {&plc.getSocket(), &rtu3.getSocket()});

  plc.printLogs();
  rtu1.printLogs();
  rtu2.printLogs();
  rtu3.printLogs();
  rtu4.printLogs();

  while (!eventQueue.empty()) {
    auto e = eventQueue.pop();
    simulationClock.advance(e.time);
    e.action();
  }

  return 0;
}
