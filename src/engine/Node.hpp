#pragma once
#include "SimulatedSocket.hpp"
#include "EthernetMedium.hpp"
#include <string>

class Node {
public:
  Node(const std::string &name, EthernetMedium &medium);

  SimulatedSocket &getSocket();

  const std::string &getName() const;

private:
  std::string name;
  SimulatedSocket socket;
};
