#ifndef simulation_hpp
#define simulation_hpp

#include "ramp.hpp"

class Simulation
{
public:
  Simulation(Ramp ramp);
  
  void setThreshold(int threshold);
  int reportTime();
private:
  Ramp ramp_;
  int threshold_;
};

#endif
