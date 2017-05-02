#ifndef GAME_H
#define GAME_H
#include "SDL2basics.hpp"
#include <string>
#include <unordered_map>
#include "../include/image.hpp"
#include "../include/scene.hpp"

namespace engine{

  class Game{
    public:
      static Game* instance;
      std::string game_name;
      std::pair<int,int> window_dimensions;
      SDL_Window* window;
      SDL_Renderer* renderer;
      std::unordered_map<std::string, Scene*> scenes;
      Scene* actual_scene;

      Game(){};
      ~Game(){};

      static Game& get_instance();
      void run();
      void game_init();
      void close();
      bool load_media();
      void set_information(std::string name,std::pair<int,int> dimensions);
      void change_scene(Scene* scene);
      void add_scene(std::string name, Scene* scene);
  };

}

#endif
