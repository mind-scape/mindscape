/**
 * @file little_girl.hpp
 * @brief Purpose: Contains methods to little_girl class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef LITTLE_GIRL_H
#define LITTLE_GIRL_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/animation.hpp"
#include "../engine/include/hitbox.hpp"
#include "../engine/include/physics.hpp"
#include "spider.hpp"
#include "fighter.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape {
	
	/**
	 * @brief A little girl class
	 *
	 * Class responsible for handling the main character of the game
	 */
	class LittleGirl : public engine::GameObject, public mindscape::Fighter {
	private:
		static LittleGirl *instance;
		
		int running_right_animation_count = 0; /**< Integer. Variable to
		save number of running animations while the Little Girl is looking 
		right */

		int running_left_animation_count = 0; /**< Integer. Variable to
		save number of running animations while the Little Girl is looking 
		left */
		
		int jumping_animation_count = 0; /**< Integer. Variable to
		save number of jumping animations while the Little Girl is jumping */
		
		int attacking_right_animation = 0; /**< Integer. Variable to
		save number of attacking animations while the Little Girl is looking 
		right */

		int attacking_left_animation = 0; /**< Integer. Variable to
		save number of attacking animations while the Little Girl is looking 
		left */
		
		void initialize_state_map();
		void initialize_hitboxes();
		void initialize_animations();
		void initialize_audio_effects();
		void initialize_as_physicable();
		void jump(std::string);
		void move_right(std::string, std::string);
		void move_left(std::string, std::string);
		void attack();
		void on_attack(engine::GameObject *);
		void die(engine::GameObject *);
		engine::Animation *create_animation(
				std::string path,
				int sprite_lines,
				int sprite_columns,
				double duration,
				std::string direction
		);
	
	public:
		LittleGirl(
				std::string name,
				std::pair<int, int> position,
				int priority
		);
		void on_event(GameEvent);
		void on_collision(
				engine::GameObject *,
				engine::Hitbox *,
				engine::Hitbox *
		);
		void update_state();
		
		~LittleGirl() {};
	};
}

#endif
