#ifndef OBSERVER_H_
#define OBSERVER_H_
#include <string>

class Subject;

class Observer {
  public:
    virtual void notify( Subject & whoNotified ) = 0; 
    virtual ~Observer() = default;
};

#endif
