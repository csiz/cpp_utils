#include "unpack_call.hpp"

#include <iostream>
#include <string>

int main(){
  auto func = [](int a, std::string s){
    std::cout << a << " " << s << std::endl;
  };

  auto args = std::make_pair(1, "one");

  csiz::unpack_call(func, args);
}
