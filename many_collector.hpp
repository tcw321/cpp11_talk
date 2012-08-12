#ifndef many_collector_hpp
#define many_collector_hpp

#include "icollector.hpp"
#include <memory>
#include <iostream>

//default template
template<typename...T>
class ManyCollector;

//specialized template
template<typename T, typename ...Rest>
class ManyCollector<T, Rest...> : public ICollector
{
public:
  ManyCollector(T v1, Rest...rest) : value1_(v1), moreCollectors_(rest...), result_(-1)
  {
  }
  void initialize()
  {
  }
  void run(int time, int value)
  {
    if (value == value1_)
      result_ = time;
    else if (result_ == -1)
      moreCollectors_.run(time,value);
  }

  int getResult() const
  {
    int other = moreCollectors_.getResult();
    if (other == -1)
      return result_;
    if (result_ != -1)
      {
	if (result_ < other)
	  return result_;
	else
	  return other;
      }
    return other;
  }
private:
  ManyCollector<Rest...> moreCollectors_;
  T value1_;
  int result_;
};

//specialized template
template<>
class ManyCollector<> : public ICollector
{
public:
  ManyCollector() : result_(-1)
  {
  }
  void initialize()
  {
  }
  void run(int time, int value)
  {
  }
  int getResult() const
  {
    return result_;
  }
private:
  int result_;
};

#endif
