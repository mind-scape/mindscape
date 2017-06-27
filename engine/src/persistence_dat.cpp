#include "persistence_dat.hpp"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace engine;

PersistenceDat * PersistenceDat::get_instance(){
  if(!instance)
    instance = new PersistenceDat();
  return instance;
}

PersistenceMap * PersistenceDat::load(std::string path){
  PersistenceMap *data = new PersistenceMap();

  std::string line;
  std::ifstream save_file(path);

  if (save_file.is_open()){
    while (std::getline(save_file,line)){
      std::istringstream iss(line);
      std::string key;
      std::string value;
      std::unordered_map<std::string, std::string> object_data;
      while(iss >> key && iss >> value){
        object_data[key] = value;
      }

      data->insert_object(object_data);
    }
    return data;
  }else{
    std::cout << "Unable to open file" << std::endl;
    return NULL;
  }
}

bool PersistenceDat::dump(std::string path, PersistenceMap * data){
  std::ofstream save_file;
  save_file.open(path);
  if(save_file.is_open())
    for(auto it = data->begin(); it < data->end(); it++){
      for(auto each_data : *it){
        save_file << each_data.first << " " << each_data.second << " ";
      }
      save_file << std::endl;
    }
  else
    return false;
  save_file.close();
  return true;
}
