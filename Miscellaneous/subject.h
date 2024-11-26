#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"

class Subject {
  std::vector<std::shared_ptr<Observer>> observers;
  public:
    void attach( std::shared_ptr<Observer> observer );
    void notifyObservers();
    virtual ~Subject() = default;
};

#endif
