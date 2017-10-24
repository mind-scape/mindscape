/**
 * @file main.cpp
 * @brief Purpose: Contains the main function.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include <iostream>
#include <string>
#include "../engine/include/game.hpp"
#include "../engine/include/level.hpp"
#include "globals.hpp"
#include "level_factory.hpp"

using namespace mindscape;

/**
 * @brief Main function of the game
 *
 * The main is responsible for the start and end of the game.
 *
 * @return Integer with the exit status
 */
int main(int, char **) {
	engine::Game &game = engine::Game::initialize(globals::game_name, globals::window_size);

	LevelFactory *level_factory = new LevelFactory();
	engine::Level *menu = level_factory->fabricate_level("../data/menu.dat");
	game.change_scene(menu);

	game.run();

	return 0;
}
