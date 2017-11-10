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
     * This class is responsible to build all Scorpion's structure, inheriting
     * of Enemy classes.
     */

    class Scorpion : public Enemy {
        private:

            void initialize_state_map();

            void initialize_hitboxes();
            void initialize_scorpion_hitbox(engine::Game);
            void initialize_scorpion_attack_hitbox(engine::Game);

            void initialize_animations();
            void initialize_walking_animations();
            void initialize_idle_animations();
            void activate_idle_animation(engine::Animation* );
            void initialize_on_attack_animations();
            void initialize_attacking_animations();
            void initialize_dying_animations();

            void initialize_as_physicable();

            void initialize_audio_effects();
            void initialize_scorpion_attacking_audio();
            void initialize_scorpion_on_attack_audio();

            void on_attack(engine::GameObject *);
            void verifies_same_nivel(float, float);
            void verifies_actual_animation();
            void verifies_left_distance_from_girl(int, const int);
            void verifies_right_distance_from_girl(int, const int);

            void attack();
            void die(engine::GameObject*);

            bool same_nivel = false; /**< Boolean.
            Check if the girl and the scorpion is on the same nivel. */

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
                std::pair<int, int> position, /**< Pair<Integer, Integer>.
                Pair structure that define Scorpion's position,
                using coordinates schema. */
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
