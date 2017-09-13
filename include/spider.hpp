/**
 * @file spider.hpp
 * @brief Purpose: Contains methods to Spider's management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef SPIDER_H
#define SPIDER_H

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

    /**
     * @brief Spider enemy class.
     *
     * This class is responsible to build all Spider's structure, inheriting of
     * Enemy classes.
     */
  
    class Spider : public Enemy {
        private:
            int walking_left_count = 0;
            int walking_right_count = 0;
            int attacking_right_count = 0;
            int attacking_left_count = 0;
            bool same_nivel = false;
            void initialize_state_map();
            void initialize_hitboxes();
            void initialize_animations();
            void initialize_audio_effects();
            void initialize_as_physicable();
            void attack();
            void on_attack(engine::GameObject *);
            void die(engine::GameObject*);
      
            engine::Animation *create_animation(
                std::string path,
                int sprite_lines,
                int sprite_columns,
                double duration,
                std::string direction
            );

        public:
            Spider(
                std::string name,
                std::pair<int, int> position,
                int priority
            );

            ~Spider(){};

            void move(engine::GameObject *);
            void on_event(GameEvent);
            void on_collision(
                engine::GameObject*, 
                engine::Hitbox*, 
                engine::Hitbox*
            );
            void notify(engine::Observable *);
    };

}

#endif
