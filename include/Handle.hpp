#ifndef _INCLUDE_HANDLE_HPP_
#define _INCLUDE_HANDLE_HPP_

#include <memory>

template<typename T>
class Handle {
public:
  using element_type = T;

  Handle(std::shared_ptr<T> ptr = nullptr) : _ptr(ptr) {}

  T* operator->() const { return _ptr.get(); }
  T& operator*() const { return *_ptr; }
  T* get() const { return _ptr.get(); }

  operator bool() const { return _ptr != nullptr; }

  void reset(std::shared_ptr<T> ptr = nullptr) { _ptr = ptr; }
  std::shared_ptr<T> release() { return std::move(_ptr); }

private:
  std::shared_ptr<T> _ptr;
};

template<typename T, typename U>
bool operator==(const Handle<T>& lhs, const Handle<U>& rhs) {
  return lhs._ptr == rhs._ptr;
}

template<typename T, typename U>
bool operator!=(const Handle<T>& lhs, const Handle<U>& rhs) {
  return lhs._ptr != rhs._ptr;
}

template<typename T, typename U>
bool operator<(const Handle<T>& lhs, const Handle<U>& rhs) {
  return lhs._ptr < rhs._ptr;
}

template<typename T, typename U>
bool operator<=(const Handle<T>& lhs, const Handle<U>& rhs) {
  return lhs._ptr <= rhs._ptr;
}

template<typename T, typename U>
bool operator>(const Handle<T>& lhs, const Handle<U>& rhs) {
  return lhs._ptr > rhs._ptr;
}

template<typename T, typename U>
bool operator>=(const Handle<T>& lhs, const Handle<U>& rhs) {
  return lhs._ptr >= rhs._ptr;
}

#endif
