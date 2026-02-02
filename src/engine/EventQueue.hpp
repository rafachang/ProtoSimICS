#pragma once
#include "Event.hpp"
#include <queue>


class EventQueue {
public:
  EventQueue();
  void push(const Event &e);

  bool empty() const;

  Event pop();

private:
  std::priority_queue<Event, std::vector<Event>, std::greater<Event>> queue;
};
