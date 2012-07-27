#include "simulation.hpp"

Simulation::Simulation(Ramp ramp) : ramp_(ramp)
{
}

void Simulation::setThreshold(int threshold)
{
  threshold_ = threshold;
}

int Simulation::reportTime()
{
  for(int counter = 0;; ++counter)
    {
      if (ramp_.run() >= threshold_)
	return counter;
    }
}
