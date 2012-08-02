#ifndef algorithm_hpp
#define algorithm_hpp

#include <memory>

class Algorithm
{
public:
  virtual ~Algorithm()
  {
  }

  virtual int run() = 0;

};

//Typename::shared_ptr<Algorithm> AlgorithmP;

#endif
