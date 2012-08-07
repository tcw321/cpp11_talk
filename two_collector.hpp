#ifndef two_collector_hpp
#define two_collector_hpp

#include "icollector.hpp"
#include <memory>
#include <iostream>

class TwoCollector : public ICollector
{
public:
  TwoCollector(int v1, int v2) : value1_(v1), value2_(v2), result_(0)
  {
  }
  void initialize()
  {
  }
  void run(int time, int value)
  {
    //    std::cout << time << " " << value << "\n";
    if (value == value1_)
      result_ = time;
    else if (value == value2_)
      result_ = time;     
  }

  int getResult() const
  {
    return result_;
  }
private:
  int value1_;
  int value2_;
  int result_;
};

#endif
