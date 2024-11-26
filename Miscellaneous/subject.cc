#include <vector>
#include "subject.h"
#include "observer.h"

void Subject::attach( std::shared_ptr<Observer> observer ) {
  this->observers.push_back(observer);
}

void Subject::notifyObservers() {
  for (std::shared_ptr<Observer> & observer : this->observers) {
    observer->notify();
  }
}
