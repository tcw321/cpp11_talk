#ifndef icollector_hpp
#define icollector_hpp

class ICollector
{
public:
  virtual ~ICollector() 
  {}
  virtual void initialize() = 0;
  virtual void run(int, int) = 0;
  virtual int getResult() const = 0;

};

#endif
// better name basecollector, one collector, two collector
