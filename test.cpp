
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
  auto ramp = std::make_shared<Ramp>();
  Simulation simulation(ramp);
  simulation.add(Collector(30));
  simulation.run();
  REQUIRE(simulation.reportTime() == 3);
}

TEST_CASE("secondthreshold2", "second threshold reverse order")
{
  auto ramp = std::make_shared<Ramp>();
  Simulation simulation(ramp);
  simulation.add(Collector(40));
  simulation.add(Collector(30));
  simulation.run();
  REQUIRE(simulation.reportTime() == 4);
  REQUIRE(simulation.reportTime() == 3);
}
