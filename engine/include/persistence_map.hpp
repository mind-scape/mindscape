#ifndef PERSISTENCE_MAP_H
#define PERSISTENCE_MAP_H

#include <unordered_map>
#include <vector>
#include <string>

namespace engine{
  
  class PersistenceMap {
    public:
      typedef std::vector<std::unordered_map<std::string, std::string> > ObjectVector; 
      typedef ObjectVector::iterator iterator;
      typedef ObjectVector::const_iterator const_iterator;

    private:
      ObjectVector persistence_map;

    public:
      PersistenceMap():persistence_map({}){};
      ~PersistenceMap(){};

      std::unordered_map<std::string, std::string> get_object_by_id(std::string);
      void insert_object(std::unordered_map<std::string, std::string>);
      void insert_object_data(std::string, std::string, std::string);
      std::string get_object_data(std::string, std::string);

      iterator begin() { return persistence_map.begin(); }
      iterator end() { return persistence_map.end(); }
  };
}
#endif
