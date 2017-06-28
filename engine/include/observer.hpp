#ifndef OBSERVER_H
#define OBSERVER_H

#include "game_object.hpp"
#include <vector>

namespace engine {
  class Observable;
  class Observer {
    public:
      virtual void notify(Observable *){};
  };
}
#endif
