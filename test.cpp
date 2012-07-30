
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ramp.hpp"
#include "simulation.hpp"

TEST_CASE("hookup", "hookup")
{
  REQUIRE(0==0);

}

TEST_CASE("ramp", "create ramp function")
{
  Ramp ramp;
  REQUIRE(ramp.run() == 0);
  REQUIRE(ramp.run() == 10);
  REQUIRE(ramp.run() == 20);
  REQUIRE(ramp.run() == 30);
  REQUIRE(ramp.run() == 40);
}

TEST_CASE("simulation", "create simulation")
{
  Ramp ramp;
  Simulation simulation(ramp);
  simulation.setThreshold(30);
  simulation.run();
  REQUIRE(simulation.reportTime() == 3);
}

TEST_CASE("secondthreshold", "second threshold")
{
  Ramp ramp;
  Simulation simulation(ramp);
  simulation.setThreshold(30);
  simulation.setThreshold(40);
  simulation.run();
  REQUIRE(simulation.reportTime() == 3);
  REQUIRE(simulation.reportTime() == 4);
}
