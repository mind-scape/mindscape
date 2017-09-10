/**
 * @file persistence_dat.cpp
 *
 * @brief Purpose: Contains methods to save the game
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 *
 */
#include "persistence_dat.hpp"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>

using namespace engine;

PersistenceDat *PersistenceDat::instance = 0;

/**
 * @brief Get Instance
 *
 * Method responsible for get instance
 *
 * @return void
 */
PersistenceDat *PersistenceDat::get_instance(){
  if (!instance)
    instance = new PersistenceDat();
  return instance;
}


/**
 * @brief Load Method
 *
 * Method responsible for load the saved game
 *
 * @param p_path path to saved game
 * @return game loaded
 */
PersistenceMap * PersistenceDat::load(std::string p_path){
  PersistenceMap *data = new PersistenceMap();

  std::stack<std::string> paths;
  paths.push(p_path);
  std::string line;

  while(!paths.empty()){
    std::string path = paths.top();
    paths.pop();
    std::ifstream save_file;
    save_file.open(path, std::ifstream::in);

    if (save_file.is_open()){
      while (std::getline(save_file,line)){
        bool is_include = false;
        std::istringstream iss(line);
        std::string key;
        std::string value;
        std::unordered_map<std::string, std::string> object_data;

        if (line != "" && line[0] != '#'){
          while(iss >> key && iss >> value){
            if((is_include = (key == "include"))){
              paths.push(value);
            }
            object_data[key] = value;
          }
          if (!is_include) data->insert_object(object_data);
        }
      }
    }
    else {
      std::cout << "Unable to open file" << std::endl;
      return NULL;
    }
  }

  return data;
}

/**
 * @brief Dump Method
 *
 * Method responsible for dump
 *
 * @param path path to save the open game in a file
 * @param data saved game
 * @return void
 */
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
