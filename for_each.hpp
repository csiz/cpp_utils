//          Copyright csiz.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tuple>
#include <type_traits>
#include <utility>

namespace detail_for_each {
  namespace detail_unpack_call {

    template<typename Func, typename Tuple, size_t ... S>
    auto unpack_call_impl(Func && func, Tuple && tuple, std::index_sequence<S ...>) 
      -> decltype(std::forward<Func>(func)(std::get<S>(std::forward<Tuple>(tuple)) ...))
    {
      return std::forward<Func>(func)(std::get<S>(std::forward<Tuple>(tuple)) ...);
    }

    template<typename Func, typename Tuple, size_t size = std::tuple_size<typename std::remove_reference<Tuple>::type>::value>
    auto unpack_call_sfinae(Func && func, Tuple && tuple)
      -> decltype(unpack_call_impl(std::forward<Func>(func), std::forward<Tuple>(tuple), std::make_index_sequence<size>()))
    {
      return unpack_call_impl(std::forward<Func>(func), std::forward<Tuple>(tuple), std::make_index_sequence<size>());
    }
  }

  /** Unpack tuple elements and use them as parameters for function. */
  template<typename Func, typename Tuple>
  auto unpack_call(Func && func, Tuple && tuple) 
    -> decltype(detail_unpack_call::unpack_call_sfinae(std::forward<Func>(func), std::forward<Tuple>(tuple)))
  {
    return detail_unpack_call::unpack_call_sfinae(std::forward<Func>(func), std::forward<Tuple>(tuple));
  }

  namespace detail_call {  
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

  /** Call function using either a simple parameter or a tuple of parameters. */
  template<typename Func, typename Param>
  auto call(Func && func, Param && param) 
    -> decltype(detail_call::call_impl(std::forward<Func>(func), std::forward<Param>(param)))
  {
    return detail_call::call_impl(std::forward<Func>(func), std::forward<Param>(param));
  }
}

/** Apply function to each element in range. 
  
  If the range elements are tuples unpack them as function parameters.
*/
template<typename Range, typename Func>
void for_each(Range && range, Func && func){
  for (auto && element : range){
    using Element = decltype(element);
    detail_for_each::call(std::forward<Func>(func), std::forward<Element>(element));
  }
}
