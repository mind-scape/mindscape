//TODO trocar os vectors de componentes para unordered maps
//TODO acabar com o primeiro construtor e definir hit box como um componente
//TODO colocar todos os estados para usar o SATE MAP

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
#include "animation.hpp"
#include "../../include/game_event.hpp"

namespace engine {

  class GameObject{
    private:
      int hp;
      std::pair<float, float> speed;
      std::pair<float,float> position;
      StateMap states;
      std::vector<Hitbox*> hitboxes;
      Animation* actual_animation = NULL;
      bool active;

      void run_collisions(GameObject *);

    protected:
      virtual void on_collision(GameObject *, Hitbox *, Hitbox *){};

    public:
      static bool on_limit_of_level;

      std::string name;
      int priority;
      bool collidable;
      std::vector<Component*> audios;
      std::vector<Component*> images;
      std::vector<Component*> texts;
      std::map<std::string, Animation*> animations;
      std::map<KeyboardEvent::Key, std::string> translations;
      std::string state;
      std::string game_object_direction;

      GameObject(){};

      GameObject(
        std::string p_name,
        std::pair<float, float> p_position,
        int p,
        std::map<KeyboardEvent::Key,std::string> p_translations,
        StateMap p_states = StateMap())
        :name(p_name),
        position(p_position),
        active(false),
        priority(p),
        translations(p_translations),
        states(p_states),
        speed(std::make_pair(0.0,0.0)){};

      ~GameObject(){};

      bool load();
      void free();
      void draw();
      void add_component(Component*);
      void add_animation(std::string, Animation*);
      bool equals(GameObject *);
      void collide(GameObject *);
      std::pair<float, float> get_position();
      float get_position_x();
      float get_position_y();
      void set_position(std::pair<float, float>);
      void set_position_x(float);
      void set_position_y(float);
      std::pair<float, float> get_speed();
      float get_speed_x();
      float get_speed_y();
      int get_hp();
      void set_hp(int);
      void set_speed(std::pair<float, float>);
      void set_speed_x(float);
      void set_speed_y(float);
      void activate();
      void deactivate();
      bool is_active();
      std::string get_state(std::string);
      std::vector<Hitbox*> get_hitboxes();
      virtual void on_event(GameEvent){};
      void update_hitboxes();
      virtual void update_state();
      void set_actual_animation(Animation*);
      Animation* get_actual_animation();
  };
}

#endif
