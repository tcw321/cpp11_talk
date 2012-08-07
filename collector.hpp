#ifndef collector_hpp
#define collector_hpp

#include "icollector.hpp"
#include <memory>
#include <iostream>

class Collector //: public ICollector
{
public:
  Collector(int v) : value_(v), result_(0)
  {
  }
  void initialize()
  {
  }
  void run(int time, int value)
  {
     if (value == value_)
      result_ = time;
  }

  int getResult() const
  {
    return result_;
  }
private:
  int value_;
  int result_;
};

#endif
