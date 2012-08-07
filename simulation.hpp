#ifndef simulation_hpp
#define simulation_hpp

#include "algorithm.hpp"
#include "icollector.hpp"

#include <vector>

class Simulation
{
public:
  Simulation(std::shared_ptr<Algorithm> alg);
  
  void setThreshold(int threshold);
  void add(std::shared_ptr<ICollector> c);

  void run();
  int reportTime();
private:
  std::shared_ptr<Algorithm> algorithm_;
  typedef std::vector<int> Thresholds;
  Thresholds thresholds_;
  
  typedef std::vector<int> Results;
  Results results_;
  Results::const_iterator resultsItr_;
  typedef std::vector<std::shared_ptr<ICollector>> CollectorArray;
  CollectorArray collectors_;
  CollectorArray::iterator collectorItr_;  
};

#endif
