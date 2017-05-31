//TODO trocar os vectors de componentes para unordered maps
//TODO acabar com o primeiro construtor e definir hit box como um componente

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include "SDL2basics.hpp"
#include "component.hpp"
#include "keyboard_event.hpp"
#include "../../include/game_event.hpp"

namespace engine {

  class GameObject{
    public:
      static bool on_limit_of_level;

      std::string name;
      int priority;
      bool collidable;
      SDL_Rect hitbox;
      std::vector<Component*> audios;
      std::vector<Component*> images;
      std::vector<Component*> texts;
      std::pair<int,int> position;
      std::map<KeyboardEvent::Key, std::string> translations;
      bool active_game_object;
      std::string state;

      GameObject(){};

      GameObject(
        std::string p_name,
        std::pair<int, int> p_position,
        int priority,
        bool collidable,
        SDL_Rect hb)
        :name(p_name),
        position(p_position),
        priority(priority),
        collidable(collidable),
        hitbox(hb),
        active_game_object(false){};

      GameObject(
        std::string p_name,
        std::pair<int, int> p_position,
        int p,
        std::map<KeyboardEvent::Key,std::string> p_translations)
        :name(p_name),
        position(p_position),
        active_game_object(false),
        priority(p),
        translations(p_translations){};

      ~GameObject(){};

      bool load();
      virtual void free(){};
      void draw();
      void add_component(std::string, Component*);
      bool equals(GameObject *);
      void collide(GameObject *);
      virtual void on_event(GameEvent){};
      virtual void on_collision(GameObject *) {std::cout << "BATEU CARAI!" << std::endl; };

    private:
      bool check_collision(GameObject *);

    protected:
      void update_hitbox(int = 0, int = 0);
  };

}

#endif
