/**
 * @file clown.hpp
 * @brief Purpose: Contains clown methods and attributes
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 *
 */
#ifndef CLOWN_H
#define CLOWN_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/hitbox.hpp"
#include "../engine/include/observable.hpp"
#include "../engine/include/animation.hpp"
#include "enemy.hpp"
#include "goop.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace mindscape {
    /**
     * @brief Clown enemy class
     *
     * This class is responsible for the implementation of clown boss.
     *
     */
    class Clown : public Enemy {
    private:
        void initialize_state_map();
        void initialize_foot_hitbox();
		void initialize_head_hitbox();
		void initialize_attack_hitbox();
        void initialize_animation_on_attack();
        void initialize_animation_dying();
        void initialize_animation_attacking();
        void initialize_animation_idle();
        void initialize_animation_idle_vunerable();
        void initialize_as_physicable();
        void initialize_audio_effects();
        void on_attack(engine::GameObject *);
        void attack(engine::GameObject*);
		void attacking(engine::GameObject*);
		void dying(engine::GameObject*);
		void vunerable(engine::GameObject*);
		void attack_girl(engine::GameObject*);
        void basic_attack();
        void double_attack();
        void serial_attack();
        void on_attack();
        void die(engine::GameObject*);
		void on_collision_platform(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
		void on_collision_little_girl(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
		void on_collision_goop(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);

		GameObject* create_goop();
        engine::Animation *create_animation(
                std::string path,
                int sprite_lines,
                int sprite_columns,
                double duration,
                std::string direction
        );


		int goops_counter = 0; /**<Interger. Variable to count the number
        * the number of goops */

        int attack_animation_trigger = 0 /**<Interger. Variable to
        * trigger the animation attack */;

        int refuted_goop_hits = 0; /**<Interger. Variable to count the number of
        * refuted goops */

        int vulnerable_counter = 0; /**<Interger. Variable to set
        * clown vunerable or not*/

        std::vector<engine::GameObject*> clown_goops;


    public:
        Clown(
                std::string name,
                std::pair<int, int> position,
                int priority
        );
        ~Clown(){};

        void on_event(GameEvent);
        void on_collision(engine::GameObject*, engine::Hitbox*, engine::Hitbox*);
        void notify(engine::Observable *);
    };

}

#endif
