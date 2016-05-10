#pragma once

#include "call.hpp"

namespace csiz {
  /** Apply function to each element in range. 
    
    If the range elements are tuples unpack them as function parameters.
  */
  template<typename Range, typename Func>
  void for_each(Range && range, Func && func){
    for (auto && element : range){
      call(std::forward<Func>(func), std::forward<decltype(element)>(element));
    }
  }
}
