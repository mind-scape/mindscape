/**
* @file background.cpp
* @brief Purpose: Contains methods that ensure background handling.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#include "background.hpp"
#include "log.hpp"
#include <assert.h>

using namespace mindscape;
/**
* @brief Updates the background on game event.
*
* The game event may change how the background is presented to the player
*
* @param GameEvent containing the game event that may affect the background.
* @return void.
*/
void Background::on_event(GameEvent game_event){
	/* Object verification */
	assert(!game_event.game_event_name.empty());

	/* Variable declaration */
    std::string event_name = game_event.game_event_name;

		if (this->name == "main_background") {
			/* This avoids making parallax event happen in the menu */
			return;
		}

    if (event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level) {
        /* When character is moving left */

        /* Moves background x coordinate to the right */
        set_position_x(get_position_x() + paralax);
    }
    else if (event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level) {
        /* When character is moving right */

        /* Moves background x coordinate to the left */
        set_position_x(get_position_x() - paralax);
    }
    else {
        INFO("Caracter is stopped");
    }
}
/**
* @brief Sets paralax behavior to the background.
*
* Paralax effect is important to the game visual experience
*
* @param int containig the position of the paralax
* @return void.
*/
void Background::set_paralax(int p_paralax) {
	/* Parameter verification */
	assert(p_paralax >= 0);

    if (p_paralax > 10 || p_paralax < 0) {
        /* If paralax is out of valid range */

        paralax = 10; /* Sets paralax to a valid value */
    }
    else {
        paralax = p_paralax; /* Sets paralax to the given parameter */
    }
}

/**
* @brief Gets the backgrounds' paralax value.
*
* If the value of the paralax is needed, there must be a getter for it
*
* @return int containing the paralax value.
*/
int Background::get_paralax() {
    return paralax;
}
