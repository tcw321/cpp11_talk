#ifndef simulation_hpp
#define simulation_hpp

#include "algorithm.hpp"
#include "collector.hpp"

#include <vector>

class Simulation
{
public:
  Simulation(std::shared_ptr<Algorithm> alg);
  
  void setThreshold(int threshold);
  void add(Collector c);

  void run();
  int reportTime();
private:
  std::shared_ptr<Algorithm> algorithm_;
  typedef std::vector<int> Thresholds;
  Thresholds thresholds_;
  
  typedef std::vector<int> Results;
  Results results_;
  Results::const_iterator resultsItr_;
  typedef std::vector<Collector> CollectorArray;
  CollectorArray collectors_;
  CollectorArray::iterator collectorItr_;  
};

#endif
