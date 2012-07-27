
#include "ramp.hpp"

Ramp::Ramp()
{
  initialValue_ = 0;
}

int Ramp::run()
{
  int current = initialValue_;
  initialValue_ += 10;
  return current;
}
