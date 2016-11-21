#pragma once

#include <tuple>
#include <utility>

namespace magic {
  namespace detail {
    // Call function with arguments from tuple indexed by S.
    template<typename Func, typename Tuple, size_t ... S>
    auto unpack_call_impl(Func && func, Tuple && tuple, std::index_sequence<S ...>) 
      -> decltype(std::forward<Func>(func)(std::get<S>(std::forward<Tuple>(tuple)) ...))
    {
      return std::forward<Func>(func)(std::get<S>(std::forward<Tuple>(tuple)) ...);
    }

    // We need to add size into the declaration somewhere so we can use SFINAE.
    template<typename Func, typename Tuple, size_t size = std::tuple_size<typename std::remove_reference<Tuple>::type>::value>
    auto unpack_call_sfinae(Func && func, Tuple && tuple)
      -> decltype(unpack_call_impl(std::forward<Func>(func), std::forward<Tuple>(tuple), std::make_index_sequence<size>()))
    {
      return unpack_call_impl(std::forward<Func>(func), std::forward<Tuple>(tuple), std::make_index_sequence<size>());
    }
  }

  /** Unpack tuple elements and use them as parameters for function. 
    
    @param func Function to call.
    @param tuple Arguments to call function with.
  */
  template<typename Func, typename Tuple>
  auto unpack_call(Func && func, Tuple && tuple) 
    -> decltype(detail::unpack_call_sfinae(std::forward<Func>(func), std::forward<Tuple>(tuple)))
  {
    return detail::unpack_call_sfinae(std::forward<Func>(func), std::forward<Tuple>(tuple));
  }
}
