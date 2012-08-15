#include "simulation.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

Simulation::Simulation(std::shared_ptr<Algorithm> alg) : algorithm_(alg), runLength_(10)
{
}

void Simulation::setThreshold(int threshold)
{
  thresholds_.push_back(threshold);
  results_.push_back(-1);
}

void Simulation::add(std::shared_ptr<ICollector> c)
{
  collectors_.push_back(c);
}

void Simulation::run()
{
  using namespace std::placeholders;
  for(int counter = 0;counter != runLength_; ++counter)
    {
      int current = algorithm_->run();
      std::for_each ( collectors_.begin(), collectors_.end(), std::bind(&ICollector::run, _1, counter, current));
    }
  collectorItr_ = collectors_.begin();
}

int Simulation::reportTime()
{
  return (*(collectorItr_++))->getResult();
}
