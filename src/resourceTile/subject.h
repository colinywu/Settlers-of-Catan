#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <string>
#include "resourceType.h"

class Observer;

class Subject {
    std::vector<Observer*> observers;

  public:
    std::vector<Observer*> getObservers() const;
    void attach(Observer *o);  
    void notifyObservers();
    virtual ResourceType getType() const = 0;

    virtual ~Subject() = default;
};

#endif
