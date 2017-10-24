/**
 * @file arm.hpp
 * @brief Purpose: Contains methods to arm class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef ARM_H
#define ARM_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/hitbox.hpp"
#include "../engine/include/observable.hpp"
#include "../engine/include/animation.hpp"
#include "enemy.hpp"
#include "little_girl.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace mindscape {
	
	/**
	  * @brief A Arm class.
	  *
	  * A class inherited from Enemy for Arm.
	  */
	class Arm : public Enemy {
	private:
		void initialize_state_map();
		void initialize_hitboxes();
		void initialize_animations();
		void initialize_as_physicable();
		engine::Animation *create_animation(std::string path,
											int sprite_lines, int sprite_columns, double duration,
											std::string direction);
	
	public:
		Arm(std::string name, std::pair<int, int> position, int priority);
		void on_event(GameEvent);
		void on_collision(engine::GameObject *, engine::Hitbox *,
						  engine::Hitbox *);
		
		~Arm() {};
	};
}

#endif
