#ifndef PERSISTENCE_DAT_H
#define PERSISTENCE_DAT_H

#include "persistence.hpp"
#include "unordered_map"

namespace engine{
  class PersistenceDat : public Persistence {
    private:
      PersistenceDat();
      static PersistenceDat *instance;

    public:
      static PersistenceDat *get_instance();
      ~PersistenceDat();
      std::unordered_map<std::string, std::string> load (std::string);
      bool dump (std::string, std::unordered_map<std::string, std::string>);
  };
}
#endif
