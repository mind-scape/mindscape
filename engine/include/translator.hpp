/**
 * @file translator.hpp
 * @brief Purpose: Contains methods to Translator's management.
 *
 * These methods define the keys used in the game.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "../../include/game_event.hpp"
#include <list>
#include "keyboard_event.hpp"
#include "event_handler.hpp"

namespace engine {

	/**
	 * @brief A Translator class.
	 *
	 * This class is responsable to describe the interaction of user 
	 * and the keyboard, where each key corresponds to an action.
	 */

  	class Translator {
    	Translator();
    	~Translator();

    	public:
      		static std::list<GameEvent> 
      			keyboard_events_to_game_events(std::list<KeyboardEvent>);
      		//static std::list<GameEvent> game_events;
      		static bool is_a_valid_event;
  	};
}

#endif

