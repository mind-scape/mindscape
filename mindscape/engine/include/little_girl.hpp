#ifndef LITTLE_GIRL_H 
#define LITTLE_GIRL_H 

#include "SDL2basics.hpp"
#include "game_object.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace engine {

  class LittleGirl : public GameObject {
    LittleGirl(std::string p_name):GameObject("LittleGirl"){};
    ~LittleGirl(){};

    bool load();
    void free();
  };

}

#endif
