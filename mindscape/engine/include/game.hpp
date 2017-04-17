#ifndef GAME_H
#define GAME_H

#include "SDL2basics.hpp"
#include <string>

namespace engine{

  class Game{
    public:
      Game(){};
      ~Game(){};
 
      static Game& get_instance();
      void run();
      bool game_init();
      void close();
      bool load_media();
      void set_information(std::string name,std::pair<int,int> dimensions); 
      static Game* instance;
 
      std::string game_name;
      std::pair<int,int> window_dimensions;
      SDL_Window* window;
      SDL_Renderer* renderer;
  };

}

#endif
