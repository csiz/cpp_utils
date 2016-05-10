#pragma once

#include "unpack_call.hpp"

namespace csiz {
  namespace detail {
    template<typename Func, typename Param>
    auto call_impl(Func && func, Param && param) 
      -> decltype(std::forward<Func>(func)(std::forward<Param>(param)))
    {
      return std::forward<Func>(func)(std::forward<Param>(param));
    }

    template<typename Func, typename Param>
    auto call_impl(Func && func, Param && param) 
      -> decltype(unpack_call(std::forward<Func>(func), std::forward<Param>(param)))
    {
      return unpack_call(std::forward<Func>(func), std::forward<Param>(param));
    }
  }

  /** Call function using either a simple parameter or a tuple of parameters.

    @param func Function to call.
    @param param Parameters to pass to the function. First try to simply call
    the function with the parameter, otherwise unpack the parameters and call it.

  */
  template<typename Func, typename Param>
  auto call(Func && func, Param && param) 
    -> decltype(detail::call_impl(std::forward<Func>(func), std::forward<Param>(param)))
  {
    return detail::call_impl(std::forward<Func>(func), std::forward<Param>(param));
  }
}
