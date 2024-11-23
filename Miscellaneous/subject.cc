#include <vector>
#include "subject.h"
#include "observer.h"

void Subject::attach( Observer* o ) {
  this->observers.push_back(o);
}

void Subject::notifyObservers() {
  for (Observer *observer : this->observers) {
    observer->notify();
  }
}
