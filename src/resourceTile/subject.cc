#include "subject.h"
#include "../vertex/observer.h"
#include <vector>
#include <algorithm>

void Subject::attach(Observer *o) { observers.emplace_back(o); }

void Subject::notifyObservers() {
    for (auto &ob : observers) ob->notify( *this );
}

std::vector<Observer*> Subject::getObservers() const{
    return observers;
}
