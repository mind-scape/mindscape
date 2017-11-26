/**
* @file action.cpp
* @brief Purpose: contains a method to ensure game executing.
*
* MIT License
* Copyright (c) 2017 MindScape
*
* https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
*/
#include <iostream>
#include <assert.h>
#include "action.hpp"
#include "../engine/include/game.hpp"
#include "log.hpp"
#include "level_factory.hpp"

using namespace mindscape;

/* Function call */

void change_scene(engine::Game *game, std::string param);
void pause_game(engine::Game *game, std::string param);
void play_game(engine::Game *game, std::string param);

/**
* @brief Handles the level execution
*
* The level execution presents more that one state and they must be handled
*
* @param std::string containing the level name
* @return void.
*/
void Action::execute(std::string param) {
	/* Object Declaration */
	engine::Game *game = &(engine::Game::get_instance()); /**< engine::Game. Instance of the game */

	/* Parameters verification */
	assert(game && !param.empty());

	/*
	 * This block of code interacts with the game scene.
	 */
	if (command == Action::CHANGE_SCENE) {
		/* Changes the game scene based on the param to changes level_factory.*/

		change_scene(game, param);
	}
	else if (command == Action::PAUSE_GAME) {
		/* Pause the game based in the game state.*/
		pause_game(game, param);
	}
	else if (command == Action::PLAY_GAME) {
		/* Changes the game state to RUNNING and play the game. */
		play_game(game, param);
	}
	else {
		/* Do nothing */
	}
}

/**
 * @brief Changes game scene.
 *
 * Changes the game scene based on the param to changes level_factory.
 *
 * @param engine::Game *game game instance
 * @param std::string containing the level name
 */
void change_scene(engine::Game *game, std::string param){
	/* Parameters verification */
	assert(game && !param.empty());

	/* Object declaration */
	LevelFactory *level_factory = new LevelFactory(); /**< LevelFactory. Initialize a new LevelFactory */
	engine::Level *level = level_factory->fabricate_level(param); /**< engine::Level. Initialize the right level */

	game->change_scene(level);
	game->set_state(engine::Game::RUNNING);

	INFO("Scene was changed");
}

/**
 * @brief Allows pause the game.
 *
 * Pause the game based in the game state.
 *
 * @param engine::Game *game game instance
 * @param std::string containing the level name
 */
void pause_game(engine::Game *game, std::string param){
	/* Parameters verification */
	assert(game && !param.empty());

	if (game->get_state() != engine::Game::PAUSED) {
		/**<
		 * A GameObject to change background to pause_background.
		 */
		engine::GameObject *pause_background =
		 game->get_actual_scene()->get_object_by_name("pause_background");
		game->get_actual_scene()->deactivate_game_object("pause_background");

		if (pause_background) {
			pause_background->free();
		}
		else {
			/* Do nothing */
		}

		/* Object declaration */
		LevelFactory *level_factory = new LevelFactory();
		level_factory->update_level(
				dynamic_cast<engine::Level *>(game->get_actual_scene()),
				"../data/pause_objects.dat"
		);
	}
	else {
		/* Do nothing */
	}

	game->set_state(engine::Game::PAUSED);

	INFO("Game PAUSED");
}

/**
 * @brief Allows play the game.
 *
 * Changes the game state to RUNNING and play the game.
 *
 * @param engine::Game *game game instance
 * @param std::string containing the level name
 */
void play_game(engine::Game *game, std::string param){
	/* Parameters verification */
	assert(game && !param.empty());

	if (game->get_state() != engine::Game::PAUSED) {
		/**<
		 * A GameObject to change background to pause_background.
		 */
		engine::GameObject *pause_background =
		 game->get_actual_scene()->get_object_by_name("pause_background");
		game->get_actual_scene()->deactivate_game_object("pause_background");

		if (pause_background) {
			pause_background->free();
		}
		else {
			/* Do nothing */
		}
	}
	else {
		/* Do nothing */
	}

	game->set_state(engine::Game::RUNNING);
}
