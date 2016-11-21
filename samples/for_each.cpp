#include "magic/for_each.hpp"

#include <vector>
#include <iostream>
#include <map>

int main(){

  std::vector<int> v = {1, 2, 3};
  std::map<std::string, int> m = {{"one", 1}, {"two", 2}};

  // Works as expected for a simple vector.
  magic::for_each(v, [](int x){
    std::cout << x << std::endl;
  });

  // More boring behaviour; iterate over a map.
  magic::for_each(m, [](std::pair<std::string, int> const& p){
    std::cout << p.first << " " << p.second << std::endl;
  });

  // This is the fancy part! Name what we're iterating over straight away.
  magic::for_each(m, [](auto key, auto value){
    std::cout << key << " " << value << std::endl;
  });

}
