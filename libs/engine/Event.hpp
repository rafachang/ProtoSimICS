#pragma once
#include <cstdint>
#include <functional>

struct Event {
  uint64_t time;
  std::function<void()> action;

  Event(uint64_t time, std::function<void()> action);
  bool operator>(const Event &other) const;
};
