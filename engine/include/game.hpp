#ifndef GAME_H
#define GAME_H

#include "SDL2basics.hpp"
#include <string>
#include <unordered_map>
#include "image.hpp"
#include "audio.hpp"
#include "text.hpp"
#include "event_handler.hpp"
#include "scene.hpp"

namespace engine{

  class Scene;
  class EventHandler;

  class Game{
    public:
      enum class State {RUNNING, PAUSED, QUIT};

      static Game* instance;
      std::string game_name;
      std::pair<int,int> window_dimensions;
      SDL_Window* window;
      SDL_Renderer* renderer;
      std::unordered_map<std::string, Scene*> scenes;
      Scene* actual_scene;
      State game_state;
      static bool quit_event;

      Game(){};
      ~Game(){};

      static Game& get_instance();
      void game_init();
      void run();
      void close();
      bool load_media();
      void set_information(std::string name,std::pair<int,int> dimensions);
      void change_scene(Scene* scene);
      void add_scene(std::string name, Scene* scene);
  };

}

#endif
