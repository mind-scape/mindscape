#ifndef __GAME_H
#define __GAME_H

#include <SDL2basics.hpp>

namespace engine{

  class Game{
    public:
      Game(std::string p_game_name,std::pair<int,int> p_window_dimensions)
        : game_name(p_game_name), window_dimensions(p_window_dimensions),instance(NULL){}
      ~Game();
 
      void Run();
      static Game* GetInstance();
 
    private:
      static Game* instance;
      std::string game_name);
      std::pair<int,int> window_dimensions();
  }

}

#endif
