#include "EventQueue.hpp"

EventQueue::EventQueue() {}
void EventQueue::push(const Event &e) { queue.push(e); }

bool EventQueue::empty() const { return queue.empty(); }

Event EventQueue::pop() {
  Event e = queue.top();
  queue.pop();
  return e;
}