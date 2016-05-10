#include "for_each.c++14.hpp"

#include <vector>
#include <iostream>
#include <map>

using namespace std;

int main(){

  vector<int> v = {1, 2, 3};
  map<string, int> m = {{"one", 1}, {"two", 2}};

  // Works as expected for a simple vector.
  for_each(v, [](int x){
    cout << x << endl;
  });

  // More boring behaviour; iterate over a map.
  for_each(m, [](pair<string, int> const& p){
    cout << p.first << " " << p.second << endl;
  });

  // This is the fancy part! Name what we're iterating over straight away.
  for_each(m, [](auto key, auto value){
    cout << key << " " << value << endl;
  });

}