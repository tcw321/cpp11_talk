#ifndef simulation_hpp
#define simulation_hpp

#include "ramp.hpp"

#include <vector>

class Simulation
{
public:
  Simulation(Ramp ramp);
  
  void setThreshold(int threshold);
  void run();
  int reportTime();
private:
  Ramp ramp_;
  typedef std::vector<int> Thresholds;
  Thresholds thresholds_;
  
  typedef std::vector<int> Results;
  Results results_;
  Results::const_iterator resultsItr_;
  
};

#endif
