#include "simulation.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

Simulation::Simulation(std::unique_ptr<Algorithm> alg) : algorithm_(std::move(alg))
{
}

void Simulation::setThreshold(int threshold)
{
  thresholds_.push_back(threshold);
  results_.push_back(-1);
}

void Simulation::add(std::unique_ptr<ICollector> c)
{
  collectors_.push_back(std::move(c));
}

void Simulation::run()
{
  int resultsFound = 0;
  for(int counter = 0;counter != 10; ++counter)
    {
      int thresholdCount = 0;
      int current = algorithm_->run();
      for ( auto& collector : collectors_)
	{
	  collector->run(counter, current);
	}
    }
  collectorItr_ = collectors_.begin();
}

int Simulation::reportTime()
{
  return (*(collectorItr_++))->getResult();
}
