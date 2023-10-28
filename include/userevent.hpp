#ifndef INCLUDE_USEREVENT_HPP_
#define INCLUDE_USEREVENT_HPP_

#include <cstdint>

namespace userevent {
  enum class Code {
    quit,
  };

  void trigger(Code code, void* data1, void* data2);
}  // namespace userevent

#endif  // INCLUDE_USEREVENT_HPP_
