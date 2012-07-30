#include "simulation.hpp"
#include <algorithm>

Simulation::Simulation(Ramp ramp) : ramp_(ramp)
{
}

void Simulation::setThreshold(int threshold)
{
  thresholds_.push_back(threshold);
  results_.push_back(-1);
}

void Simulation::run()
{
  int resultsFound = 0;
  for(int counter = 0;; ++counter)
    {
      int thresholdCount = 0;
      int current = ramp_.run();
      std::for_each(thresholds_.begin(), thresholds_.end(),
	       [=, &resultsFound, &thresholdCount](int value){
	          if (current == value)
	          {
	            results_[thresholdCount] = counter;
                    ++resultsFound;
	          }
                  ++thresholdCount;
		    });
      if (thresholds_.size() == resultsFound)
	break;
    }
  resultsItr_ = results_.begin();
}

int Simulation::reportTime()
{
  return *(resultsItr_++);
}
