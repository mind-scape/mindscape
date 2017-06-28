#ifndef PERSISTENCE_DAT_H
#define PERSISTENCE_DAT_H

#include "persistence.hpp"
#include "persistence_map.hpp"
#include "unordered_map"

namespace engine{
  class PersistenceDat : public Persistence {
    private:
      PersistenceDat(){};
      static PersistenceDat *instance;

    public:
      static PersistenceDat *get_instance();
      ~PersistenceDat(){};

      void operator=(PersistenceDat const&) = delete;
      PersistenceMap * load (std::string);
      bool dump (std::string, PersistenceMap *);
  };
}
#endif
