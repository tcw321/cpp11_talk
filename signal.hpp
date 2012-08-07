#ifndef signal_hpp
#define signal_hpp

#include <vector>

#include "algorithm.hpp"

class Signal : public Algorithm
{
public:
  Signal(const std::vector<int> &values);
  int run();
private:
  std::vector<int> values_;
  std::vector<int>::iterator itr;
};

#endif

