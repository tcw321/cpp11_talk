#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ramp.hpp"
#include "simulation.hpp"
#include "signal.hpp"
#include "collector.hpp"
#include "two_collector.hpp"

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
  simulation.add(std::make_shared<Collector>(30));
  simulation.run();
  REQUIRE(simulation.reportTime() == 3);
}

TEST_CASE("secondthreshold2", "second threshold reverse order")
{
  auto ramp = std::make_shared<Ramp>();
  Simulation simulation(ramp);
  simulation.add(std::make_shared<Collector>(40));
  simulation.add(std::make_shared<Collector>(30));
  simulation.run();
  REQUIRE(simulation.reportTime() == 4);
  REQUIRE(simulation.reportTime() == 3);
}

TEST_CASE("range", "range")
{
  std::vector<int> data = {2,3,40,50,30,-10,0,10,20,25,30,31,-20,0,0,0};
  auto signal = std::make_shared<Signal>(data);
  Simulation simulation(signal);
  simulation.add(std::make_shared<Collector>(40));
  simulation.add(std::make_shared<TwoCollector>(25, -40));
  simulation.add(std::make_shared<TwoCollector>(-40,25));
  simulation.run();
  REQUIRE(simulation.reportTime() == 2);
}

// list a wait time
