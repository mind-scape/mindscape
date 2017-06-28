#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "game_object.hpp"
#include "observer.hpp"
#include <vector>

namespace engine {
  class Observable {
    public:
      virtual void attach_observer(Observer *) = 0;
      virtual void detach_observer(Observer *) = 0;
      virtual void notify_observers() = 0;
  };
}
#endif
