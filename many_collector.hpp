#ifndef many_collector_hpp
#define many_collector_hpp

#include "icollector.hpp"
#include <memory>
#include <iostream>

template<typename...T>
class ManyCollector;

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
    std::cout << "result " << result_ << " value " << value1_ << "\n";
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

template<typename T>
class ManyCollector<T> : public ICollector
{
public:
  ManyCollector(int value) : value_(value), result_(-1)
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
