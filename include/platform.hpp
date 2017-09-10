/**
 * @file platform.hpp
 * @brief Purpose: Contains the attributes and methods for Platform class.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/keyboard_event.hpp"
#include "../engine/include/image.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace mindscape {
	/**
  	 * @brief A 2D Platform class.
  	 *
  	 * Class responsible for managing the platforms used in the game.
  	 */
	class Platform : public engine::GameObject {
	private:
		void initialize_animations();

	public:
		Platform(
				std::string p_name,
				std::pair<int, int> position,
				int priority
		);

		~Platform() {};

		void on_event(GameEvent game_event);
	};
}

#endif
