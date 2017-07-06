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
#include "color.hpp"
#include "hitbox.hpp"

namespace engine{

  class Scene;
  class EventHandler;

  class Game{
    public:
      typedef enum {
        RUNNING, PAUSED, QUIT
      } State;

    private:
      static Game* instance;
      std::string name;
      std::pair<int,int> window_dimensions;
      Color game_background_color = Color(0xAA, 0xAA, 0xAA, 0xAA);
      State state;
      SDL_Window* window;
      SDL_Renderer* renderer;
      Scene* actual_scene;
      bool loaded_media = false;

      Game(){};
      void init();
      void set_information(std::string,std::pair<int,int>);

    public:
      ~Game(){};
      static Game& get_instance();
      static Game& initialize(std::string, std::pair<int, int>);
      void run();
      void close();
      void load_media();
      bool is_media_loaded();
      void change_scene(Scene *);
      void set_game_background_color(int R, int G, int B, int A);
      void set_name(std::string);
      std::string get_name();
      void set_window_dimensions(std::pair<int, int>);
      std::pair<int, int> get_window_dimensions();
      void set_state(State);
      State get_state();
      SDL_Renderer *get_renderer();
      Scene* get_actual_scene();
  };
}

#endif
