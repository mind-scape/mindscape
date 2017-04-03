#ifndef __GAME_H
#define __GAME_H

#include "State.h"
#include <iostream>
#include <SDL2basics.hpp>

namespace engine{

  class Game{
    public:
      Game(std::string game_name,std::pair<int,int> window_dimensions)
        : ms_game_name(game_name), ms_window_dimensions(window_dimensions),intance(NULL){}
      ~Game();
 
      void Run();
      static Game * GetInstance();
 
    private:
      static Game * instance;
      std::string ms_game_name);
      std::pair<int,int> ms_window_dimensions();
  }

}

#endif
