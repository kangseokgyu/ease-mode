#pragma once

#include <chrono>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

#include "ease-mode/details/mutex.hpp"

namespace ease {

template <class T, class Mutex> //
class mode {
public:
  using mutex_t = typename Mutex::mutex_t;
  mode<T, Mutex>() : _m(Mutex::mutex()) {}
  ~mode() = default;

  mode(const mode &other) = delete;
  mode(mode &&other) = delete;

  mode &operator=(const mode &other) = delete;
  mode &operator=(mode &&other) = delete;

  bool change(const T &t) {
    std::lock_guard<mutex_t> guard(*_m);
    if (_cur_mode != t) {
      _cur_mode = t;
      _changed = true;
      return true;
    }
    return false;
  }

  std::pair<bool, T> check() {
    std::lock_guard<mutex_t> guard(*_m);
    if (_changed) {
      _changed = false;
      return std::make_pair(true, _cur_mode);
    }
    return std::make_pair(false, _cur_mode);
  }

private:
  std::unique_ptr<mutex_t> _m;
  bool _changed = false;
  T _cur_mode = T::defval;
};

template <class T> //
using mode_mt = mode<T, details::ease_mutex>;
template <class T> //
using mode_st = mode<T, details::ease_null_mutex>;

}; // namespace ease
