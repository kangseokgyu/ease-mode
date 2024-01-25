#pragma once

#include <memory>
#include <mutex>

namespace ease {
namespace details {

struct null_mutex {
  void lock() {}
  void unlock() noexcept {}
  bool try_lock() { return true; }
};

struct ease_mutex {
  using mutex_t = std::mutex;
  static std::unique_ptr<mutex_t> mutex() {
    std::unique_ptr<mutex_t> mutex_ptr(new mutex_t());
    return mutex_ptr;
  }
};

struct ease_null_mutex {
  using mutex_t = null_mutex;
  static std::unique_ptr<mutex_t> mutex() {
    std::unique_ptr<mutex_t> mutex_ptr(new mutex_t());
    return mutex_ptr;
  }
};

}; // namespace details
}; // namespace ease
