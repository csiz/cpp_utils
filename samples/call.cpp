#include "magic/call.hpp"

#include <iostream>
#include <string>

int main(){
  auto func = [](int, std::string){
    std::cout << "called with 2 parameters" << std::endl;
  };

  auto func_pair = [](std::pair<int, std::string>){
    std::cout << "called with a pair as parameter" << std::endl;
  };

  auto args = std::make_pair(1, "one");

  magic::call(func, args);
  magic::call(func_pair, args);
}
