/**
 * @file music_player.hpp
 * @brief Purpose: Contains the attributes and method for music_player class.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "../engine/include/game_object.hpp"
#include "../engine/include/time.hpp"
#include "../engine/include/game.hpp"
#include "../engine/include/keyboard_event.hpp"
#include <string>

namespace mindscape {

	/**
 	 * @brief A Music Player class.
 	 *
 	 * Class responsible for managing the games' music.
 	 */
	class MusicPlayer : public engine::GameObject {
	private:
		int cont = 0;
		bool test = true; /**< Boolean. Boolean that defines if the test mode is on*/

		engine::Time *timer; /**< engine::Time*. A pointer to a timer*/

		int time = 0; /**< Integer. Integer that keeps track of the time*/
		int time_aux = 0; /**< Integer. Auxiliar integer to help time tracking*/

		engine::Game *game; /**< engine::Game*. Pointer to a game instance*/

		int sub_position_x = 0; /**< Integer. X axis position */

	public:
		/**
		 * @brief MusicPlayer constructor
		 *
		 * This method initializes everything needed by the music player class.
		 *
		 * @param name Name of the object
		 * @param position Pair of integers representing x and y position
		 * @param priority Rendering priority of the object
		 */
		MusicPlayer(
				std::string name,
				std::pair<int, int> position,
				int priority
		)
				: engine::GameObject(
				name,
				position,
				priority,
				{
						{engine::KeyboardEvent::LEFT,  "MOVE_LEFT"},
						{engine::KeyboardEvent::RIGHT, "MOVE_RIGHT"},
				}
		) {
			timer->init();
			engine::Game &game = engine::Game::get_instance();
		};

		~MusicPlayer() {};

		void update_state();

		void on_event(GameEvent);
	};
}

#endif
