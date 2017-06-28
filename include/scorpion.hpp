#ifndef SCORPION_H
#define SCORPION_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/hitbox.hpp"
#include "../engine/include/observable.hpp"
#include "enemy.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace mindscape {
  class Scorpion : public Enemy {
    private:
      int walking_left_count = 0;
      int walking_right_count = 0;
      int attacking_right_count = 0;
      int attacking_left_count = 0;

    public:
      Scorpion(
        std::string name,
        std::pair<int, int> position,
        int priority)
        :Enemy(
          name,
          position,
          priority
        ){ //[FIXME] Constructor should not be implemented here
          states.set_state("ACTION_STATE","NORMAL");
          engine::Game& game = engine::Game::get_instance();

          engine::Animation* scorpion_left = new engine::Animation(
            game.get_renderer(),
            "../assets/images/sprites/enemies/scorpion/scorpion_walking_left.png",
            false,
            std::make_pair(0, 0),
            1,1,5,0.9,true,"LEFT"
          );

          scorpion_left->set_values(
            std::make_pair(320, 320),
            std::make_pair(320, 320),
            std::make_pair(0, 0)
          );

          engine::Animation* scorpion_right = new engine::Animation(
            game.get_renderer(),
            "../assets/images/sprites/enemies/scorpion/scorpion_walking_right.png",
            false,
            std::make_pair(0, 0),
            1,1,5,0.9,true,"RIGHT"
          );

          scorpion_right->set_values(
            std::make_pair(320, 320),
            std::make_pair(320, 320),
            std::make_pair(0, 0)
          );

          engine::Hitbox* scorpion_hitbox = new engine::Hitbox(
            "scorpion_hitbox",
            this->get_position(),
            std::make_pair(40, 312),
            std::make_pair(180,8),
            game.get_renderer()
          );

          engine::Hitbox* scorpion_attack = new engine::Hitbox(
            "scorpion_attack",
            this->get_position(),
            std::make_pair(5, 200),
            std::make_pair(283,10),
            game.get_renderer()
          );

          collidable = true;
          add_animation("walking_right", scorpion_left);
          add_animation("walking_left", scorpion_right);
          add_component(scorpion_attack);
          add_component(scorpion_hitbox);
          set_actual_animation(scorpion_left);
        };
      ~Scorpion(){};

      void attack();
      void move(engine::GameObject *);
      void on_event(GameEvent);
      void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
      void notify(engine::Observable *);
  };

}

#endif
