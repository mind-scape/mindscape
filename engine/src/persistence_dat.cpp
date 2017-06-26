#include "persistence_dat.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace engine;

PersistenceDat * PersistenceDat::get_instance(){
  if(!instance)
    instance = new PersistenceDat();
  return instance;
}

std::unordered_map<std::string, std::string> PersistenceDat::load(std::string path){
  std::unordered_map<std::string, std::string> data;

  std::string line;
  std::ifstream save_file(path);

  if (save_file.is_open()){
    while (std::getline(save_file,line)){
      for (auto str : line) {
       
    std::cout << "Unable to open file" << std::endl;
}

bool PersistenceDat::dump(std::string path, std::unordered_mad<std::string, std::string> data){
  ofstream save_file;
  save_file.open(path)
  if(save_file.is_open())
    for(auto each : data)
      save_file << each.first << " " << each.second << std::endl;
  else
    return false;
  save_file.close();
  return true;
}
