/**
 * @file scorpion.hpp
 * @brief Purpose: Contains methods to Scorpion's management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef SCORPION_H
#define SCORPION_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/hitbox.hpp"
#include "../engine/include/observable.hpp"
#include "../engine/include/animation.hpp"
#include "enemy.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace mindscape {

    /**
     * @brief Scorpion enemy class.
     *
     * This class is responsible to build all Scorpion's structure, inheriting of
     * Enemy classes.
     */
    
    class Scorpion : public Enemy {
        private:

            void initialize_state_map();
            void initialize_hitboxes();
            void initialize_animations();
            void initialize_as_physicable();
            void initialize_audio_effects();
            void on_attack(engine::GameObject *);
            void attack();
            void die(engine::GameObject*);

            bool same_nivel = false; /**< Boolean. Check if the girl and the scorpion is on the same nivel. */

            engine::Animation *create_animation(
                std::string path,
                int sprite_lines,
                int sprite_columns,
                double duration,
                std::string direction
            );

        public:
            Scorpion(
                std::string name, /**< String. Scorpion's name. */
                std::pair<int, int> position, /**< Pair<int, int>. Scorpion's position, using coordinates schema. */
                int priority /**< Integer. Priority of enemy. */
            );
            ~Scorpion(){};

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
