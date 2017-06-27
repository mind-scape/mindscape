#ifndef SPIDER_H
#define SPIDER_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/hitbox.hpp"
#include "enemy.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace mindscape{

  class Spider : public Enemy {
    private:
      int walking_left_count = 0;
      int walking_right_count = 0;
      int attacking_right_count = 0;
      int attacking_left_count = 0;

    public:
      Spider(std::string p_name, std::pair<int, int> position, int p): Enemy(p_name, position, p){
        states.set_state("ACTION_STATE","NORMAL");
        engine::Game& game = engine::Game::get_instance();

        engine::Animation* spider_left = new engine::Animation(
          game.get_renderer(),
          "../assets/images/sprites/enemies/spider/spider_walking_left.png",
          false,
          std::make_pair(0, 0),
          1,1,4,0.9,true,"LEFT"
        );
        spider_left->set_values(
          std::make_pair(288, 288),
          std::make_pair(288, 288),
          std::make_pair(0, 0)
        );

        engine::Animation* spider_right = new engine::Animation(
          game.get_renderer(),
          "../assets/images/sprites/enemies/spider/spider_walking_right.png",
          false,
          std::make_pair(0, 0),
          1,1,4,0.9,true,"RIGHT"
        );
        spider_right->set_values(
          std::make_pair(288, 288),
          std::make_pair(288, 288),
          std::make_pair(0, 0)
        );

        engine::Hitbox* spider_hitbox = new engine::Hitbox("spider_hitbox", this->get_position(), std::make_pair(60, 280), std::make_pair(180,8), game.get_renderer());
        engine::Hitbox* spider_attack = new engine::Hitbox("spider_attack", this->get_position(), std::make_pair(5, 200), std::make_pair(283,10), game.get_renderer());
        collidable = true;
        add_animation("walking_right", spider_left);
        add_animation("walking_left", spider_right);
        add_component(spider_attack);
        add_component(spider_hitbox);
        set_actual_animation(spider_left);
      };
      ~Spider(){};

      void attack();
      void move(GameEvent);
      void on_event(GameEvent);
      void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
  };

}

#endif
