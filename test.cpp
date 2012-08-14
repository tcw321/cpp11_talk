#include <vector>
#include <thread>

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

#include "many_collector.hpp"

TEST_CASE("many", "many")
{
  std::vector<int> data {2,3,40,50,30,-10,0,10,20,25,30,31,-20,0,0,0};
  auto signal = std::make_shared<Signal>(data);
  Simulation simulation(signal);
  simulation.add(std::make_shared<ManyCollector<int,int,int,int>>(2,9,11,23));
  simulation.add(std::make_shared<ManyCollector<int,int,int,int>>(9,2,11,23));
  simulation.add(std::make_shared<ManyCollector<int,int,int,int>>(9,11,2,23));
  simulation.add(std::make_shared<ManyCollector<int,int,int,int>>(9,11,23,2));
  simulation.add(std::make_shared<ManyCollector<int,int,int,int>>(50,30,-10,10));
  simulation.add(std::make_shared<ManyCollector<int,int,int,int>>(30,50,-10,10));
  simulation.add(std::make_shared<ManyCollector<int,int,int,int>>(30,-10,50,10));
  simulation.add(std::make_shared<ManyCollector<int,int,int,int>>(10,30,-10,50));
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

TEST_CASE("threads", "run two simulations in different threads")
{
  std::vector<int> data1 {2,3,40,50,30,-10,0,10,20,25,30,31,-20,0,0,0};
  auto signal1 = std::make_shared<Signal>(data1);
  Simulation simulation1(signal1);
  simulation1.add(std::make_shared<ManyCollector<int,int,int,int>>(2,9,11,23));

  std::vector<int> data2 {2,3,40,50,30,-10,0,10,20,25,30,31,-20,0,0,0};
  auto signal2 = std::make_shared<Signal>(data2);
  Simulation simulation2(signal2);
  simulation2.add(std::make_shared<ManyCollector<int,int,int,int>>(1,9,30,23));
  std::thread t(&Simulation::run, &simulation1);
  simulation2.run();
  t.join();
  REQUIRE(simulation1.reportTime() == 0);
  REQUIRE(simulation2.reportTime() == 4); 

}

// list a wait time
