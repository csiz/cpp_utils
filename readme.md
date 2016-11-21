Utility library
===============

magic::for_each
---------------

For each loop that can also iterate over maps nicely.

Iterate over vectors:
    
    vector<int> v = {1, 2, 3};
    for_each(v, [](int x){
      cout << x << endl;
    });

Iterate over maps, naming the keys and values:
  
    map<string, int> m = {{"one", 1}, {"two", 2}};
    for_each(m, [](auto key, auto value){
      cout << key << " " << value << endl;
    });

