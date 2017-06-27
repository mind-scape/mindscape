#include "persistence_map.hpp"

using namespace engine;

std::unordered_map<std::string, std::string> PersistenceMap::get_object_by_id(std::string id){
  int iid = std::stoi(id);
  return persistence_map[iid];
}

void PersistenceMap::insert_object(std::unordered_map<std::string, std::string> object){
  persistence_map.push_back(object);
}

void PersistenceMap::insert_object_data(std::string id, std::string key, std::string data){
   int iid = std::stoi(id);
   persistence_map[iid][key] = data;
}

std::string PersistenceMap::get_object_data(std::string id, std::string key){
  int iid = std::stoi(id);
  return persistence_map[iid][key];
}
