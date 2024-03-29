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
  auto ramp = std::unique_ptr<Ramp>(new Ramp());
  Simulation simulation(std::move(ramp));
  simulation.add(std::unique_ptr<Collector>(new Collector(30)));
  simulation.run();
  REQUIRE(simulation.reportTime() == 3);
}

TEST_CASE("secondthreshold2", "second threshold reverse order")
{
  auto ramp = std::unique_ptr<Ramp>(new Ramp());
  Simulation simulation(std::move(ramp));
  simulation.add(std::unique_ptr<Collector>(new Collector(40)));
  simulation.add(std::unique_ptr<Collector>(new Collector(30)));
  simulation.run();
  REQUIRE(simulation.reportTime() == 4);
  REQUIRE(simulation.reportTime() == 3);
}

TEST_CASE("range", "range")
{
  std::vector<int> data = {2,3,40,50,30,-10,0,10,20,25,30,31,-20,0,0,0};
  auto signal = std::unique_ptr<Signal>(new Signal(data));
  Simulation simulation(std::move(signal));
  simulation.add(std::unique_ptr<Collector>(new Collector(40)));
  simulation.add(std::unique_ptr<TwoCollector>(new TwoCollector(25, -40)));
  simulation.add(std::unique_ptr<TwoCollector>(new TwoCollector(-40,25)));
  simulation.run();
  REQUIRE(simulation.reportTime() == 2);
}

#include "many_collector.hpp"

TEST_CASE("many", "many")
{
  std::vector<int> data {2,3,40,50,30,-10,0,10,20,25,30,31,-20,0,0,0};
  auto signal = std::unique_ptr<Signal>(new Signal(data));
  Simulation simulation(std::move(signal));
  simulation.add(std::unique_ptr<ManyCollector<int,int,int,int>>(new ManyCollector<int, int, int, int>(2,9,11,23)));
  simulation.add(std::unique_ptr<ManyCollector<int,int,int,int>>(new ManyCollector<int, int, int, int>(9,2,11,23)));
  simulation.add(std::unique_ptr<ManyCollector<int,int,int,int>>(new ManyCollector<int, int, int, int>(9,11,2,23)));
  simulation.add(std::unique_ptr<ManyCollector<int,int,int,int>>(new ManyCollector<int, int, int, int>(9,11,23,2)));
  simulation.add(std::unique_ptr<ManyCollector<int,int,int,int>>(new ManyCollector<int, int, int, int>(50,30,-10,10)));
  simulation.add(std::unique_ptr<ManyCollector<int,int,int,int>>(new ManyCollector<int, int, int, int>(30,50,-10,10)));
  simulation.add(std::unique_ptr<ManyCollector<int,int,int,int>>(new ManyCollector<int, int, int, int>(30,-10,50,10)));
  simulation.add(std::unique_ptr<ManyCollector<int,int,int,int>>(new ManyCollector<int, int, int, int>(10,30,-10,50)));
  simulation.run();
  REQUIRE(simulation.reportTime() == 0);
  REQUIRE(simulation.reportTime() == 0);
  REQUIRE(simulation.reportTime() == 0);
  REQUIRE(simulation.reportTime() == 0);

  REQUIRE(simulation.reportTime() == 3);
  REQUIRE(simulation.reportTime() == 3);
  REQUIRE(simulation.reportTime() == 3);
  REQUIRE(simulation.reportTime() == 3);
}

// list a wait time
