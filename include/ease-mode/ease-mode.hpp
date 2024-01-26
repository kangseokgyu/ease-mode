#pragma once

#include <memory>
#include <mutex>
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

  /**
   * @brief 모드를 변경한다.
   *
   * @param t 변경할 모드
   * @return true 변경한 경우
   * @return false 변경이 필요 없는 경우
   */
  bool change(const T &t) {
    std::lock_guard<mutex_t> guard(*_m);
    if (_cur_mode != t) {
      _cur_mode = t;
      _changed = true;
      return true;
    }
    return false;
  }

  /**
   * @brief 모드를 변경한다.
   * 락을 잡을 수 없는 경우 변경하지 않는다.
   *
   * @param t 변경할 모드
   * @return true 변경에 성공한 경우
   * @return false 변경하지 않았거나 락을 잡지 못한 경우
   */
  bool try_change(const T &t) {
    std::unique_lock<mutex_t> guard(*_m, std::try_to_lock);
    if (guard.owns_lock()) {
      if (_cur_mode != t) {
        _cur_mode = t;
        _changed = true;
        return true;
      }
    }
    return false;
  }

  /**
   * @brief 모드가 변경됐는지 확인한다.
   *
   * @return std::pair<bool, T> 변경된 모드이 있으면 true와 변경된 모드,
   * 모드가 변경되지 않았으면 false와 현재 모드
   */
  std::pair<bool, T> check() {
    std::lock_guard<mutex_t> guard(*_m);
    if (_changed) {
      _changed = false;
      return std::make_pair(true, _cur_mode);
    }
    return std::make_pair(false, _cur_mode);
  }

  /**
   * @brief mode가 변경된 것을 나중에 확인하기 위해 상태를 변경한다.
   *
   */
  void check_later() {
    std::lock_guard<mutex_t> guard(*_m);
    _changed = true;
  }

  /**
   * @brief 현재 모드를 가져온다.
   *
   * @return T 현재 모드
   */
  T get() {
    std::lock_guard<mutex_t> guard(*_m);
    return _cur_mode;
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
