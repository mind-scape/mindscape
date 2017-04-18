#ifndef GAME_H
#define GAME_H
#include "SDL2basics.hpp"
#include <string>
#include "../include/image.hpp"

namespace engine{

  class Game{
    public:
      std::string game_name;
      std::pair<int,int> window_dimensions;
      SDL_Window* window;
      SDL_Renderer* renderer;
      Image* image_1;

      Game(){};
      ~Game(){};

      static Game& get_instance();
      void run();
      void game_init();
      void close();
      bool load_media();
      void set_information(std::string name,std::pair<int,int> dimensions);
      static Game* instance;
  };

}

#endif
