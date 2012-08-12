#ifndef simulation_hpp
#define simulation_hpp

#include "algorithm.hpp"
#include "icollector.hpp"

#include <vector>

class Simulation
{
public:
  Simulation(std::unique_ptr<Algorithm> alg);
  
  void setThreshold(int threshold);
  void add(std::unique_ptr<ICollector> c);

  void run();
  int reportTime();
private:
  std::unique_ptr<Algorithm> algorithm_;
  typedef std::vector<int> Thresholds;
  Thresholds thresholds_;
  
  typedef std::vector<int> Results;
  Results results_;
  Results::const_iterator resultsItr_;
  typedef std::vector<std::unique_ptr<ICollector>> CollectorArray;
  CollectorArray collectors_;
  CollectorArray::iterator collectorItr_;  
};

#endif
