/**
 * @file platform.cpp
 * @brief Purpose: Contains the methods for Platform class.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "platform.hpp"
#include "../engine/include/game.hpp"
#include <assert.h>
using namespace mindscape;

/**
 * @brief Platform class constructor
 *
 * Initializes everything need for the platform.
 *
 * @param name The object's name.
 * @param position Pair of integers representing the x and y position.
 * @param priority Priority in object's rendering.
 *
 * @return void
 */
Platform::Platform(
		std::string name,
		std::pair<int, int> position,
		int priority)
		: engine::GameObject(name, position, priority,
							 {{engine::KeyboardEvent::LEFT,  "MOVE_LEFT"},
							  {engine::KeyboardEvent::RIGHT, "MOVE_RIGHT"}}
) {};

/**
 * @brief Event processor method
 *
 * Process Game Events received.
 *
 * @param game_event The game event to be received.
 *
 * @return void
 */
void Platform::on_event(GameEvent game_event) {
	/* Functions call */

	/* Movement of platform */
	platform_movement(game_event);

	/*
	 * First Level Limiter.
     * All limiter are in pixels.
	 */
	first_level_clown(game_event);

	/*
	 * Second Level Limiter
	 * All limiters are in pixels
	 */
	second_level_boss(game_event);
}

/**
 * @brief Movements platform.
 *
 * Movements platform based on the girl's movement
 *
 * @param game_event The game event to be received.
 *
 * @return void.
 */
void Platform::platform_movement(GameEvent game_event){
	/* Parameter verification */
	assert(!game_event.game_event_name.empty());

	/* Variables and constants declaration */
	std::string event_name = game_event.game_event_name; /**< string. Name of the game_event */
	const int movement_platform = 10; /**< int. Movement of the platform (value in pixels) */

	if (event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level) {
		/* set the right position of the platform based in the game_event */

		set_position_x(get_position_x() + movement_platform);
	}
	else if (event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level) {
		/* set the left position of the platform based in the game_event */

		set_position_x(get_position_x() - movement_platform);
	}
	else {
		/* Do nothing */
	}
}

/**
 * @brief Level limiter.
 *
 * This method limits the level in right and left position in pixels.
 *
 * @param game_event The game event to be received.
 *
 * @return void.
 */
void Platform::first_level_clown(GameEvent game_event){
	if (name == "clown_tree") {
		/* Constants declaration */
		const int first_level_inicial_limiter = -1300; /**< Int. Left limit in pixel of the girl can walk */
		const int first_level_final_limiter = 13350; /**< Int. Right limit in pixel of the girl can walk */

		if (get_position_x() > first_level_final_limiter) {
			/* Sets the limit of the map in axis x and don't let the girl pass this limit */

			engine::GameObject::on_limit_of_level = true;

			set_position_x(first_level_final_limiter);
		}
		else if (get_position_x() < first_level_inicial_limiter) {
			/* Sets the limit of the map in axis x and don't let the girl pass this limit */

			engine::GameObject::on_limit_of_level = true;

			set_position_x(first_level_inicial_limiter);
		}
		else {
			/* The girl is in between the limits */

			engine::GameObject::on_limit_of_level = false;
		}
	}
	else {
		/* Do nothing */
	}
}

/**
 * @brief Level limiter.
 *
 * This method limits the level in right and left position in pixels.
 *
 * @param game_event The game event to be received.
 *
 * @return void.
 */
void Platform::second_level_boss(GameEvent game_event){
	if (name == "limiter") {
		/* Constants declaration */
		const int second_level_inicial_limiter = 0; /**< Int. Left limit in pixel of the girl can walk */
		const int second_level_final_limiter = 3000; /**< Int. Right limit in pixel of the girl can walk */

		if (get_position_x() > second_level_final_limiter) {
			/* Sets the limit of the map in axis x and don't let the girl pass this limit */

			engine::GameObject::on_limit_of_level = true;

			set_position_x(second_level_final_limiter);
		}
		else if (get_position_x() < second_level_inicial_limiter) {
			/* Sets the limit of the map in axis x and don't let the girl pass this limit */

			engine::GameObject::on_limit_of_level = true;

			set_position_x(second_level_inicial_limiter);
		}
		else {
			/* The girl is in between the limits */

			engine::GameObject::on_limit_of_level = false;
		}
	}
	else {
		/* Do nothing */
	}
}
