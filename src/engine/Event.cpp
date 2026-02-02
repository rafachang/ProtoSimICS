#include "Event.hpp"

Event::Event(uint64_t t, std::function<void()> a) : time(t), action(a) {}

bool Event::operator>(const Event &other) const { return time > other.time; }