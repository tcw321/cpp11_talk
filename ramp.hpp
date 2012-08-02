#ifndef ramp_hpp
#define ramp_hpp

#include "algorithm.hpp"

class Ramp : public Algorithm
{
public:
  Ramp();
  int run();

private:
  int initialValue_;
};

#endif // ramp_hpp
