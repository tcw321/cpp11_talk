#include "simulation.hpp"

Simulation::Simulation(Ramp ramp) : ramp_(ramp)
{
}

void Simulation::setThreshold(int threshold)
{
  thresholds_.push_back(threshold);
}

void Simulation::run()
{
  for(int counter = 0;; ++counter)
    {
      int current = ramp_.run();
      for (Thresholds::iterator itr = thresholds_.begin();
	   itr != thresholds_.end();  ++itr)
	{
	  if (current == *itr)
	    {
	      results_.push_back(counter);
	    }
	}
      if (results_.size() == thresholds_.size())
	break;
    }
  resultsItr_ = results_.begin();
}

int Simulation::reportTime()
{
  return *(resultsItr_++);
}
