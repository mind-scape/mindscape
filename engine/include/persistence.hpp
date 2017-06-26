#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "unordered_map"

namespace engine{
  class Persistence {
    public:
      virtual std::unordered_map<std::string, std::string> load (std::string)=0;
      virtual bool dump (std::string, std::unordered_map<std::string, std::string>)=0;
  };
}
#endif
