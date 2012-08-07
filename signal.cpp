#include "signal.hpp"

#include <iostream>

Signal::Signal(const std::vector<int> &values) : values_(values)
{
  itr = values_.begin();
}

int Signal::run()
{
  int v = *(itr++);
  //  std::cout << v << " \n";
  return v;
}
