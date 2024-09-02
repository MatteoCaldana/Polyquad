#pragma once

#include "dispatcher.hpp"

namespace polyquad {
  struct ShapeDispatcherMap {
    static std::map<shape_key, process_fn> map;
  };
}
