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
#include "image.hpp"
#include "text.hpp"
#include "audio.hpp"
#include "hitbox.hpp"
#include "keyboard_event.hpp"
#include "state_map.hpp"
#include "../../include/game_event.hpp"

namespace engine {

  class GameObject{
    private:
      StateMap states;
      std::vector<Hitbox*> hitboxes;

      void run_collisions(GameObject *);

    protected:
      std::pair<float, float> speed;

      virtual void on_collision(GameObject *, Hitbox *, Hitbox *){};

    public:
      static bool on_limit_of_level;

      std::string name;
      int priority;
      bool collidable;
      std::vector<Component*> audios;
      std::vector<Component*> images;
      std::vector<Component*> texts;
      std::vector<Component*> animations;
      std::pair<float,float> position;
      std::map<KeyboardEvent::Key, std::string> translations;
      bool active_game_object;
      std::string state;

      GameObject(){};

      GameObject(
        std::string p_name,
        std::pair<int, int> p_position,
        int p,
        std::map<KeyboardEvent::Key,std::string> p_translations,
        StateMap p_states = StateMap())
        :name(p_name),
        position(p_position),
        active_game_object(false),
        priority(p),
        translations(p_translations),
        states(p_states),
        speed(std::make_pair(0.0,0.0)){};

      ~GameObject(){};

      bool load();
      void free();
      void draw();
      void add_component(Component*);
      bool equals(GameObject *);
      void collide(GameObject *);
      std::string get_state(std::string);
      std::vector<Hitbox*> get_hitboxes();
      virtual void on_event(GameEvent){};
      void update_hitboxes();
      virtual void update(unsigned){};
  };
}

#endif
