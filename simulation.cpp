#include "simulation.hpp"

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
      for (Thresholds::iterator itr = thresholds_.begin();
	   itr != thresholds_.end();  ++itr)
	{
	  if (current == *itr)
	    {
	      results_[thresholdCount] = counter;
              ++resultsFound;
	    }
          ++thresholdCount;
	}
      if (thresholds_.size() == resultsFound)
	break;
    }
  resultsItr_ = results_.begin();
}

int Simulation::reportTime()
{
  return *(resultsItr_++);
}
