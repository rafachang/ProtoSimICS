#include "Node.hpp"

Node::Node(const std::string &name, EthernetMedium &medium)
    : name(name), socket(medium) {}

SimulatedSocket &Node::getSocket() { return socket; }
const std::string &Node::getName() const { return name; }