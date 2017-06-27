#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "unordered_map"
#include "persistence_map.hpp"

namespace engine{
  class Persistence {
    public:
      virtual PersistenceMap * load (std::string)=0;
      virtual bool dump (std::string, PersistenceMap *)=0;
  };
}
#endif
